/******************************************************************************
 * CubeTest.cpp
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

#include "CubeTestCore.hpp"

#include <cmrc/cmrc.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>

#include "3D/Cube.hpp"
#include "GL/Shader.hpp"
#include "GL/ShaderProgram.hpp"
#include "LoggerV2/Log.hpp"

using namespace game_engine;

namespace cube_test {

void CubeTestCore::RegisterCallbacks() {
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

void CubeTestCore::Setup() {
  cube_ = _3D::Cube(renderer_, fs_, "cube");
  cube_.Move(glm::vec3(0.0, 0.5, 0.0));
  cube_.Scale(0.25);

  camera_.Init(renderer_.GetWindowSize());
}

void CubeTestCore::Render() {
  cube_.Rotate(
      glm::vec3(glm::radians(0.1f), glm::radians(0.2f), glm::radians(-0.3f)));
  renderer_.SetColor(ShaderPrograms::DEFAULT, glm::vec4(cube_color_, 1.0f));
  camera_.DrawModel(renderer_, cube_);
}

void CubeTestCore::Tick() {}

} /* namespace cube_test */
