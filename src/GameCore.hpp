/******************************************************************************
 * GameCore.hpp
 * Copyright (C) 2019  Mel McCalla <melmccalla@gmail.com>
 *
 * This file is part of GameEngine.
 *
 * GameEngine is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GameEngine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GameEngine.  If not, see <http://www.gnu.org/licenses/>.
 *****************************************************************************/
#ifndef SRC_GAMECORE_HPP_
#define SRC_GAMECORE_HPP_

#include "CallbackHandler.hpp"

#include <string>
#include <string_view>

#include <Renderer.hpp>
#include <WindowManager.hpp>

#include <2D/FpsRenderer.hpp>
#include <2D/TextRenderer.hpp>

#include <GL/GLRenderer.hpp>
#include <GL/GLWindowManager.hpp>

#include <Util/Singleton.hpp>

#include <gflags/gflags.h>
#include <gflags/gflags_completions.h>

#include <Logging/Client.hpp>

/**
 * @brief Holds all classes for GameEngine
 */
namespace game_engine {

constexpr inline glm::vec4 kScreenClearColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

inline logging::Client client;

class GameCoreImpl {
	public:

};

/**
 * @brief The main class of GameEngine
 *
 * Derive from this class to implement your game.
 *
 * The following functions and variables must be defined by your class:
 * | Identifier                     | Purpose                                                                              |
 * |--------------------------------|--------------------------------------------------------------------------------------|
 * | const std::string program_name | The name of your program                                                             |
 * | void setup()                   | Put your game's setup code in this function.  Called once at beginning of execution. |
 * | void tick()                    | Put your game's tick code in this function.  Called once per tick.                   |
 * | void render()                  | Put your game's render code in this function.  Called once per frame.                |
 *
 * @tparam Derived Your game class
 * @tparam _Renderer The actual renderer.  If left unspecified, defaults to GL::GLRenderer
 * @tparam _WindowManager The actual window manager.  If left unspecified, defaults to GL::GLWindowManager
 */
template <
	typename Derived,
	typename _Renderer = gl::GLRenderer,
	typename _WindowManager = gl::GLWindowManager
>
class GameCore : public Singleton<Derived>,
				 public _2D::FpsRenderer,
				 public CallbackHandler,
				 public InputHandler,
				 public Crtp<GameCore, Derived, _Renderer, _WindowManager> {
	public:
		/**
		 * @brief Runs the program and parses command line flags.
		 */
		static void Main(int* argc, char*** argv) {
			using namespace std::literals::string_literals;

			::gflags::SetUsageMessage("Sample usage:\n\t"s
					+ (*argv)[0] + " [flags...]");
			::gflags::SetVersionString("0.0.1");
			::gflags::ParseCommandLineFlags(argc, argv, true);
			::gflags::HandleCommandLineHelpFlags();

			Singleton<Derived>::GetInstance().RunLoop();
		}

		/**
		 * @brief Runs the program.
		 */
		void RunLoop() {
			Setup();
			Loop();
		}

	private:
		/**
		 * @brief Sets up the program
		 */
		void Setup() {
			PreSetup();
			this->Underlying().RegisterCallbacks();
			this->Underlying().Setup();
			PostSetup();
		}

		/**
		 * @brief Main render function
		 *
		 * Calls preRender, then calls the derived class's render function,
		 * then calls postRender
		 */
		void Render() {
			PreRender();
			this->Underlying().Render();
			PostRender();
		}
		/**
		 * @brief Main tick function
		 *
		 * Calls PreTick, then calls the derived class's Tick function,
		 * then calls PostTick
		 */
		void Tick() {
			PreTick();
			this->Underlying().Tick();
			PostTick();
		}

		/**
		 * @brief Run prior to main setup
		 */
		void PreSetup() {
			SetProgramName(this->Underlying().program_name_);
			renderer_.Init(std::string(program_name_));
			InitFpsRenderer(renderer_);
			RegisterDefaultCallbacks();
		}

		/**
		 * @brief Run after main setup
		 */
		void PostSetup() const {

		}

		/**
		 * @brief Run prior to main tick function
		 */
		void PreTick() const {

		}

		/**
		 * @brief Run after main tick function
		 */
		void PostTick() {
			CalculateFps();
			DispatchCallbacks();
		}

		/**
		 * @brief Run prior to main render function
		 */
		void PreRender() {
			renderer_.Clear(kScreenClearColor);
			IncrementFrameCount();
			StartFrameTimer();
		}
		/**
		 * @brief Run after main render function
		 */
		void PostRender() {
			RenderFps(renderer_);
			StopFrameTimer();
			CalculateFrameTime();
			renderer_.Swap();
		}

		/**
		 * @brief Registers default event callbacks
		 *
		 * Set's up all default callbacks in the following table:
		 *  |Event						| Action                                                |
		 *  |---------------------------|-------------------------------------------------------|
		 *  |Timeout callback (Tick)	| Runs the tick function                                |
		 *  |Timeout callback (Render)	| Runs the render function                              |
		 *  |Quit event					| Quits the program                                     |
		 *  |Window resize event		| Prompts the renderer to redraw the window's bounds    |
		 *  |Q key press				| Quits the program                                     |
		 *  |F key press				| Toggles the FPS counter                               |
		 *  |F11 key press				| Toggles fullscreen                                    |
		 *  |V key press				| Toggles VSync                                         |
		 *  |E key press				| Toggles the cursor                                    |
		 */
		void RegisterDefaultCallbacks() {
			RegisterTimeoutCallback("tick", ms_per_tick_, [this]() { Tick(); } , true);
			RegisterTimeoutCallback("render", 0, [this]() { Render(); }, true);

			RegisterQuitEventCallback([](SDL_QuitEvent&) {
				LOG_I("Exiting gracefully");
				SDL_Quit();
				exit(EXIT_SUCCESS);
			});
			RegisterWindowEventCallback([this](SDL_WindowEvent& ev) {
				switch(ev.event) {
					case SDL_WINDOWEVENT_RESIZED:
						renderer_.RedrawWindowBounds(glm::ivec2(ev.data1, ev.data2));
				}
			});

			RegisterKeyboardEventCallback(SDL_SCANCODE_Q,   KeyEventType::DOWN, [this](SDL_KeyboardEvent&) { renderer_.Quit(); });
			RegisterKeyboardEventCallback(SDL_SCANCODE_F,   KeyEventType::DOWN, [this](SDL_KeyboardEvent&) { ToggleFps(); });
			RegisterKeyboardEventCallback(SDL_SCANCODE_F11, KeyEventType::DOWN, [this](SDL_KeyboardEvent&) { renderer_.ToggleFullscreen(); });
			RegisterKeyboardEventCallback(SDL_SCANCODE_V,   KeyEventType::DOWN, [this](SDL_KeyboardEvent&) { renderer_.ToggleVSync(); });
			RegisterKeyboardEventCallback(SDL_SCANCODE_E,   KeyEventType::DOWN, [this](SDL_KeyboardEvent&) { renderer_.ToggleCursor(); });
		}

		/**
		 * @brief The main loop
		 */
		void Loop() {
			for(;;) {
				DispatchTimeoutEvents();
			}
		}

		/**
		 * @brief Sets the program's name
		 * @param name The program's new name
		 */
		void SetProgramName(const std::string_view name) {
			program_name_ = name;
		}

	protected:
		/**
		 * @brief Object responsible for actual rendering
		 */
		_Renderer renderer_;

		/**
		 * @brief The program's name
		 */
		std::string_view program_name_;
};


} /* namespace game_engine */

#include "GameCore.tpp"

#endif /* SRC_GAMECORE_HPP_ */
