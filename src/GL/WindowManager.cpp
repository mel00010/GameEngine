/******************************************************************************
 * WindowManager.cpp
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

#include "WindowManager.hpp"

#include <Log.hpp>

namespace GameEngine {
namespace GL {

SDL_Window* WindowManager::getWindow() {
	return window;
}
void WindowManager::setWindow(SDL_Window* p) {
	window = p;
}

glm::ivec2 WindowManager::getWindowSize() {
	glm::ivec2 v(0, 0);
	SDL_GetWindowSize(window, &v.x, &v.y);
	return v;
}

glm::ivec2 WindowManager::getWindowSize(SDL_Window* p) {
	glm::ivec2 v(0, 0);
	SDL_GetWindowSize(p, &v.x, &v.y);
	return v;
}

void WindowManager::setFullscreen(bool enable) {
	if (SDL_GetDesktopDisplayMode(SDL_GetWindowDisplayIndex(window), &native) != 0) {
		// In case of error...
		LOG_E("Could not get display mode for video display #"<< SDL_GetWindowDisplayIndex(window) <<": " << SDL_GetError());
		throw EXIT_FAILURE;
	} else {
		// On success, print the current display mode.
		LOG_D("Display #" << SDL_GetWindowDisplayIndex(window) <<": native display mode is " << native.w << "x" << native.h << "px @ " << native.refresh_rate << "hz.");
	}
	isScreenFullscreen = enable;
	if (isScreenFullscreen) {
		current = native;
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
		SDL_SetWindowDisplayMode(window, &current);
	} else {
		current = native;
		SDL_SetWindowFullscreen(window, 0);
	}
}
bool WindowManager::isFullscreen() {
	return isScreenFullscreen;
}
void WindowManager::toggleFullscreen() {
	setFullscreen(!isScreenFullscreen);
}

void WindowManager::setVSyncEnabled(bool enable) {
	vsync_enabled = enable;
	SDL_GL_SetSwapInterval(vsync_enabled);
}
bool WindowManager::isVSyncEnabled() {
	return vsync_enabled;
}
void WindowManager::enableVSync() {
	setVSyncEnabled(true);
}
void WindowManager::disableVSync() {
	setVSyncEnabled(false);
}
void WindowManager::toggleVSync() {
	setVSyncEnabled(!vsync_enabled);
}

void WindowManager::quit() {
	SDL_Event sdlevent;
	sdlevent.type = SDL_QUIT;
	SDL_PushEvent(&sdlevent);
}

bool WindowManager::isCursorDisabled() {
	return cursor_disabled;
}
void WindowManager::disableCursor(bool disabled) {
	cursor_disabled = disabled;
	if (cursor_disabled) {
		SDL_ShowCursor(SDL_DISABLE);
		SDL_SetRelativeMouseMode(SDL_TRUE);
	} else {
		SDL_ShowCursor(SDL_ENABLE);
		SDL_SetRelativeMouseMode(SDL_FALSE);
	}
}
bool WindowManager::toggleCursor() {
	if (cursor_disabled) {
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

} /* namespace GL */
} /* namespace GameEngine */
