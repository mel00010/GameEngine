/******************************************************************************
 * GameCore.tpp
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

#ifndef SRC_GAMECORE_TPP_
#define SRC_GAMECORE_TPP_

#include "Attribute.hpp"
#include "GameCore.hpp"
#include "Shader.hpp"

#include <Log.hpp>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <algorithm>
#include <functional>
#include <numeric>

namespace GameEngine {

template <typename Derived> GameCoreBase<Derived>::GameCoreBase() : ms_per_tick(50) {

}

template <typename Derived> void GameCoreBase<Derived>::runLoop() {
	preSetup();
	derived().setup();
	postSetup();

	loop();
}

template <typename Derived> void GameCoreBase<Derived>::preSetup() {
	registerTimeoutCallback("tick", ms_per_tick, [this]() {
		preTick();
		derived().tick();
		postTick();
	}, true);
	registerTimeoutCallback("render", 0, [this]() {
		preRender();
		derived().render();
		postRender();
	}, true);
	registerQuitEventCallback([](SDL_QuitEvent&) {
		LOG_I("Exiting gracefully");
		SDL_Quit();
		exit(EXIT_SUCCESS);
	});
	registerWindowEventCallback([](SDL_WindowEvent& ev) {
		switch(ev.event) {
			case SDL_WINDOWEVENT_RESIZED:
				glViewport(0, 0, ev.data1, ev.data2);
		}
	});

	derived().registerCallbacks();
	registerDefaultCallbacks();

	initSDL();
	initGL();
}
template <typename Derived> void GameCoreBase<Derived>::registerDefaultCallbacks() {
	registerKeyboardEventCallback(SDL_SCANCODE_Q,   KeyEventType::DOWN, [this](SDL_KeyboardEvent&) { quit(); });
	registerKeyboardEventCallback(SDL_SCANCODE_F,   KeyEventType::DOWN, [this](SDL_KeyboardEvent&) { toggleFPS(); });
	registerKeyboardEventCallback(SDL_SCANCODE_F11, KeyEventType::DOWN, [this](SDL_KeyboardEvent&) { toggleFullscreen(); });
	registerKeyboardEventCallback(SDL_SCANCODE_B,   KeyEventType::DOWN, [this](SDL_KeyboardEvent&) { toggleFPSCap(); });
	registerKeyboardEventCallback(SDL_SCANCODE_V,   KeyEventType::DOWN, [this](SDL_KeyboardEvent&) { toggleVSync(); });
	registerKeyboardEventCallback(SDL_SCANCODE_E,   KeyEventType::DOWN, [this](SDL_KeyboardEvent&) { toggleCursor(); });
}

template <typename Derived> void GameCoreBase<Derived>::postSetup() {

}

template <typename Derived> void GameCoreBase<Derived>::preTick() {

}

template <typename Derived> void GameCoreBase<Derived>::postTick() {
	calculateFPS();
	dispatchCallbacks();
}

template <typename Derived> void GameCoreBase<Derived>::preRender() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	frames_rendered++;
	total_frames_rendered++;
}
template <typename Derived> void GameCoreBase<Derived>::postRender() {
	renderFPS();
	SDL_GL_SwapWindow(window);
}

template <typename Derived> void GameCoreBase<Derived>::loop() {
	for(;;) {
		std::list<std::string> remove_list;
		for (auto& i : timeout_callbacks) {
			size_t curr_time = SDL_GetTicks();
			if(curr_time > i.start_time + i.ms) {
				i.callback();
				if(i.repeat) {
					i.start_time = curr_time;
				} else {
					remove_list.push_back(i.identifier);
				}
			}
		}
		for (auto& i : remove_list) {
			unregisterTimeoutCallback(i);
		}
	}
}

template <typename Derived> void GameCoreBase<Derived>::initSDL() {
	/* SDL-related initialising functions */
	SDL_Init(SDL_INIT_VIDEO);
	int flags = IMG_INIT_JPG | IMG_INIT_PNG;
	if( !( IMG_Init( flags ) & flags ) ) {
		LOG_F( "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() );
		throw EXIT_FAILURE;
	}

	// Request an OpenGL 4.5 context (should be core)
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);

	// Also request a depth buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	window = SDL_CreateWindow("DVD",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		1920, 1080,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	SDL_GL_CreateContext(window);
	enableVSync();
}

template <typename Derived> void GameCoreBase<Derived>::initGL() {
	/* Extension wrangler initialising */
	glewExperimental = GL_TRUE;
	GLenum glew_status = glewInit();
	if (glew_status != GLEW_OK) {
		LOG_F("Error: glewInit: " << glewGetErrorString(glew_status));
		throw EXIT_FAILURE;
	}
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	text.init(window);
}

template <typename Derived> SDL_Window* GameCoreBase<Derived>::getWindow() {
	return window;
}

template <typename Derived> void GameCoreBase<Derived>::setFullscreen(bool enable) {
	int should_be_zero = SDL_GetDesktopDisplayMode(SDL_GetWindowDisplayIndex(window), &native);

	if(should_be_zero != 0) {
		// In case of error...
		LOG_E("Could not get display mode for video display #"<< SDL_GetWindowDisplayIndex(window) <<": " << SDL_GetError());
		throw EXIT_FAILURE;
	} else {
		// On success, print the current display mode.
		LOG_D("Display #" << SDL_GetWindowDisplayIndex(window) <<": native display mode is " << native.w << "x" << native.h << "px @ " << native.refresh_rate << "hz.");
	}
	isScreenFullscreen = enable;
	if(isScreenFullscreen) {
		current = native;
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
		SDL_SetWindowDisplayMode(window, &current);
	} else {
		current = native;
		SDL_SetWindowFullscreen(window, 0);
	}
}

template <typename Derived> bool GameCoreBase<Derived>::isCursorDisabled() {
	return cursor_disabled;
}
template <typename Derived> void GameCoreBase<Derived>::disableCursor(bool disabled) {
	cursor_disabled = disabled;
	if(cursor_disabled) {
		SDL_ShowCursor(SDL_DISABLE);
		SDL_SetRelativeMouseMode(SDL_TRUE);
	} else {
		SDL_ShowCursor(SDL_ENABLE);
		SDL_SetRelativeMouseMode(SDL_FALSE);
	}
}
template <typename Derived> bool GameCoreBase<Derived>::toggleCursor() {
	if(cursor_disabled) {
		cursor_disabled = false;
		SDL_ShowCursor(SDL_ENABLE);
		SDL_SetRelativeMouseMode(SDL_FALSE);
	} else {
		cursor_disabled = true;
		SDL_ShowCursor(SDL_DISABLE);
		SDL_SetRelativeMouseMode(SDL_TRUE);
	}
	return cursor_disabled;
}

template <typename Derived> void GameCoreBase<Derived>::dispatchCallbacks() {
	SDL_Event ev;
	while (SDL_PollEvent(&ev)) {
		switch(ev.type) {
			case SDL_WINDOWEVENT:
				for(auto& i: window_event_callbacks) {
					i(ev.window);
				}
				break;
			case SDL_KEYDOWN:
				if(ev.key.repeat != 0) {
					break;
				}
				key_status[ev.key.keysym.scancode] = true;
				for(auto& i: key_down_callbacks[ev.key.keysym.scancode]) {
					i(ev.key);
				}
				break;
			case SDL_KEYUP:
				key_status[ev.key.keysym.scancode] = false;
				for(auto& i: key_up_callbacks[ev.key.keysym.scancode]) {
					i(ev.key);
				}
				break;
			case SDL_MOUSEMOTION:
				for(auto& i: m_move_callbacks) {
					i(ev.motion, glm::ivec2(ev.motion.x, ev.motion.y), glm::ivec2(ev.motion.xrel, ev.motion.yrel));
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				mouse_buttons_status[ev.button.button] = true;
				for(auto& i: m_button_down_callbacks[ev.button.button]) {
					i(ev.button, glm::ivec2(ev.button.x, ev.button.y));
				}
				break;
			case SDL_MOUSEBUTTONUP:
				mouse_buttons_status[ev.button.button] = false;
				for(auto& i: m_button_up_callbacks[ev.button.button]) {
					i(ev.button, glm::ivec2(ev.button.x, ev.button.y));
				}
				break;
			case SDL_MOUSEWHEEL:
				mouse_wheel_status += glm::ivec2(ev.wheel.x, ev.wheel.y);
				for(auto& i: m_immediate_wheel_callbacks) {
					i(ev.wheel, glm::ivec2(ev.wheel.x, ev.wheel.y));
				}
				break;
		}
		for(auto& callback_pair : event_callbacks) {
			if(callback_pair.first(ev)) {
				callback_pair.second(ev);
			}
		}
	}
	if(mouse_wheel_status != glm::ivec2(0, 0)) {
		for(auto& callback : m_wheel_callbacks) {
			callback(mouse_wheel_status);
		}
		mouse_wheel_status = glm::ivec2(0, 0);
	}

	for(size_t i = 0; i < key_held_callbacks.size(); i++) {
		if(key_status[i]) {
			for(auto& callback : key_held_callbacks[i]) {
				callback();
			}
		}
	}
	for(size_t i = 0; i < m_button_held_callbacks.size(); i++) {
		if(mouse_buttons_status[i]) {
			for(auto& callback : m_button_held_callbacks[i]) {
				callback();
			}
		}
	}
}

template <typename Derived> void GameCoreBase<Derived>::calculateFPS() {
	static size_t tick_counter(0);
	static size_t pos(0);
	static std::array<double, 20> fps_avg_array({0});

	tick_counter++;

	fps = static_cast<double>(frames_rendered) * static_cast<double>(ticks_per_second);
	fps_avg = std::accumulate(fps_avg_array.begin(), fps_avg_array.end(), 0) / 20;

	fps_avg_array[pos] = fps;
	if (pos >= 19) {
		pos = 0;
	} else {
		pos++;
	}
	if(tick_counter > ticks_per_second/10) {
		tick_counter = 0;
		std::stringstream ss;
		ss << std::fixed << std::setprecision(0) << fps_avg;
		fps_to_render = ss.str();
	}

	frames_rendered = 0;
}

template <typename Derived> void GameCoreBase<Derived>::renderFPS() {
	glm::vec3 text_color = glm::vec3(1.0, 1.0, 1.0);

	if(fps_shown) {
		int x;
		int y;
		SDL_GetWindowSize(window, &x, &y);
		text.renderText(fps_to_render, x-80, y-50, 1.0f, text_color);
	}
}

} /* namespace GameEngine */

#endif /* SRC_GAMECORE_TPP_ */

