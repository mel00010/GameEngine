/******************************************************************************
 * Mesh.hpp
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
#ifndef SRC_MESH_HPP_
#define SRC_MESH_HPP_

#define GLM_ENABLE_EXPERIMENTAL

#include <GL/GL.hpp>
#include <GL/Program.hpp>

#include "Primitive.hpp"
#include "Texture.hpp"
#include "Vertex.hpp"

#include <Log.hpp>

#include <glm/gtx/euler_angles.hpp>
#include <GL/glew.h>
#include <vector>


namespace GameEngine {
namespace _3D {

class Mesh {
	public:
		Mesh() {}
		Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures,
				const Primitive mode = Primitive::TRIANGLES, bool indices_enabled = true);
		void draw(GL::ProgramRef prog);

	protected:
		void setupMesh();

	public:
		/*  Mesh Data  */
		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
		std::vector<Texture> textures;
	protected:
		GL::GL gl;
		Primitive mode = Primitive::TRIANGLES;
		bool indices_enabled = true;
		friend std::ostream& operator<<(std::ostream& os, Mesh m);
};
inline std::ostream& operator<<(std::ostream& os, Mesh m) {
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
	os << "GL::GL gl = " << m.gl << std::endl;
	os << "Primitive mode = " << m.mode << std::endl;
	os << "bool indices_enabled = " << m.indices_enabled << std::endl;
	os << pop_indent << "}";
	return os;
}



} /* namespace _3D */
} /* namespace GameEngine */



#endif /* SRC_MESH_HPP_ */
