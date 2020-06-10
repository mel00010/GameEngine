/******************************************************************************
 * Skybox.tpp
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
#ifndef SRC_3D_SKYBOX_TPP_
#define SRC_3D_SKYBOX_TPP_

#include "3D/Skybox.hpp"

namespace game_engine::_3D {

template <typename Renderer>
Skybox::Skybox(Renderer& renderer, const cmrc::embedded_filesystem& fs,
               const std::string& path) {
  LoadSkybox(renderer, fs, path);
}

template <typename Renderer>
void Skybox::LoadSkybox(Renderer& renderer, const cmrc::embedded_filesystem& fs,
                        const std::string& path) {
  cube_.LoadCube(renderer, fs, path, ShaderPrograms::SKYBOX);
}

template <typename Renderer>
void Skybox::Draw(const Renderer& renderer, const ShaderPrograms shaders) {
  glDepthMask(GL_FALSE);
  cube_.Draw(renderer, shaders);
  glDepthMask(GL_TRUE);
}

} /* namespace game_engine::_3D */

#endif /* SRC_3D_SKYBOX_TPP_ */
