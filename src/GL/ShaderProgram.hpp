/******************************************************************************
 * ShaderProgram.hpp
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
#ifndef SRC_GL_SHADERPROGRAM_HPP_
#define SRC_GL_SHADERPROGRAM_HPP_

#include <memory>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "LoggerV2/Log.hpp"

namespace game_engine {
namespace gl {

class Shader;

class ShaderProgram {
 public:
  ShaderProgram& operator=(const ShaderProgram& rhs) = default;
  ShaderProgram(const ShaderProgram& rhs) = default;
  ShaderProgram& operator=(ShaderProgram&& rhs) noexcept = default;
  ShaderProgram(ShaderProgram&& rhs) noexcept = default;
  ShaderProgram() = default;
  ~ShaderProgram() noexcept = default;

 public:
  void AttachShader(Shader& shader);

  bool Link();
  bool Init();

 public:
  bool IsValid() const;
  void SetValid(bool validity = false);

  GLuint GetProgramHandle();
  GLuint GetPh();

  void UseProgram() const;
  void Use() const;

  void SetBool(const std::string& name, bool value) const;
  void SetInt(const std::string& name, int value) const;
  void SetFloat(const std::string& name, float value) const;
  void SetVec2(const std::string& name, const glm::vec2& value) const;
  void SetVec2(const std::string& name, float x, float y) const;
  void SetVec3(const std::string& name, const glm::vec3& value) const;
  void SetVec3(const std::string& name, float x, float y, float z) const;
  void SetVec4(const std::string& name, const glm::vec4& value) const;
  void SetVec4(const std::string& name, float x, float y, float z,
               float w) const;
  void SetMat2(const std::string& name, const glm::mat2& mat) const;
  void SetMat3(const std::string& name, const glm::mat3& mat) const;
  void SetMat4(const std::string& name, const glm::mat4& mat) const;

  void swap(ShaderProgram& other) noexcept {
    using std::swap;
    swap(other.program_, program_);
    swap(other.valid_, valid_);
    swap(other.shaders_, shaders_);
  }

 private:
  GLuint program_ = 0;
  bool valid_ = false;

  std::vector<Shader*> shaders_{};
  logging::Log log_ = logging::Log("main");
};

inline void swap(ShaderProgram& a, ShaderProgram& b) noexcept { a.swap(b); }

} /* namespace gl */
} /* namespace game_engine */

#endif /* SRC_GL_SHADERPROGRAM_HPP_ */
