/******************************************************************************
 * FPSRenderer.hpp
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
#ifndef SRC_2D_FPSRENDERER_HPP_
#define SRC_2D_FPSRENDERER_HPP_

#include "TextRenderer.hpp"

#include <chrono>
#include <utility>

namespace game_engine {
namespace _2D {

using Clock = std::chrono::high_resolution_clock;

class FpsRenderer {
	public:
		template<typename Renderer> void InitFpsRenderer(Renderer& renderer) {
			text_.Init(renderer);
		}
		template<typename Renderer> void RenderFps(const Renderer& renderer) {
			glm::vec3 text_color(1.0, 1.0, 1.0);

			if(IsFpsShown()) {
				text_.RenderTextRelativeToTopRight(renderer, fps_str_, 80, 50, 1.0f, text_color);
			}
		}
		void CalculateFps();
		void CalculateFrameTime();

		void SetShowFps(const bool enable = false);
		bool IsFpsShown();
		void ShowFps();
		void HideFps();
		void ToggleFps();

		void IncrementFrameCount();
		void StartFrameTimer();
		void StopFrameTimer();

		void swap(FpsRenderer& other) noexcept {
			using std::swap;
			swap(other.text_, text_);
			swap(other.fps_shown_, fps_shown_);
			swap(other.frames_rendered_, frames_rendered_);
			swap(other.total_frames_rendered_, total_frames_rendered_);
			swap(other.ms_per_tick_, ms_per_tick_);
			swap(other.ticks_per_second_, ticks_per_second_);
			swap(other.fps_, fps_);
			swap(other.frame_time_ns_, frame_time_ns_);
			swap(other.frame_time_us_, frame_time_us_);
			swap(other.frame_time_ms_, frame_time_ms_);
			swap(other.frame_time_s_, frame_time_s_);
			swap(other.fps_avg_, fps_avg_);
			swap(other.fps_str_, fps_str_);
			swap(other.prev_frame_time_, prev_frame_time_);
			swap(other.curr_frame_time_, curr_frame_time_);
			swap(other.frame_start_time_, frame_start_time_);
			swap(other.frame_stop_time_, frame_stop_time_);
		}
	protected:
		TextRenderer text_;
		bool fps_shown_ = true;

		size_t frames_rendered_ = 0;
		size_t total_frames_rendered_ = 0;

		size_t ms_per_tick_ = 50;
		double ticks_per_second_ = 1000/ms_per_tick_;

		double fps_ = 100;
		double frame_time_ns_ = 0;
		double frame_time_us_ = 0;
		double frame_time_ms_ = 0;
		double frame_time_s_ = 0;

		double fps_avg_ = 100;
		std::string fps_str_ = "100";

		size_t prev_frame_time_ = 0;
		size_t curr_frame_time_ = 0;
		std::chrono::time_point<Clock> frame_start_time_;
		std::chrono::time_point<Clock> frame_stop_time_;
};

inline void swap(FpsRenderer& a, FpsRenderer& b) noexcept {
	a.swap(b);
}

} /* namespace _2D */
} /* namespace game_engine */



#endif /* SRC_2D_FPSRENDERER_HPP_ */
