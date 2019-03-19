/******************************************************************************
 * Model.hpp
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
#ifndef SRC_MODEL_HPP_
#define SRC_MODEL_HPP_

#define GLM_ENABLE_EXPERIMENTAL

#include "GL.hpp"
#include "Program.hpp"

#include <GL/glew.h>
#include <glm/gtx/euler_angles.hpp>

#include <vector>


namespace GameEngine {

enum class Primitive : GLenum {
	POINTS = GL_POINTS,
	LINES = GL_LINES,
	LINE_STRIP = GL_LINE_STRIP,
	LINE_LOOP = GL_LINE_LOOP,
	TRIANGLES = GL_TRIANGLES,
	TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
	TRIANGLE_FAN = GL_TRIANGLE_FAN,
	QUADS = GL_QUADS,
	QUAD_STRIP = GL_QUAD_STRIP,
	PATCHES = GL_PATCHES
};

template<typename Vertex>
class Model {
	public:
		Model() {}
		void init(const Primitive _mode, GLuint _texture) {
			mode = _mode;
			texture = _texture;
			gl.init();
			gl.bind();
			valid = false;
		}

		void addVertex(Vertex vertex) {
			vertices.push_back(vertex);
		}
		void addIndex(unsigned index)  {
			indices.push_back(index);
		}
		void finalize() {
			gl.allocate(vertices.size() * sizeof(Vertex), indices.size() * sizeof(unsigned int), &vertices[0], &indices[0]);
			// vertex
			gl.addVertexPointer(0, sizeof(Vertex::pos)/sizeof(GLfloat), GL_FLOAT, sizeof(Vertex), offsetof(Vertex, pos));
			gl.addVertexPointer(1, sizeof(Vertex::tex)/sizeof(GLfloat), GL_FLOAT, sizeof(Vertex), offsetof(Vertex, tex));
			valid = true;
		}

		void rotate(glm::vec3 delta) {
			model *= glm::orientate4(delta);
		}
		void move(glm::vec3 delta) {
			model = glm::translate(model, delta);
		}
		void scale(double scale) {
			model = glm::scale(model, glm::vec3(scale, scale, scale));
		}


		void draw() {
			// bind textures on corresponding texture units
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture);

			gl.bind();

			if(indices_enabled) {
				glDrawElements(static_cast<GLenum>(mode), indices.size(), GL_UNSIGNED_INT, 0);
			} else {
				glDrawArrays(static_cast<GLenum>(mode), 0, vertices.size());
			}
		}

	public:
		void enableIndices() {
			indices_enabled = true;
		}
		void disableIndices() {
			indices_enabled = false;
		}

	public:
		glm::mat4 model = glm::mat4(1.0f);
	protected:
		Primitive mode = Primitive::POINTS;
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;

		GLuint texture;

		GL gl;
		bool valid = false;
		bool indices_enabled = false;


};

} /* namespace GameEngine */

#endif /* SRC_MODEL_HPP_ */
