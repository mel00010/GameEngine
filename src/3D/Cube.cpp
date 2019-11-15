/******************************************************************************
 * Cube.cpp
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

#include "Cube.hpp"

namespace GameEngine {
namespace _3D {

std::ostream& operator<<(std::ostream& os, Cube m) {
	os << "Cube {" << std::endl << push_indent;
	os << "Model model = " << m.model << std::endl;
	os << pop_indent << "}";
	return os;
}


Cube::CubeMesh::CubeMesh(std::vector<Vertex> _vertices, std::vector<GLuint> _indices, Cubemap _cube_map) :
		vertices(_vertices), indices(_indices), cube_map(_cube_map) {
}

std::ostream& operator<<(std::ostream& os, const Cube::CubeMesh& m) {
	os << "Cube::Mesh {" << push_indent << std::endl;
	os << "std::vector<Vertex> vertices = [ " << push_indent << std::endl;
	for (auto& i : m.vertices) {
		os <<  i << ", " << std::endl;
	}
	os << pop_indent << "]" << std::endl;
	os << "std::vector<GLuint> indices = [ " << push_indent << std::endl;
	for (auto& i : m.indices) {
		os << i << ", " << std::endl;
	}
	os << pop_indent << "]" << std::endl;
	os << "VBO_handle handle = " << m.handle << std::endl;
	os << pop_indent << "}";
	return os;
}

} /* namespace _3D */
} /* namespace GameEngine */


