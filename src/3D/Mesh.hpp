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
#ifndef SRC_3D_MESH_HPP_
#define SRC_3D_MESH_HPP_

#define GLM_ENABLE_EXPERIMENTAL

#include "Primitive.hpp"
#include "Texture.hpp"
#include "Vertex.hpp"

#include <Renderer.hpp>
#include <VBO_handle.hpp>

#include <vector>
#include <GL/glew.h>


namespace GameEngine {
namespace _3D {

class Mesh {
	public:
		Mesh() {}
		Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures,
				const Primitive mode = Primitive::TRIANGLES);
		template<typename Renderer> void setupMesh(Renderer& renderer, ShaderPrograms shaders);

		template<typename Renderer> void draw(Renderer& renderer, ShaderPrograms shaders);

	protected:

	public:
		/*  Mesh Data  */
		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
		std::vector<Texture> textures;

	protected:
		VBO_handle handle;
		std::vector<std::string> texture_strings;
		Primitive mode = Primitive::TRIANGLES;

		friend std::ostream& operator<<(std::ostream& os, const Mesh& m);
};



} /* namespace _3D */
} /* namespace GameEngine */

#include "Mesh.tpp"

#endif /* SRC_3D_MESH_HPP_ */
