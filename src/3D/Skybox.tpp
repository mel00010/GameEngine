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

#include "Skybox.hpp"

namespace GameEngine {
namespace _3D {

template<typename Renderer>
Skybox::Skybox(Renderer& renderer, cmrc::embedded_filesystem& fs,  const std::string& path) {
	loadSkybox(renderer, fs, path);
}

template<typename Renderer>
void Skybox::loadSkybox(Renderer& renderer, cmrc::embedded_filesystem& fs, const std::string& path) {
	cube.loadCube(renderer, ShaderPrograms::SKYBOX, fs, path);
}

template<typename Renderer> void Skybox::draw(Renderer& renderer) {
	glDepthMask(GL_FALSE);
	cube.draw(renderer, ShaderPrograms::SKYBOX);
	glDepthMask(GL_TRUE);

}

} /* namespace _3D */
} /* namespace GameEngine */

#endif /* SRC_3D_SKYBOX_TPP_ */