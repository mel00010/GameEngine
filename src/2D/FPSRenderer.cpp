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

#include "FPSRenderer.hpp"

#include <GL/WindowManager.hpp>

#include <chrono>
#include <iomanip>
#include <numeric>


namespace GameEngine {
namespace _2D {

void FPSRenderer::calculateFPS() {
	static size_t tick_counter(0);
	static size_t pos(0);
	static std::array<double, 20> fps_avg_array({0});

	tick_counter++;

	fps = static_cast<double>(frames_rendered) * static_cast<double>(ticks_per_second);
	fps_avg = std::accumulate(fps_avg_array.begin(), fps_avg_array.end(), 0) / 20;

	fps_avg_array[pos] = fps;
	if( pos >= 19) {
		pos = 0;
	} else {
		pos++;
	}

	if(tick_counter > ticks_per_second/10) {
		tick_counter = 0;
		std::stringstream ss;
		ss << std::fixed << std::setprecision(0) << fps_avg;
		fps_str = ss.str();
	}
	frames_rendered = 0;
}
void FPSRenderer::calculateFrameTime() {
	static size_t pos(0);
	static std::array<double, 20> time_avg_array({0});
	time_avg_array[pos] = std::chrono::duration_cast<std::chrono::nanoseconds>(frame_stop_time - frame_start_time).count();
	if( pos >= 19) {
		pos = 0;
	} else {
		pos++;
	}
	frame_time_ns = std::accumulate(time_avg_array.begin(), time_avg_array.end(), 0) / 20.0;
	frame_time_us = frame_time_ns/1000.0;
	frame_time_ms = frame_time_ns/1000000.0;
	frame_time_s =  frame_time_ns/1000000000.0;
}

void FPSRenderer::renderFPS() {
	glm::vec3 text_color(1.0, 1.0, 1.0);

	if(isFPSShown()) {
		text.renderTextRelativeToTopRight(fps_str, 80, 50, 1.0f, text_color);
	}
}

void FPSRenderer::setShowFPS(bool enable) {
	fps_shown = enable;
}
bool FPSRenderer::isFPSShown() {
	return fps_shown;
}
void FPSRenderer::showFPS() {
	setShowFPS(true);
}
void FPSRenderer::hideFPS() {
	setShowFPS(false);
}
void FPSRenderer::toggleFPS() {
	fps_shown = !fps_shown;
}

void FPSRenderer::incrementFrameCount() {
	frames_rendered++;
	total_frames_rendered++;
}

void FPSRenderer::startFrameTimer() {
	frame_start_time = Clock::now();
}
void FPSRenderer::stopFrameTimer() {
	frame_stop_time = Clock::now();
}

} /* namespace _2D */
} /* namespace GameEngine */

