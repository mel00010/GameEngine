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
#ifndef SRC_2D_TEXTRENDERER_HPP_
#define SRC_2D_TEXTRENDERER_HPP_

#include <3D/Texture.hpp>

#include <Util/Singleton.hpp>

#include <Renderer.hpp>
#include <Vertex.hpp>

#include <glm/glm.hpp>
#include <GL/glew.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <SDL2/SDL.h>

#include <map>
#include <string>

namespace GameEngine {
namespace _2D {

class TextRenderer {
	public:
		template<typename Renderer>
		void init(Renderer& renderer);

		template<typename Renderer>
		void renderText(Renderer& renderer, std::string text, float x, float y, float scale, glm::vec3 color);

		template<typename Renderer>
		void renderTextRelativeToTopRight(Renderer& renderer, std::string text, float x, float y, float scale, glm::vec3 color);

	protected:
		struct Character {
			_3D::Texture 	Texture;	// Glyph texture
			glm::ivec2		Size;		// Size of glyph
			glm::ivec2		Bearing;	// Offset from baseline to left/top of glyph
			FT_Pos			Advance;	// Offset to advance to next glyph
		};

		std::map<char, Character> characters;

		bool valid = false;
		VBO_handle handle;
};

} /* namespace _2D */
} /* namespace GameEngine */

#include "TextRenderer.tpp"

#endif /* SRC_2D_TEXTRENDERER_HPP_ */
