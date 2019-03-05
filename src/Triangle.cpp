/******************************************************************************
 * Triangle.cpp
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

#include "Triangle.hpp"

#include "Attribute.hpp"
#include "Program.hpp"
#include "Shader.hpp"

#include <Resources.hpp>

#include <GL/glew.h>

#include <Log.hpp>

namespace GameEngine {

//GLuint program;
//GLint attribute_coord2d;


//bool init_resources(void) {
//	GLint compile_ok = GL_FALSE, link_ok = GL_FALSE;
//
//	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
//
//	// GLSL version
//	const char* version;
//	int profile;
//	SDL_GL_GetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, &profile);
//	if (profile == SDL_GL_CONTEXT_PROFILE_ES)
//		version = "#version 100\n";  // OpenGL ES 2.0
//	else
//		version = "#version 120\n";  // OpenGL 2.1
//
//	const GLchar* vs_sources[] = {
//		version,
//		"attribute vec2 coord2d;                  "
//		"void main(void) {                        "
//		"  gl_Position = vec4(coord2d, 0.0, 1.0); "
//		"}"
//	};
//	glShaderSource(vs, 2, vs_sources, NULL);
//	glCompileShader(vs);
//	glGetShaderiv(vs, GL_COMPILE_STATUS, &compile_ok);
//	if (!compile_ok) {
//		LOG_F("Error in vertex shader");
//		return false;
//	}
//
//	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
//	const GLchar* fs_sources[] = {
//		version,
//		"void main(void) {        "
//		"  gl_FragColor[0] = 0.0; "
//		"  gl_FragColor[1] = 0.0; "
//		"  gl_FragColor[2] = 1.0; "
//		"}"
//	};
//	glShaderSource(fs, 2, fs_sources, NULL);
//	glCompileShader(fs);
//	glGetShaderiv(fs, GL_COMPILE_STATUS, &compile_ok);
//	if (!compile_ok) {
//		LOG_F("Error in fragment shader");
//		return false;
//	}
//
//	program = glCreateProgram();
//	glAttachShader(program, vs);
//	glAttachShader(program, fs);
//	glLinkProgram(program);
//	glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
//	if (!link_ok) {
//		LOG_F("Error in glLinkProgram");
//		return false;
//	}
//
//	const char* attribute_name = "coord2d";
//	attribute_coord2d = glGetAttribLocation(program, attribute_name);
//	if (attribute_coord2d == -1) {
//		LOG_F("Could not bind attribute " << attribute_name);
//		return false;
//	}
//
//	return true;
//
//}

ProgramRef init_program() {
	ProgramRef program = std::make_shared<Program>();
	ShaderRef vertex_shader = std::make_shared<Shader>(ResourceID::VERTEX_SHADER, ShaderType::VERTEX);
	ShaderRef fragment_shader = std::make_shared<Shader>(ResourceID::FRAGMENT_SHADER, ShaderType::FRAGMENT);
	AttributeRef coord2d = std::make_shared<Attribute>("coord2d");

	if(!vertex_shader->init()) {
		return program;
	}
	if(!fragment_shader->init()) {
		return program;
	}
	program->attachShader(vertex_shader);
	program->attachShader(fragment_shader);
	if(!program->link()) {
		return program;
	}
	if(!coord2d->init(program)) {
		program->setValid(false);
		return program;
	}
	program->addAttribute(coord2d);
	return program;
}

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

void main_loop(SDL_Window* window, ProgramRef program) {
	while (true) {
		SDL_Event ev;
		while (SDL_PollEvent(&ev)) {
			if (ev.type == SDL_QUIT)
				return;
		}
		render(window, program);
	}
}

} /* namespace GameEngine */

