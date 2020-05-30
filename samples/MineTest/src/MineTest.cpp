/******************************************************************************
 * MineTest.cpp
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

#include "MineTest.hpp"

#include <thread>

#include <cmrc/cmrc.hpp>
#include <glm/glm.hpp>

#include "3D/Model.hpp"
#include "GL/Shader.hpp"
#include "GL/ShaderProgram.hpp"
#include "LoggerV2/Log.hpp"

using namespace game_engine;

namespace mine_test {

void MineTest::RegisterCallbacks() {
  RegisterKeyboardEventCallback(SDL_SCANCODE_W, KeyEventType::HELD, [this]() {
    glm::vec3 dir = camera_.camera_front_;
    dir.y = 0.0f;
    dir *= 0.125;
    camera_.MoveCamera(dir);
  });
  RegisterKeyboardEventCallback(SDL_SCANCODE_A, KeyEventType::HELD, [this]() {
    glm::vec3 dir =
        -glm::normalize(glm::cross(camera_.camera_front_, camera_.camera_up_));
    dir.y = 0.0f;
    dir *= 0.125;
    camera_.MoveCamera(dir);
  });
  RegisterKeyboardEventCallback(SDL_SCANCODE_S, KeyEventType::HELD, [this]() {
    glm::vec3 dir = -camera_.camera_front_;
    dir.y = 0.0f;
    dir *= 0.125;
    camera_.MoveCamera(dir);
  });
  RegisterKeyboardEventCallback(SDL_SCANCODE_D, KeyEventType::HELD, [this]() {
    glm::vec3 dir =
        glm::normalize(glm::cross(camera_.camera_front_, camera_.camera_up_));
    dir.y = 0.0f;
    dir *= 0.125;
    camera_.MoveCamera(dir);
  });
  RegisterKeyboardEventCallback(SDL_SCANCODE_SPACE, KeyEventType::HELD,
                                [this]() {
                                  glm::vec3 dir = camera_.camera_up_;
                                  dir *= 0.025;
                                  camera_.MoveCamera(dir);
                                });
  RegisterKeyboardEventCallback(SDL_SCANCODE_LSHIFT, KeyEventType::HELD,
                                [this]() {
                                  glm::vec3 dir = -camera_.camera_up_;
                                  dir *= 0.025;
                                  camera_.MoveCamera(dir);
                                });
  RegisterKeyboardEventCallback(SDL_SCANCODE_RSHIFT, KeyEventType::HELD,
                                [this]() {
                                  glm::vec3 dir = -camera_.camera_up_;
                                  dir *= 0.025;
                                  camera_.MoveCamera(dir);
                                });
  RegisterKeyboardEventCallback(SDL_SCANCODE_O, KeyEventType::DOWN,
                                [this](SDL_KeyboardEvent&) { oof_.Play(); });
  RegisterKeyboardEventCallback(SDL_SCANCODE_P, KeyEventType::DOWN,
                                [this](SDL_KeyboardEvent&) { ouch_.Play(); });
  RegisterKeyboardEventCallback(
      SDL_SCANCODE_R, KeyEventType::DOWN,
      [this](SDL_KeyboardEvent&) { rickroll_.Play(); });
  RegisterKeyboardEventCallback(
      SDL_SCANCODE_T, KeyEventType::DOWN,
      [this](SDL_KeyboardEvent&) { rickroll_.Pause(); });
  RegisterKeyboardEventCallback(
      SDL_SCANCODE_Y, KeyEventType::DOWN,
      [this](SDL_KeyboardEvent&) { rickroll_.Resume(); });

  RegisterMouseMotionEventCallback(
      [this](SDL_MouseMotionEvent&, glm::ivec2 /* pos */, glm::ivec2 delta) {
        if (renderer_.IsCursorDisabled()) {
          camera_.RotateCamera(static_cast<double>(delta.x) / 10,
                               -static_cast<double>(delta.y) / 10);
        }
      });
  RegisterWindowEventCallback([this](SDL_WindowEvent& ev) {
    switch (ev.event) {
      case SDL_WINDOWEVENT_RESIZED:
        camera_.UpdateProjection(glm::ivec2(ev.data1, ev.data2));
    }
  });
  RegisterTimeoutCallback(
      "ms_per_frame", 1000,
      [this]() {
        log_.Debug("ms/frame = {} | fps = {}", frame_time_ms_, fps_avg_);
      },
      true);
}

void MineTest::Setup() {
  grid_ = _3D::Model(renderer_, fs_, "grid");
  grid_.Rotate(
      glm::vec3(glm::radians(91.0f), glm::radians(90.0f), glm::radians(0.0f)));

  //	cobble_block.

  camera_.Init(renderer_.GetWindowSize());

  oof_ = sound::Sound(fs_.open("oof.ogg"));
  ouch_ = sound::Sound(fs_.open("ouch.ogg"));
  rickroll_ = sound::Music(fs_.open("rickroll.ogg"));
}

void MineTest::Render() {
  renderer_.SetColor(ShaderPrograms::DEFAULT, glm::vec4(kLineColor, 1.0f));
  camera_.DrawModel(renderer_, grid_);
}

void MineTest::Tick() {}

}  // namespace mine_test
