/******************************************************************************
 * FPSRenderer.cpp
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

#include "2D/FpsRenderer.hpp"

#include <chrono>
#include <iomanip>
#include <numeric>

namespace game_engine::_2D {

void FpsRenderer::CalculateFps() {
  static size_t tick_counter(0);
  static size_t pos(0);
  static std::array<double, 20> fps_avg_array({0});

  tick_counter++;

  fps_ = static_cast<double>(frames_rendered_) *
         static_cast<double>(ticks_per_second_);
  fps_avg_ =
      std::accumulate(fps_avg_array.begin(), fps_avg_array.end(), 0) / 20.0;

  fps_avg_array[pos] = fps_;
  if (pos >= 19) {
    pos = 0;
  } else {
    pos++;
  }

  if (tick_counter > ticks_per_second_ / 10) {
    tick_counter = 0;
    std::stringstream ss;
    ss << std::fixed << std::setprecision(0) << fps_avg_;
    fps_str_ = ss.str();
  }
  frames_rendered_ = 0;
}
void FpsRenderer::CalculateFrameTime() {
  static size_t pos(0);
  static std::array<double, 20> time_avg_array({0});
  time_avg_array[pos] = std::chrono::duration_cast<std::chrono::nanoseconds>(
                            frame_stop_time_ - frame_start_time_)
                            .count();
  if (pos >= 19) {
    pos = 0;
  } else {
    pos++;
  }
  frame_time_ns_ =
      std::accumulate(time_avg_array.begin(), time_avg_array.end(), 0) / 20.0;
  frame_time_us_ = frame_time_ns_ / 1000.0;
  frame_time_ms_ = frame_time_ns_ / 1000000.0;
  frame_time_s_ = frame_time_ns_ / 1000000000.0;
}

void FpsRenderer::SetShowFps(const bool enable) { fps_shown_ = enable; }
bool FpsRenderer::IsFpsShown() { return fps_shown_; }
void FpsRenderer::ShowFps() { SetShowFps(true); }
void FpsRenderer::HideFps() { SetShowFps(false); }
void FpsRenderer::ToggleFps() { fps_shown_ = !fps_shown_; }

void FpsRenderer::IncrementFrameCount() {
  frames_rendered_++;
  total_frames_rendered_++;
}

void FpsRenderer::StartFrameTimer() { frame_start_time_ = Clock::now(); }
void FpsRenderer::StopFrameTimer() { frame_stop_time_ = Clock::now(); }

} /* namespace game_engine::_2D */
