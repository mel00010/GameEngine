/******************************************************************************
 * Mesh.cpp
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

#include "Mesh.hpp"

#include <Log.hpp>

namespace GameEngine {
namespace _3D {

Mesh::Mesh(std::vector<Vertex> _vertices, std::vector<GLuint> _indices, std::vector<Texture> _textures,
		const Primitive _mode) :
		vertices(_vertices), indices(_indices), textures(_textures), mode(_mode) {
}



std::ostream& operator<<(std::ostream& os, const Mesh& m) {
	os << "Mesh {" << push_indent << std::endl;
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
	os << "std::vector<Texture> textures = [ " << push_indent  << std::endl;
	for (auto& i : m.textures) {
		os << i << ", " << std::endl;
	}
	os << pop_indent << "]" << std::endl;
	os << "VBO_handle handle = " << m.handle << std::endl;
	os << "std::vector<std::string> texture_strings = [ " << push_indent  << std::endl;
	for (auto& i : m.texture_strings) {
		os << "\"" << i << "\", " << std::endl;
	}
	os << "Primitive mode = " << m.mode << std::endl;
	os << pop_indent << "}";
	return os;
}

} /* namespace _3D */
} /* namespace GameEngine */
