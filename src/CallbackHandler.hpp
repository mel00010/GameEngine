/******************************************************************************
 * CallbackHandler.hpp
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
#ifndef SRC_CALLBACKHANDLER_HPP_
#define SRC_CALLBACKHANDLER_HPP_

#include "InputHandler.hpp"

#include <array>
#include <functional>
#include <list>

#include <glm/glm.hpp>
#include <SDL2/SDL.h>

namespace GameEngine {

enum class KeyEventType {
	UP,
	DOWN,
	HELD
};
enum class ButtonEventType {
	UP,
	DOWN,
	HELD
};
class TimeoutCallback {
	public:
		std::string identifier;
		size_t start_time;
		size_t ms;
		bool repeat;
		std::function<void(void)> callback;
};

class CallbackHandler {
	public:
		void dispatchCallbacks();
		void dispatchTimeoutEvents();

	public:
		bool registerQuitEventCallback(std::function<void(SDL_QuitEvent&)> callback);

		bool registerWindowEventCallback(std::function<void(SDL_WindowEvent&)> callback);

		bool registerKeyboardEventCallback(SDL_Scancode key,
						::GameEngine::KeyEventType type,
						std::function<void(SDL_KeyboardEvent&)> callback);
		bool registerKeyboardEventCallback(SDL_Scancode key,
						::GameEngine::KeyEventType type,
						std::function<void(void)> callback);
		bool registerTextEditingEventCallback(std::function<void(SDL_TextEditingEvent&)> callback);
		bool registerTextInputEventCallback(std::function<void(SDL_TextInputEvent&)> callback);

		bool registerMouseMotionEventCallback(
				std::function<void(SDL_MouseMotionEvent&, glm::ivec2 /* pos */, glm::ivec2 /* delta */)> callback);
		bool registerMouseButtonEventCallback(uint8_t button,
				ButtonEventType type,
				std::function<void(SDL_MouseButtonEvent&, glm::ivec2 /* pos */)> callback);
		bool registerMouseButtonEventCallback(uint8_t button,
				ButtonEventType type,
				std::function<void(void)> callback);
		bool registerImmediateMouseWheelEventCallback(std::function<void(SDL_MouseWheelEvent&, glm::ivec2 /* delta */)> callback);
		bool registerMouseWheelEventCallback(std::function<void(glm::ivec2 /* delta */)> callback);

		bool registerJoyAxisEventCallback(std::function<void(SDL_JoyAxisEvent&)> callback);
		bool registerJoyBallEventCallback(	std::function<void(SDL_JoyBallEvent&)> callback);
		bool registerJoyHatEventCallback(std::function<void(SDL_JoyHatEvent&)> callback);
		bool registerJoyButtonEventCallback(
				uint8_t button,
				ButtonEventType type,
				std::function<void(SDL_JoyButtonEvent&)> callback);
		bool registerJoyDeviceAddedEventCallback(std::function<void(SDL_JoyDeviceEvent&)> callback);
		bool registerJoyDeviceRemovedEventCallback(std::function<void(SDL_JoyDeviceEvent&)> callback);

		bool registerControllerAxisEventCallback(std::function<void(SDL_ControllerAxisEvent&)> callback);
		bool registerControllerButtonEventCallback(
				SDL_GameControllerButton button,
				ButtonEventType type,
				std::function<void(SDL_ControllerButtonEvent&)> callback);
		bool registerControllerDeviceAddedEventCallback(std::function<void(SDL_ControllerDeviceEvent&)> callback);
		bool registerControllerDeviceRemovedEventCallback(std::function<void(SDL_ControllerDeviceEvent&)> callback);
		bool registerControllerDeviceRemappedEventCallback(std::function<void(SDL_ControllerDeviceEvent&)> callback);

		bool registerFingerEventCallback(std::function<void(SDL_TouchFingerEvent&)> callback);

		bool registerDollarGestureEventCallback(std::function<void(SDL_DollarGestureEvent&)> callback);

		bool registerMultiGestureEventCallback(std::function<void(SDL_MultiGestureEvent&)> callback);

		bool registerDropEventCallback(std::function<void(SDL_DropEvent&)> callback);

		bool registerAudioDeviceEventCallback(std::function<void(SDL_AudioDeviceEvent&)> callback);

		bool registerGenericEventCallback(
				std::function<bool(SDL_Event&)> event_matcher,
				std::function<void(SDL_Event&)> callback);

		bool registerTimeoutCallback(std::string identifier, size_t ms,
				std::function<void(void)> callback, bool repeat = false);
		bool unregisterTimeoutCallback(std::string identifier);

	private:
		std::list<std::function<void(SDL_WindowEvent&)>> window_event_callbacks;

		std::array<std::list<std::function<void(SDL_KeyboardEvent&)>>, 512> key_up_callbacks;
		std::array<std::list<std::function<void(SDL_KeyboardEvent&)>>, 512> key_down_callbacks;
		std::array<std::list<std::function<void(void)>>, 512> key_held_callbacks;

		std::list<std::function<void(SDL_MouseMotionEvent&, glm::ivec2 /* pos */, glm::ivec2 /* delta */)>> m_move_callbacks;
		std::array<std::list<std::function<void(SDL_MouseButtonEvent&, glm::ivec2 /* pos */)>>, SDL_BUTTON_X2 + 1> m_button_up_callbacks;
		std::array<std::list<std::function<void(SDL_MouseButtonEvent&, glm::ivec2 /* pos */)>>, SDL_BUTTON_X2 + 1> m_button_down_callbacks;
		std::array<std::list<std::function<void(void)>>, SDL_BUTTON_X2 + 1> m_button_held_callbacks;
		std::list<std::function<void(SDL_MouseWheelEvent&, glm::ivec2 /* delta */)>> m_immediate_wheel_callbacks;
		std::list<std::function<void(glm::ivec2 /* delta */)>> m_wheel_callbacks;

		std::list<TimeoutCallback> timeout_callbacks;

		std::list<std::pair<std::function<bool(SDL_Event&)>, std::function<void(SDL_Event&)>>> event_callbacks;

		InputHandler handler;
};

} /* namespace GameEngine */




#endif /* SRC_CALLBACKHANDLER_HPP_ */
