/******************************************************************************
 * CallbackRegistration.cpp
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

#include "GameCore.hpp"

namespace GameEngine {

bool GameCore::registerQuitEventCallback(std::function<void(SDL_QuitEvent&)> callback) {
	auto matcher = [](SDL_Event& ev) -> bool {
		if(ev.type == SDL_QUIT) {
			return true;
		}
		return false;
	};
	auto caller = [callback](SDL_Event& ev) -> void {
		callback(ev.quit);
	};
	registerGenericEventCallback(matcher, caller);
	return true;
}

bool GameCore::registerWindowEventCallback(std::function<void(SDL_WindowEvent&)> callback) {
	window_event_callbacks.push_back(callback);
	return true;
}

bool GameCore::registerKeyboardEventCallback(SDL_Scancode key,
				KeyEventType type,
				std::function<void(SDL_KeyboardEvent&)> callback) {
	if(type == KeyEventType::DOWN) {
		key_up_callbacks[key].push_back(callback);
	}
	if(type == KeyEventType::UP) {
		key_down_callbacks[key].push_back(callback);
	}
	return true;
}
bool GameCore::registerKeyboardEventCallback(SDL_Scancode key,
				KeyEventType type,
				std::function<void(void)> callback) {
	if(type == KeyEventType::HELD) {
		key_held_callbacks[key].push_back(callback);
	}
	return true;
}
bool GameCore::registerTextEditingEventCallback(std::function<void(SDL_TextEditingEvent&)> callback) {
	auto matcher = [](SDL_Event& ev) -> bool {
		if(ev.type == SDL_TEXTEDITING) {
			return true;
		}
		return false;
	};
	auto caller = [callback](SDL_Event& ev) -> void {
		callback(ev.edit);
	};
	registerGenericEventCallback(matcher, caller);
	return true;
}
bool GameCore::registerTextInputEventCallback(std::function<void(SDL_TextInputEvent&)> callback) {
	auto matcher = [](SDL_Event& ev) -> bool {
		if(ev.type == SDL_TEXTINPUT) {
			return true;
		}
		return false;
	};
	auto caller = [callback](SDL_Event& ev) -> void {
		callback(ev.text);
	};
	registerGenericEventCallback(matcher, caller);
	return true;
}

bool GameCore::registerMouseMotionEventCallback(
		std::function<void(SDL_MouseMotionEvent&, ivec2 /* pos */, ivec2 /* delta */)> callback) {
	m_move_callbacks.push_back(callback);
	return true;
}
bool GameCore::registerMouseButtonEventCallback(uint8_t button,
		ButtonEventType type,
		std::function<void(SDL_MouseButtonEvent&, ivec2 /* pos */)> callback) {
	if(type == ButtonEventType::DOWN) {
		m_button_down_callbacks[button].push_back(callback);
	}
	if(type == ButtonEventType::UP) {
		m_button_up_callbacks[button].push_back(callback);
	}
	return true;
}
bool GameCore::registerMouseButtonEventCallback(uint8_t button,
		ButtonEventType type,
		std::function<void(void)> callback) {
	if(type == ButtonEventType::HELD) {
		m_button_held_callbacks[button].push_back(callback);
	}
	return true;
}
bool GameCore::registerMouseWheelEventCallback(std::function<void(SDL_MouseWheelEvent&, ivec2 /* delta */)> callback) {
	m_wheel_callbacks.push_back(callback);
	return true;
}

bool GameCore::registerJoyAxisEventCallback(std::function<void(SDL_JoyAxisEvent&)> callback) {
	auto matcher = [](SDL_Event& ev) -> bool {
		if(ev.type == SDL_JOYAXISMOTION) {
			return true;
		}
		return false;
	};
	auto caller = [callback](SDL_Event& ev) -> void {
		callback(ev.jaxis);
	};
	registerGenericEventCallback(matcher, caller);
	return true;
}
bool GameCore::registerJoyBallEventCallback(	std::function<void(SDL_JoyBallEvent&)> callback) {
	auto matcher = [](SDL_Event& ev) -> bool {
		if(ev.type == SDL_JOYBALLMOTION) {
			return true;
		}
		return false;
	};
	auto caller = [callback](SDL_Event& ev) -> void {
		callback(ev.jball);
	};
	registerGenericEventCallback(matcher, caller);
	return true;
}
bool GameCore::registerJoyHatEventCallback(std::function<void(SDL_JoyHatEvent&)> callback) {
	auto matcher = [](SDL_Event& ev) -> bool {
		if(ev.type == SDL_JOYHATMOTION) {
			return true;
		}
		return false;
	};
	auto caller = [callback](SDL_Event& ev) -> void {
		callback(ev.jhat);
	};
	registerGenericEventCallback(matcher, caller);
	return true;
}
bool GameCore::registerJoyButtonEventCallback(
		uint8_t button,
		ButtonEventType type,
		std::function<void(SDL_JoyButtonEvent&)> callback) {
	auto matcher = [button, type, this](SDL_Event& ev) -> bool {
		if(type == ButtonEventType::DOWN) {
			if(ev.type == SDL_JOYBUTTONDOWN) {
				if(ev.jbutton.button == button) {
					return true;
				}
			}
		}
		if(type == ButtonEventType::UP) {
			if(ev.type == SDL_JOYBUTTONUP) {
				if(ev.jbutton.button == button) {
					return true;
				}
			}
		}
		if(type == ButtonEventType::HELD) {
			if(joystick_buttons_status[button]) {
				return true;
			}
		}

		return false;
	};
	auto caller = [callback](SDL_Event& ev) -> void {
		callback(ev.jbutton);
	};
	registerGenericEventCallback(matcher, caller);
	return true;
}
bool GameCore::registerJoyDeviceAddedEventCallback(std::function<void(SDL_JoyDeviceEvent&)> callback) {
	auto matcher = [](SDL_Event& ev) -> bool {
		if(ev.type == SDL_JOYDEVICEADDED) {
			return true;
		}
		return false;
	};
	auto caller = [callback](SDL_Event& ev) -> void {
		callback(ev.jdevice);
	};
	registerGenericEventCallback(matcher, caller);
	return true;
}
bool GameCore::registerJoyDeviceRemovedEventCallback(std::function<void(SDL_JoyDeviceEvent&)> callback) {
	auto matcher = [](SDL_Event& ev) -> bool {
		if(ev.type == SDL_JOYDEVICEREMOVED) {
			return true;
		}
		return false;
	};
	auto caller = [callback](SDL_Event& ev) -> void {
		callback(ev.jdevice);
	};
	registerGenericEventCallback(matcher, caller);
	return true;
}

bool GameCore::registerControllerAxisEventCallback(std::function<void(SDL_ControllerAxisEvent&)> callback) {
	auto matcher = [](SDL_Event& ev) -> bool {
		if(ev.type == SDL_CONTROLLERAXISMOTION) {
			return true;
		}
		return false;
	};
	auto caller = [callback](SDL_Event& ev) -> void {
		callback(ev.caxis);
	};
	registerGenericEventCallback(matcher, caller);
	return true;
}
bool GameCore::registerControllerButtonEventCallback(
		SDL_GameControllerButton button,
		ButtonEventType type,
		std::function<void(SDL_ControllerButtonEvent&)> callback) {
	auto matcher = [button, type, this](SDL_Event& ev) -> bool {
		if(type == ButtonEventType::DOWN) {
			if(ev.type == SDL_CONTROLLERBUTTONDOWN) {
				if(ev.cbutton.button == button) {
					return true;
				}
			}
		}
		if(type == ButtonEventType::UP) {
			if(ev.type == SDL_CONTROLLERBUTTONUP) {
				if(ev.cbutton.button == button) {
					return true;
				}
			}
		}
		if(type == ButtonEventType::HELD) {
			if(controller_buttons_status[button]) {
				return true;
			}
		}

		return false;
	};
	auto caller = [callback](SDL_Event& ev) -> void {
		callback(ev.cbutton);
	};
	registerGenericEventCallback(matcher, caller);
	return true;
}
bool GameCore::registerControllerDeviceAddedEventCallback(std::function<void(SDL_ControllerDeviceEvent&)> callback) {
	auto matcher = [](SDL_Event& ev) -> bool {
		if(ev.type == SDL_CONTROLLERDEVICEADDED) {
			return true;
		}
		return false;
	};
	auto caller = [callback](SDL_Event& ev) -> void {
		callback(ev.cdevice);
	};
	registerGenericEventCallback(matcher, caller);
	return true;
}
bool GameCore::registerControllerDeviceRemovedEventCallback(std::function<void(SDL_ControllerDeviceEvent&)> callback) {
	auto matcher = [](SDL_Event& ev) -> bool {
		if(ev.type == SDL_CONTROLLERDEVICEREMOVED) {
			return true;
		}
		return false;
	};
	auto caller = [callback](SDL_Event& ev) -> void {
		callback(ev.cdevice);
	};
	registerGenericEventCallback(matcher, caller);
	return true;
}
bool GameCore::registerControllerDeviceRemappedEventCallback(std::function<void(SDL_ControllerDeviceEvent&)> callback) {
	auto matcher = [](SDL_Event& ev) -> bool {
		if(ev.type == SDL_CONTROLLERDEVICEREMAPPED) {
			return true;
		}
		return false;
	};
	auto caller = [callback](SDL_Event& ev) -> void {
		callback(ev.cdevice);
	};
	registerGenericEventCallback(matcher, caller);
	return true;
}

bool GameCore::registerFingerEventCallback(std::function<void(SDL_TouchFingerEvent&)> callback) {
	auto matcher = [](SDL_Event& ev) -> bool {
		if(		ev.type == SDL_FINGERMOTION ||
				ev.type == SDL_FINGERDOWN ||
				ev.type == SDL_FINGERUP) {
			return true;
		}
		return false;
	};
	auto caller = [callback](SDL_Event& ev) -> void {
		callback(ev.tfinger);
	};
	registerGenericEventCallback(matcher, caller);
	return true;
}

bool GameCore::registerDollarGestureEventCallback(std::function<void(SDL_DollarGestureEvent&)> callback) {
	auto matcher = [](SDL_Event& ev) -> bool {
		if(		ev.type == SDL_DOLLARGESTURE ||
				ev.type == SDL_DOLLARRECORD) {
			return true;
		}
		return false;
	};
	auto caller = [callback](SDL_Event& ev) -> void {
		callback(ev.dgesture);
	};
	registerGenericEventCallback(matcher, caller);
	return true;
}

bool GameCore::registerMultiGestureEventCallback(std::function<void(SDL_MultiGestureEvent&)> callback) {
	auto matcher = [](SDL_Event& ev) -> bool {
		if(ev.type == SDL_MULTIGESTURE) {
			return true;
		}
		return false;
	};
	auto caller = [callback](SDL_Event& ev) -> void {
		callback(ev.mgesture);
	};
	registerGenericEventCallback(matcher, caller);
	return true;
}

bool GameCore::registerDropEventCallback(std::function<void(SDL_DropEvent&)> callback) {
	auto matcher = [](SDL_Event& ev) -> bool {
		if(		ev.type == SDL_DROPFILE ||
				ev.type == SDL_DROPTEXT ||
				ev.type == SDL_DROPBEGIN ||
				ev.type == SDL_DROPCOMPLETE) {
			return true;
		}
		return false;
	};
	auto caller = [callback](SDL_Event& ev) -> void {
		callback(ev.drop);
	};
	registerGenericEventCallback(matcher, caller);
	return true;
}

bool GameCore::registerAudioDeviceEventCallback(std::function<void(SDL_AudioDeviceEvent&)> callback) {
	auto matcher = [](SDL_Event& ev) -> bool {
		if(ev.type == SDL_AUDIODEVICEADDED || ev.type == SDL_AUDIODEVICEREMOVED) {
			return true;
		}
		return false;
	};
	auto caller = [callback](SDL_Event& ev) -> void {
		callback(ev.adevice);
	};
	registerGenericEventCallback(matcher, caller);
	return true;
}

bool GameCore::registerGenericEventCallback(
		std::function<bool(SDL_Event&)> event_matcher,
		std::function<void(SDL_Event&)> callback) {
	event_callbacks.push_back(std::make_pair(event_matcher, callback));
	return true;
}

} /* namespace GameEngine */


