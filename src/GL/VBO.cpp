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

#include "VBO.hpp"

#include <GL/glew.h>

namespace GameEngine {
namespace GL {

void VBO::init(ShaderPrograms shader) {
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	shaders = shader;
}

void VBO::bind() {
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
}

void VBO::allocate(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices) {
	bind();
	n_vertices = vertices.size();
	n_indices = indices.size();
	if(n_vertices != 0) {
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_DYNAMIC_DRAW);
	}
	if(n_indices != 0) {
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),  &indices[0], GL_DYNAMIC_DRAW);
	}
	addVertexPointers();
}

void VBO::update(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices) {
	bind();
	if(std::min(n_vertices, vertices.size()) != 0) {
		glBufferSubData(GL_ARRAY_BUFFER, 0, std::min(n_vertices, vertices.size()) * sizeof(Vertex), &vertices[0]);
	}
	if(std::min(n_indices, indices.size()) != 0) {
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, std::min(n_indices, indices.size()), &indices[0]);
	}
}
void VBO::addVertexPointer(GLuint id, size_t vec_size, GLenum type, size_t stride, size_t offset) {
	bind();
	glVertexAttribPointer(id, vec_size, type, GL_FALSE, stride, (void*)offset);
	glEnableVertexAttribArray(id);
}
void VBO::addVertexPointers() {
	addVertexPointer(0,  3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, position));
	addVertexPointer(2,  3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, normal));
	addVertexPointer(3,  4, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, color));
	addVertexPointer(4,  4, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, secondary_color));
	addVertexPointer(5,  3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, tangent));
	addVertexPointer(6,  3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, bitangent));
	addVertexPointer(7,  2, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, tex_coord0));
	addVertexPointer(8,  2, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, tex_coord1));
	addVertexPointer(9,  2, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, tex_coord2));
	addVertexPointer(10, 2, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, tex_coord3));
	addVertexPointer(11, 2, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, tex_coord4));
	addVertexPointer(12, 2, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, tex_coord5));
	addVertexPointer(13, 2, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, tex_coord6));
	addVertexPointer(14, 2, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, tex_coord7));
	addVertexPointer(15, 1, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, fog_coord));
}

} /* namespace GL */
} /* namespace GameEngine */


