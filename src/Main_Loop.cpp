/******************************************************************************
 * Main_Loop.cpp
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

#include "Main_Loop.hpp"

#include "Program.hpp"
#include "Render.hpp"

#include <Log.hpp>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

namespace GameEngine {

void main_loop(SDL_Window* window, ProgramRef program) {
	size_t prev_time = 0;
	size_t curr_time = 0;
	size_t frames_rendered = 0;
	size_t total_frames_rendered = 0;

	bool cursor_disabled = false;

	glm::ivec2 prev_mouse_pos = glm::ivec2(0, 0);
	glm::ivec2 curr_mouse_pos = glm::ivec2(0, 0);

	glm::ivec2 prev_wheel_pos = glm::ivec2(0, 0);
	glm::ivec2 curr_wheel_pos = glm::ivec2(0, 0);

	for(;;) {
		SDL_Event ev;
		while (SDL_PollEvent(&ev)) {
			switch (ev.type) {
				case SDL_QUIT:
					return;
				case SDL_KEYDOWN:
					if(ev.key.repeat != 0) {
						break;
					}
					switch(ev.key.keysym.scancode) {
						case SDL_SCANCODE_0:
						case SDL_SCANCODE_1:
						case SDL_SCANCODE_2:
						case SDL_SCANCODE_3:
						case SDL_SCANCODE_4:
						case SDL_SCANCODE_5:
						case SDL_SCANCODE_6:
						case SDL_SCANCODE_7:
						case SDL_SCANCODE_8:
						case SDL_SCANCODE_9:
							LOG_D("Key down");
							break;
						case SDL_SCANCODE_A:
							LOG_D("A key pressed");
							break;
						case SDL_SCANCODE_B:
						case SDL_SCANCODE_C:
							LOG_D("Key down");
							break;
						case SDL_SCANCODE_D:
							LOG_D("D key pressed");
							break;
						case SDL_SCANCODE_E:
							if(cursor_disabled == true) {
								SDL_ShowCursor(SDL_ENABLE);
								cursor_disabled = false;
							} else {
								SDL_ShowCursor(SDL_DISABLE);
								cursor_disabled = true;
							}
							LOG_D("E key pressed");
							break;
						case SDL_SCANCODE_F:
						case SDL_SCANCODE_G:
						case SDL_SCANCODE_H:
						case SDL_SCANCODE_I:
						case SDL_SCANCODE_J:
						case SDL_SCANCODE_K:
						case SDL_SCANCODE_L:
						case SDL_SCANCODE_M:
						case SDL_SCANCODE_N:
						case SDL_SCANCODE_O:
						case SDL_SCANCODE_P:
						case SDL_SCANCODE_Q:
							LOG_D("Q key pressed");
							break;
						case SDL_SCANCODE_R:
							LOG_D("Key down");
							break;
						case SDL_SCANCODE_S:
							LOG_D("S key pressed");
							break;
						case SDL_SCANCODE_T:
						case SDL_SCANCODE_U:
						case SDL_SCANCODE_V:
							LOG_D("Key down");
							break;
						case SDL_SCANCODE_W:
							LOG_D("W key pressed");
							break;
						case SDL_SCANCODE_X:
						case SDL_SCANCODE_Y:
						case SDL_SCANCODE_Z:
						case SDL_SCANCODE_RETURN:
						case SDL_SCANCODE_ESCAPE:
						case SDL_SCANCODE_BACKSPACE:
						case SDL_SCANCODE_TAB:
						case SDL_SCANCODE_SPACE:
						case SDL_SCANCODE_MINUS:
						case SDL_SCANCODE_EQUALS:
						case SDL_SCANCODE_LEFTBRACKET:
						case SDL_SCANCODE_RIGHTBRACKET:
						case SDL_SCANCODE_BACKSLASH:
						case SDL_SCANCODE_SEMICOLON:
						case SDL_SCANCODE_APOSTROPHE:
						case SDL_SCANCODE_GRAVE:
						case SDL_SCANCODE_COMMA:
						case SDL_SCANCODE_PERIOD:
						case SDL_SCANCODE_SLASH:
						case SDL_SCANCODE_CAPSLOCK:
						case SDL_SCANCODE_F1:
						case SDL_SCANCODE_F2:
						case SDL_SCANCODE_F3:
						case SDL_SCANCODE_F4:
						case SDL_SCANCODE_F5:
						case SDL_SCANCODE_F6:
						case SDL_SCANCODE_F7:
						case SDL_SCANCODE_F8:
						case SDL_SCANCODE_F9:
						case SDL_SCANCODE_F10:
						case SDL_SCANCODE_F11:
						case SDL_SCANCODE_F12:
						case SDL_SCANCODE_F13:
						case SDL_SCANCODE_F14:
						case SDL_SCANCODE_F15:
						case SDL_SCANCODE_F16:
						case SDL_SCANCODE_F17:
						case SDL_SCANCODE_F18:
						case SDL_SCANCODE_F19:
						case SDL_SCANCODE_F20:
						case SDL_SCANCODE_F21:
						case SDL_SCANCODE_F22:
						case SDL_SCANCODE_F23:
						case SDL_SCANCODE_F24:
						case SDL_SCANCODE_PRINTSCREEN:
						case SDL_SCANCODE_SCROLLLOCK:
						case SDL_SCANCODE_PAUSE:
						case SDL_SCANCODE_INSERT:
						case SDL_SCANCODE_HOME:
						case SDL_SCANCODE_PAGEUP:
						case SDL_SCANCODE_DELETE:
						case SDL_SCANCODE_END:
						case SDL_SCANCODE_PAGEDOWN:
						case SDL_SCANCODE_RIGHT:
						case SDL_SCANCODE_LEFT:
						case SDL_SCANCODE_DOWN:
						case SDL_SCANCODE_UP:
						case SDL_SCANCODE_NUMLOCKCLEAR:
						case SDL_SCANCODE_KP_DIVIDE:
						case SDL_SCANCODE_KP_MULTIPLY:
						case SDL_SCANCODE_KP_MINUS:
						case SDL_SCANCODE_KP_PLUS:
						case SDL_SCANCODE_KP_ENTER:
						case SDL_SCANCODE_KP_1:
						case SDL_SCANCODE_KP_2:
						case SDL_SCANCODE_KP_3:
						case SDL_SCANCODE_KP_4:
						case SDL_SCANCODE_KP_5:
						case SDL_SCANCODE_KP_6:
						case SDL_SCANCODE_KP_7:
						case SDL_SCANCODE_KP_8:
						case SDL_SCANCODE_KP_9:
						case SDL_SCANCODE_KP_0:
						case SDL_SCANCODE_KP_PERIOD:
						case SDL_SCANCODE_APPLICATION:
						case SDL_SCANCODE_KP_EQUALS:
						case SDL_SCANCODE_LCTRL:
						case SDL_SCANCODE_LSHIFT:
						case SDL_SCANCODE_LALT:
						case SDL_SCANCODE_LGUI:
						case SDL_SCANCODE_RCTRL:
						case SDL_SCANCODE_RSHIFT:
						case SDL_SCANCODE_RALT:
						case SDL_SCANCODE_RGUI:
							LOG_D("Key down");
							break;
						default:
							LOG_D("Unknown key pressed");

					}
					break;
				case SDL_KEYUP:
					switch(ev.key.keysym.scancode) {
						case SDL_SCANCODE_0:
						case SDL_SCANCODE_1:
						case SDL_SCANCODE_2:
						case SDL_SCANCODE_3:
						case SDL_SCANCODE_4:
						case SDL_SCANCODE_5:
						case SDL_SCANCODE_6:
						case SDL_SCANCODE_7:
						case SDL_SCANCODE_8:
						case SDL_SCANCODE_9:
							LOG_D("Key up");
							break;
						case SDL_SCANCODE_A:
							LOG_D("A key released");
							break;
						case SDL_SCANCODE_B:
						case SDL_SCANCODE_C:
							LOG_D("Key up");
							break;
						case SDL_SCANCODE_D:
							LOG_D("D key released");
							break;
						case SDL_SCANCODE_E:
							LOG_D("E key released");
							break;
						case SDL_SCANCODE_F:
						case SDL_SCANCODE_G:
						case SDL_SCANCODE_H:
						case SDL_SCANCODE_I:
						case SDL_SCANCODE_J:
						case SDL_SCANCODE_K:
						case SDL_SCANCODE_L:
						case SDL_SCANCODE_M:
						case SDL_SCANCODE_N:
						case SDL_SCANCODE_O:
						case SDL_SCANCODE_P:
						case SDL_SCANCODE_Q:
							LOG_D("Q key released");
							break;
						case SDL_SCANCODE_R:
							LOG_D("Key up");
							break;
						case SDL_SCANCODE_S:
							LOG_D("S key released");
							break;
						case SDL_SCANCODE_T:
						case SDL_SCANCODE_U:
						case SDL_SCANCODE_V:
							LOG_D("Key up");
							break;
						case SDL_SCANCODE_W:
							LOG_D("W key released");
							break;
						case SDL_SCANCODE_X:
						case SDL_SCANCODE_Y:
						case SDL_SCANCODE_Z:
						case SDL_SCANCODE_RETURN:
						case SDL_SCANCODE_ESCAPE:
						case SDL_SCANCODE_BACKSPACE:
						case SDL_SCANCODE_TAB:
						case SDL_SCANCODE_SPACE:
						case SDL_SCANCODE_MINUS:
						case SDL_SCANCODE_EQUALS:
						case SDL_SCANCODE_LEFTBRACKET:
						case SDL_SCANCODE_RIGHTBRACKET:
						case SDL_SCANCODE_BACKSLASH:
						case SDL_SCANCODE_SEMICOLON:
						case SDL_SCANCODE_APOSTROPHE:
						case SDL_SCANCODE_GRAVE:
						case SDL_SCANCODE_COMMA:
						case SDL_SCANCODE_PERIOD:
						case SDL_SCANCODE_SLASH:
						case SDL_SCANCODE_CAPSLOCK:
						case SDL_SCANCODE_F1:
						case SDL_SCANCODE_F2:
						case SDL_SCANCODE_F3:
						case SDL_SCANCODE_F4:
						case SDL_SCANCODE_F5:
						case SDL_SCANCODE_F6:
						case SDL_SCANCODE_F7:
						case SDL_SCANCODE_F8:
						case SDL_SCANCODE_F9:
						case SDL_SCANCODE_F10:
						case SDL_SCANCODE_F11:
						case SDL_SCANCODE_F12:
						case SDL_SCANCODE_F13:
						case SDL_SCANCODE_F14:
						case SDL_SCANCODE_F15:
						case SDL_SCANCODE_F16:
						case SDL_SCANCODE_F17:
						case SDL_SCANCODE_F18:
						case SDL_SCANCODE_F19:
						case SDL_SCANCODE_F20:
						case SDL_SCANCODE_F21:
						case SDL_SCANCODE_F22:
						case SDL_SCANCODE_F23:
						case SDL_SCANCODE_F24:
						case SDL_SCANCODE_PRINTSCREEN:
						case SDL_SCANCODE_SCROLLLOCK:
						case SDL_SCANCODE_PAUSE:
						case SDL_SCANCODE_INSERT:
						case SDL_SCANCODE_HOME:
						case SDL_SCANCODE_PAGEUP:
						case SDL_SCANCODE_DELETE:
						case SDL_SCANCODE_END:
						case SDL_SCANCODE_PAGEDOWN:
						case SDL_SCANCODE_RIGHT:
						case SDL_SCANCODE_LEFT:
						case SDL_SCANCODE_DOWN:
						case SDL_SCANCODE_UP:
						case SDL_SCANCODE_NUMLOCKCLEAR:
						case SDL_SCANCODE_KP_DIVIDE:
						case SDL_SCANCODE_KP_MULTIPLY:
						case SDL_SCANCODE_KP_MINUS:
						case SDL_SCANCODE_KP_PLUS:
						case SDL_SCANCODE_KP_ENTER:
						case SDL_SCANCODE_KP_1:
						case SDL_SCANCODE_KP_2:
						case SDL_SCANCODE_KP_3:
						case SDL_SCANCODE_KP_4:
						case SDL_SCANCODE_KP_5:
						case SDL_SCANCODE_KP_6:
						case SDL_SCANCODE_KP_7:
						case SDL_SCANCODE_KP_8:
						case SDL_SCANCODE_KP_9:
						case SDL_SCANCODE_KP_0:
						case SDL_SCANCODE_KP_PERIOD:
						case SDL_SCANCODE_APPLICATION:
						case SDL_SCANCODE_KP_EQUALS:
						case SDL_SCANCODE_LCTRL:
						case SDL_SCANCODE_LSHIFT:
						case SDL_SCANCODE_LALT:
						case SDL_SCANCODE_LGUI:
						case SDL_SCANCODE_RCTRL:
						case SDL_SCANCODE_RSHIFT:
						case SDL_SCANCODE_RALT:
						case SDL_SCANCODE_RGUI:
							LOG_D("Key up");
							break;
						default:
							LOG_D("Unknown key released");

					}
					break;
				case SDL_MOUSEMOTION:
//					LOG_D("Mouse moved to x=" << ev.motion.x << " and y=" << ev.motion.y
//							<< " with dx=" << ev.motion.xrel << " and dy=" << ev.motion.yrel);
					curr_mouse_pos = glm::ivec2(ev.motion.x, ev.motion.y);
					break;
				case SDL_MOUSEBUTTONDOWN:
					switch(ev.button.button) {
						case SDL_BUTTON_LEFT:
							LOG_D("Left mouse button pressed");
							break;
						case SDL_BUTTON_MIDDLE:
							LOG_D("Middle mouse button pressed");
							break;
						case SDL_BUTTON_RIGHT:
							LOG_D("Right mouse button pressed");
							break;
						case SDL_BUTTON_X1:
							LOG_D("X1 mouse button pressed");
							break;
						case SDL_BUTTON_X2:
							LOG_D("X2 mouse button pressed");
							break;
					}
					break;
				case SDL_MOUSEBUTTONUP:
					switch(ev.button.button) {
						case SDL_BUTTON_LEFT:
							LOG_D("Left mouse button released");
							break;
						case SDL_BUTTON_MIDDLE:
							LOG_D("Middle mouse button released");
							break;
						case SDL_BUTTON_RIGHT:
							LOG_D("Right mouse button released");
							break;
						case SDL_BUTTON_X1:
							LOG_D("X1 mouse button released");
							break;
						case SDL_BUTTON_X2:
							LOG_D("X2 mouse button released");
							break;
					}
					break;
				case SDL_MOUSEWHEEL:
					curr_wheel_pos += glm::ivec2(ev.wheel.x, ev.wheel.y);
					break;
				default:
					break;
			}
		}
		if(cursor_disabled) {
			int x;
			int y;
			SDL_GetWindowSize(window, &x, &y);

			SDL_WarpMouseInWindow(window, x/2, y/2);
		}
		render(window, program);

		curr_time = SDL_GetTicks();
		frames_rendered++;
		total_frames_rendered++;
		if (curr_time > prev_time + 1000) { // If last prinf() was more than 1 sec ago
			LOG_I("ms/frame = " << 1000.0/double(frames_rendered) << "\tFPS = " << double(frames_rendered)/1.0);
			frames_rendered = 0;
			prev_time = curr_time;
		}
		if (((curr_time - prev_time) % 100) == 0) {
			if(prev_mouse_pos != curr_mouse_pos) {
				LOG_D("Mouse moved " << (curr_mouse_pos - prev_mouse_pos) << " units to " << curr_mouse_pos);
			}
			prev_mouse_pos = curr_mouse_pos;

			glm::ivec2 delta = curr_wheel_pos - prev_wheel_pos;
			if(delta.y > 0) { 			// scroll up
				LOG_D("Mouse wheel scrolled up "    << delta.y
						<< " units to position " << curr_wheel_pos.y);
			} else if(delta.y < 0) {	// scroll down
				LOG_D("Mouse wheel scrolled down " << -delta.y
						<< " units to position " << curr_wheel_pos.y);
			}
			if(delta.x > 0) {			// scroll right
				LOG_D("Mouse wheel scrolled right " << delta.x
						<< " units to position " << curr_wheel_pos.x);
			} else if(delta.x < 0) {	// scroll left
				LOG_D("Mouse wheel scrolled left " << -delta.x
						<< " units to position " << curr_wheel_pos.x);
			}
			prev_wheel_pos = curr_wheel_pos;
		}
	}
}

} /* namespace GameEngine */

