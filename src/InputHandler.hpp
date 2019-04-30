/******************************************************************************
 * InputHandler.hpp
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
#ifndef SRC_INPUTHANDLER_HPP_
#define SRC_INPUTHANDLER_HPP_

#include <array>

#include <glm/glm.hpp>
#include <SDL2/SDL.h>

namespace GameEngine {

class InputHandler {
	public:
		void setKeyStatus(SDL_Scancode key, bool status);
		bool getKeyStatus(SDL_Scancode key);
		bool getKeyStatus(size_t key);

		void setMouseButtonStatus(uint8_t button, bool status);
		bool getMouseButtonStatus(uint8_t button);

		void setControllerButtonStatus(SDL_GameControllerButton button, bool status);
		bool getControllerButtonStatus(SDL_GameControllerButton button);

		void setJoyButtonStatus(uint8_t button, bool status);
		bool getJoyButtonStatus(uint8_t button);

		void setMouseWheelPos(glm::ivec2 pos);
		void addToMouseWheelPos(glm::ivec2 delta);
		glm::ivec2 getMouseWheelPos();

		void setMousePos(glm::ivec2 pos);
		void addToMousePos(glm::ivec2 delta);
		glm::ivec2 getMousePos();

	private:
		std::array<bool, SDL_NUM_SCANCODES> key_status = {false};
		std::array<bool, SDL_BUTTON_X2 + 1> mouse_buttons_status = {false};
		std::array<bool, SDL_CONTROLLER_BUTTON_MAX> controller_buttons_status = {false};
		std::array<bool, std::numeric_limits<uint8_t>::max()> joystick_buttons_status = {false};
		glm::ivec2 mouse_wheel_pos = glm::ivec2(0, 0);
		glm::ivec2 mouse_pos = glm::ivec2(0, 0);

//		glm::ivec2 prev_mouse_pos = glm::ivec2(0, 0);
//		glm::ivec2 curr_mouse_pos = glm::ivec2(0, 0);
//
//		glm::ivec2 prev_wheel_pos = glm::ivec2(0, 0);
//		glm::ivec2 curr_wheel_pos = glm::ivec2(0, 0);
};

} /* namespace GameEngine */




#endif /* SRC_INPUTHANDLER_HPP_ */
