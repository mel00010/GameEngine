/******************************************************************************
 * main.cpp
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

#include "Triangle.hpp"

#include "Attribute.hpp"
#include "GameCore.hpp"
#include "Program.hpp"
#include "Shader.hpp"
#include "Window.hpp"

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <ft2build.h>
#include FT_FREETYPE_H

#include <Log.hpp>

using namespace GameEngine;

int main(void) {
	LOG_D("Initializing...");
	GameCore& core = GameCore::getInstance();
	core.registerQuitEventCallback([](SDL_QuitEvent&) {
		LOG_I("Exiting gracefully");
		exit(EXIT_SUCCESS);
	});
	core.registerKeyboardEventCallback(SDL_SCANCODE_W, KeyEventType::DOWN, [](SDL_KeyboardEvent&) {
		LOG_D("W key pressed");
	});
	core.registerKeyboardEventCallback(SDL_SCANCODE_A, KeyEventType::DOWN, [](SDL_KeyboardEvent&) {
		LOG_D("A key pressed");
	});
	core.registerKeyboardEventCallback(SDL_SCANCODE_S, KeyEventType::DOWN, [](SDL_KeyboardEvent&) {
		LOG_D("S key pressed");
	});
	core.registerKeyboardEventCallback(SDL_SCANCODE_D, KeyEventType::DOWN, [](SDL_KeyboardEvent&) {
		LOG_D("D key pressed");
	});
	core.registerKeyboardEventCallback(SDL_SCANCODE_E, KeyEventType::DOWN, [](SDL_KeyboardEvent&) {
		LOG_D("E key pressed");
	});
	core.registerKeyboardEventCallback(SDL_SCANCODE_E, KeyEventType::DOWN, [&core](SDL_KeyboardEvent&) {
		core.toggleCursor();
	});

	core.registerKeyboardEventCallback(SDL_SCANCODE_W, KeyEventType::UP, [](SDL_KeyboardEvent&) {
		LOG_D("W key released");
	});
	core.registerKeyboardEventCallback(SDL_SCANCODE_A, KeyEventType::UP, [](SDL_KeyboardEvent&) {
		LOG_D("A key released");
	});
	core.registerKeyboardEventCallback(SDL_SCANCODE_S, KeyEventType::UP, [](SDL_KeyboardEvent&) {
		LOG_D("S key released");
	});
	core.registerKeyboardEventCallback(SDL_SCANCODE_D, KeyEventType::UP, [](SDL_KeyboardEvent&) {
		LOG_D("D key released");
	});
	core.registerKeyboardEventCallback(SDL_SCANCODE_E, KeyEventType::UP, [](SDL_KeyboardEvent&) {
		LOG_D("E key released");
	});

	core.registerKeyboardEventCallback(SDL_SCANCODE_W, KeyEventType::HELD, []() {
		LOG_D("W key being held");
	});
	core.registerKeyboardEventCallback(SDL_SCANCODE_A, KeyEventType::HELD, []() {
		LOG_D("A key being held");
	});
	core.registerKeyboardEventCallback(SDL_SCANCODE_S, KeyEventType::HELD, []() {
		LOG_D("S key being held");
	});
	core.registerKeyboardEventCallback(SDL_SCANCODE_D, KeyEventType::HELD, []() {
		LOG_D("D key being held");
	});
	core.registerKeyboardEventCallback(SDL_SCANCODE_E, KeyEventType::HELD, []() {
		LOG_D("E key being held");
	});

	core.registerMouseButtonEventCallback(SDL_BUTTON_LEFT, ButtonEventType::DOWN, [](SDL_MouseButtonEvent&, ivec2 pos) {
		LOG_D("Left mouse button clicked at " << pos);
	});
	core.registerMouseButtonEventCallback(SDL_BUTTON_RIGHT, ButtonEventType::DOWN, [](SDL_MouseButtonEvent&, ivec2 pos) {
		LOG_D("Right mouse button clicked at " << pos);
	});
	core.registerMouseButtonEventCallback(SDL_BUTTON_MIDDLE, ButtonEventType::DOWN, [](SDL_MouseButtonEvent&, ivec2 pos) {
		LOG_D("Middle mouse button clicked at " << pos);
	});
	core.registerMouseButtonEventCallback(SDL_BUTTON_X1, ButtonEventType::DOWN, [](SDL_MouseButtonEvent&, ivec2 pos) {
		LOG_D("Back mouse button clicked at " << pos);
	});
	core.registerMouseButtonEventCallback(SDL_BUTTON_X2, ButtonEventType::DOWN, [](SDL_MouseButtonEvent&, ivec2 pos) {
		LOG_D("Forward mouse button clicked at " << pos);
	});

	core.registerMouseMotionEventCallback([](SDL_MouseMotionEvent&, ivec2 pos, ivec2 delta) {
//		LOG_D("Mouse moved " << delta << " units to position " << pos);
	});

	core.registerWindowEventCallback([](SDL_WindowEvent& ev) {
		switch(ev.event) {
			case SDL_WINDOWEVENT_SHOWN:
				LOG_D("Window has been shown");
				break;
			case SDL_WINDOWEVENT_HIDDEN:
				LOG_D("Window has been hidden");
				break;
			case SDL_WINDOWEVENT_EXPOSED:
				LOG_D("Window has been exposed and should be redrawn");
				break;
			case SDL_WINDOWEVENT_MOVED:
				LOG_D("Window has been moved to " << ivec2(ev.data1, ev.data2));
				break;
			case SDL_WINDOWEVENT_RESIZED:
				LOG_D("Window has been resized to " << ev.data1 << " by " << ev.data2 << " pixels");
				glViewport(0, 0, ev.data1, ev.data2);
				DVDCore::getInstance().setScale(((ev.data1/1920.0)/2) + ((ev.data2/1080.0)/2));
				break;
			case SDL_WINDOWEVENT_SIZE_CHANGED:
				LOG_D("Window size has been changed");
				break;
			case SDL_WINDOWEVENT_MINIMIZED:
				LOG_D("Window has been minimized");
				break;
			case SDL_WINDOWEVENT_MAXIMIZED:
				LOG_D("Window has been maximized");
				break;
			case SDL_WINDOWEVENT_RESTORED:
				LOG_D("Window has been restored to it's original size and shape");
				break;
			case SDL_WINDOWEVENT_ENTER:
				LOG_D("Window has gained mouse focus");
				break;
			case SDL_WINDOWEVENT_LEAVE:
				LOG_D("Window has lost mouse focus");
				break;
			case SDL_WINDOWEVENT_FOCUS_GAINED:
				LOG_D("Window has gained keyboard focus");
				break;
			case SDL_WINDOWEVENT_FOCUS_LOST:
				LOG_D("Window has lost keyboard focus");
				break;
			case SDL_WINDOWEVENT_CLOSE:
				LOG_D("Window manager is requesting that the window be closed");
				break;
			case SDL_WINDOWEVENT_TAKE_FOCUS:
				LOG_D("Window is being offered focus");
				break;
			case SDL_WINDOWEVENT_HIT_TEST:
				LOG_D("Window had a hit test that wasn't SDL_HITTEST_NORMAL");
				break;
		}
	});

	LOG_D("Initialized, running loop");
	core.runLoop();

	return EXIT_SUCCESS;
}
