/******************************************************************************
 * Vertex.hpp
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
#ifndef SRC_VERTEX_HPP_
#define SRC_VERTEX_HPP_

#include "GL.hpp"

#include <glm/gtx/euler_angles.hpp>

namespace GameEngine {

struct Vertex {
	glm::vec4 position;
	glm::vec4 normal;
	glm::vec4 color;
	glm::vec4 secondary_color;
	glm::vec4 tangent;
	glm::vec4 bitangent;
	glm::vec4 tex_coord0;
	glm::vec4 tex_coord1;
	glm::vec4 tex_coord2;
	glm::vec4 tex_coord3;
	glm::vec4 tex_coord4;
	glm::vec4 tex_coord5;
	glm::vec4 tex_coord6;
	glm::vec4 tex_coord7;
	glm::vec4 tex_coord8;
	glm::vec4 tex_coord9;
	glm::vec4 tex_coord10;
	glm::vec4 tex_coord11;
	glm::vec4 tex_coord12;
	glm::vec4 tex_coord13;
	glm::vec4 tex_coord14;
	glm::vec4 tex_coord15;
	GLfloat fog_coord;

	Vertex(glm::vec4 _pos, glm::vec4 _norm, glm::vec4 _tex) : position(_pos), normal(_norm), tex_coord0(_tex) {}
	static void addVertexPointers(GL& gl) {
		gl.addVertexPointer(0,  4, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, position));
		gl.addVertexPointer(1,  4, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, normal));
		gl.addVertexPointer(2,  4, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, color));
		gl.addVertexPointer(4,  4, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, secondary_color));
		gl.addVertexPointer(5,  4, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, fog_coord));
		gl.addVertexPointer(6,  4, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, tangent));
		gl.addVertexPointer(7,  4, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, bitangent));
		gl.addVertexPointer(8,  4, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, tex_coord0));
		gl.addVertexPointer(9,  4, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, tex_coord1));
		gl.addVertexPointer(10, 4, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, tex_coord2));
		gl.addVertexPointer(11, 4, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, tex_coord3));
		gl.addVertexPointer(12, 4, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, tex_coord4));
		gl.addVertexPointer(13, 4, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, tex_coord5));
		gl.addVertexPointer(14, 4, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, tex_coord6));
		gl.addVertexPointer(15, 4, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, tex_coord7));
		gl.addVertexPointer(16, 4, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, tex_coord8));
		gl.addVertexPointer(17, 4, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, tex_coord9));
		gl.addVertexPointer(18, 4, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, tex_coord10));
		gl.addVertexPointer(19, 4, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, tex_coord11));
		gl.addVertexPointer(20, 4, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, tex_coord12));
		gl.addVertexPointer(21, 4, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, tex_coord13));
		gl.addVertexPointer(22, 4, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, tex_coord14));
		gl.addVertexPointer(23, 4, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, tex_coord15));
		gl.addVertexPointer(24, 1, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, fog_coord));
	}
};

} /* namespace GameEngine */




#endif /* SRC_VERTEX_HPP_ */
