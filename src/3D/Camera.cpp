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

#include "3D/Camera.hpp"

#include "LoggerV2/Log.hpp"

namespace game_engine {
namespace _3D {
void Camera::Init(const glm::ivec2 size) {
  fov_ = 45.0f;
  curr_size_ = size;
  UpdateView();
  UpdateProjection(size);
  valid_ = true;
}

void Camera::SetCameraRotation(glm::vec3 rotation) {
  camera_front_ = glm::normalize(rotation);
  UpdateView();
}
void Camera::SetCameraPos(const glm::vec3 pos) {
  camera_pos_ = pos;
  UpdateView();
}
void Camera::RotateCamera(const double yaw, const double pitch) {
  yaw_ += yaw;
  pitch_ += pitch;
  if (pitch_ > 89.99) {
    pitch_ = 89.99;
  }
  if (pitch_ < -89.99) {
    pitch_ = -89.99;
  }

  glm::vec3 direction;
  direction.x = cos(glm::radians(pitch_)) * cos(glm::radians(yaw_));
  direction.y = sin(glm::radians(pitch_));
  direction.z = cos(glm::radians(pitch_)) * sin(glm::radians(yaw_));
  camera_front_ = glm::normalize(direction);
  UpdateView();
}
void Camera::MoveCamera(const glm::vec3 delta) {
  camera_pos_ += delta;
  UpdateView();
}
void Camera::SetFov(const float fov) {
  fov_ = fov;
  UpdateProjection(curr_size_);
}
void Camera::UpdateView() {
  view_ = glm::lookAt(camera_pos_, camera_pos_ + camera_front_, camera_up_);
}
void Camera::UpdateProjection(glm::ivec2 size) {
  curr_size_ = size;
  projection_ = glm::perspective(
      glm::radians(fov_),
      static_cast<float>(size.x) / static_cast<float>(size.y), 0.1f, 100.0f);
}
} /* namespace _3D */
} /* namespace game_engine */
