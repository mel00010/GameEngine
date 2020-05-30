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

#include <ostream>
#include <vector>

#include <GL/glew.h>

#include "ShaderPrograms.hpp"
#include "Vertex.hpp"

namespace game_engine {
namespace gl {

class Vbo {
 public:
  void Init(ShaderPrograms shader);
  void Bind();
  void Allocate(const std::vector<Vertex>& vertices,
                const std::vector<GLuint>& indices);
  void Update(const std::vector<Vertex>& vertices,
              const std::vector<GLuint>& indices);
  void AddVertexPointer(GLuint id, size_t vec_size, GLenum type, size_t stride,
                        size_t offset);
  void AddVertexPointers();

 public:
  GLuint vao_ = 0;
  GLuint vbo_ = 0;
  GLuint ebo_ = 0;
  size_t n_vertices_ = 0;
  size_t n_indices_ = 0;
  ShaderPrograms shaders_ = ShaderPrograms::NULL_SHADER;
};

inline std::ostream& operator<<(std::ostream& os, const Vbo vbo) {
  return os << "GL {\n"
            << "GLuint vao_ = " << static_cast<unsigned int>(vbo.vao_) << "\n"
            << "GLuint vbo_ = " << static_cast<unsigned int>(vbo.vbo_) << "\n"
            << "GLuint ebo_ = " << static_cast<unsigned int>(vbo.ebo_) << "\n"
            << "size_t n_vertices_" << vbo.n_vertices_ << "\n"
            << "size_t n_indices_" << vbo.n_indices_ << "\n"
            << "ShaderPrograms shaders_ = " << vbo.shaders_ << "\n"
            << "}";
}

} /* namespace gl */
} /* namespace game_engine */

#endif /* SRC_GL_VBO_HPP_ */
