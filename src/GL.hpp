/******************************************************************************
 * GL.hpp
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
#ifndef SRC_GL_HPP_
#define SRC_GL_HPP_

#include "Program.hpp"

#include <GL/glew.h>

namespace GameEngine {

class GL {
	public:
		void init() {
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);
		}
		void bind() {
			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		}
		void allocate(size_t vertex_size, size_t index_size, const GLvoid* verticies = nullptr, const GLvoid* indicies = nullptr) {
			bind();
			glBufferData(GL_ARRAY_BUFFER, vertex_size, verticies, GL_STATIC_DRAW);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_size, indicies, GL_STATIC_DRAW);
		}
		void addVertexPointer(size_t id, size_t vec_size, size_t type, size_t stride, size_t offset) {
			bind();
			glVertexAttribPointer(id, vec_size, type, GL_FALSE, stride, (void*)offset);
			glEnableVertexAttribArray(id);
		}
	public:
		GLuint VAO;
		GLuint VBO;
		GLuint EBO;
};

} /* namespace GameEngine */



#endif /* SRC_GL_HPP_ */
