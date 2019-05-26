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

namespace GameEngine {
namespace _3D {

Mesh::Mesh(std::vector<Vertex> _vertices, std::vector<GLuint> _indices, std::vector<Texture> _textures,
		const Primitive _mode, bool _indices_enabled) :
		vertices(_vertices), indices(_indices), textures(_textures), mode(_mode), indices_enabled(_indices_enabled) {
	setupMesh();
}

void Mesh::setupMesh() {
	gl.init();
	gl.bind();
	gl.allocate(vertices.size() * sizeof(Vertex), indices.size() * sizeof(GLuint), &vertices[0], &indices[0]);
	Vertex::addVertexPointers(gl);
}

void Mesh::draw(GL::ProgramRef prog)  {
//	prog->useProgram();
	gl.bind();
	GLuint diffuse_num = 0;
	GLuint specular_num = 0;
	GLuint normal_num = 0;
	GLuint height_num = 0;

	for(size_t i = 0; i < textures.size(); i++) {
		// retrieve texture number (the N in diffuse_textureN)
		std::string number;
		std::string name;
		switch(textures[i].type) {
			case TextureType::DIFFUSE:
				name += "texture_diffuse";
				number = std::to_string(diffuse_num++);
				break;
			case TextureType::SPECULAR:
				name += "texture_specular";
				number = std::to_string(specular_num++);
				break;
			case TextureType::NORMAL:
				name += "texture_normal";
				number = std::to_string(normal_num++);
				break;
			case TextureType::HEIGHT:
				name += "texture_normal";
				number = std::to_string(height_num++);
				break;
		}
		prog->useProgram();
		glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
		prog->setInt(name + number, i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
//		LOG_D(textures[i].id);
	}
	glActiveTexture(GL_TEXTURE0);

	gl.bind();
	// draw mesh
	if(indices_enabled) {
		glDrawElements(static_cast<GLenum>(mode), indices.size(), GL_UNSIGNED_INT, 0);
	} else {
		glDrawArrays(static_cast<GLenum>(mode), 0, vertices.size());
	}
}

} /* namespace _3D */
} /* namespace GameEngine */
