/******************************************************************************
 * VBO.cpp
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

#include "Vbo.hpp"

#include <GL/glew.h>

namespace game_engine {
namespace gl {

void Vbo::Init(ShaderPrograms shader) {
	glGenVertexArrays(1, &vao_);
	glGenBuffers(1, &vbo_);
	glGenBuffers(1, &ebo_);
	shaders_ = shader;
}

void Vbo::Bind() {
	glBindVertexArray(vao_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
}

void Vbo::Allocate(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices) {
	Bind();
	n_vertices_ = vertices.size();
	n_indices_ = indices.size();
	if(n_vertices_ != 0) {
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_DYNAMIC_DRAW);
	}
	if(n_indices_ != 0) {
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),  &indices[0], GL_DYNAMIC_DRAW);
	}
	AddVertexPointers();
}

void Vbo::Update(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices) {
	Bind();
	if(std::min(n_vertices_, vertices.size()) != 0) {
		glBufferSubData(GL_ARRAY_BUFFER, 0, std::min(n_vertices_, vertices.size()) * sizeof(Vertex), &vertices[0]);
	}
	if(std::min(n_indices_, indices.size()) != 0) {
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, std::min(n_indices_, indices.size()), &indices[0]);
	}
}
void Vbo::AddVertexPointer(GLuint id, size_t vec_size, GLenum type, size_t stride, size_t offset) {
	Bind();
	glVertexAttribPointer(id, vec_size, type, GL_FALSE, stride, (void*)offset);
	glEnableVertexAttribArray(id);
}
void Vbo::AddVertexPointers() {
	AddVertexPointer(0,  3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, position));
	AddVertexPointer(2,  3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, normal));
	AddVertexPointer(3,  4, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, color));
	AddVertexPointer(4,  4, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, secondary_color));
	AddVertexPointer(5,  3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, tangent));
	AddVertexPointer(6,  3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, bitangent));
	AddVertexPointer(7,  2, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, tex_coord0));
	AddVertexPointer(8,  2, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, tex_coord1));
	AddVertexPointer(9,  2, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, tex_coord2));
	AddVertexPointer(10, 2, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, tex_coord3));
	AddVertexPointer(11, 2, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, tex_coord4));
	AddVertexPointer(12, 2, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, tex_coord5));
	AddVertexPointer(13, 2, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, tex_coord6));
	AddVertexPointer(14, 2, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, tex_coord7));
	AddVertexPointer(15, 1, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, fog_coord));
}

} /* namespace gl */
} /* namespace game_engine */


