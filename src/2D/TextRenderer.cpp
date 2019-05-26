/******************************************************************************
 * TextRenderer.cpp
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

#include "TextRenderer.hpp"

#include <GL/Program.hpp>
#include <GL/Shader.hpp>
#include <GL/WindowManager.hpp>

#include <Log.hpp>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace GameEngine {
namespace _2D {

TextRenderer::TextRenderer() : window(nullptr), valid(false) {}

void TextRenderer::init(SDL_Window* _window) {
	p = std::make_shared<GL::Program>();
	p->init();
	std::string vertex =
			"#version 450\n"
			"layout (location = 0) in vec2 pos;\n"
			"layout (location = 1) in vec2 tex;\n"
			"out vec2 TexCoord;\n"
			"uniform mat4 projection;\n"
			"void main() {\n"
			"	gl_Position = projection * vec4(pos, 1.0f, 1.0f);\n"
			"	TexCoord = tex;\n"
			"}";
	std::string fragment =
			"#version 450\n"
			"out vec4 oColor;\n"
			"in vec2 TexCoord;\n"
			"uniform sampler2D text;\n"
			"uniform vec3 color;\n"
			"void main() {\n"
			"	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoord).r);\n"
			"	oColor = vec4(color, 1.0) * sampled;\n"
			"}";
	GL::ShaderRef vertex_shader = std::make_shared<GL::Shader>(vertex, GL::ShaderType::VERTEX);
	GL::ShaderRef fragment_shader = std::make_shared<GL::Shader>(fragment, GL::ShaderType::FRAGMENT);
	vertex_shader->init();
	fragment_shader->init();
	p->attachShader(vertex_shader);
	p->attachShader(fragment_shader);
	p->link();

	/* When all init functions run without errors,
	   the glsl_program can initialise the resources */
	if (!p->isValid()) { throw EXIT_FAILURE; }
	p->useProgram();
	window = _window;

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

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

	for (GLubyte c = 0; c < 128; c++) {
		// Load character glyph
		if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
			LOG_E("Freetype: Failed to load Glyph");
			continue;
		}
		// Generate texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Now store character for later use
		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		characters.insert(std::pair<GLchar, Character>(c, character));
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	gl.init();
	gl.bind();
	gl.allocate(sizeof(float) * 6 * 4, sizeof(float) * 6 * 4);

	// vertex attribute
	gl.addVertexPointer(0, 2, GL_FLOAT, sizeof(GLfloat) * 4, 0);
	gl.addVertexPointer(1, 2, GL_FLOAT, sizeof(GLfloat) * 4, sizeof(GLfloat) * 2);

	valid = true;
}
void TextRenderer::renderTextRelativeToTopRight(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color) {
	glm::ivec2 size = GL::WindowManager::getWindowSize(window);
	renderText(text, size.x - x, size.y - y, scale, color);
}

void TextRenderer::renderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color) {
	glEnable(GL_BLEND);

	if(!valid) { return; }
	p->useProgram();
	gl.bind();

	glm::ivec2 size = GL::WindowManager::getWindowSize(window);
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(size.x), 0.0f, static_cast<GLfloat>(size.y));
	glUniformMatrix4fv(glGetUniformLocation(p->getPH(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	// Activate corresponding render state
	glUniform3f(glGetUniformLocation(p->getPH(), "color"), color.x, color.y, color.z);
	glActiveTexture(GL_TEXTURE0);

	// Iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++) {
		Character ch = characters[*c];

		GLfloat xpos = x + ch.Bearing.x * scale;
		GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		GLfloat w = ch.Size.x * scale;
		GLfloat h = ch.Size.y * scale;
		// Update VBO for each character
		GLfloat vertices[6][4] = {
			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 1.0 },

			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 0.0 }
		};
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// Update content of VBO memory
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_BLEND);

}

} /* namespace _2D */
} /* namespace GameEngine */

