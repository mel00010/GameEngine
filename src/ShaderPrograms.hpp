/******************************************************************************
 * ShaderPrograms.hpp
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
#ifndef SRC_SHADERPROGRAMS_HPP_
#define SRC_SHADERPROGRAMS_HPP_

#include <GL/glew.h>

#include "LoggerV2/Log.hpp"
#include "Util/EnumBitMask.hpp"

namespace game_engine {

enum class ShaderPrograms : GLuint {
  NULL_SHADER = 0,
  DEFAULT = (1 << 0),
  CUBE = (1 << 1),
  TEXT = (1 << 2),
  SKYBOX = (1 << 3)
};
ENABLE_BITMASK_OPERATORS(ShaderPrograms);

inline std::ostream& operator<<(std::ostream& os, const ShaderPrograms sp) {
  std::string out;
  if (sp == ShaderPrograms::NULL_SHADER) {
    return os << "ShaderPrograms::NULL_SHADER";
  }
  if ((sp & ShaderPrograms::DEFAULT) != ShaderPrograms::NULL_SHADER) {
    if (out.length() != 0) {
      out += " | ";
    }
    out += "DEFAULT";
  }
  if ((sp & ShaderPrograms::CUBE) != ShaderPrograms::NULL_SHADER) {
    if (out.length() != 0) {
      out += " | ";
    }
    out += "CUBE";
  }
  if ((sp & ShaderPrograms::TEXT) != ShaderPrograms::NULL_SHADER) {
    if (out.length() != 0) {
      out += " | ";
    }
    out += "TEXT";
  }
  if ((sp & ShaderPrograms::SKYBOX) != ShaderPrograms::NULL_SHADER) {
    if (out.length() != 0) {
      out += " | ";
    }
    out += "SKYBOX";
  }
  return os << out;
}

} /* namespace game_engine */

#endif /* SRC_SHADERPROGRAMS_HPP_ */
