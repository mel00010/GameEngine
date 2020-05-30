/******************************************************************************
 * Texture.hpp
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
#ifndef SRC_3D_TEXTURE_HPP_
#define SRC_3D_TEXTURE_HPP_

#include <string>
#include <utility>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmrc/cmrc.hpp>
#include <glm/glm.hpp>

#include "3D/PixelFormat.hpp"
#include "LoggerV2/Log.hpp"
#include "ShaderPrograms.hpp"

namespace game_engine {
namespace _3D {

enum class TextureType : std::uint8_t { DIFFUSE, SPECULAR, NORMAL, HEIGHT };
std::ostream& operator<<(std::ostream& os, const TextureType type);

class Texture {
 public:
  Texture() = default;
  Texture& operator=(const Texture& rhs) = default;
  Texture(const Texture& rhs) = default;
  Texture& operator=(Texture&& rhs) noexcept = default;
  Texture(Texture&& rhs) noexcept = default;
  ~Texture() noexcept = default;

  Texture(const GLuint id, const TextureType type, const std::string path)
      : id_(id), type_(type), path_(path) {}

  template <typename Renderer>
  Texture(const Renderer& renderer, const cmrc::file file,
          const ShaderPrograms shader_program, const TextureType type);

  template <typename Renderer>
  GLuint LoadTexture(const Renderer& renderer, const cmrc::file file,
                     const ShaderPrograms shader_program,
                     const TextureType _type = TextureType::DIFFUSE);
  template <typename Renderer>
  GLuint LoadTextureFromMemory(const Renderer& renderer, const glm::ivec2 size,
                               const _3D::PixelFormat pixel_format,
                               const void* buffer,
                               const ShaderPrograms shader_program,
                               const TextureType _type = TextureType::DIFFUSE);

  void swap(Texture& other) noexcept {
    using std::swap;
    swap(other.id_, id_);
    swap(other.type_, type_);
    swap(other.path_, path_);
  }

 protected:
  static PixelFormat DeterminePixelFormat(const SDL_PixelFormat* format);
  friend class Cubemap;

 public:
  unsigned int id_{};
  TextureType type_{};
  std::string path_{};

 private:
  logging::Log log_ = logging::Log("main");
};

std::ostream& operator<<(std::ostream& os, const Texture& text);

inline void swap(Texture& a, Texture& b) noexcept { a.swap(b); }

} /* namespace _3D */
} /* namespace game_engine */

#include "3D/Texture.tpp"

#endif /* SRC_3D_TEXTURE_HPP_ */
