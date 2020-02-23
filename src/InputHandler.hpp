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

namespace game_engine {
/**
 * @brief Helper class handling HID input
 */
class InputHandler {
	public:
		/**
		 * @brief Set a key's status
		 * @param key Key to set status of
		 * @param status Boolean representing the key's status according to this table:
		 * 		  | State | Key status  |
		 * 		  |-------|-------------|
		 * 		  | True  | Pressed     |
		 * 		  | False | Not pressed |
		 */
		void SetKeyStatus(SDL_Scancode key, bool status);
		/**
		 * @brief Get the status of a key
		 * @param key Key to get status of
		 * @return Returns a boolean according to the following table:
		 * 		   | State | Key status  |
		 * 		   |-------|-------------|
		 * 		   | True  | Pressed     |
		 * 		   | False | Not pressed |
		 */
		bool GetKeyStatus(SDL_Scancode key);
		/**
		 * @brief Get the status of a key by array index
		 * @param key Key to get status of
		 * @return Returns a boolean according to the following table:
		 * 		   | State | Key status  |
		 * 		   |-------|-------------|
		 * 		   | True  | Pressed     |
		 * 		   | False | Not pressed |
		 */
		bool GetKeyStatus(size_t key);

		/**
		 * @brief Set the status of a mouse button
		 * @param button Mouse button to set status of
		 * @param status Boolean representing the button's status according to this table:
		 * 		   | State | Button status  |
		 * 		   |-------|----------------|
		 * 		   | True  | Pressed        |
		 * 		   | False | Not pressed    |
		 */
		void SetMouseButtonStatus(uint8_t button, bool status);
		/**
		 * @brief Get the status of a mouse button
		 * @param button Mouse button to get status of
		 * @return Returns a boolean according to the following table:
		 * 		   | State | Button status  |
		 * 		   |-------|----------------|
		 * 		   | True  | Pressed        |
		 * 		   | False | Not pressed    |
		 */
		bool GetMouseButtonStatus(uint8_t button);

		/**
		 * @brief Set the status of a controller button
		 * @param button Controller button to set status of
		 * @param status Boolean representing the button's status according to this table:
		 * 		   | State | Button status  |
		 * 		   |-------|----------------|
		 * 		   | True  | Pressed        |
		 * 		   | False | Not pressed    |
		 */
		void SetControllerButtonStatus(SDL_GameControllerButton button, bool status);
		/**
		 * @brief Get the status of a controller button
		 * @param button Controller button to get status of
		 * @return Returns a boolean according to the following table:
		 * 		   | State | Button status  |
		 * 		   |-------|----------------|
		 * 		   | True  | Pressed        |
		 * 		   | False | Not pressed    |
		 */
		bool GetControllerButtonStatus(SDL_GameControllerButton button);

		/**
		 * @brief Set the status of a joystick button
		 * @param button Joystick button to set status of
		 * @param status Boolean representing the button's status according to this table:
		 * 		   | State | Button status  |
		 * 		   |-------|----------------|
		 * 		   | True  | Pressed        |
		 * 		   | False | Not pressed    |
		 */
		void SetJoyButtonStatus(uint8_t button, bool status);
		/**
		 * @brief Get the status of a joystick button
		 * @param button Joystick button to get status of
		 * @return Returns a boolean according to the following table:
		 * 		   | State | Button status  |
		 * 		   |-------|----------------|
		 * 		   | True  | Pressed        |
		 * 		   | False | Not pressed    |
		 */
		bool GetJoyButtonStatus(uint8_t button);

		/**
		 * @brief Set the position of the mouse wheel
		 * @param pos A glm::ivec2 containing new position of the mouse wheel
		 */
		void SetMouseWheelPos(glm::ivec2 pos);
		/**
		 * @brief Add to the position of the mouse wheel
		 * @param delta A glm::ivec2 to be added to the mouse wheel's position
		 */
		void AddToMouseWheelPos(glm::ivec2 delta);
		/**
		 * @brief Get the position of the mouse wheel
		 * @return Returns an glm::ivec2 containing the mouse wheel's position
		 */
		glm::ivec2 GetMouseWheelPos();

		/**
		 * @brief Set the position of the mouse
		 * @param pos A glm::ivec2 containing new position of the mouse
		 */
		void SetMousePos(glm::ivec2 pos);
		/**
		 * @brief Add to the position of the mouse
		 * @param delta A glm::ivec2 to be added to the mouse's position
		 */
		void AddToMousePos(glm::ivec2 delta);
		/**
		 * @brief Get the position of the mouse
		 * @return Returns an glm::ivec2 containing the mouse's position
		 */
		glm::ivec2 GetMousePos();

	private:
		/**
		 * @brief An array containing the status of the keyboard's keys
		 */
		std::array<bool, SDL_NUM_SCANCODES> key_status_ = {false};
		/**
		 * @brief An array containing the status of the mouse buttons
		 */
		std::array<bool, SDL_BUTTON_X2 + 1> mouse_buttons_status_ = {false};
		/**
		 * @brief An array containing the status of the controller buttons
		 */
		std::array<bool, SDL_CONTROLLER_BUTTON_MAX> controller_buttons_status_ = {false};
		/**
		 * @brief An array containing the status of the joystick buttons
		 */
		std::array<bool, std::numeric_limits<uint8_t>::max()> joystick_buttons_status_ = {false};
		/**
		 * @brief The position of the mouse wheel
		 */
		glm::ivec2 mouse_wheel_pos_ = glm::ivec2(0, 0);
		/**
		 * @brief The position of the mouse
		 */
		glm::ivec2 mouse_pos_ = glm::ivec2(0, 0);
};

} /* namespace game_engine */




#endif /* SRC_INPUTHANDLER_HPP_ */
