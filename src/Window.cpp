/******************************************************************************
 * Window.cpp
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

#include "Window.hpp"

#include <Log.hpp>

#include <GL/glew.h>

namespace GameEngine {

Window::Window(std::string _title, int width, int height,
		int x_pos, int y_pos, uint32_t _flags) :
	title(_title), size(width, height), pos(x_pos, y_pos),
	flags(_flags | SDL_WINDOW_OPENGL),
	window_ref(nullptr), valid(false) {
}
Window::Window(std::string _title, ivec2 _size, ivec2 _pos, uint32_t _flags) :
	title(_title), size(_size), pos(_pos),
	flags(_flags | SDL_WINDOW_OPENGL),
	window_ref(nullptr), valid(false) {
}

Window::Window() :
		title(""), size(0, 0), pos(0, 0),
		flags(0),
		window_ref(nullptr), valid(false) {

}

Window::~Window() {
	if(isValid()) {
		SDL_DestroyWindow(window_ref);
	}
	valid = false;
}

bool Window::create() {
	if(isValid()) {
		return isValid();
	}

	SDL_Window* window_ref = SDL_CreateWindow(title.c_str(), pos.x, pos.y, size.x, size.y, flags);
	SDL_GL_CreateContext(window_ref);
	SDL_GL_SetSwapInterval(0);

	valid = true;
	return isValid();
}


std::string Window::getTitle() {
	title = SDL_GetWindowTitle(window_ref);
	return title;
}

void Window::setTitle(std::string _title) {
	SDL_SetWindowTitle(window_ref, _title.c_str());
	title = _title;
}

ivec2 Window::getSize() {
	SDL_GetWindowSize(window_ref, &size.x, &size.y);
	return size;
}

void Window::setSize(ivec2 _size) {
	size = _size;
	SDL_SetWindowSize(window_ref, size.x, size.y);
}

void Window::setSize(int width, int height) {
	size = ivec2(width, height);
	SDL_SetWindowSize(window_ref, size.x, size.y);
}

ivec2 Window::getPos() {
	SDL_GetWindowPosition(window_ref, &pos.x, &pos.y);
	return pos;
}

void Window::setPos(ivec2 _pos) {
	pos = _pos;
	SDL_SetWindowPosition(window_ref, pos.x, pos.y);
}

void Window::setPos(int x, int y) {
	pos = ivec2(x, y);
	SDL_SetWindowPosition(window_ref, pos.x, pos.y);
}

uint32_t Window::getFlags() {
	return flags;
}

SDL_Window* Window::getWindowRef() {
	return window_ref;
}

bool Window::isValid() {
	return valid;
}

} /* namespace GameEngine */
