/******************************************************************************
 * CallbackRegistration.tpp
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

#ifndef SRC_CALLBACKREGISTRATION_TPP_
#define SRC_CALLBACKREGISTRATION_TPP_

#include "GameCore.hpp"

namespace GameEngine {

template <typename Derived> bool GameCoreBase<Derived>::registerQuitEventCallback(std::function<void(SDL_QuitEvent&)> callback) {
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

template <typename Derived> bool GameCoreBase<Derived>::registerWindowEventCallback(std::function<void(SDL_WindowEvent&)> callback) {
	window_event_callbacks.push_back(callback);
	return true;
}

template <typename Derived> bool GameCoreBase<Derived>::registerKeyboardEventCallback(SDL_Scancode key,
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
template <typename Derived> bool GameCoreBase<Derived>::registerKeyboardEventCallback(SDL_Scancode key,
				KeyEventType type,
				std::function<void(void)> callback) {
	if(type == KeyEventType::HELD) {
		key_held_callbacks[key].push_back(callback);
	}
	return true;
}
template <typename Derived> bool GameCoreBase<Derived>::registerTextEditingEventCallback(std::function<void(SDL_TextEditingEvent&)> callback) {
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
template <typename Derived> bool GameCoreBase<Derived>::registerTextInputEventCallback(std::function<void(SDL_TextInputEvent&)> callback) {
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

template <typename Derived> bool GameCoreBase<Derived>::registerMouseMotionEventCallback(
		std::function<void(SDL_MouseMotionEvent&, glm::ivec2 /* pos */, glm::ivec2 /* delta */)> callback) {
	m_move_callbacks.push_back(callback);
	return true;
}
template <typename Derived> bool GameCoreBase<Derived>::registerMouseButtonEventCallback(uint8_t button,
		ButtonEventType type,
		std::function<void(SDL_MouseButtonEvent&, glm::ivec2 /* pos */)> callback) {
	if(type == ButtonEventType::DOWN) {
		m_button_down_callbacks[button].push_back(callback);
	}
	if(type == ButtonEventType::UP) {
		m_button_up_callbacks[button].push_back(callback);
	}
	return true;
}
template <typename Derived> bool GameCoreBase<Derived>::registerMouseButtonEventCallback(uint8_t button,
		ButtonEventType type,
		std::function<void(void)> callback) {
	if(type == ButtonEventType::HELD) {
		m_button_held_callbacks[button].push_back(callback);
	}
	return true;
}
template <typename Derived> bool GameCoreBase<Derived>::registerImmediateMouseWheelEventCallback(std::function<void(SDL_MouseWheelEvent&, glm::ivec2 /* delta */)> callback) {
	m_immediate_wheel_callbacks.push_back(callback);
	return true;
}
template <typename Derived> bool GameCoreBase<Derived>::registerMouseWheelEventCallback(std::function<void(glm::ivec2 /* delta */)> callback) {
	m_wheel_callbacks.push_back(callback);
	return true;
}

template <typename Derived> bool GameCoreBase<Derived>::registerJoyAxisEventCallback(std::function<void(SDL_JoyAxisEvent&)> callback) {
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
template <typename Derived> bool GameCoreBase<Derived>::registerJoyBallEventCallback(	std::function<void(SDL_JoyBallEvent&)> callback) {
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
template <typename Derived> bool GameCoreBase<Derived>::registerJoyHatEventCallback(std::function<void(SDL_JoyHatEvent&)> callback) {
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
template <typename Derived> bool GameCoreBase<Derived>::registerJoyButtonEventCallback(
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
template <typename Derived> bool GameCoreBase<Derived>::registerJoyDeviceAddedEventCallback(std::function<void(SDL_JoyDeviceEvent&)> callback) {
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
template <typename Derived> bool GameCoreBase<Derived>::registerJoyDeviceRemovedEventCallback(std::function<void(SDL_JoyDeviceEvent&)> callback) {
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

template <typename Derived> bool GameCoreBase<Derived>::registerControllerAxisEventCallback(std::function<void(SDL_ControllerAxisEvent&)> callback) {
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
template <typename Derived> bool GameCoreBase<Derived>::registerControllerButtonEventCallback(
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
template <typename Derived> bool GameCoreBase<Derived>::registerControllerDeviceAddedEventCallback(std::function<void(SDL_ControllerDeviceEvent&)> callback) {
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
template <typename Derived> bool GameCoreBase<Derived>::registerControllerDeviceRemovedEventCallback(std::function<void(SDL_ControllerDeviceEvent&)> callback) {
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
template <typename Derived> bool GameCoreBase<Derived>::registerControllerDeviceRemappedEventCallback(std::function<void(SDL_ControllerDeviceEvent&)> callback) {
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

template <typename Derived> bool GameCoreBase<Derived>::registerFingerEventCallback(std::function<void(SDL_TouchFingerEvent&)> callback) {
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

template <typename Derived> bool GameCoreBase<Derived>::registerDollarGestureEventCallback(std::function<void(SDL_DollarGestureEvent&)> callback) {
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

template <typename Derived> bool GameCoreBase<Derived>::registerMultiGestureEventCallback(std::function<void(SDL_MultiGestureEvent&)> callback) {
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

template <typename Derived> bool GameCoreBase<Derived>::registerDropEventCallback(std::function<void(SDL_DropEvent&)> callback) {
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

template <typename Derived> bool GameCoreBase<Derived>::registerAudioDeviceEventCallback(std::function<void(SDL_AudioDeviceEvent&)> callback) {
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

template <typename Derived> bool GameCoreBase<Derived>::registerGenericEventCallback(
		std::function<bool(SDL_Event&)> event_matcher,
		std::function<void(SDL_Event&)> callback) {
	event_callbacks.push_back(std::make_pair(event_matcher, callback));
	return true;
}

template <typename Derived> bool GameCoreBase<Derived>::registerTimeoutCallback(std::string identifier, size_t ms, std::function<void(void)> callback, bool repeat) {
	for(auto& i : timeout_callbacks) {
		if(i.identifier == identifier) {
			return false;
		}
	}

	timeout_callbacks.emplace_back(TimeoutCallback {
		identifier,
		SDL_GetTicks(),
		ms,
		repeat,
		callback,
	});
	return true;
}

template <typename Derived> bool GameCoreBase<Derived>::unregisterTimeoutCallback(std::string identifier) {
	for (auto i = timeout_callbacks.begin(); i != timeout_callbacks.end(); i++) {
		if(i->identifier == identifier) {
			timeout_callbacks.erase(i);
			return true;
		}
	}
	return false;
}

} /* namespace GameEngine */

#endif /* SRC_CALLBACKREGISTRATION_TPP_ */
