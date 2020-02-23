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
#include <utility>

namespace game_engine {
namespace _2D {

class TextRenderer {
	public:
		template<typename Renderer>
		void Init(Renderer& renderer);

		template<typename Renderer>
		void RenderText(const Renderer& renderer, const std::string text,
				const float x, const float y, const float scale, const glm::vec3 color);

		template<typename Renderer>
		void RenderTextRelativeToTopRight(const Renderer& renderer, const std::string text,
				const float x, const float y, const float scale, const glm::vec3 color);

		void swap(TextRenderer& other) noexcept {
			using std::swap;
			swap(other.characters_, characters_);
			swap(other.valid_, valid_);
			swap(other.handle_, handle_);
		}

		struct Character {
				_3D::Texture texture; // Glyph texture
				glm::ivec2 size; // Size of glyph
				glm::ivec2 bearing; // Offset from baseline to left/top of glyph
				FT_Pos advance; // Offset to advance to next glyph

				void swap(Character &other) noexcept {
					using std::swap;
					swap(other.texture, texture);
					swap(other.size, size);
					swap(other.bearing, bearing);
					swap(other.advance, advance);
				}
		};
	protected:
		std::map<char, Character> characters_;

		bool valid_ = false;
		VboHandle handle_;
};

inline void swap(TextRenderer::Character& a, TextRenderer::Character& b) noexcept {
	a.swap(b);
}

inline void swap(TextRenderer& a, TextRenderer& b) noexcept {
	a.swap(b);
}

} /* namespace _2D */
} /* namespace game_engine */

#include "TextRenderer.tpp"

#endif /* SRC_2D_TEXTRENDERER_HPP_ */
