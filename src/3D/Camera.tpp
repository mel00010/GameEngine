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

namespace GameEngine {
namespace _3D {

template<typename Renderer> void Camera::drawModel(Renderer& renderer, Model& model, ShaderPrograms shaders) {
	renderer.setMatrices(shaders, model.model, view, projection);
	model.draw(renderer, shaders);
}

template<typename Renderer> void Camera::drawModel(Renderer& renderer, Cube& model, ShaderPrograms shaders) {
	renderer.setMatrices(shaders, model.model, view, projection);
	model.draw(renderer, shaders);
}
template<typename Renderer> void Camera::drawModel(Renderer& renderer, Skybox& model, ShaderPrograms shaders) {
	renderer.setMatrices(shaders, glm::mat4(1.0f), glm::mat4(glm::mat3(view)), projection);
	model.draw(renderer);
}

} /* namespace _3D */
} /* namespace GameEngine */

#endif /* SRC_3D_CAMERA_TPP_ */
