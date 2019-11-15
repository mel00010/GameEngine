/******************************************************************************
 * VBO.hpp
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
#ifndef SRC_GL_VBO_HPP_
#define SRC_GL_VBO_HPP_

#include <ShaderPrograms.hpp>
#include <Vertex.hpp>

#include <GL/glew.h>
#include <ostream>

namespace GameEngine {
namespace GL {

class VBO {
	public:
		void init(ShaderPrograms shader);
		void bind();
		void allocate(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices);
		void update(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices);
		void addVertexPointer(GLuint id, size_t vec_size, GLenum type, size_t stride, size_t offset);
		void addVertexPointers();
	public:
		GLuint vao = 0;
		GLuint vbo = 0;
		GLuint ebo = 0;
		size_t n_vertices = 0;
		size_t n_indices = 0;
		ShaderPrograms shaders = ShaderPrograms::NULL_SHADER;
};

inline std::ostream& operator<<(std::ostream& os, const VBO vbo) {
	return os << "GL {\n"<< push_indent
			<< "GLuint VAO = "<< static_cast<unsigned int>(vbo.vao) << "\n"
			<< "GLuint VBO = " << static_cast<unsigned int>(vbo.vbo) << "\n"
			<< "GLuint EBO = " << static_cast<unsigned int>(vbo.ebo) << "\n"
			<< "size_t n_vertices" << vbo.n_vertices << "\n"
			<< "size_t n_indices" << vbo.n_indices << "\n"
			<< "ShaderPrograms shaders = " << vbo.shaders << "\n"
			<< pop_indent << "}";
}


} /* namespace GL */
} /* namespace GameEngine */

#endif /* SRC_GL_VBO_HPP_ */
