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

#include <limits>
#include <string>
#include <string_view>

#include "LoggerV2/Client.hpp"
#include "LoggerV2/Log.hpp"
#include "LoggerV2/Telemetry.hpp"
#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/flags/usage.h"
#include "absl/strings/str_cat.h"

#include "2D/FpsRenderer.hpp"
#include "2D/TextRenderer.hpp"
#include "CallbackHandler.hpp"
#include "GL/GLRenderer.hpp"
#include "GL/GLWindowManager.hpp"
#include "Renderer.hpp"
#include "Util/Singleton.hpp"
#include "WindowManager.hpp"

/**
 * @brief Holds all classes for GameEngine
 */
namespace game_engine {

constexpr inline glm::vec4 kScreenClearColor =
    glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
inline constexpr double kFrameTimeMinVal = 0.0;
inline constexpr double kFrameTimeAlarmMinVal = 0.0;
inline constexpr double kFrameTimeMaxVal = 1000.0;
inline constexpr double kFrameTimeAlarmMaxVal = 16666.0;
inline constexpr bool kFrameTimeEnable = true;

inline constexpr double kFpsMinVal = 0.0;
inline constexpr double kFpsAlarmMinVal = 60.0;
inline constexpr double kFpsMaxVal = 80.00;
inline constexpr double kFpsAlarmMaxVal = std::numeric_limits<double>::max();
inline constexpr bool kFpsRawEnable = true;
inline constexpr bool kFpsRollAvgEnable = true;

/**
 * @brief The main class of GameEngine
 *
 * Derive from this class to implement your game.
 *
 * The following functions and variables must be defined by your class:
 * | Identifier                     | Purpose                                  |
 * |--------------------------------|------------------------------------------|
 * | const std::string program_name | The name of your program                 |
 * | void setup()                   | Put your game's setup code in this
 *                                    function.  Called once at beginning of
 *                                    execution.                               |
 * | void tick()                    | Put your game's tick code in this
 *                                    function.  Called once per tick.         |
 * | void render()                  | Put your game's render code in this
 *                                    function.  Called once per frame.        |
 *
 * @tparam Derived Your game class
 * @tparam _Renderer The actual renderer.  If left unspecified, defaults to
 *                   GL::GLRenderer
 * @tparam _WindowManager The actual window manager.  If left unspecified,
 *                        defaults to GL::GLWindowManager
 */
template <typename Derived, typename _Renderer = gl::GLRenderer,
          typename _WindowManager = gl::GLWindowManager>
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
    ::absl::SetProgramUsageMessage(
        absl::StrCat("Sample usage:\n\t", (*argv)[0], " [flags...]"));
    //    absl::SetProgramVersionMessage("0.0.1");
    ::absl::ParseCommandLine(*argc, *argv);

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
    log_trace_.RegisterThread("Main");
    log_game_engine_module_ = log_trace_.RegisterModule("Game Engine").value();
    frame_time_telem_ = log_telem_
                            .Create("Performance/Frame time", kFrameTimeMinVal,
                                    kFrameTimeAlarmMinVal, kFrameTimeMaxVal,
                                    kFrameTimeAlarmMaxVal, kFrameTimeEnable)
                            .value();
    fps_raw_telem_ =
        log_telem_
            .Create("Performance/FPS Raw", kFpsMinVal, kFpsAlarmMinVal,
                    kFpsMaxVal, kFpsAlarmMaxVal, kFpsRawEnable)
            .value();
    fps_roll_avg_telem_ =
        log_telem_
            .Create("Performance/FPS", kFpsMinVal, kFpsAlarmMinVal, kFpsMaxVal,
                    kFpsAlarmMaxVal, kFpsRawEnable)
            .value();
    renderer_.Init(std::string(program_name_));
    InitFpsRenderer(renderer_);
    RegisterDefaultCallbacks();
  }

  /**
   * @brief Run after main setup
   */
  void PostSetup() const {}

  /**
   * @brief Run prior to main tick function
   */
  void PreTick() const {}

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
    frame_time_telem_.Add(frame_time_us_);
    fps_raw_telem_.Add(fps_);
    fps_roll_avg_telem_.Add(fps_avg_);
  }

  /**
   * @brief Registers default event callbacks
   *
   * Set's up all default callbacks in the following table:
   *  |Event						| Action |
   *  |---------------------------|-------------------------------------------------------|
   *  |Timeout callback (Tick)	| Runs the tick function | |Timeout callback
   * (Render)	| Runs the render function                              | |Quit
   * event					| Quits the program | |Window
   * resize event		| Prompts the renderer to redraw the window's
   * bounds | |Q key press				| Quits the program | |F
   * key press				| Toggles the FPS counter | |F11 key
   * press				| Toggles fullscreen |
   *  |V key press				| Toggles VSync | |E key press
   * | Toggles the cursor                                    |
   */
  void RegisterDefaultCallbacks() {
    RegisterTimeoutCallback(
        "tick", ms_per_tick_, [this]() { Tick(); }, true);
    RegisterTimeoutCallback(
        "render", 0, [this]() { Render(); }, true);

    RegisterQuitEventCallback([this](SDL_QuitEvent&) {
      log_trace_.Info(log_game_engine_module_, "Exiting gracefully");
      SDL_Quit();
      exit(EXIT_SUCCESS);
    });
    RegisterWindowEventCallback([this](SDL_WindowEvent& ev) {
      switch (ev.event) {
        case SDL_WINDOWEVENT_RESIZED:
          renderer_.RedrawWindowBounds(glm::ivec2(ev.data1, ev.data2));
      }
    });

    RegisterKeyboardEventCallback(
        SDL_SCANCODE_Q, KeyEventType::DOWN,
        [this](SDL_KeyboardEvent&) { renderer_.Quit(); });
    RegisterKeyboardEventCallback(SDL_SCANCODE_F, KeyEventType::DOWN,
                                  [this](SDL_KeyboardEvent&) { ToggleFps(); });
    RegisterKeyboardEventCallback(
        SDL_SCANCODE_F11, KeyEventType::DOWN,
        [this](SDL_KeyboardEvent&) { renderer_.ToggleFullscreen(); });
    RegisterKeyboardEventCallback(
        SDL_SCANCODE_V, KeyEventType::DOWN,
        [this](SDL_KeyboardEvent&) { renderer_.ToggleVSync(); });
    RegisterKeyboardEventCallback(
        SDL_SCANCODE_E, KeyEventType::DOWN,
        [this](SDL_KeyboardEvent&) { renderer_.ToggleCursor(); });
  }

  /**
   * @brief The main loop
   */
  void Loop() {
    for (;;) {
      DispatchTimeoutEvents();
    }
  }

  /**
   * @brief Sets the program's name
   * @param name The program's new name
   */
  void SetProgramName(const std::string_view name) { program_name_ = name; }

 protected:
  /**
   * @brief Object responsible for actual rendering
   */
  _Renderer renderer_;

  /**
   * @brief The program's name
   */
  std::string_view program_name_;
  logging::Client log_client_ = logging::Client("main");
  logging::Log log_trace_ = logging::Log("main");
  logging::ModuleHandle log_game_engine_module_{};
  logging::Telemetry log_telem_ = logging::Telemetry("telemetry");
  logging::TelemetryChannelHandle frame_time_telem_{};
  logging::TelemetryChannelHandle fps_roll_avg_telem_{};
  logging::TelemetryChannelHandle fps_raw_telem_{};
};

} /* namespace game_engine */

#include "GameCore.tpp"

#endif /* SRC_GAMECORE_HPP_ */
