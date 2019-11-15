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

namespace GameEngine {
namespace _2D {

using Clock = std::chrono::high_resolution_clock;

class FPSRenderer {
	public:
		template<typename Renderer> void initFPSRenderer(Renderer& renderer) {
			text.init(renderer);
		}
		template<typename Renderer> void renderFPS(Renderer& renderer) {
			glm::vec3 text_color(1.0, 1.0, 1.0);

			if(isFPSShown()) {
				text.renderTextRelativeToTopRight(renderer, fps_str, 80, 50, 1.0f, text_color);
			}
		}
		void calculateFPS();
		void calculateFrameTime();

		void setShowFPS(bool enable = false);
		bool isFPSShown();
		void showFPS();
		void hideFPS();
		void toggleFPS();

		void incrementFrameCount();
		void startFrameTimer();
		void stopFrameTimer();
	protected:
		TextRenderer text;
		bool fps_shown = true;

		size_t frames_rendered = 0;
		size_t total_frames_rendered = 0;

		size_t ms_per_tick = 50;
		double ticks_per_second = 1000/ms_per_tick;

		double fps = 100;
		double frame_time_ns = 0;
		double frame_time_us = 0;
		double frame_time_ms = 0;
		double frame_time_s = 0;

		double fps_avg = 100;
		std::string fps_str = "100";

		size_t prev_frame_time = 0;
		size_t curr_frame_time = 0;
		std::chrono::time_point<Clock> frame_start_time;
		std::chrono::time_point<Clock> frame_stop_time;
};

} /* namespace _2D */
} /* namespace GameEngine */



#endif /* SRC_2D_FPSRENDERER_HPP_ */
