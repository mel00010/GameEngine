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

#include <utility>
#include <vector>

#include <GL/glew.h>

#include "3D/Primitive.hpp"
#include "3D/Texture.hpp"
#include "Renderer.hpp"
#include "VboHandle.hpp"
#include "Vertex.hpp"

namespace game_engine::_3D {

class Mesh {
 public:
  Mesh() noexcept = default;
  Mesh& operator=(const Mesh& rhs) = default;
  Mesh(const Mesh& rhs) = default;
  Mesh& operator=(Mesh&& rhs) noexcept = default;
  Mesh(Mesh&& rhs) noexcept = default;
  ~Mesh() noexcept = default;

  Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices,
       const std::vector<Texture>& textures,
       const Primitive mode = Primitive::TRIANGLES);

  template <typename Renderer>
  void Init(Renderer& renderer, const ShaderPrograms shaders);
  template <typename Renderer>
  void Draw(const Renderer& renderer, const ShaderPrograms shaders) const;

  void swap(Mesh& other) noexcept {
    using std::swap;
    swap(other.vertices_, vertices_);
    swap(other.indices_, indices_);
    swap(other.textures_, textures_);
    swap(other.handle_, handle_);
    swap(other.texture_strings_, texture_strings_);
    swap(other.mode_, mode_);
  }

 public:
  /*  Mesh Data  */
  std::vector<Vertex> vertices_{};
  std::vector<GLuint> indices_{};
  std::vector<Texture> textures_{};

 protected:
  VboHandle handle_{};
  std::vector<std::string> texture_strings_{};
  Primitive mode_{Primitive::TRIANGLES};

  friend std::ostream& operator<<(std::ostream& os, const Mesh& m);

 private:
  logging::Log log_ = logging::Log("main");
};

inline void swap(Mesh& a, Mesh& b) noexcept { a.swap(b); }

} /* namespace game_engine::_3D */

#include "3D/Mesh.tpp"

#endif /* SRC_3D_MESH_HPP_ */
