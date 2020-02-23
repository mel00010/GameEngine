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

namespace game_engine {

/**
 * @brief Defines the different execution times for a key event
 */
enum class KeyEventType : std::uint8_t {
	UP,  //!< Event occurs when key is raised
	DOWN,//!< Event occurs when key is depressed
	HELD //!< Event occurs once per tick while key is held down
};

/**
 * @brief Defines the different execution times for a button event
 */
enum class ButtonEventType : std::uint8_t {
	UP,  //!< Event occurs when button is raised
	DOWN,//!< Event occurs when button is depressed
	HELD //!< Event occurs once per tick while button is held down
};

/**
 * @brief Holds information necessary for a timeout callback
 */
struct TimeoutCallback {
	public:
		/**
		 * @brief A string identifying the callback
		 */
		std::string identifier;
		/**
		 * @brief Time callback is registered
		 */
		size_t start_time;
		/**
		 * @brief How long from start time to execute the callback in ms
		 */
		size_t ms;
		/**
		 * @brief Should the callback repeat
		 */
		bool repeat;
		/**
		 * @brief Function to execute as the callback
		 */
		std::function<void(void)> callback;
};

/**
 * @brief Helper class handling event callbacks
 */
class CallbackHandler {
	public:
		/**
		 * @brief Process and dispatch all event callbacks
		 */
		void DispatchCallbacks();

		/**
		 * @brief Dispatch timeout events that are set to be executed
		 */
		void DispatchTimeoutEvents();

	public:
		/**
		 * @brief Register a callback to be executed on a quit event
		 * @param callback Function to be executed
		 * @return Returns true if callback is registered
		 */
		bool RegisterQuitEventCallback(std::function<void(SDL_QuitEvent&)> callback);

		/**
		 * @brief Register a callback to be executed on a window event
		 * @param callback Function to be executed
		 * @return Returns true if callback is registered
		 */
		bool RegisterWindowEventCallback(std::function<void(SDL_WindowEvent&)> callback);

		/**
		 * @brief Register a callback to be executed on a keyboard event
		 * @param key Key to bind the callback to
		 * @param type Type of key event
		 * @param callback Function to be executed
		 * @return Returns true if callback is registered
		 */
		bool RegisterKeyboardEventCallback(SDL_Scancode key,
						KeyEventType type,
						std::function<void(SDL_KeyboardEvent&)> callback);
		/**
		 * @brief Register a callback to be executed on a keyboard event
		 * @param key Key to bind the callback to
		 * @param type Type of key event
		 * @param callback Function to be executed
		 * @return Returns true if callback is registered
		 */
		bool RegisterKeyboardEventCallback(SDL_Scancode key,
						KeyEventType type,
						std::function<void(void)> callback);
		/**
		 * @brief Register a callback to be executed on a text editing event
		 * @param callback Function to be executed
		 * @return Returns true if callback is registered
		 */
		bool RegisterTextEditingEventCallback(std::function<void(SDL_TextEditingEvent&)> callback);
		/**
		 * @brief Register a callback to be executed on a text input event
		 * @param callback Function to be executed
		 * @return Returns true if callback is registered
		 */
		bool RegisterTextInputEventCallback(std::function<void(SDL_TextInputEvent&)> callback);

		/**
		 * @brief Register a callback to be executed on a mouse motion event
		 * @param callback Function to be executed
		 * @return Returns true if callback is registered
		 */
		bool RegisterMouseMotionEventCallback(
				std::function<void(SDL_MouseMotionEvent&, glm::ivec2 /* pos */, glm::ivec2 /* delta */)> callback);
		/**
		 * @brief Register a callback to be executed on a mouse button event
		 * @param button Button to bind the event to
		 * @param type Type of button event
		 * @param callback Function to be executed
		 * @return Returns true if callback is registered
		 */
		bool RegisterMouseButtonEventCallback(uint8_t button,
				ButtonEventType type,
				std::function<void(SDL_MouseButtonEvent&, glm::ivec2 /* pos */)> callback);
		/**
		 * @brief Register a callback to be executed on a mouse button event
		 * @param button Button to bind the event to
		 * @param type Type of button event
		 * @param callback Function to be executed
		 * @return Returns true if callback is registered
		 */
		bool RegisterMouseButtonEventCallback(uint8_t button,
				ButtonEventType type,
				std::function<void(void)> callback);
		/**
		 * @brief Register a callback to be executed immediately on a mouse wheel event
		 * @param callback Function to be executed
		 * @return Returns true if callback is registered
		 */
		bool RegisterImmediateMouseWheelEventCallback(std::function<void(SDL_MouseWheelEvent&, glm::ivec2 /* delta */)> callback);
		/**
		 * @brief Register a callback to be executed on a mouse wheel event
		 * @param callback Function to be executed
		 * @return Returns true if callback is registered
		 */
		bool RegisterMouseWheelEventCallback(std::function<void(glm::ivec2 /* delta */)> callback);

		/**
		 * @brief Register a callback to be executed on a joystick axis event
		 * @param callback Function to be executed
		 * @return Returns true if callback is registered
		 */
		bool RegisterJoyAxisEventCallback(std::function<void(SDL_JoyAxisEvent&)> callback);
		/**
		 * @brief Register a callback to be executed on a joystick ball event
		 * @param callback Function to be executed
		 * @return Returns true if callback is registered
		 */
		bool RegisterJoyBallEventCallback(	std::function<void(SDL_JoyBallEvent&)> callback);
		/**
		 * @brief Register a callback to be executed on a joystick hat event
		 * @param callback Function to be executed
		 * @return Returns true if callback is registered
		 */
		bool RegisterJoyHatEventCallback(std::function<void(SDL_JoyHatEvent&)> callback);
		/**
		 * @brief Register a callback to be executed on a joystick button event
		 * @param button Button to bind the callback to
		 * @param type Type of button event
		 * @param callback Function to be executed
		 * @return Returns true if callback is registered
		 */
		bool RegisterJoyButtonEventCallback(
				uint8_t button,
				ButtonEventType type,
				std::function<void(SDL_JoyButtonEvent&)> callback);
		/**
		 * @brief Register a callback to be executed on a joystick device addition event
		 * @param callback Function to be executed
		 * @return Returns true if callback is registered
		 */
		bool RegisterJoyDeviceAddedEventCallback(std::function<void(SDL_JoyDeviceEvent&)> callback);
		/**
		 * @brief Register a callback to be executed on a joystick device removal event
		 * @param callback Function to be executed
		 * @return Returns true if callback is registered
		 */
		bool RegisterJoyDeviceRemovedEventCallback(std::function<void(SDL_JoyDeviceEvent&)> callback);

		/**
		 * @brief Register a callback to be executed on a controller axis event
		 * @param callback Function to be executed
		 * @return Returns true if callback is registered
		 */
		bool RegisterControllerAxisEventCallback(std::function<void(SDL_ControllerAxisEvent&)> callback);
		/**
		 * @brief Register a callback to be executed on a controller button event
		 * @param button Button to bind the callback to
		 * @param type Type of button press event
		 * @param callback Function to be executed
		 * @return Returns true if callback is registered
		 */
		bool RegisterControllerButtonEventCallback(
				SDL_GameControllerButton button,
				ButtonEventType type,
				std::function<void(SDL_ControllerButtonEvent&)> callback);
		/**
		 * @brief Register a callback to be executed on a controller device addition event
		 * @param callback Function to be executed
		 * @return Returns true if callback is registered
		 */
		bool RegisterControllerDeviceAddedEventCallback(std::function<void(SDL_ControllerDeviceEvent&)> callback);
		/**
		 * @brief Register a callback to be executed on a controller device removal event
		 * @param callback Function to be executed
		 * @return Returns true if callback is registered
		 */
		bool RegisterControllerDeviceRemovedEventCallback(std::function<void(SDL_ControllerDeviceEvent&)> callback);
		/**
		 * @brief Register a callback to be executed on a controller device remap event
		 * @param callback Function to be executed
		 * @return Returns true if callback is registered
		 */
		bool RegisterControllerDeviceRemappedEventCallback(std::function<void(SDL_ControllerDeviceEvent&)> callback);

		/**
		 * @brief Register a callback to be executed on a finger event
		 * @param callback Function to be executed
		 * @return Returns true if callback is registered
		 */
		bool RegisterFingerEventCallback(std::function<void(SDL_TouchFingerEvent&)> callback);

		/**
		 * @brief Register a callback to be executed on a dollar gesture event
		 * @param callback Function to be executed
		 * @return Returns true if callback is registered
		 */
		bool RegisterDollarGestureEventCallback(std::function<void(SDL_DollarGestureEvent&)> callback);

		/**
		 * @brief Register a callback to be executed on a multigesture event
		 * @param callback Function to be executed
		 * @return Returns true if callback is registered
		 */
		bool RegisterMultiGestureEventCallback(std::function<void(SDL_MultiGestureEvent&)> callback);

		/**
		 * @brief Register a callback to be executed on a drop event
		 * @param callback Function to be executed
		 * @return Returns true if callback is registered
		 */
		bool RegisterDropEventCallback(std::function<void(SDL_DropEvent&)> callback);

		/**
		 * @brief Register a callback to be executed on a audio device event
		 * @param callback Function to be executed
		 * @return Returns true if callback is registered
		 */
		bool RegisterAudioDeviceEventCallback(std::function<void(SDL_AudioDeviceEvent&)> callback);

		/**
		 * @brief Register a callback to be executed if an event satisfies event_matcher
		 * @param event_matcher Boolean function matcher that returns true if the callback
		 * 		  is to be executed for a given \c SDL_Event
		 * @param callback Function to be executed
		 * @return Returns true if callback is registered
		 */
		bool RegisterGenericEventCallback(
				std::function<bool(SDL_Event&)> event_matcher,
				std::function<void(SDL_Event&)> callback);

		/**
		 * @brief Register a callback to be executed after a certain amount of time has elapsed
		 * @param identifier String identifying the callback
		 * @param ms Time in milliseconds after which the callback is executed
		 * @param callback Function to be executed
		 * @param repeat Boolean representing whether the callback should repeat
		 * @return Returns true if callback is registered
		 */
		bool RegisterTimeoutCallback(std::string identifier, size_t ms,
				std::function<void(void)> callback, bool repeat = false);
		/**
		 * @brief Unregister a callback by identifier
		 * @param identifier String identifier of the callback to unregister
		 * @return Always returns false
		 */
		bool UnregisterTimeoutCallback(std::string identifier);

	private:
		/**
		 * @brief List of all window event callback functions
		 */
		std::list<std::function<void(SDL_WindowEvent&)>> window_event_callbacks_;

		/**
		 * @brief Array of lists of key up event callback functions
		 */
		std::array<std::list<std::function<void(SDL_KeyboardEvent&)>>, 512> key_up_callbacks_;
		/**
		 * @brief Array of lists of key down event callback functions
		 */
		std::array<std::list<std::function<void(SDL_KeyboardEvent&)>>, 512> key_down_callbacks_;
		/**
		 * @brief Array of lists of key held event callback functions
		 */
		std::array<std::list<std::function<void(void)>>, 512> key_held_callbacks_;

		/**
		 * @brief List of mouse move event callback functions
		 */
		std::list<std::function<void(SDL_MouseMotionEvent&, glm::ivec2 /* pos */, glm::ivec2 /* delta */)>> m_move_callbacks_;
		/**
		 * @brief Array of lists of mouse button up event callback functions
		 */
		std::array<std::list<std::function<void(SDL_MouseButtonEvent&, glm::ivec2 /* pos */)>>, SDL_BUTTON_X2 + 1> m_button_up_callbacks_;
		/**
		 * @brief Array of lists of mouse button down event callback functions
		 */
		std::array<std::list<std::function<void(SDL_MouseButtonEvent&, glm::ivec2 /* pos */)>>, SDL_BUTTON_X2 + 1> m_button_down_callbacks_;
		/**
		 * @brief Array of lists of mouse button held event callback functions
		 */
		std::array<std::list<std::function<void(void)>>, SDL_BUTTON_X2 + 1> m_button_held_callbacks_;
		/**
		 * @brief List of immediate mouse wheel event callback functions
		 */
		std::list<std::function<void(SDL_MouseWheelEvent&, glm::ivec2 /* delta */)>> m_immediate_wheel_callbacks_;
		/**
		 * @brief List of mouse wheel event callback functions
		 */
		std::list<std::function<void(glm::ivec2 /* delta */)>> m_wheel_callbacks_;

		/**
		 * @brief List of timeout callback objects
		 */
		std::list<TimeoutCallback> timeout_callbacks_;

		/**
		 * @brief List of event callbacks and their event matchers
		 */
		std::list<std::pair<std::function<bool(SDL_Event&)>, std::function<void(SDL_Event&)>>> event_callbacks_;

		/**
		 * @brief Helper class handling HID input
		 */
		InputHandler handler_;
};

} /* namespace game_engine */




#endif /* SRC_CALLBACKHANDLER_HPP_ */
