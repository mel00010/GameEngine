/******************************************************************************
 * TextRenderer.hpp
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
#ifndef SRC_TEXTRENDERER_HPP_
#define SRC_TEXTRENDERER_HPP_

#include "GL.hpp"
#include "Program.hpp"

#include <glm/glm.hpp>
#include <GL/glew.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <SDL2/SDL.h>


#include <map>

namespace GameEngine {

class TextRenderer {
	public:
		TextRenderer();
		void init(SDL_Window* window);
		void renderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);

	protected:
		struct Character {
			GLuint		TextureID;  // ID handle of the glyph texture
			glm::ivec2	Size;       // Size of glyph
			glm::ivec2	Bearing;    // Offset from baseline to left/top of glyph
			FT_Pos		Advance;    // Offset to advance to next glyph
		};

		std::map<GLchar, Character> characters;
		GL gl;
		SDL_Window* window;
		ProgramRef p = nullptr;

		bool valid;
};

} /* namespace GameEngine */




#endif /* SRC_TEXTRENDERER_HPP_ */
