/******************************************************************************
 * Texture.cpp
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

#include "3D/Texture.hpp"

#include <array>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>

#include <GL/glew.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>

#include "LoggerV2/Log.hpp"

namespace game_engine {
namespace _3D {

enum class Color : std::int8_t {
  EMPTY = -1,
  RED = 0,
  GREEN = 1,
  BLUE = 2,
  ALPHA = 3
};

bool IsRed(const Color color) { return (color == Color::RED); }
bool IsGreen(const Color color) { return (color == Color::GREEN); }
bool IsBlue(const Color color) { return (color == Color::BLUE); }
bool IsAlpha(const Color color) { return (color == Color::ALPHA); }
bool IsEmpty(const Color color) { return (color == Color::EMPTY); }

PixelFormat Texture::DeterminePixelFormat(const SDL_PixelFormat* format) {
  PixelFormat f;
  logging::Log log = logging::Log("main");

  std::array<Color, 4> bytes = {Color::EMPTY, Color::EMPTY, Color::EMPTY,
                                Color::EMPTY};

  if ((format->Rmask & 0x000000FF) != 0) {
    bytes[0] = Color::RED;
  }
  if ((format->Rmask & 0x0000FF00) != 0) {
    bytes[1] = Color::RED;
  }
  if ((format->Rmask & 0x00FF0000) != 0) {
    bytes[2] = Color::RED;
  }
  if ((format->Rmask & 0xFF000000) != 0) {
    bytes[3] = Color::RED;
  }

  if ((format->Gmask & 0x000000FF) != 0) {
    bytes[0] = Color::GREEN;
  }
  if ((format->Gmask & 0x0000FF00) != 0) {
    bytes[1] = Color::GREEN;
  }
  if ((format->Gmask & 0x00FF0000) != 0) {
    bytes[2] = Color::GREEN;
  }
  if ((format->Gmask & 0xFF000000) != 0) {
    bytes[3] = Color::GREEN;
  }

  if ((format->Bmask & 0x000000FF) != 0) {
    bytes[0] = Color::BLUE;
  }
  if ((format->Bmask & 0x0000FF00) != 0) {
    bytes[1] = Color::BLUE;
  }
  if ((format->Bmask & 0x00FF0000) != 0) {
    bytes[2] = Color::BLUE;
  }
  if ((format->Bmask & 0xFF000000) != 0) {
    bytes[3] = Color::BLUE;
  }

  if ((format->Amask & 0x000000FF) != 0) {
    bytes[0] = Color::ALPHA;
  }
  if ((format->Amask & 0x0000FF00) != 0) {
    bytes[1] = Color::ALPHA;
  }
  if ((format->Amask & 0x00FF0000) != 0) {
    bytes[2] = Color::ALPHA;
  }
  if ((format->Amask & 0xFF000000) != 0) {
    bytes[3] = Color::ALPHA;
  }

  if (IsRed(bytes[0]) && IsGreen(bytes[1]) && IsBlue(bytes[2]) &&
      IsAlpha(bytes[3])) {
    f.e_format = GL_RGBA;
    f.i_format = GL_RGBA;
  } else if (IsRed(bytes[0]) && IsGreen(bytes[1]) && IsBlue(bytes[2]) &&
             IsEmpty(bytes[3])) {
    f.e_format = GL_RGB;
    f.i_format = GL_RGB;
  } else if (IsBlue(bytes[0]) && IsGreen(bytes[1]) && IsRed(bytes[2]) &&
             IsAlpha(bytes[3])) {
    f.e_format = GL_BGRA;
    f.i_format = GL_RGBA;
  } else if (IsBlue(bytes[0]) && IsGreen(bytes[1]) && IsRed(bytes[2]) &&
             IsEmpty(bytes[3])) {
    f.e_format = GL_BGR;
    f.i_format = GL_RGB;
  } else if (IsRed(bytes[0]) && IsGreen(bytes[1]) && IsEmpty(bytes[2]) &&
             IsEmpty(bytes[3])) {
    f.e_format = GL_RG;
    f.i_format = GL_RG;
  } else if (IsRed(bytes[0]) && IsEmpty(bytes[1]) && IsEmpty(bytes[2]) &&
             IsEmpty(bytes[3])) {
    f.e_format = GL_RED;
    f.i_format = GL_RED;
  } else {
    log.Error("Unsupported pixel format in file!");
    log.Error("format->Rmask = {:#x}", format->Rmask);
    log.Error("format->Gmask = {:#x}", format->Gmask);
    log.Error("format->Bmask = {:#x}", format->Bmask);
    log.Error("format->Amask = {:#x}", format->Amask);
    f.e_format = GL_RGBA;
    f.i_format = GL_RGBA;
    throw EXIT_FAILURE;
  }
  return f;
}

std::ostream& operator<<(std::ostream& os, const Texture& text) {
  return os << "Texture {\n"
            << "GLuint id_ = " << text.id_ << "\n"
            << "TextureType type_ = " << text.type_ << "\n"
            << "std::string path_ = \"" << text.path_ << "\"\n}";
}
std::ostream& operator<<(std::ostream& os, const TextureType type) {
  switch (type) {
    case TextureType::DIFFUSE:
      return os << "TextureType::DIFFUSE";
    case TextureType::SPECULAR:
      return os << "TextureType::SPECULAR";
    case TextureType::NORMAL:
      return os << "TextureType::NORMAL";
    case TextureType::HEIGHT:
      return os << "TextureType::HEIGHT";
  }
  return os;
}

} /* namespace _3D */
} /* namespace game_engine */
