/******************************************************************************
 * GLWindowManager.cpp
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

#include "GLWindowManager.hpp"

#include <GL/glew.h>
#include <Log.hpp>
#include <SDL2/SDL.h>


namespace GameEngine {
namespace GL {

SDL_Window* GLWindowManager::window = nullptr;

void GLWindowManager::init(std::string program_name) {
//	setWindow(SDL_CreateWindow(program_name.c_str(),
//		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
//		1920, 1080,
//		SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL));
//	SDL_GL_CreateContext(getWindow());
//	enableVSync();
}

SDL_Window* GLWindowManager::getWindow() {
	return window;
}
void GLWindowManager::setWindow(SDL_Window* p) {
	window = p;
}

glm::ivec2 GLWindowManager::getWindowSize() {
	glm::ivec2 v(0, 0);
	SDL_GetWindowSize(window, &v.x, &v.y);
	return v;
}

void GLWindowManager::setFullscreen(bool enable) {
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
bool GLWindowManager::isFullscreen() {
	return isScreenFullscreen;
}
void GLWindowManager::toggleFullscreen() {
	setFullscreen(!isScreenFullscreen);
}

void GLWindowManager::setVSyncEnabled(bool enable) {
	vsync_enabled = enable;
	SDL_GL_SetSwapInterval(vsync_enabled);
}
bool GLWindowManager::isVSyncEnabled() {
	return vsync_enabled;
}
void GLWindowManager::enableVSync() {
	setVSyncEnabled(true);
}
void GLWindowManager::disableVSync() {
	setVSyncEnabled(false);
}
void GLWindowManager::toggleVSync() {
	setVSyncEnabled(!vsync_enabled);
}

void GLWindowManager::quit() {
	SDL_Event sdlevent;
	sdlevent.type = SDL_QUIT;
	SDL_PushEvent(&sdlevent);
}

bool GLWindowManager::isCursorDisabled() {
	return cursor_disabled;
}
void GLWindowManager::disableCursor(bool disabled) {
	cursor_disabled = disabled;
	if (cursor_disabled) {
		SDL_ShowCursor(SDL_DISABLE);
		SDL_SetRelativeMouseMode(SDL_TRUE);
	} else {
		SDL_ShowCursor(SDL_ENABLE);
		SDL_SetRelativeMouseMode(SDL_FALSE);
	}
}
bool GLWindowManager::toggleCursor() {
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

void GLWindowManager::redrawWindowBounds(glm::ivec2 size) {
	glViewport(0, 0, size.x, size.y);
}

} /* namespace GL */
} /* namespace GameEngine */
