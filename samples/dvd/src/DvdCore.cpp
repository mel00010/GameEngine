/******************************************************************************
 * DVDcppLog
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

#include "DvdCore.hpp"

#include <algorithm>
#include <functional>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/color_space.hpp>

#include "GL/Shader.hpp"
#include "GameCore.hpp"
#include "LoggerV2/Log.hpp"

// clang-format off
#include <ft2build.h>
#include FT_FREETYPE_H
// clang-format on

using namespace game_engine;

namespace dvd {

void DvdCore::RegisterCallbacks() {
  RegisterKeyboardEventCallback(SDL_SCANCODE_R, KeyEventType::DOWN,
                                [this](SDL_KeyboardEvent&) { this->Reset(); });
  RegisterKeyboardEventCallback(SDL_SCANCODE_A, KeyEventType::DOWN,
                                [this](SDL_KeyboardEvent&) { AddDvd(); });
  RegisterKeyboardEventCallback(SDL_SCANCODE_D, KeyEventType::DOWN,
                                [this](SDL_KeyboardEvent&) { RemoveDvd(); });
  RegisterKeyboardEventCallback(
      SDL_SCANCODE_PAGEUP, KeyEventType::HELD,
      [this]() { scroll_factor_ *= 1.0 + (0.0525 / scroll_factor_); });
  RegisterKeyboardEventCallback(
      SDL_SCANCODE_PAGEDOWN, KeyEventType::HELD,
      [this]() { scroll_factor_ *= 1.0 - (scroll_factor_ / 18.095); });

  RegisterMouseWheelEventCallback([this](glm::ivec2 delta) {
    size_t curr_time = SDL_GetTicks();
    ModifySpeed(static_cast<double>(delta.y) * scroll_factor_ * 0.1);
    if ((curr_time > prev_time_ + 10) || counter_ == 10) {
      prev_time_ = curr_time;
      counter_ = 0;
    }
    counter_++;
  });

  RegisterWindowEventCallback([this](SDL_WindowEvent& ev) {
    switch (ev.event) {
      case SDL_WINDOWEVENT_RESIZED:
        SetScale(glm::dvec2(ev.data1, ev.data2) / glm::dvec2(1920, 1080));
    }
  });
  RegisterTimeoutCallback(
      "ms_per_frame", 1000,
      [this]() {
        log_.Debug("ms/frame = {} | fps = {}", frame_time_ms_, fps_avg_);
      },
      true);
}

void DvdCore::Setup() {
  SetSpeed(2.0f);
  AddDvd();
}

void DvdCore::Render() {
  for (auto& i : dvds_) {
    i.Draw(renderer_, fps_);
  }
}

void DvdCore::Tick() {}

}  // namespace dvd
