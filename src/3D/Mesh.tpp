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

#include "3D/Mesh.hpp"

namespace game_engine::_3D {

template <typename Renderer>
void Mesh::Init(Renderer& renderer, const ShaderPrograms shaders) {
  // TODO Decouple from rendering logic
  handle_ = renderer.GenerateVbo(shaders, vertices_, indices_);
}

template <typename Renderer>
void Mesh::Draw(const Renderer& renderer, const ShaderPrograms shaders) const {
  for (GLuint i = 0; i < textures_.size(); i++) {
    renderer.BindTexture(shaders, texture_strings_[i], textures_[i], i);
  }

  // draw mesh
  renderer.Render(handle_, mode_);
  //  log_.CAPTURE(handle_.uuid_);
}

} /* namespace game_engine::_3D */

#endif /* SRC_3D_MESH_TPP_ */
