/******************************************************************************
 * GameCore.hpp
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
#ifndef SRC_GAMECORE_HPP_
#define SRC_GAMECORE_HPP_

#include "GL.hpp"
#include "Program.hpp"
#include "Singleton.hpp"
#include "TextRenderer.hpp"
#include "Texture.hpp"


#include <array>
#include <functional>
#include <limits>
#include <list>
#include <map>

#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>



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

template <class Derived> class GameCore;

template <typename Derived>
class GameCoreBase {
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
	public:
		SDL_Window* getWindow();
		bool isCursorDisabled();
		void disableCursor(bool disabled = true);
		bool toggleCursor();

	public:
		void runLoop();

	protected:
		void registerDefaultCallbacks();

	protected:
		void preSetup();
		void preTick();
		void preRender();
		void postSetup();
		void postTick();
		void postRender();

		void loop();
		void dispatchCallbacks();
		void renderFPS();

		void calculateFPS();

		void initSDL();
		void initGL();
		void initFreeType();

		GameCoreBase();
	public:
		void setShowFPS(bool enable = false) { fps_shown = enable; }
		bool isFPSShown() { return fps_shown; }
		void showFPS() { setShowFPS(true); }
		void hideFPS() { setShowFPS(false); }
		void toggleFPS() { fps_shown = !fps_shown; }

		void setFullscreen(bool enable = false);
		bool isFullscreen() { return isScreenFullscreen; }
		void toggleFullscreen() { setFullscreen(!isScreenFullscreen); }

		void setFPSCap(size_t cap = 60) {
			if(fps_cap == cap) {
				return;
			}
			fps_cap = cap;

			if(!fps_cap_enabled) {
				return;
			}

			unregisterTimeoutCallback("render");

			registerTimeoutCallback("render", 1000/fps_cap, [this]() {
				preRender();
				derived().render();
				postRender();
			}, true);
		}
		size_t getFPS_Cap() { return fps_cap; }

		void setFPSCapEnabled(bool enable = false) {
			if(fps_cap_enabled == enable) {
				return;
			}
			fps_cap_enabled = enable;
			unregisterTimeoutCallback("render");

			size_t ms = 0;
			if(fps_cap_enabled) {
				ms = 1000/fps_cap;
			}

			registerTimeoutCallback("render", ms, [this]() {
				preRender();
				derived().render();
				postRender();
			}, true);
		}
		bool isFPSCapEnabled() { return fps_cap_enabled; }
		void toggleFPSCap() { setFPSCapEnabled(!fps_cap_enabled); }

		void setVSyncEnabled(bool enable = false) {
			vsync_enabled = enable;
			SDL_GL_SetSwapInterval(vsync_enabled);
		}
		bool isVSyncEnabled() { return vsync_enabled; }
		void enableVSync() { setVSyncEnabled(true); }
		void disableVSync() { setVSyncEnabled(false); }
		void toggleVSync() { setVSyncEnabled(!vsync_enabled); }

		void quit() {
			SDL_Event sdlevent;
			sdlevent.type = SDL_QUIT;
			SDL_PushEvent(&sdlevent);
		}


	public:
		/**** Convenience method for CRTP ****/
		Derived& derived() {
			return *static_cast<Derived*>(this);
		}
		using SubClass_T = Derived;
		friend Singleton<GameCoreBase<Derived>>;
		friend GameCore<Derived>;

	protected:
		GL gl;
		ProgramRef p;
		SDL_Window* window = nullptr;

		TextRenderer text;


		SDL_DisplayMode native;
		SDL_DisplayMode current;

		size_t frames_rendered = 0;
		size_t total_frames_rendered = 0;

		size_t ms_per_tick;
		double ticks_per_second = 1000/ms_per_tick;

		double fps = 100;
		double fps_avg = 100;
		std::string fps_to_render = "100";

		bool fps_shown = true;

		bool fps_cap_enabled = false;
		size_t fps_cap = 60;

		size_t prev_frame_time = 0;
		size_t curr_frame_time = 0;

		bool cursor_disabled = false;


		bool isScreenFullscreen = false;
		bool vsync_enabled = false;



		/* Input state */
		std::array<bool, SDL_NUM_SCANCODES> key_status = {false};
		std::array<bool, SDL_BUTTON_X2 + 1> mouse_buttons_status = {false};
		std::array<bool, SDL_CONTROLLER_BUTTON_MAX> controller_buttons_status = {false};
		std::array<bool, std::numeric_limits<uint8_t>::max()> joystick_buttons_status = {false};
		glm::ivec2 mouse_wheel_status = glm::ivec2(0, 0);

		glm::ivec2 prev_mouse_pos = glm::ivec2(0, 0);
		glm::ivec2 curr_mouse_pos = glm::ivec2(0, 0);

		glm::ivec2 prev_wheel_pos = glm::ivec2(0, 0);
		glm::ivec2 curr_wheel_pos = glm::ivec2(0, 0);

		/* Callbacks */
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
};
template <class Derived>
class GameCore : public GameCoreBase<Derived>, public Singleton<Derived> {};

} /* namespace GameEngine */

#include "GameCore.tpp"
#include "CallbackRegistration.tpp"

#endif /* SRC_GAMECORE_HPP_ */
