/******************************************************************************
 * WindowManager.hpp
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
#ifndef SRC_WINDOWMANAGER_HPP_
#define SRC_WINDOWMANAGER_HPP_

#include <glm/glm.hpp>
#include <SDL2/SDL.h>

namespace GameEngine {

class WindowManager {
	public:
		SDL_Window* getWindow();
		void setWindow(SDL_Window* p);

		glm::ivec2 getWindowSize();
		static glm::ivec2 getWindowSize(SDL_Window* p);

		void setFullscreen(bool enable = false);
		bool isFullscreen();
		void toggleFullscreen();

		void setVSyncEnabled(bool enable = false);
		bool isVSyncEnabled();
		void enableVSync();
		void disableVSync();
		void toggleVSync();

		void quit();
		bool isCursorDisabled();
		void disableCursor(bool disabled = true);
		bool toggleCursor();

	private:
		SDL_Window* window = nullptr;

		bool cursor_disabled = false;
		bool isScreenFullscreen = false;
		bool vsync_enabled = false;

		SDL_DisplayMode native;
		SDL_DisplayMode current;
};

} /* namespace GameEngine */




#endif /* SRC_WINDOWMANAGER_HPP_ */
