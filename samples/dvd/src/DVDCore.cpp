/******************************************************************************
 * DVDCore.cpp
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

#include "DVDCore.hpp"

#include <GameCore.hpp>

#include <Attribute.hpp>
#include <Shader.hpp>

#include <Log.hpp>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/random.hpp>

#include <Resources.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <algorithm>
#include <functional>
#include <numeric>

using namespace GameEngine;

void DVDCore::setup() {
	/* SDL-related initialising functions */
	SDL_Init(SDL_INIT_VIDEO);
	int flags = IMG_INIT_JPG | IMG_INIT_PNG;
	if( !( IMG_Init( flags ) & flags ) ) {
		LOG_F( "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() );
		throw EXIT_FAILURE;
	}

	// Request an OpenGL 4.5 context (should be core)
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	// Also request a depth buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	window = SDL_CreateWindow("DVD",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		1920, 1080,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	SDL_GL_CreateContext(window);
	enableVSync();

	/* Extension wrangler initialising */
	glewExperimental = GL_TRUE;
	GLenum glew_status = glewInit();
	if (glew_status != GLEW_OK) {
		LOG_F("Error: glewInit: " << glewGetErrorString(glew_status));
		throw EXIT_FAILURE;
	}

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
		Characters.insert(std::pair<GLchar, Character>(c, character));
	}
	glBindTexture(GL_TEXTURE_2D, 0);


	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	program = std::make_shared<Program>();
	program->init();
	ShaderRef vertex_shader = std::make_shared<Shader>(Resources[static_cast<size_t>(ResourceID::VERTEX_SHADER)], ShaderType::VERTEX);
	ShaderRef fragment_shader = std::make_shared<Shader>(Resources[static_cast<size_t>(ResourceID::FRAGMENT_SHADER)], ShaderType::FRAGMENT);
	vertex_shader->init();
	fragment_shader->init();
	program->attachShader(vertex_shader);
	program->attachShader(fragment_shader);
	program->link();

	/* When all init functions run without errors,
	   the glsl_program can initialise the resources */
	if (!program->isValid()) {
		throw EXIT_FAILURE;
	}

		glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 100 * 4, NULL, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLfloat) * 100 * 4, NULL, GL_DYNAMIC_DRAW);

	// vertex attribute
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	Texture texture;
	texture.loadTexture(Resources[static_cast<size_t>(ResourceID::DVD)]);
	texture1 = texture.texture;

	glUseProgram(program->getPH());
	glUniform1i(glGetUniformLocation(program->getPH(), "text"), 0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(VAO);
	logo_color = glm::abs(glm::sphericalRand(1.0f));
}

void DVDCore::setFullscreen(bool enable) {
	int should_be_zero = SDL_GetDesktopDisplayMode(SDL_GetWindowDisplayIndex(window), &native);

	if(should_be_zero != 0) {
		// In case of error...
		LOG_E("Could not get display mode for video display #"<< SDL_GetWindowDisplayIndex(window) <<": " << SDL_GetError());
		throw EXIT_FAILURE;
	} else {
		// On success, print the current display mode.
		LOG_D("Display #" << SDL_GetWindowDisplayIndex(window) <<": native display mode is " << native.w << "x" << native.h << "px @ " << native.refresh_rate << "hz.");
	}
	isScreenFullscreen = enable;
	if(isScreenFullscreen) {
		current = native;
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
		SDL_SetWindowDisplayMode(window, &current);
	} else {
		current = native;
		SDL_SetWindowFullscreen(window, 0);
	}
}

void DVDCore::render() {
	if(FPS_cap_enabled) {
		for(;;) {
			curr_frame_time = SDL_GetTicks();
			if(curr_frame_time > prev_frame_time + (1000/FPS_cap)) {
				prev_frame_time = curr_frame_time;
				break;
			}
		}
	}
	frames_rendered++;
	total_frames_rendered++;
	int x;
	int y;
	SDL_GetWindowSize(window, &x, &y);
	if(cursor_disabled) {
		SDL_WarpMouseInWindow(window, x/2, y/2);
	}
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(program->getPH());

	renderLogo();

	if(FPS_shown) {
		renderText(fps_to_render, x-80, y-50, 1.0f, text_color);
	}
	SDL_GL_SwapWindow(window);

}

void DVDCore::renderLogo() {
	// bind textures on corresponding texture units
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	float vertices[] = {
		// positions  // texture coords
		 0.5f,  0.5f, 1.0f, 1.0f, // top right
		 0.5f, -0.5f, 1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f, 1.0f, // top left
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(indices), indices);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// create transformations
	glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

	transform = glm::translate(transform, translate_vec);
	transform = glm::scale(transform, glm::vec3(0.5 / scale.x, 0.5 / scale.y, 0.5));

	glm::vec2 pos = glm::vec2(translate_vec.x, translate_vec.y);
	if(std::abs(pos.x - ((scale.x - 0.235)/scale.x)) < length(delta_vec * glm::vec3(speed / (scale.x * fps * 4.0f), speed / (scale.y * fps * 4.0f), 0.0f)) * 0.5) {

		delta_vec = glm::normalize(glm::reflect(delta_vec, glm::vec3(1.0, 0.0, 0.0)
				+ glm::ballRand(0.05f)) * glm::vec3(1.0f, 1.0f, 0.0f));

		logo_color = glm::abs(glm::sphericalRand(1.0f));
	}

	if(std::abs(pos.y - ((scale.y - 0.115)/scale.y)) < length(delta_vec * glm::vec3(speed / (scale.x * fps * 4.0f), speed / (scale.y * fps * 4.0f), 0.0f)) * 0.5) {

		delta_vec = glm::normalize(glm::reflect(delta_vec, glm::vec3(0.0, 1.0, 0.0)
				+ glm::ballRand(0.05f)) * glm::vec3(1.0f, 1.0f, 0.0f));

		logo_color = glm::abs(glm::sphericalRand(1.0f));
	}
	if(std::abs(pos.x + ((scale.x - 0.235)/scale.x)) < length(delta_vec * glm::vec3(speed / (scale.x * fps * 4.0f), speed / (scale.y * fps * 4.0f), 0.0f)) * 0.5) {

		delta_vec = glm::normalize(glm::reflect(delta_vec, glm::vec3(1.0, 0.0, 0.0)
				+ glm::ballRand(0.05f)) * glm::vec3(1.0f, 1.0f, 0.0f));
		logo_color = glm::abs(glm::sphericalRand(1.0f));
	}
	if(std::abs(pos.y + ((scale.y - 0.115)/scale.y)) < length(delta_vec * glm::vec3(speed / (scale.x * fps * 4.0f), speed / (scale.y * fps * 4.0f), 0.0f)) * 0.5) {

		delta_vec = glm::normalize(glm::reflect(delta_vec, glm::vec3(0.0, 1.0, 0.0)
				+ glm::ballRand(0.05f)) * glm::vec3(1.0f, 1.0f, 0.0f));

		logo_color = glm::abs(glm::sphericalRand(1.0f));
	}
	translate_vec += delta_vec * glm::vec3(speed / (scale.x * fps * 4.0f), speed / (scale.y * fps * 4.0f), 0.0f);
	glUniform3fv(glGetUniformLocation(program->getPH(), "color"), 1, (float*)glm::value_ptr(logo_color));

	// get matrix's uniform location and set matrix
	unsigned int transformLoc = glGetUniformLocation(program->getPH(), "projection");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

	// render container
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void DVDCore::renderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color) {
	int w;
	int h;
	SDL_GetWindowSize(window, &w, &h);
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(w), 0.0f, static_cast<GLfloat>(h));
	glUniformMatrix4fv(glGetUniformLocation(program->getPH(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	// Activate corresponding render state
	glUniform3f(glGetUniformLocation(program->getPH(), "color"), color.x, color.y, color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	// Iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++) {
		Character ch = Characters[*c];

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
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void DVDCore::tick() {
	SDL_Event ev;
	tick_counter++;

	fps = static_cast<double>(frames_rendered) * static_cast<double>(ticks_per_second);
	fps_avg = std::accumulate(fps_avg_array.begin(), fps_avg_array.end(), 0) / 20;
	fps_avg_array[pos] = fps;
	if (pos == 19) {
		pos = 0;
	} else {
		pos++;
	}
	if(tick_counter > ticks_per_second/10) {
//		LOG_D("FPS:  " << fps //<< " | Frames rendered this tick: " << frames_rendered
//				<< " | ms/frame = " << static_cast<double>(ms_per_tick)/static_cast<double>(frames_rendered));
//		LOG_D("translate_vec = " << translate_vec << " | delta_vec = " << delta_vec);

		tick_counter = 0;
		std::stringstream ss;
		ss << std::fixed << std::setprecision(0) << fps_avg;
		fps_to_render = ss.str();
	}

	frames_rendered = 0;

	while (SDL_PollEvent(&ev)) {
		switch(ev.type) {
			case SDL_WINDOWEVENT:
				for(auto& i: window_event_callbacks) {
					i(ev.window);
				}
				break;
			case SDL_KEYDOWN:
				if(ev.key.repeat != 0) {
					break;
				}
				key_status[ev.key.keysym.scancode] = true;
				for(auto& i: key_down_callbacks[ev.key.keysym.scancode]) {
					i(ev.key);
				}
				break;
			case SDL_KEYUP:
				key_status[ev.key.keysym.scancode] = false;
				for(auto& i: key_up_callbacks[ev.key.keysym.scancode]) {
					i(ev.key);
				}
				break;
			case SDL_MOUSEMOTION:
				for(auto& i: m_move_callbacks) {
					i(ev.motion, ivec2(ev.motion.x, ev.motion.y), ivec2(ev.motion.xrel, ev.motion.yrel));
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				mouse_buttons_status[ev.button.button] = true;
				for(auto& i: m_button_down_callbacks[ev.button.button]) {
					i(ev.button, ivec2(ev.button.x, ev.button.y));
				}
				break;
			case SDL_MOUSEBUTTONUP:
				mouse_buttons_status[ev.button.button] = false;
				for(auto& i: m_button_up_callbacks[ev.button.button]) {
					i(ev.button, ivec2(ev.button.x, ev.button.y));
				}
				break;
			case SDL_MOUSEWHEEL:
				for(auto& i: m_wheel_callbacks) {
					i(ev.wheel, ivec2(ev.wheel.x, ev.wheel.y));
				}
				break;
		}
		for(auto& callback_pair : event_callbacks) {
			if(callback_pair.first(ev)) {
				callback_pair.second(ev);
			}
		}
		for(size_t i = 0; i < key_held_callbacks.size(); i++) {
			if(key_status[i]) {
				for(auto& callback : key_held_callbacks[i]) {
					callback();
				}
			}
		}
		for(size_t i = 0; i < m_button_held_callbacks.size(); i++) {
			if(mouse_buttons_status[i]) {
				for(auto& callback : m_button_held_callbacks[i]) {
					callback();
				}
			}
		}
	}
}

