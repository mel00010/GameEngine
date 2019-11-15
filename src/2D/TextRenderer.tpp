/******************************************************************************
 * TextRenderer.tpp
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
#ifndef SRC_2D_TEXTRENDERER_TPP_
#define SRC_2D_TEXTRENDERER_TPP_

#include "TextRenderer.hpp"

#include <Renderer.hpp>
#include <Vertex.hpp>

#include <glm/glm.hpp>
#include <Log.hpp>
#include <string>
#include <vector>

namespace GameEngine {
namespace _2D {

template<typename Renderer>
void TextRenderer::init(Renderer& renderer) {
	FT_Library ft;
	FT_Face face;

	if (FT_Init_FreeType(&ft)) {
		LOG_E("Freetype:  Could not init FreeType Library");
		throw EXIT_FAILURE;
	}

	if (FT_New_Face(ft, "/usr/share/fonts/truetype/msttcorefonts/arial.ttf", 0, &face)) {
		LOG_E("Freetype: Failed to load font");
		throw EXIT_FAILURE;
	}
	FT_Set_Pixel_Sizes(face, 0, 48);
	if (FT_Load_Char(face, 'X', FT_LOAD_RENDER)) {
		LOG_E("Freetype: Failed to load Glyph");
		throw EXIT_FAILURE;
	}

	renderer.disable_byte_alignement_restriction();

	for (uint8_t c = 0; c < 128; c++) {

		// Load character glyph
		if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
			LOG_E("Freetype: Failed to load Glyph");
			continue;
		}

		FT_Bitmap bitmap = face->glyph->bitmap;

		// Generate texture
		_3D::Texture texture;
		texture.loadTextureFromMemory(
				renderer,
				glm::ivec2(bitmap.width, bitmap.rows),
				_3D::PixelFormat {GL_RED, GL_RED},
				bitmap.buffer,
				ShaderPrograms::TEXT,
				_3D::TextureType::DIFFUSE);


		// Now store character for later use
		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		characters.insert(std::pair<GLchar, Character>(c, character));
	}
	renderer.disable_byte_alignement_restriction();

	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	// Update VBO for each character
	std::vector<Vertex> vertices = {
			Vertex(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)), // top right
			Vertex(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)), // bottom right
			Vertex(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)), // bottom left
			Vertex(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f))  // top left
	};
	std::vector<GLuint> indices = {
			0, 1, 3,
			1, 2, 3
	};

	handle = renderer.generateVBO(ShaderPrograms::TEXT, vertices, indices);
	valid = true;
}

template<typename Renderer>
void TextRenderer::renderTextRelativeToTopRight(Renderer& renderer,
		std::string text, float x, float y, float scale, glm::vec3 color) {
	glm::ivec2 size = renderer.getWindowSize();
	renderText(renderer, text, size.x - x, size.y - y, scale, color);
}
template<typename Renderer>
void TextRenderer::renderText(Renderer& renderer,
		std::string text, float x, float y, float scale, glm::vec3 color) {
	renderer.useShader(ShaderPrograms::TEXT);
	renderer.enable_blending();
	if(!valid) {
		LOG_E("Text renderer not valid!");
		return;
	}

	glm::ivec2 size = renderer.getWindowSize();

	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(size.x), 0.0f, static_cast<float>(size.y));
	renderer.setMatrices(ShaderPrograms::TEXT, glm::mat4(1), glm::mat4(1), projection);

	// Activate corresponding render state
	renderer.setColor(ShaderPrograms::TEXT, glm::vec4(color, 1.0));
	// Iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++) {
		Character ch = characters[*c];

		float xpos = x + ch.Bearing.x * scale;
		float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		float w = ch.Size.x * scale;
		float h = ch.Size.y * scale;
		std::vector<Vertex> vertices = {
				Vertex(glm::vec3(xpos + w, ypos,     1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)), // top right
				Vertex(glm::vec3(xpos + w, ypos + h, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)), // bottom right
				Vertex(glm::vec3(xpos,     ypos + h, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)), // bottom left
				Vertex(glm::vec3(xpos,     ypos,     1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f))  // top left
		};
		std::vector<GLuint> indices = {
				0, 1, 3,
				1, 2, 3
		};
		// Render glyph texture over quad
		renderer.bindTexture(ShaderPrograms::TEXT, "texture_diffuse0", ch.Texture, 0);
//		renderer.setSwizzleMask(GL_RED, GL_RED, GL_RED, GL_ONE);
		// Update content of VBO memory
		handle = renderer.updateVBO(handle, vertices, indices);

		// Render quad
		renderer.render(handle, _3D::Primitive::TRIANGLES);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
	}
	renderer.disable_blending();

//	renderer.setSwizzleMask(GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA);
	renderer.useShader(ShaderPrograms::DEFAULT);
}


} /* namespace _2D */
} /* namespace GameEngine */

#endif /* SRC_2D_TEXTRENDERER_TPP_ */
