/******************************************************************************
 * Camera.cpp
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

#include "Camera.hpp"

#include <Log.hpp>

namespace GameEngine {
namespace _3D {
void Camera::init(glm::ivec2 size) {
	fov = 45.0f;
	curr_size = size;
	updateView();
	updateProjection(size);
	valid = true;
}

void Camera::setCameraRotation(glm::vec3 rotation) {
	cameraFront = glm::normalize(rotation);
	updateView();
}
void Camera::setCameraPos(glm::vec3 pos) {
	cameraPos = pos;
	updateView();
}
void Camera::rotateCamera(double _yaw, double _pitch) {
	yaw += _yaw;
	pitch += _pitch;
	if(pitch > 89.99) {
		pitch = 89.99;
	}
	if(pitch < -89.99) {
		pitch = -89.99;
	}

	glm::vec3 direction;
	direction.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	direction.y = sin(glm::radians(pitch));
	direction.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	cameraFront = glm::normalize(direction);
	updateView();
}
void Camera::moveCamera(glm::vec3 delta) {
	cameraPos += delta;
	updateView();
}
void Camera::setFOV(float _fov) {
	fov = _fov;
	updateProjection(curr_size);
}
void Camera::updateView() {
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}
void Camera::updateProjection(glm::ivec2 size) {
	curr_size = size;
	projection = glm::perspective(
			glm::radians(fov), static_cast<float>(size.x) / static_cast<float>(size.y), 0.1f, 100.0f);
}
} /* namespace _3D */
} /* namespace GameEngine */



