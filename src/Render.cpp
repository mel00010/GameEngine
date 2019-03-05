/******************************************************************************
 * Render.cpp
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

#include "Render.hpp"

#include "Attribute.hpp"
#include "Program.hpp"

#include <SDL2/SDL.h>

namespace GameEngine {

void render(SDL_Window* window, ProgramRef program) {
	/* Clear the background as white */
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(program->getProgramHandle());
	glEnableVertexAttribArray(program->getAttributes()[0]->location);
	GLfloat triangle_vertices[] = {
		0.0,  0.8,
	   -0.8, -0.8,
		0.8, -0.8,
	};
	/* Describe our vertices array to OpenGL (it can't guess its format automatically) */
	glVertexAttribPointer(
		program->getAttributes()[0]->location, // attribute
		2,                 // number of elements per vertex, here (x,y)
		GL_FLOAT,          // the type of each element
		GL_FALSE,          // take our values as-is
		0,                 // no extra data between each position
		triangle_vertices  // pointer to the C array
						  );

	/* Push each element in buffer_vertices to the vertex shader */
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(program->getAttributes()[0]->location);

	/* Display the result */
	SDL_GL_SwapWindow(window);
}

} /* namespace GameEngine */


