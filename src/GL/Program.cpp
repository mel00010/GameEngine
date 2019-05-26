/******************************************************************************
 * Program.cpp
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

#include "Program.hpp"

#include "Attribute.hpp"
#include "Shader.hpp"

#include <Log.hpp>


namespace GameEngine {
namespace GL {

Program::Program() : program(-1), valid(false) { }
Program::~Program() { }

bool Program::init() {
	program = glCreateProgram();
	return true;
}
void Program::attachShader(ShaderRef shader) {
	shaders.push_back(shader);
	glAttachShader(program, shader->getShaderHandle());
}

bool Program::link() {
	if(isValid()) { return isValid(); }
	glLinkProgram(program);

	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
	if(isLinked == GL_FALSE) {
		GLint log_size = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_size);
		std::string log_contents;
		log_contents.reserve(log_size);
		glGetProgramInfoLog(program, log_contents.capacity(), &log_size, log_contents.data());
		LOG_E("Program linking failed!  Program log output follows:");
		LOG_E(log_contents);
		glDeleteProgram(program);
		return (valid = false);
	}
	for(auto i : shaders) {
		glDetachShader(program, i->getShaderHandle());
	}
	shaders.clear();
	return (valid = true);
}

bool Program::isValid() const {							return valid; }
void Program::setValid(bool validity) {					valid = validity; }

GLuint Program::getProgramHandle() {					return program; }
GLuint Program::getPH() {								return getProgramHandle(); }

void Program::addAttribute(AttributeRef attribute) {	attributes.push_back(attribute); }
std::vector<AttributeRef>& Program::getAttributes() {	return attributes; }

void Program::useProgram() {
	glUseProgram(program);
}
void Program::use() {
	useProgram();
}

void Program::setBool(const std::string &name, bool value) const {
	if(!isValid()) { return; }
	glUniform1i(glGetUniformLocation(program, name.c_str()), (int)value);
}
void Program::setInt(const std::string &name, int value) const {
	if(!isValid()) { return; }
	glUniform1i(glGetUniformLocation(program, name.c_str()), value);
}
void Program::setFloat(const std::string &name, float value) const {
	if(!isValid()) { return; }
	glUniform1f(glGetUniformLocation(program, name.c_str()), value);
}
void Program::setVec2(const std::string &name, const glm::vec2 &value) const {
	if(!isValid()) { return; }
	glUniform2fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]);
}
void Program::setVec2(const std::string &name, float x, float y) const {
	if(!isValid()) { return; }
	glUniform2f(glGetUniformLocation(program, name.c_str()), x, y);
}
void Program::setVec3(const std::string &name, const glm::vec3 &value) const {
	if(!isValid()) { return; }
	glUniform3fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]);
}
void Program::setVec3(const std::string &name, float x, float y, float z) const {
	if(!isValid()) { return; }
	glUniform3f(glGetUniformLocation(program, name.c_str()), x, y, z);
}
void Program::setVec4(const std::string &name, const glm::vec4 &value) const {
	if(!isValid()) { return; }
	glUniform4fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]);
}
void Program::setVec4(const std::string &name, float x, float y, float z, float w) const {
	if(!isValid()) { return; }
	glUniform4f(glGetUniformLocation(program, name.c_str()), x, y, z, w);
}
void Program::setMat2(const std::string &name, const glm::mat2 &mat) const {
	if(!isValid()) { return; }
	glUniformMatrix2fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void Program::setMat3(const std::string &name, const glm::mat3 &mat) const {
	if(!isValid()) { return; }
	glUniformMatrix3fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void Program::setMat4(const std::string &name, const glm::mat4 &mat) const {
	if(!isValid()) { return; }
	glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

} /* namespace GL */
} /* namespace GameEngine */

