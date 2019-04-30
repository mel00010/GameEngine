/******************************************************************************
 * InputHandler.cpp
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

#include "InputHandler.hpp"

namespace GameEngine {

void InputHandler::setKeyStatus(SDL_Scancode key, bool status) {
	key_status[key] = status;
}
bool InputHandler::getKeyStatus(SDL_Scancode key) {
	return key_status[key];
}
bool InputHandler::getKeyStatus(size_t key) {
	return key_status[key];
}

void InputHandler::setMouseButtonStatus(uint8_t button, bool status) {
	mouse_buttons_status[button] = status;
}
bool InputHandler::getMouseButtonStatus(uint8_t button) {
	return mouse_buttons_status[button];
}

void InputHandler::setControllerButtonStatus(SDL_GameControllerButton button, bool status) {
	controller_buttons_status[button] = status;
}
bool InputHandler::getControllerButtonStatus(SDL_GameControllerButton button) {
	return controller_buttons_status[button];
}

void InputHandler::setJoyButtonStatus(uint8_t button, bool status) {
	joystick_buttons_status[button] = status;
}
bool InputHandler::getJoyButtonStatus(uint8_t button) {
	return joystick_buttons_status[button];
}

void InputHandler::setMouseWheelPos(glm::ivec2 pos) {
	mouse_wheel_pos = pos;
}
void InputHandler::addToMouseWheelPos(glm::ivec2 delta) {
	mouse_wheel_pos += delta;
}
glm::ivec2 InputHandler::getMouseWheelPos() {
	return mouse_wheel_pos;
}

void InputHandler::setMousePos(glm::ivec2 pos) {
	mouse_pos = pos;
}
void InputHandler::addToMousePos(glm::ivec2 delta) {
	mouse_pos += delta;
}
glm::ivec2 InputHandler::getMousePos() {
	return mouse_pos;
}

} /* namespace GameEngine */


