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

#include <Renderer.hpp>
#include <WindowManager.hpp>

#include <2D/FPSRenderer.hpp>
#include <2D/TextRenderer.hpp>

#include <GL/GLRenderer.hpp>
#include <GL/GLWindowManager.hpp>

#include <Util/Singleton.hpp>

#define SCREEN_CLEAR_COLOR glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)

/**
 * @brief Holds all classes for GameEngine
 */
namespace GameEngine {

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
	typename _Renderer = GL::GLRenderer,
	typename _WindowManager = GL::GLWindowManager
>
class GameCore : public Singleton<Derived>,
				 public _2D::FPSRenderer,
				 public CallbackHandler,
				 public InputHandler {
	public:
		/**
		 * @brief Runs the program.
		 */
		void runLoop() {
			setup();
			loop();
		}
	private:
		/**
		 * @brief A convenience function for CRTP
		 * @return Returns a reference to the derived class
		 */
		Derived& derived() {
			return *static_cast<Derived*>(this);
		}

		/**
		 * @brief Sets up the program
		 */
		void setup() {
			preSetup();
			derived().registerCallbacks();
			derived().setup();
			postSetup();
		}

		/**
		 * @brief Main render function
		 *
		 * Calls preRender, then calls the derived class's render function,
		 * then calls postRender
		 */
		void render() {
			preRender();
			derived().render();
			postRender();
		}
		/**
		 * @brief Main tick function
		 *
		 * Calls preTick, then calls the derived class's tick function,
		 * then calls postTick
		 */
		void tick() {
			preTick();
			derived().tick();
			postTick();
		}

		/**
		 * @brief Run prior to main setup
		 */
		void preSetup() {
			setProgramName(derived().program_name);
			renderer.init(program_name);
			initFPSRenderer(renderer);
			registerDefaultCallbacks();
		}

		/**
		 * @brief Run after main setup
		 */
		void postSetup() {

		}

		/**
		 * @brief Run prior to main tick function
		 */
		void preTick() {

		}

		/**
		 * @brief Run after main tick function
		 */
		void postTick() {
			calculateFPS();
			dispatchCallbacks();
		}

		/**
		 * @brief Run prior to main render function
		 */
		void preRender() {
			renderer.clear(SCREEN_CLEAR_COLOR);
			incrementFrameCount();
			startFrameTimer();
		}
		/**
		 * @brief Run after main render function
		 */
		void postRender() {
			renderFPS(renderer);
			stopFrameTimer();
			calculateFrameTime();
			renderer.swap();
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
		void registerDefaultCallbacks() {
			registerTimeoutCallback("tick", ms_per_tick, [&]() { tick(); } , true);
			registerTimeoutCallback("render", 0, [&]() { render(); }, true);

			registerQuitEventCallback([](SDL_QuitEvent&) {
				LOG_I("Exiting gracefully");
				SDL_Quit();
				exit(EXIT_SUCCESS);
			});
			registerWindowEventCallback([this](SDL_WindowEvent& ev) {
				switch(ev.event) {
					case SDL_WINDOWEVENT_RESIZED:
						renderer.redrawWindowBounds(glm::ivec2(ev.data1, ev.data2));
				}
			});

			registerKeyboardEventCallback(SDL_SCANCODE_Q,   KeyEventType::DOWN, [this](SDL_KeyboardEvent&) { renderer.quit(); });
			registerKeyboardEventCallback(SDL_SCANCODE_F,   KeyEventType::DOWN, [this](SDL_KeyboardEvent&) { toggleFPS(); });
			registerKeyboardEventCallback(SDL_SCANCODE_F11, KeyEventType::DOWN, [this](SDL_KeyboardEvent&) { renderer.toggleFullscreen(); });
			registerKeyboardEventCallback(SDL_SCANCODE_V,   KeyEventType::DOWN, [this](SDL_KeyboardEvent&) { renderer.toggleVSync(); });
			registerKeyboardEventCallback(SDL_SCANCODE_E,   KeyEventType::DOWN, [this](SDL_KeyboardEvent&) { renderer.toggleCursor(); });
		}

		/**
		 * @brief The main loop
		 */
		void loop() {
			for(;;) {
				dispatchTimeoutEvents();
			}
		}

		/**
		 * @brief Sets the program's name
		 * @param name The program's new name
		 */
		void setProgramName(std::string name) {
			program_name = name;
		}

	protected:
		/**
		 * @brief Object responsible for actual rendering
		 */
		_Renderer renderer;

		/**
		 * @brief The program's name
		 */
		std::string program_name;
};


} /* namespace GameEngine */

#include "GameCore.tpp"

#endif /* SRC_GAMECORE_HPP_ */
