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

#include "3D/Cube.hpp"
#include "3D/Model.hpp"

CMRC_DECLARE(_3D);

namespace game_engine::_3D {

template <typename Renderer>
Cube::Cube(Renderer& renderer, const cmrc::embedded_filesystem& fs,
           const std::string& path, const ShaderPrograms shaders) {
  LoadCube(renderer, fs, path, shaders);
}

template <typename Renderer>
void Cube::LoadCube(Renderer& renderer, const cmrc::embedded_filesystem& fs,
                    const std::string& path, const ShaderPrograms shaders) {
  auto cube_fs = cmrc::_3D::get_filesystem();

  cube_mesh_.cube_map_.LoadCubemap(renderer, fs, path, shaders);
  Model temp_model;
  temp_model.LoadModel(renderer, cube_fs, "cube");
  cube_mesh_.vertices_ = temp_model.meshes_[0].vertices_;
  cube_mesh_.indices_ = temp_model.meshes_[0].indices_;

  if (!renderer.HasVbo(cube_mesh_.handle_)) {
    cube_mesh_.handle_ = renderer.GenerateVbo(shaders, cube_mesh_.vertices_,
                                              cube_mesh_.indices_);
  }
}

template <typename Renderer>
void Cube::Draw(const Renderer& renderer, const ShaderPrograms shaders) const {
  cube_mesh_.Draw(renderer, shaders);
}

template <typename Renderer>
void Cube::CubeMesh::Draw(const Renderer& renderer,
                          const ShaderPrograms shaders) const {
  renderer.BindCubemap(shaders, "cube_map", cube_map_, 0);
  renderer.SetUniform(shaders, "color", glm::vec3(1.0, 1.0, 1.0));

  // draw mesh
  renderer.Render(handle_, Primitive::TRIANGLES);
}

} /* namespace game_engine::_3D */

#endif /* SRC_3D_CUBE_TPP_ */
