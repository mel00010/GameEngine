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

namespace game_engine {

void InputHandler::SetKeyStatus(SDL_Scancode key, bool status) {
  key_status_[key] = status;
}
bool InputHandler::GetKeyStatus(SDL_Scancode key) { return key_status_[key]; }
bool InputHandler::GetKeyStatus(size_t key) { return key_status_[key]; }

void InputHandler::SetMouseButtonStatus(uint8_t button, bool status) {
  mouse_buttons_status_[button] = status;
}
bool InputHandler::GetMouseButtonStatus(uint8_t button) {
  return mouse_buttons_status_[button];
}

void InputHandler::SetControllerButtonStatus(SDL_GameControllerButton button,
                                             bool status) {
  controller_buttons_status_[button] = status;
}
bool InputHandler::GetControllerButtonStatus(SDL_GameControllerButton button) {
  return controller_buttons_status_[button];
}

void InputHandler::SetJoyButtonStatus(uint8_t button, bool status) {
  joystick_buttons_status_[button] = status;
}
bool InputHandler::GetJoyButtonStatus(uint8_t button) {
  return joystick_buttons_status_[button];
}

void InputHandler::SetMouseWheelPos(glm::ivec2 pos) { mouse_wheel_pos_ = pos; }
void InputHandler::AddToMouseWheelPos(glm::ivec2 delta) {
  mouse_wheel_pos_ += delta;
}
glm::ivec2 InputHandler::GetMouseWheelPos() { return mouse_wheel_pos_; }

void InputHandler::SetMousePos(glm::ivec2 pos) { mouse_pos_ = pos; }
void InputHandler::AddToMousePos(glm::ivec2 delta) { mouse_pos_ += delta; }
glm::ivec2 InputHandler::GetMousePos() { return mouse_pos_; }

} /* namespace game_engine */
