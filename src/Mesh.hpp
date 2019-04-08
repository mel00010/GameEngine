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

#include "GL.hpp"
#include "Primitive.hpp"
#include "Program.hpp"
#include "Texture.hpp"
#include "Vertex.hpp"

#include <glm/gtx/euler_angles.hpp>
#include <GL/glew.h>
#include <vector>


namespace GameEngine {

class Mesh {
	public:
		Mesh() {}
		Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures,
				const Primitive mode, bool indices_enabled);
		void draw(ProgramRef prog);

	protected:
		void setupMesh();

	public:
		/*  Mesh Data  */
		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
		std::vector<Texture> textures;

	protected:
		GL gl;
		Primitive mode = Primitive::TRIANGLES;
		bool indices_enabled = true;
};

} /* namespace GameEngine */




#endif /* SRC_MESH_HPP_ */
