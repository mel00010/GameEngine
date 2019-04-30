/******************************************************************************
 * CallbackHandler.cpp
 * Copyright (C) 2019  Mel McCalla <melmccalla@gmail.com> *
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

#include "CallbackHandler.hpp"

#include "InputHandler.hpp"

namespace GameEngine {

void CallbackHandler::dispatchCallbacks() {
	SDL_Event ev;
	while (SDL_PollEvent(&ev)) {
		switch(ev.type) {
			case SDL_WINDOWEVENT:
				for(auto& i: window_event_callbacks) {
					i(ev.window);
				}
				break;
			case SDL_KEYDOWN:
				if(ev.key.repeat != 0) {
					break;
				}
				handler.setKeyStatus(ev.key.keysym.scancode, true);
				for(auto& i: key_down_callbacks[ev.key.keysym.scancode]) {
					i(ev.key);
				}
				break;
			case SDL_KEYUP:
				handler.setKeyStatus(ev.key.keysym.scancode, false);
				for(auto& i: key_up_callbacks[ev.key.keysym.scancode]) {
					i(ev.key);
				}
				break;
			case SDL_MOUSEMOTION:
				for(auto& i: m_move_callbacks) {
					i(ev.motion, glm::ivec2(ev.motion.x, ev.motion.y), glm::ivec2(ev.motion.xrel, ev.motion.yrel));
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				handler.setMouseButtonStatus(ev.button.button, true);
				for(auto& i: m_button_down_callbacks[ev.button.button]) {
					i(ev.button, glm::ivec2(ev.button.x, ev.button.y));
				}
				break;
			case SDL_MOUSEBUTTONUP:
				handler.setMouseButtonStatus(ev.button.button, false);
				for(auto& i: m_button_up_callbacks[ev.button.button]) {
					i(ev.button, glm::ivec2(ev.button.x, ev.button.y));
				}
				break;
			case SDL_MOUSEWHEEL:
				handler.addToMouseWheelPos(glm::ivec2(ev.wheel.x, ev.wheel.y));
				for(auto& i: m_immediate_wheel_callbacks) {
					i(ev.wheel, glm::ivec2(ev.wheel.x, ev.wheel.y));
				}
				break;
		}
		for(auto& callback_pair : event_callbacks) {
			if(callback_pair.first(ev)) {
				callback_pair.second(ev);
			}
		}
	}
	if(handler.getMouseWheelPos() != glm::ivec2(0, 0)) {
		for(auto& callback : m_wheel_callbacks) {
			callback(handler.getMouseWheelPos());
		}
		handler.setMouseWheelPos(glm::ivec2(0, 0));
	}

	for(size_t i = 0; i < key_held_callbacks.size(); i++) {
		if(handler.getKeyStatus(i)) {
			for(auto& callback : key_held_callbacks[i]) {
				callback();
			}
		}
	}
	for(size_t i = 0; i < m_button_held_callbacks.size(); i++) {
		if(handler.getMouseButtonStatus(i)) {
			for(auto& callback : m_button_held_callbacks[i]) {
				callback();
			}
		}
	}
}

void CallbackHandler::dispatchTimeoutEvents() {
	std::list<std::string> remove_list;
	for (auto& i : timeout_callbacks) {
		size_t curr_time = SDL_GetTicks();
		if(curr_time > i.start_time + i.ms) {
			i.callback();
			if(i.repeat) {
				i.start_time = curr_time;
			} else {
				remove_list.push_back(i.identifier);
			}
		}
	}
	for (auto& i : remove_list) {
		unregisterTimeoutCallback(i);
	}
}

bool CallbackHandler::registerQuitEventCallback(std::function<void(SDL_QuitEvent&)> callback) {
	auto matcher = [](SDL_Event& ev) -> bool { return ev.type == SDL_QUIT; };
	auto caller = [callback](SDL_Event& ev) -> void { callback(ev.quit); };
	registerGenericEventCallback(matcher, caller);
	return true;
}
bool CallbackHandler::registerWindowEventCallback(std::function<void(SDL_WindowEvent&)> callback) {
	window_event_callbacks.push_back(callback);
	return true;
}

bool CallbackHandler::registerKeyboardEventCallback(SDL_Scancode key,
				KeyEventType type,
				std::function<void(SDL_KeyboardEvent&)> callback) {
	if(type == KeyEventType::DOWN)	{ key_up_callbacks[key].push_back(callback); }
	if(type == KeyEventType::UP)	{ key_down_callbacks[key].push_back(callback); }
	return true;
}
bool CallbackHandler::registerKeyboardEventCallback(SDL_Scancode key,
				KeyEventType type,
				std::function<void(void)> callback) {
	if(type == KeyEventType::HELD) { key_held_callbacks[key].push_back(callback); }
	return true;
}
bool CallbackHandler::registerTextEditingEventCallback(std::function<void(SDL_TextEditingEvent&)> callback) {
	auto matcher = [](SDL_Event& ev) -> bool { return ev.type == SDL_TEXTEDITING;};
	auto caller = [callback](SDL_Event& ev) -> void { callback(ev.edit);};
	registerGenericEventCallback(matcher, caller);
	return true;
}
bool CallbackHandler::registerTextInputEventCallback(std::function<void(SDL_TextInputEvent&)> callback) {
	auto matcher = [](SDL_Event& ev) -> bool { return ev.type == SDL_TEXTINPUT;	};
	auto caller = [callback](SDL_Event& ev) -> void { callback(ev.text); };
	registerGenericEventCallback(matcher, caller);
	return true;
}

bool CallbackHandler::registerMouseMotionEventCallback(
		std::function<void(SDL_MouseMotionEvent&, glm::ivec2 /* pos */, glm::ivec2 /* delta */)> callback) {
	m_move_callbacks.push_back(callback);
	return true;
}
bool CallbackHandler::registerMouseButtonEventCallback(uint8_t button,
		ButtonEventType type,
		std::function<void(SDL_MouseButtonEvent&, glm::ivec2 /* pos */)> callback) {
	if(type == ButtonEventType::DOWN)	{ m_button_down_callbacks[button].push_back(callback); }
	if(type == ButtonEventType::UP)		{ m_button_up_callbacks[button].push_back(callback); }
	return true;
}
bool CallbackHandler::registerMouseButtonEventCallback(uint8_t button,
		ButtonEventType type,
		std::function<void(void)> callback) {
	if(type == ButtonEventType::HELD) { m_button_held_callbacks[button].push_back(callback); }
	return true;
}
bool CallbackHandler::registerImmediateMouseWheelEventCallback(std::function<void(SDL_MouseWheelEvent&, glm::ivec2 /* delta */)> callback) {
	m_immediate_wheel_callbacks.push_back(callback);
	return true;
}
bool CallbackHandler::registerMouseWheelEventCallback(std::function<void(glm::ivec2 /* delta */)> callback) {
	m_wheel_callbacks.push_back(callback);
	return true;
}

bool CallbackHandler::registerJoyAxisEventCallback(std::function<void(SDL_JoyAxisEvent&)> callback) {
	auto matcher = [](SDL_Event& ev) -> bool { return ev.type == SDL_JOYAXISMOTION; };
	auto caller = [callback](SDL_Event& ev) -> void { callback(ev.jaxis); };
	registerGenericEventCallback(matcher, caller);
	return true;
}
bool CallbackHandler::registerJoyBallEventCallback(	std::function<void(SDL_JoyBallEvent&)> callback) {
	auto matcher = [](SDL_Event& ev) -> bool { return ev.type == SDL_JOYBALLMOTION; };
	auto caller = [callback](SDL_Event& ev) -> void { callback(ev.jball); };
	registerGenericEventCallback(matcher, caller);
	return true;
}
bool CallbackHandler::registerJoyHatEventCallback(std::function<void(SDL_JoyHatEvent&)> callback) {
	auto matcher = [](SDL_Event& ev) -> bool { return ev.type == SDL_JOYHATMOTION; };
	auto caller = [callback](SDL_Event& ev) -> void { callback(ev.jhat); };
	registerGenericEventCallback(matcher, caller);
	return true;
}
bool CallbackHandler::registerJoyButtonEventCallback(
		uint8_t button,
		ButtonEventType type,
		std::function<void(SDL_JoyButtonEvent&)> callback) {
	auto matcher = [button, type, this](SDL_Event& ev) -> bool {
		return	(type == ButtonEventType::DOWN && ev.type == SDL_JOYBUTTONDOWN && ev.jbutton.button == button) ||
				(type == ButtonEventType::UP && ev.type == SDL_JOYBUTTONUP && ev.jbutton.button == button) ||
				(type == ButtonEventType::HELD && handler.getJoyButtonStatus(button));
	};
	auto caller = [callback](SDL_Event& ev) -> void { callback(ev.jbutton); };
	registerGenericEventCallback(matcher, caller);
	return true;
}
bool CallbackHandler::registerJoyDeviceAddedEventCallback(std::function<void(SDL_JoyDeviceEvent&)> callback) {
	auto matcher = [](SDL_Event& ev) -> bool { return ev.type == SDL_JOYDEVICEADDED; };
	auto caller = [callback](SDL_Event& ev) -> void { callback(ev.jdevice); };
	registerGenericEventCallback(matcher, caller);
	return true;
}
bool CallbackHandler::registerJoyDeviceRemovedEventCallback(std::function<void(SDL_JoyDeviceEvent&)> callback) {
	auto matcher = [](SDL_Event& ev) -> bool { return ev.type == SDL_JOYDEVICEREMOVED; };
	auto caller = [callback](SDL_Event& ev) -> void { callback(ev.jdevice); };
	registerGenericEventCallback(matcher, caller);
	return true;
}

bool CallbackHandler::registerControllerAxisEventCallback(std::function<void(SDL_ControllerAxisEvent&)> callback) {
	auto matcher = [](SDL_Event& ev) -> bool { return ev.type == SDL_CONTROLLERAXISMOTION; };
	auto caller = [callback](SDL_Event& ev) -> void { callback(ev.caxis); };
	registerGenericEventCallback(matcher, caller);
	return true;
}
bool CallbackHandler::registerControllerButtonEventCallback(
		SDL_GameControllerButton button,
		ButtonEventType type,
		std::function<void(SDL_ControllerButtonEvent&)> callback) {
	auto matcher = [button, type, this](SDL_Event& ev) -> bool {
		return	(type == ButtonEventType::DOWN && ev.type == SDL_CONTROLLERBUTTONDOWN && ev.cbutton.button == button) ||
				(type == ButtonEventType::UP && ev.type == SDL_CONTROLLERBUTTONUP && ev.cbutton.button == button) ||
				(type == ButtonEventType::HELD && handler.getControllerButtonStatus(button));
	};
	auto caller = [callback](SDL_Event& ev) -> void { callback(ev.cbutton); };
	registerGenericEventCallback(matcher, caller);
	return true;
}
bool CallbackHandler::registerControllerDeviceAddedEventCallback(std::function<void(SDL_ControllerDeviceEvent&)> callback) {
	auto matcher = [](SDL_Event& ev) -> bool { return ev.type == SDL_CONTROLLERDEVICEADDED; };
	auto caller = [callback](SDL_Event& ev) -> void { callback(ev.cdevice); };
	registerGenericEventCallback(matcher, caller);
	return true;
}
bool CallbackHandler::registerControllerDeviceRemovedEventCallback(std::function<void(SDL_ControllerDeviceEvent&)> callback) {
	auto matcher = [](SDL_Event& ev) -> bool { return ev.type == SDL_CONTROLLERDEVICEREMOVED; };
	auto caller = [callback](SDL_Event& ev) -> void { callback(ev.cdevice); };
	registerGenericEventCallback(matcher, caller);
	return true;
}
bool CallbackHandler::registerControllerDeviceRemappedEventCallback(std::function<void(SDL_ControllerDeviceEvent&)> callback) {
	auto matcher = [](SDL_Event& ev) -> bool { return ev.type == SDL_CONTROLLERDEVICEREMAPPED; };
	auto caller = [callback](SDL_Event& ev) -> void { callback(ev.cdevice); };
	registerGenericEventCallback(matcher, caller);
	return true;
}

bool CallbackHandler::registerFingerEventCallback(std::function<void(SDL_TouchFingerEvent&)> callback) {
	auto matcher = [](SDL_Event& ev) -> bool { return ev.type == SDL_FINGERMOTION || ev.type == SDL_FINGERDOWN || ev.type == SDL_FINGERUP; };
	auto caller = [callback](SDL_Event& ev) -> void { callback(ev.tfinger); };
	registerGenericEventCallback(matcher, caller);
	return true;
}
bool CallbackHandler::registerDollarGestureEventCallback(std::function<void(SDL_DollarGestureEvent&)> callback) {
	auto matcher = [](SDL_Event& ev) -> bool { return ev.type == SDL_DOLLARGESTURE || ev.type == SDL_DOLLARRECORD; };
	auto caller = [callback](SDL_Event& ev) -> void { callback(ev.dgesture); };
	registerGenericEventCallback(matcher, caller);
	return true;
}
bool CallbackHandler::registerMultiGestureEventCallback(std::function<void(SDL_MultiGestureEvent&)> callback) {
	auto matcher = [](SDL_Event& ev) -> bool { return ev.type == SDL_MULTIGESTURE; };
	auto caller = [callback](SDL_Event& ev) -> void { callback(ev.mgesture); };
	registerGenericEventCallback(matcher, caller);
	return true;
}

bool CallbackHandler::registerDropEventCallback(std::function<void(SDL_DropEvent&)> callback) {
	auto matcher = [](SDL_Event& ev) -> bool { return ev.type == SDL_DROPFILE || ev.type == SDL_DROPTEXT
												   || ev.type == SDL_DROPBEGIN || ev.type == SDL_DROPCOMPLETE; };
	auto caller = [callback](SDL_Event& ev) -> void { callback(ev.drop);};
	registerGenericEventCallback(matcher, caller);
	return true;
}

bool CallbackHandler::registerAudioDeviceEventCallback(std::function<void(SDL_AudioDeviceEvent&)> callback) {
	auto matcher = [](SDL_Event& ev) -> bool { return ev.type == SDL_AUDIODEVICEADDED || ev.type == SDL_AUDIODEVICEREMOVED; };
	auto caller = [callback](SDL_Event& ev) -> void { callback(ev.adevice); };
	registerGenericEventCallback(matcher, caller);
	return true;
}

bool CallbackHandler::registerGenericEventCallback(
		std::function<bool(SDL_Event&)> event_matcher,
		std::function<void(SDL_Event&)> callback) {
	event_callbacks.push_back(std::make_pair(event_matcher, callback));
	return true;
}
bool CallbackHandler::registerTimeoutCallback(std::string identifier, size_t ms, std::function<void(void)> callback, bool repeat) {
	if(std::any_of(timeout_callbacks.begin(), timeout_callbacks.end(), [&identifier](TimeoutCallback c) { return c.identifier == identifier; })) {return false; }
	timeout_callbacks.emplace_back(TimeoutCallback { identifier, SDL_GetTicks(), ms, repeat, callback, } );
	return true;
}
bool CallbackHandler::unregisterTimeoutCallback(std::string identifier) {
	timeout_callbacks.erase( std::remove_if (timeout_callbacks.begin(), timeout_callbacks.end(),
		[&identifier](TimeoutCallback c) { return c.identifier == identifier; }), timeout_callbacks.end());
	return false;
}

} /* namespace GameEngine */
