/******************************************************************************
 * Cube.tpp
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
#ifndef SRC_3D_CUBE_TPP_
#define SRC_3D_CUBE_TPP_

#include "Cube.hpp"

CMRC_DECLARE(_3D);

namespace GameEngine {
namespace _3D {

template<typename Renderer>
Cube::Cube(Renderer& renderer, ShaderPrograms shaders, cmrc::embedded_filesystem& fs,  const std::string& path) {
	loadCube(renderer, shaders, fs, path);
}


template<typename Renderer>
void Cube::loadCube(Renderer& renderer, ShaderPrograms shaders, cmrc::embedded_filesystem& fs, const std::string& path) {
	auto cube_fs = cmrc::_3D::get_filesystem();

	cube_mesh.cube_map.loadCubemap(renderer, shaders, fs, path);
	model.loadModel(renderer, cube_fs, "cube");
	cube_mesh.vertices = model.meshes[0].vertices;
	cube_mesh.indices = model.meshes[0].indices;
}

template<typename Renderer> void Cube::draw(Renderer& renderer, ShaderPrograms shaders) {
	cube_mesh.draw(renderer, shaders);
}

template<typename Renderer> void Cube::CubeMesh::draw(Renderer& renderer, ShaderPrograms shaders) {
	renderer.bindCubemap(shaders, "cube_map", cube_map, 0);
	if(!renderer.has_vbo(handle)) {
		handle = renderer.generateVBO(shaders, vertices, indices);
	}

	// draw mesh
	renderer.render(handle, Primitive::TRIANGLES);
}

} /* namespace _3D */
} /* namespace GameEngine */



#endif /* SRC_3D_CUBE_TPP_ */
