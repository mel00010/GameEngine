/******************************************************************************
 * GLWindowManager.hpp
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
#ifndef SRC_GL_GLWINDOWMANAGER_HPP_
#define SRC_GL_GLWINDOWMANAGER_HPP_

#include <WindowManager.hpp>

#include <glm/glm.hpp>
#include <SDL2/SDL.h>

namespace GameEngine {
namespace GL {

class GLWindowManager : public WindowManager<GLWindowManager> {
	public:
		void init(std::string program_name);
		SDL_Window* getWindow();
		void setWindow(SDL_Window* p);

		static glm::ivec2 getWindowSize();

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

		void redrawWindowBounds(glm::ivec2 size);

	public:
		static SDL_Window* window;

	protected:
		bool cursor_disabled = false;
		bool isScreenFullscreen = false;
		bool vsync_enabled = false;

		SDL_DisplayMode native;
		SDL_DisplayMode current;
};

} /* namespace GL */
} /* namespace GameEngine */



#endif /* SRC_GL_GLWINDOWMANAGER_HPP_ */
