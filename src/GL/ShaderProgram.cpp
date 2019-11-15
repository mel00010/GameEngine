/******************************************************************************
 * ShaderProgram.cpp
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
#include "ShaderProgram.hpp"

#include <Log.hpp>


namespace GameEngine {
namespace GL {

ShaderProgram::ShaderProgram() : program(0), valid(false) { }
ShaderProgram::~ShaderProgram() { }

bool ShaderProgram::init() {
	program = glCreateProgram();
	return true;
}
void ShaderProgram::attachShader(Shader& shader) {
	shaders.push_back(&shader);
	glAttachShader(program, shader.getShaderHandle());
}

bool ShaderProgram::link() {
	if(isValid()) { return isValid(); }
	glLinkProgram(program);

	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
	if(isLinked == GL_FALSE) {
		GLint log_size = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_size);
		std::string log_contents;
		log_contents.reserve(log_size);
		glGetProgramInfoLog(program, log_contents.capacity(), &log_size, &log_contents[0]);
		LOG_E("Program linking failed!  Program log output follows:");
		LOG_E(log_contents);
		glDeleteProgram(program);
		return (valid = false);
	}
	for(auto& i : shaders) {
		glDetachShader(program, i->getShaderHandle());
	}
	shaders.clear();
	return (valid = true);
}

bool ShaderProgram::isValid() const {							return valid; }
void ShaderProgram::setValid(bool validity) {					valid = validity; }

GLuint ShaderProgram::getProgramHandle() {					return program; }
GLuint ShaderProgram::getPH() {								return getProgramHandle(); }

void ShaderProgram::useProgram() const {
	glUseProgram(program);
}
void ShaderProgram::use() const {
	useProgram();
}

void ShaderProgram::setBool(const std::string &name, bool value) const {
	if(!isValid()) { return; }
	use();
	glUniform1i(glGetUniformLocation(program, name.c_str()), (int)value);
}
void ShaderProgram::setInt(const std::string &name, int value) const {
	if(!isValid()) { return; }
	use();
	glUniform1i(glGetUniformLocation(program, name.c_str()), value);
}
void ShaderProgram::setFloat(const std::string &name, float value) const {
	if(!isValid()) { return; }
	use();
	glUniform1f(glGetUniformLocation(program, name.c_str()), value);
}
void ShaderProgram::setVec2(const std::string &name, const glm::vec2 &value) const {
	if(!isValid()) { return; }
	use();
	glUniform2fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]);
}
void ShaderProgram::setVec2(const std::string &name, float x, float y) const {
	if(!isValid()) { return; }
	use();
	glUniform2f(glGetUniformLocation(program, name.c_str()), x, y);
}
void ShaderProgram::setVec3(const std::string &name, const glm::vec3 &value) const {
	if(!isValid()) { return; }
	use();
	glUniform3fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]);
}
void ShaderProgram::setVec3(const std::string &name, float x, float y, float z) const {
	if(!isValid()) { return; }
	use();
	glUniform3f(glGetUniformLocation(program, name.c_str()), x, y, z);
}
void ShaderProgram::setVec4(const std::string &name, const glm::vec4 &value) const {
	if(!isValid()) { return; }
	use();
	glUniform4fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]);
}
void ShaderProgram::setVec4(const std::string &name, float x, float y, float z, float w) const {
	if(!isValid()) { return; }
	use();
	glUniform4f(glGetUniformLocation(program, name.c_str()), x, y, z, w);
}
void ShaderProgram::setMat2(const std::string &name, const glm::mat2 &mat) const {
	if(!isValid()) { return; }
	use();
	glUniformMatrix2fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void ShaderProgram::setMat3(const std::string &name, const glm::mat3 &mat) const {
	if(!isValid()) { return; }
	use();
	glUniformMatrix3fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void ShaderProgram::setMat4(const std::string &name, const glm::mat4 &mat) const {
	if(!isValid()) { return; }
	use();
	glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

} /* namespace GL */
} /* namespace GameEngine */

