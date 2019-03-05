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

enum class ResourceID : size_t;
enum class ResourceType : size_t;
class Resource {
	public:
		ResourceID id;
		ResourceType type;
		const char* file_path;
};

namespace GameEngine {

Shader::Shader(Resource resource, ShaderType _type) :
		type(_type),
		file_path(resource.file_path),
		shader(glCreateShader(static_cast<GLenum>(_type))),
		valid(false) {
	char *base_path = SDL_GetBasePath();
}
Shader::~Shader() {
	if(isValid()) {
		glDeleteShader(shader);
	}
	valid = false;
}

bool Shader::init() {
	if(isValid()) {
		return isValid();
	}
	std::string file_location;
	char *base_path = SDL_GetBasePath();
	if (base_path) {
		file_location = base_path;
	} else {
		file_location = SDL_strdup("./");
	}
	file_location+=file_path;
	std::ifstream file(file_location);
	std::string source((std::istreambuf_iterator<char>(file)),
			std::istreambuf_iterator<char>());
	const char* c_str = source.c_str();
	glShaderSource(shader, 1, &c_str, NULL);
	glCompileShader(shader);

	GLint isCompiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

	if(isCompiled == GL_FALSE) {
		GLint log_size = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_size);
		std::string log_contents;
		log_contents.reserve(log_size);
		glGetShaderInfoLog(shader, log_contents.capacity(), &log_size, log_contents.data());
		LOG_E("Shader of type " << type << " failed to compile!  Shader compiler log output follows:");
		LOG_E(log_contents);
		LOG_E("Shading language version = " << glGetString(GL_SHADING_LANGUAGE_VERSION));
		glDeleteShader(shader);
		valid = false;
		return valid;
	}
	valid = true;
	return valid;
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

} /* namespace GameEngine */

