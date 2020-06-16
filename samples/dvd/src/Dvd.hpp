/******************************************************************************
 * DVD.hpp
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
#ifndef SAMPLES_DVD_SRC_DVD_HPP_
#define SAMPLES_DVD_SRC_DVD_HPP_

#include <vector>

#include <GL/glew.h>
#include <cmrc/cmrc.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtx/color_space.hpp>

#include "LoggerV2/Log.hpp"

#include "3D/Texture.hpp"
#include "Renderer.hpp"
#include "Util/Uuid.hpp"
#include "Vertex.hpp"

CMRC_DECLARE(dvd);

using namespace game_engine;

namespace dvd {

class Dvd final {
 public:
  template <typename Renderer>
  explicit Dvd(Renderer& renderer)
      : fs_(cmrc::dvd::get_filesystem()),
        logo_color_(
            glm::rgbColor(glm::vec3(glm::linearRand(0.0, 360.0), 1.0, 1.0))),
        dvd_texture_(renderer, fs_.open("dvd.png"), ShaderPrograms::DEFAULT,
                     _3D::TextureType::DIFFUSE),
        vertices_(
            {Vertex(glm::vec3(0.5f, 0.5f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec2(1.0f, 1.0f)),  // top right
             Vertex(glm::vec3(0.5f, -0.5f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec2(1.0f, 0.0f)),  // bottom right
             Vertex(glm::vec3(-0.5f, -0.5f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec2(0.0f, 0.0f)),  // bottom left
             Vertex(glm::vec3(-0.5f, 0.5f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec2(0.0f, 1.0f))}),  // top left
        indices_({0, 1, 3, 1, 2, 3}),
        handle_(
            renderer.GenerateVbo(ShaderPrograms::DEFAULT, vertices_, indices_)),

        delta_vec_(glm::vec3(glm::circularRand(1.0), 0.0)) {}

  template <typename Renderer>
  void Draw(Renderer& renderer, const double fps) {
    //			LOG_D("Starting DVD render");
    renderer.BindTexture(ShaderPrograms::DEFAULT, "texture_diffuse0",
                         dvd_texture_, 0);
    // create transformations
    glm::mat4 projection = glm::mat4(
        1.0f);  // make sure to initialize matrix to identity matrix first

    projection = glm::translate(projection, translate_vec_);
    projection = glm::scale(projection, 0.5f / glm::vec3(scale_, 1.0));

    glm::vec3 right_surface = glm::vec3(1.0, 0.0, 0.0);
    glm::vec3 left_surface = glm::vec3(1.0, 0.0, 0.0);
    glm::vec3 top_surface = glm::vec3(0.0, 1.0, 0.0);
    glm::vec3 bottom_surface = glm::vec3(0.0, 1.0, 0.0);

    right_surface += glm::vec3(glm::diskRand(0.05f), 0.0f);
    left_surface += glm::vec3(glm::diskRand(0.05f), 0.0f);
    top_surface += glm::vec3(glm::diskRand(0.05f), 0.0f);
    bottom_surface += glm::vec3(glm::diskRand(0.05f), 0.0f);

    glm::dvec2 offset = (scale_ - glm::dvec2(0.235, 0.115)) / scale_;

    glm::vec3 scale_factor = glm::vec3(speed_ / (scale_ * fps * 4.0), 0.0);
    double length = glm::length(delta_vec_ * scale_factor);

    bool reflected = false;
    if (IsAtWindowEdge(WindowEdge::RIGHT, length, offset)) {
      delta_vec_ = glm::normalize(glm::reflect(delta_vec_, right_surface));
      translate_vec_.x = offset.x - length;
      reflected = true;
    }
    if (IsAtWindowEdge(WindowEdge::LEFT, length, offset)) {
      delta_vec_ = glm::normalize(glm::reflect(delta_vec_, left_surface));
      translate_vec_.x = -offset.x + length;
      reflected = true;
    }
    if (IsAtWindowEdge(WindowEdge::TOP, length, offset)) {
      delta_vec_ = glm::normalize(glm::reflect(delta_vec_, top_surface));
      translate_vec_.y = offset.y - length;
      reflected = true;
    }
    if (IsAtWindowEdge(WindowEdge::BOTTOM, length, offset)) {
      delta_vec_ = glm::normalize(glm::reflect(delta_vec_, bottom_surface));
      translate_vec_.y = -offset.y + length;
      reflected = true;
    }
    if (reflected) {
      UpdateLogoColor();
    }
    translate_vec_ += delta_vec_ * scale_factor;

    renderer.SetColor(ShaderPrograms::DEFAULT, logo_color_);
    renderer.SetMatrices(ShaderPrograms::DEFAULT, glm::mat4(1), glm::mat4(1),
                         projection);

    renderer.Render(handle_, _3D::Primitive::TRIANGLES);
    //			LOG_D("Finished DVD render");
  }

  void SetScale(const glm::dvec2 _scale) { scale_ = _scale; }

  void SetSpeed(const double _speed = 1.0) { speed_ = _speed; }
  void ModifySpeed(const double delta = 0.0) { speed_ *= (1.0 + delta); }
  double GetSpeed() { return speed_; }
  void Reset() { translate_vec_ = glm::vec3(0.0); }

 protected:
  enum class WindowEdge : std::uint8_t { TOP, BOTTOM, LEFT, RIGHT };
  bool IsAtWindowEdge(const WindowEdge edge, const double length,
                      const glm::dvec2 offset);
  glm::vec3 UpdateLogoColor();

 protected:
  const cmrc::embedded_filesystem fs_;

  glm::vec3 logo_color_ = glm::vec3(1.0, 1.0, 1.0);

  _3D::Texture dvd_texture_;
  std::vector<Vertex> vertices_;
  std::vector<GLuint> indices_;
  VboHandle handle_;

  glm::vec3 translate_vec_ = glm::vec3(0.0);
  glm::vec3 delta_vec_ = glm::normalize(glm::vec3(1.0, 1.0, 0.0));

  glm::dvec2 scale_ = glm::dvec2(1.0, 1.0);
  double speed_ = 1.0;
};

}  // namespace dvd

#endif /* SAMPLES_DVD_SRC_DVD_HPP_ */
