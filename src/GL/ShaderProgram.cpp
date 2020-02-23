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


namespace game_engine {
namespace gl {

bool ShaderProgram::Init() {
	program_ = glCreateProgram();
	return true;
}
void ShaderProgram::AttachShader(Shader& shader) {
	shaders_.push_back(&shader);
	glAttachShader(program_, shader.getShaderHandle());
}

bool ShaderProgram::Link() {
	if(IsValid()) { return IsValid(); }
	glLinkProgram(program_);

	GLint isLinked = 0;
	glGetProgramiv(program_, GL_LINK_STATUS, (int*)&isLinked);
	if(isLinked == GL_FALSE) {
		GLint log_size = 0;
		glGetProgramiv(program_, GL_INFO_LOG_LENGTH, &log_size);
		std::string log_contents;
		log_contents.reserve(log_size);
		glGetProgramInfoLog(program_, log_contents.capacity(), &log_size, &log_contents[0]);
		LOG_E("Program linking failed!  Program log output follows:");
		LOG_E(log_contents);
		glDeleteProgram(program_);
		return (valid_ = false);
	}
	for(auto& i : shaders_) {
		glDetachShader(program_, i->getShaderHandle());
	}
	shaders_.clear();
	return (valid_ = true);
}

bool ShaderProgram::IsValid() const {							return valid_; }
void ShaderProgram::SetValid(bool validity) {					valid_ = validity; }

GLuint ShaderProgram::GetProgramHandle() {					return program_; }
GLuint ShaderProgram::GetPh() {								return GetProgramHandle(); }

void ShaderProgram::UseProgram() const {
	glUseProgram(program_);
}
void ShaderProgram::Use() const {
	UseProgram();
}

void ShaderProgram::SetBool(const std::string &name, bool value) const {
	if(!IsValid()) { return; }
	Use();
	glUniform1i(glGetUniformLocation(program_, name.c_str()), (int)value);
}
void ShaderProgram::SetInt(const std::string &name, int value) const {
	if(!IsValid()) { return; }
	Use();
	glUniform1i(glGetUniformLocation(program_, name.c_str()), value);
}
void ShaderProgram::SetFloat(const std::string &name, float value) const {
	if(!IsValid()) { return; }
	Use();
	glUniform1f(glGetUniformLocation(program_, name.c_str()), value);
}
void ShaderProgram::SetVec2(const std::string &name, const glm::vec2 &value) const {
	if(!IsValid()) { return; }
	Use();
	glUniform2fv(glGetUniformLocation(program_, name.c_str()), 1, &value[0]);
}
void ShaderProgram::SetVec2(const std::string &name, float x, float y) const {
	if(!IsValid()) { return; }
	Use();
	glUniform2f(glGetUniformLocation(program_, name.c_str()), x, y);
}
void ShaderProgram::SetVec3(const std::string &name, const glm::vec3 &value) const {
	if(!IsValid()) { return; }
	Use();
	glUniform3fv(glGetUniformLocation(program_, name.c_str()), 1, &value[0]);
}
void ShaderProgram::SetVec3(const std::string &name, float x, float y, float z) const {
	if(!IsValid()) { return; }
	Use();
	glUniform3f(glGetUniformLocation(program_, name.c_str()), x, y, z);
}
void ShaderProgram::SetVec4(const std::string &name, const glm::vec4 &value) const {
	if(!IsValid()) { return; }
	Use();
	glUniform4fv(glGetUniformLocation(program_, name.c_str()), 1, &value[0]);
}
void ShaderProgram::SetVec4(const std::string &name, float x, float y, float z, float w) const {
	if(!IsValid()) { return; }
	Use();
	glUniform4f(glGetUniformLocation(program_, name.c_str()), x, y, z, w);
}
void ShaderProgram::SetMat2(const std::string &name, const glm::mat2 &mat) const {
	if(!IsValid()) { return; }
	Use();
	glUniformMatrix2fv(glGetUniformLocation(program_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void ShaderProgram::SetMat3(const std::string &name, const glm::mat3 &mat) const {
	if(!IsValid()) { return; }
	Use();
	glUniformMatrix3fv(glGetUniformLocation(program_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void ShaderProgram::SetMat4(const std::string &name, const glm::mat4 &mat) const {
	if(!IsValid()) { return; }
	Use();
	glUniformMatrix4fv(glGetUniformLocation(program_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

} /* namespace gl */
} /* namespace game_engine */

