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

#include <glm/glm.hpp>
#include <Log.hpp>

namespace game_engine {

struct Vertex {
	glm::vec3 position = glm::vec3(0.0, 0.0, 0.0);
	glm::vec3 normal = glm::vec3(0.0, 0.0, 0.0);
	glm::vec4 color = glm::vec4(1.0, 1.0, 1.0, 1.0);
	glm::vec4 secondary_color = glm::vec4(1.0, 1.0, 1.0, 1.0);
	glm::vec3 tangent = glm::vec3(0.0, 0.0, 0.0);
	glm::vec3 bitangent = glm::vec3(0.0, 0.0, 0.0);
	glm::vec2 tex_coord0 = glm::vec2(0.0, 0.0);
	glm::vec2 tex_coord1 = glm::vec2(0.0, 0.0);
	glm::vec2 tex_coord2 = glm::vec2(0.0, 0.0);
	glm::vec2 tex_coord3 = glm::vec2(0.0, 0.0);
	glm::vec2 tex_coord4 = glm::vec2(0.0, 0.0);
	glm::vec2 tex_coord5 = glm::vec2(0.0, 0.0);
	glm::vec2 tex_coord6 = glm::vec2(0.0, 0.0);
	glm::vec2 tex_coord7 = glm::vec2(0.0, 0.0);
	float     fog_coord = 0.0f;

	Vertex(glm::vec3 _pos, glm::vec3 _norm, glm::vec2 _tex) : position(_pos), normal(_norm), tex_coord0(_tex) {}
	Vertex() {}
};

inline std::ostream& operator<<(std::ostream& os, const Vertex& v) {
	return os << "Vertex {\n" << push_indent
			<< "glm::vec3 position        = " << v.position << "\n"
			<< "glm::vec3 normal          = " << v.normal << "\n"
			<< "glm::vec4 color           = " << v.color << "\n"
			<< "glm::vec4 secondary_color = " << v.secondary_color << "\n"
			<< "glm::vec3 tangent         = " << v.tangent << "\n"
			<< "glm::vec3 bitangent       = " << v.bitangent << "\n"
			<< "glm::vec2 tex_coord0      = " << v.tex_coord0 << "\n"
			<< "glm::vec2 tex_coord1      = " << v.tex_coord1 << "\n"
			<< "glm::vec2 tex_coord2      = " << v.tex_coord2 << "\n"
			<< "glm::vec2 tex_coord3      = " << v.tex_coord3 << "\n"
			<< "glm::vec2 tex_coord4      = " << v.tex_coord4 << "\n"
			<< "glm::vec2 tex_coord5      = " << v.tex_coord5 << "\n"
			<< "glm::vec2 tex_coord6      = " << v.tex_coord6 << "\n"
			<< "glm::vec2 tex_coord7      = " << v.tex_coord7 << "\n"
			<< "GLfloat   fog_coord       = " << v.fog_coord << "\n"
			<< pop_indent << "}";

}

} /* namespace game_engine */



#endif /* SRC_3D_VERTEX_HPP_ */
