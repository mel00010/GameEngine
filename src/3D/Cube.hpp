/******************************************************************************
 * Cube.hpp
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
#ifndef SRC_3D_CUBE_HPP_
#define SRC_3D_CUBE_HPP_

#include <glm/glm.hpp>

#include "Cubemap.hpp"
#include "Model.hpp"

#include <cmrc/cmrc.hpp>
#include <GL/glew.h>

#include <vector>

namespace GameEngine {
namespace _3D {

class Cube {
	public:
		Cube() {}

		template<typename Renderer>
		Cube(Renderer& renderer, ShaderPrograms shaders, cmrc::embedded_filesystem& fs, const std::string& path);

		template<typename Renderer>
		void loadCube(Renderer& renderer, ShaderPrograms shaders, cmrc::embedded_filesystem& fs, const std::string& path);

		template<typename Renderer>
		void draw(Renderer& renderer, ShaderPrograms shaders);

	protected:
		Model model;

		class CubeMesh {
			public:
				VBO_handle handle;
				std::vector<Vertex> vertices;
				std::vector<GLuint> indices;
				Cubemap cube_map;

				CubeMesh() {}
				CubeMesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, Cubemap cube_map);

				template<typename Renderer> void draw(Renderer& renderer, ShaderPrograms shaders);
		};

		CubeMesh cube_mesh;

		friend std::ostream& operator<<(std::ostream& os, Cube m);
		friend std::ostream& operator<<(std::ostream& os, const Cube::CubeMesh& m);
};


} /* namespace _3D */
} /* namespace GameEngine */

#include "Cube.tpp"

#endif /* SRC_3D_CUBE_HPP_ */
