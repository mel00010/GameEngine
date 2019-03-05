/******************************************************************************
 * Triangle.hpp
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
#ifndef SRC_TRIANGLE_HPP_
#define SRC_TRIANGLE_HPP_

#include "Program.hpp"

#include <SDL2/SDL.h>

namespace GameEngine {

//bool init_resources(void);
ProgramRef init_program(void);
void render(SDL_Window* window, ProgramRef program);
//void free_resources(ProgramRef program);
void main_loop(SDL_Window* window, ProgramRef program);


} /* namespace GameEngine */

#endif /* SRC_TRIANGLE_HPP_ */
