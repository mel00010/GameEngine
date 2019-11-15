/******************************************************************************
 * Mesh.tpp
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
#ifndef SRC_3D_MESH_TPP_
#define SRC_3D_MESH_TPP_

#include "Mesh.hpp"

namespace GameEngine {
namespace _3D {

template<typename Renderer> void Mesh::setupMesh(Renderer& renderer, ShaderPrograms shaders) {
	// TODO Decouple from rendering logic
	handle = renderer.generateVBO(shaders, vertices, indices);

	GLuint diffuse_num = 0;
	GLuint specular_num = 0;
	GLuint normal_num = 0;
	GLuint height_num = 0;

	for(GLuint i = 0; i < textures.size(); i++) {
		switch(textures[i].type) {
			case TextureType::DIFFUSE:
				texture_strings.push_back("texture_diffuse" + std::to_string(diffuse_num++));
				break;
			case TextureType::SPECULAR:
				texture_strings.push_back("texture_specular" + std::to_string(specular_num++));
				break;
			case TextureType::NORMAL:
				texture_strings.push_back("texture_normal" + std::to_string(normal_num++));
				break;
			case TextureType::HEIGHT:
				texture_strings.push_back("texture_normal" + std::to_string(height_num++));
				break;
		}
	}
}

template<typename Renderer> void Mesh::draw(Renderer& renderer, ShaderPrograms shaders) {
	if(!renderer.has_vbo(handle)) {
		setupMesh(renderer, shaders);
	}

	for(GLuint i = 0; i < textures.size(); i++) {
		renderer.bindTexture(shaders, texture_strings[i], textures[i], i);
	}

	// draw mesh
	renderer.render(handle, mode);

//	LOG_D("this = " << *this);
}


} /* namespace _3D */
} /* namespace GameEngine */

#endif /* SRC_3D_MESH_TPP_ */
