/******************************************************************************
 * Shader.hpp
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
#ifndef SRC_GL_SHADER_HPP_
#define SRC_GL_SHADER_HPP_

#include <memory>
#include <ostream>
#include <string>
#include <utility>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <cmrc/cmrc.hpp>
#include <glm/glm.hpp>

#include "LoggerV2/Log.hpp"

namespace game_engine {
namespace gl {

enum class ShaderType : GLenum {
  VERTEX = GL_VERTEX_SHADER,
  TESS_CONTROL = GL_TESS_CONTROL_SHADER,
  TESS_EVALUATION = GL_TESS_EVALUATION_SHADER,
  GEOMETRY = GL_GEOMETRY_SHADER,
  FRAGMENT = GL_FRAGMENT_SHADER,
  COMPUTE = GL_COMPUTE_SHADER
};
inline std::ostream& operator<<(std::ostream& os, const ShaderType type) {
  switch (type) {
    case ShaderType::VERTEX:
      return os << "ShaderType::VERTEX";
    case ShaderType::TESS_CONTROL:
      return os << "ShaderType::TESS_CONTROL";
    case ShaderType::TESS_EVALUATION:
      return os << "ShaderType::TESS_EVALUATION";
    case ShaderType::GEOMETRY:
      return os << "ShaderType::GEOMETRY";
    case ShaderType::FRAGMENT:
      return os << "ShaderType::FRAGMENT";
    case ShaderType::COMPUTE:
      return os << "ShaderType::COMPUTE";
  }
  return os;
}

class Shader {
 public:
  Shader() noexcept = default;
  Shader& operator=(const Shader& rhs) = default;
  Shader(const Shader& rhs) = default;
  Shader& operator=(Shader&& rhs) noexcept = default;
  Shader(Shader&& rhs) noexcept = default;

  Shader(const cmrc::file file, ShaderType _type)
      : source{std::string(file.begin(), file.end())},
        type(_type),
        shader(glCreateShader(static_cast<GLenum>(_type))) {}
  Shader(std::string source, ShaderType type);
  ~Shader() noexcept;
  bool Init();

 public:
  bool isValid() const;
  ShaderType getShaderType();
  GLuint getShaderHandle();

  void swap(Shader& other) noexcept {
    using std::swap;
    swap(other.source, source);
    swap(other.type, type);
    swap(other.shader, shader);
    swap(other.valid, valid);
  }

 protected:
  std::string source{};
  ShaderType type{};
  GLuint shader{};
  bool valid{};

 private:
  logging::Log log_ = logging::Log("main");
};

inline void swap(Shader& a, Shader& b) noexcept { a.swap(b); }

} /* namespace gl */
} /* namespace game_engine */

#endif /* SRC_GL_SHADER_HPP_ */
