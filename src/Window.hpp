/******************************************************************************
 * Window.hpp
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
#ifndef SRC_WINDOW_HPP_
#define SRC_WINDOW_HPP_

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <string>
#include <memory>

using namespace glm;

namespace GameEngine {

class Window {
	public:
		Window(std::string title,
				ivec2 size = ivec2(640, 480),
				ivec2 pos = ivec2(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED),
				uint32_t flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
		Window(std::string title,
				int width,
				int height,
				int x_pos = SDL_WINDOWPOS_CENTERED,
				int y_pos = SDL_WINDOWPOS_CENTERED,
				uint32_t flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
		Window();

		~Window();

		Window(Window const&) = delete;
		void operator=(Window const&) = delete;

		bool create();

	public:
		std::string getTitle();
		void setTitle(std::string title);
		ivec2 getSize();
		void setSize(ivec2 size);
		void setSize(int width, int height);
		ivec2 getPos();
		void setPos(ivec2 pos);
		void setPos(int x, int y);
		uint32_t getFlags();
		SDL_Window* getWindowRef();

		bool isValid();

		SDL_Window* window_ref;

	protected:
		std::string title;
		ivec2 size;
		ivec2 pos;
		uint32_t flags;


		bool valid;
};

using WindowRef = std::shared_ptr<Window>;


} /* namespace GameEngine */



#endif /* SRC_WINDOW_HPP_ */
