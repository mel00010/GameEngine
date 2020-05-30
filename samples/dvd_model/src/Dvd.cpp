/******************************************************************************
 * Dvd.cpp
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

#include "Dvd.hpp"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/color_space.hpp>

#include "3D/Texture.hpp"
#include "LoggerV2/Log.hpp"

using namespace game_engine;

namespace dvd {

void Dvd::SetScale(const glm::dvec2 _scale) { scale_ = _scale; }

void Dvd::SetSpeed(const float _speed) { speed_ = _speed; }
void Dvd::ModifySpeed(const float delta) { speed_ *= (1.0 + delta); }
double Dvd::GetSpeed() { return speed_; }
void Dvd::Reset() { dvd_.MoveTo(glm::vec3(0.0)); }

void Dvd::CalculateMovement(const float fps) {
  glm::vec3 scale_factor = glm::vec3(speed_ / (scale_ * fps * 4.0f), 0.0);
  glm::vec2 offset = (scale_ - glm::vec2(0.235, 0.115)) / scale_;
  float length = glm::length(delta_vec_ * scale_factor);

  dvd_.Move(delta_vec_ * scale_factor);

  if (IsAtWindowEdge(WindowEdge::RIGHT, length, offset)) {
    delta_vec_ =
        glm::reflect(delta_vec_, glm::vec3(1.0, 0.0, 0.0) +
                                     glm::vec3(glm::diskRand(0.05), 0.0));
    dvd_.MoveXTo(offset.x - length);
    UpdateLogoColor();
  }
  if (IsAtWindowEdge(WindowEdge::LEFT, length, offset)) {
    delta_vec_ =
        glm::reflect(delta_vec_, glm::vec3(1.0, 0.0, 0.0) +
                                     glm::vec3(glm::diskRand(0.05), 0.0));
    dvd_.MoveXTo(-offset.x + length);
    UpdateLogoColor();
  }
  if (IsAtWindowEdge(WindowEdge::TOP, length, offset)) {
    delta_vec_ =
        glm::reflect(delta_vec_, glm::vec3(0.0, 1.0, 0.0) +
                                     glm::vec3(glm::diskRand(0.05), 0.0));
    dvd_.MoveYTo(offset.y - length);
    UpdateLogoColor();
  }
  if (IsAtWindowEdge(WindowEdge::BOTTOM, length, offset)) {
    delta_vec_ =
        glm::reflect(delta_vec_, glm::vec3(0.0, 1.0, 0.0) +
                                     glm::vec3(glm::diskRand(0.05), 0.0));
    dvd_.MoveYTo(-offset.y + length);
    UpdateLogoColor();
  }
  delta_vec_ = glm::normalize(delta_vec_);
}

bool Dvd::IsAtWindowEdge(const WindowEdge edge, const float length,
                         const glm::vec2 offset) {
  switch (edge) {
    case WindowEdge::RIGHT:
      return length > (offset.x - dvd_.position_.x);
    case WindowEdge::LEFT:
      return length > (offset.x + dvd_.position_.x);
    case WindowEdge::TOP:
      return length > (offset.y - dvd_.position_.y);
    case WindowEdge::BOTTOM:
      return length > (offset.y + dvd_.position_.y);
  }
  return false;
}

void Dvd::UpdateLogoColor() {
  glm::vec3 logo_color_hsv = glm::vec3(glm::linearRand(0.0, 360.0), 1.0, 1.0);
  logo_color_ = glm::rgbColor(logo_color_hsv);
}

} /* namespace dvd */
