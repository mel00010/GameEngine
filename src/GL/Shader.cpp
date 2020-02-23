/******************************************************************************
 * Shader.cpp
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

#include "Shader.hpp"

#include <Log.hpp>

#include <SDL2/SDL.h>

#include <fstream>
#include <streambuf>

namespace game_engine {
namespace gl {

Shader::Shader(std::string _source, ShaderType _type) :
		source(_source), type(_type), shader(0), valid(false) {
}

Shader::~Shader() noexcept {
	if (isValid()) {
//		LOG_D("shader = " << shader);
		glDeleteShader(shader);
	}
	valid = false;
}

bool Shader::Init() {
	if (isValid()) {
		return isValid();
	}
	shader = glCreateShader(static_cast<GLenum>(type));

	const char* c_str = source.c_str();
	glShaderSource(shader, 1, &c_str, NULL);
	glCompileShader(shader);

	GLint isCompiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_FALSE) {
		GLint log_size = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_size);
		std::string log_contents;
		log_contents.reserve(log_size);
		glGetShaderInfoLog(shader, log_contents.capacity(), &log_size, &log_contents[0]);
		LOG_E("Shader of type " << type << " failed to compile!  Shader compiler log output follows:");
		LOG_E(log_contents);
		LOG_E("Shading language version = " << glGetString(GL_SHADING_LANGUAGE_VERSION));
		glDeleteShader(shader);
		return (valid = false);
	}
	return (valid = true);
}

bool Shader::isValid() const {
	return valid;
}
ShaderType Shader::getShaderType() {
	return type;
}
GLuint Shader::getShaderHandle() {
	return shader;
}

} /* namespace gl */
} /* namespace game_engine */
