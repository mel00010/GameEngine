/******************************************************************************
 * Camera.tpp
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
#ifndef SRC_3D_CAMERA_TPP_
#define SRC_3D_CAMERA_TPP_

#include "Camera.hpp"

namespace game_engine {
namespace _3D {

template<typename Renderer> void Camera::DrawModel(const Renderer& renderer, Model& model, ShaderPrograms shaders) {
	renderer.SetMatrices(shaders, model.model_, view_, projection_);
	model.Draw(renderer, shaders);
}

template<typename Renderer> void Camera::DrawModel(const Renderer& renderer, Cube& cube, ShaderPrograms shaders) {
	renderer.SetMatrices(shaders, cube.model_, view_, projection_);
	cube.Draw(renderer, shaders);
}
template<typename Renderer> void Camera::DrawModel(const Renderer& renderer, Skybox& skybox, ShaderPrograms shaders) {
	renderer.SetMatrices(shaders, glm::mat4(1.0f), glm::mat4(glm::mat3(view_)), projection_);
	skybox.Draw(renderer, shaders);
}

} /* namespace _3D */
} /* namespace game_engine */

#endif /* SRC_3D_CAMERA_TPP_ */
