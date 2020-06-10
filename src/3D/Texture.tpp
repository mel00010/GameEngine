/******************************************************************************
 * Texture.tpp
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
#ifndef SRC_3D_TEXTURE_TPP_
#define SRC_3D_TEXTURE_TPP_

#include <glm/glm.hpp>

#include "3D/Texture.hpp"

namespace game_engine::_3D {

template <typename Renderer>
Texture::Texture(const Renderer& renderer, const cmrc::file file,
                 const ShaderPrograms shader_program, const TextureType type)
    : id_{0}, type_(TextureType::DIFFUSE) {
  LoadTexture(renderer, file, shader_program, type);
}

template <typename Renderer>
GLuint Texture::LoadTexture(const Renderer& renderer, const cmrc::file file,
                            const ShaderPrograms shader_program,
                            const TextureType type) {
  log_.Debug("Opening {}.", file.path());
  std::vector<uint8_t> file_contents(file.begin(), file.end());
  path_ = file.path();
  std::string ext{};
  if (path_.rfind('.') == std::string::npos) {
    ext = path_;
  } else {
    ext = path_.substr(path_.rfind('.'));
  }

  // New SDL surface and load the image
  SDL_Surface* surface = IMG_LoadTyped_RW(
      SDL_RWFromMem(file_contents.data(), file_contents.size()), 1,
      ext.c_str());

  // Check if image data loaded ok
  if (surface == 0) {
    log_.Error("Error!  surface == 0");
    log_.Error("file.path() = {}", file.path());
    log_.Error("texture_type = {}", type);

    throw EXIT_FAILURE;
  }

  // Get dimensions
  glm::ivec2 size(surface->w, surface->h);

  // Check that the image's dimensions are powers of 2
  if ((size.x & (size.x - 1)) != 0) {
    log_.Warning("Non power-of-two texture loaded: {}", file.path());
  } else if ((size.y & (size.y - 1)) != 0) {
    log_.Warning("Non power-of-two texture loaded: {}", file.path());
  }

  PixelFormat format = DeterminePixelFormat(surface->format);

  LoadTextureFromMemory(renderer, size, format, surface->pixels, shader_program,
                        type);

  // Free SDL surface
  SDL_FreeSurface(surface);

  return id_;
}

template <typename Renderer>
GLuint Texture::LoadTextureFromMemory(const Renderer& renderer,
                                      const glm::ivec2 size,
                                      const _3D::PixelFormat pixel_format,
                                      const void* buffer,
                                      const ShaderPrograms shader_program,
                                      const TextureType _type) {
  if (path_ == "") {
    path_ = "N/A";
  }
  type_ = _type;
  id_ = renderer.CreateTexture(shader_program, pixel_format, size, buffer);
  return id_;
}
} /* namespace game_engine::_3D */

#endif /* SRC_3D_TEXTURE_TPP_ */
