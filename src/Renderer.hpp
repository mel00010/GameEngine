/******************************************************************************
 * Renderer.hpp
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
#ifndef SRC_RENDERER_HPP_
#define SRC_RENDERER_HPP_

#include <string>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "3D/Cubemap.hpp"
#include "3D/PixelFormat.hpp"
#include "3D/Primitive.hpp"
#include "3D/Texture.hpp"
#include "ShaderPrograms.hpp"
#include "Util/Crtp.hpp"
#include "Util/EnumBitMask.hpp"
#include "Util/Uuid.hpp"
#include "VboHandle.hpp"
#include "Vertex.hpp"
#include "WindowManager.hpp"

namespace game_engine {

// template <typename T>
// concept Shape = requires(const T& t) {
//  { t.area() }
//  ->float;
//};

/**
 * @brief Base class for Renderer objects
 * @tparam R_Derived Derived renderer class
 * @tparam W_Derived Window Manager
 */
template <typename R_Derived, typename W_Derived>
class Renderer : public W_Derived, Crtp<Renderer, R_Derived, W_Derived> {
 public:
  /**
   * @brief Initialize the renderer
   */
  void Init(const std::string program_name) const {
    this->Underlying().init(program_name);
  }

  void UseShader(const ShaderPrograms shader_program) const {
    this->Underlying().useShader(shader_program);
  }
  /**
   * @brief Generate a VBO
   * @param shader_program Shader with which to render object with
   * @param vertices Vector containing the vertices for the VBO
   * @param indices Vector containing the indices for the VBO
   * @return Returns a handle to the generated VBO
   */
  VboHandle GenerateVbo(const ShaderPrograms shader_program,
                        const std::vector<Vertex>& vertices,
                        const std::vector<GLuint>& indices) {
    return this->Underlying().generateVBO(shader_program, vertices, indices);
  }
  /**
   * @brief Update a VBO
   * @param vbo_handle Handle of the VBO to update
   * @param vertices Vector containing the vertices for the VBO
   * @param indices Vector containing the indices for the VBO
   * @return Returns a handle to the updated VBO
   */
  VboHandle UpdateVbo(const VboHandle vbo_handle,
                      const std::vector<Vertex>& vertices,
                      const std::vector<GLuint>& indices) const {
    return this->Underlying().UpdateVbo(vbo_handle, vertices, indices);
  }
  /**
   * @brief Test whether a handle references a valid VBO
   * @param vbo_handle Handle to test
   * @return Returns true if the handle references a valid VBO, false otherwise.
   */
  bool HasVbo(const VboHandle vbo_handle) const {
    return this->Underlying().HasVbo(vbo_handle);
  }
  /**
   * @brief Render a given VBO
   * @param vbo_handle Handle of VBO to render
   * @param mode Primitive type of objects inside VBO
   */
  void Render(const VboHandle vbo_handle, const _3D::Primitive mode) const {
    this->Underlying().Render(vbo_handle, mode);
  }
  /**
   * @brief Set the matrix uniforms
   * @param shader_program Shader to set uniforms for
   * @param model Model matrix
   * @param view View matrix
   * @param projection Projection matrix
   */
  void SetMatrices(const ShaderPrograms shader_program, const glm::mat4& model,
                   const glm::mat4& view, const glm::mat4& projection) const {
    this->Underlying().SetMatrices(shader_program, model, view, projection);
  }
  /**
   * @brief Bind a texture
   * @param shader_program Shader to bind texture to
   * @param name Name of uniform to bind to
   * @param texture Texture to bind
   * @param texture_unit Texture unit to bind to
   */
  void BindTexture(const ShaderPrograms shader_program, const std::string& name,
                   const _3D::Texture& texture,
                   const GLuint texture_unit) const {
    this->Underlying().BindTexture(shader_program, name, texture, texture_unit);
  }
  /**
   * @brief Bind a cube map
   * @param shader_program Shader to bind texture to
   * @param name Name of uniform to bind to
   * @param cube_map Cube map to bind
   * @param texture_unit C unit to bind to
   */
  void BindCubemap(const ShaderPrograms shader_program, const std::string& name,
                   const _3D::Cubemap& cube_map,
                   const GLuint texture_unit) const {
    this->Underlying().BindCubeMap(shader_program, name, cube_map,
                                   texture_unit);
  }

  /**
   * @brief Enable blending
   */
  void EnableBlending() const { this->Underlying().EnableBlending(); }
  /**
   * @brief Disable blending
   */
  void DisableElending() const { this->Underlying().DisableBlending(); }
  /**
   * @brief Enable depth testing
   */
  void EnableDepthTesting() const { this->Underlying().EnableDepthTesting(); }
  /**
   * @brief Disable depth testing
   */
  void DisableDepthTesting() const { this->Underlying().DisableDepthTesting(); }

  /**
   * @brief Set the color uniform
   * @param color Color to set it to
   */
  void SetColor(const glm::vec3 color) const {
    this->Underlying().SetColor(color);
  }
  /**
   * @brief Create a texture
   * @param format Format of the pixels in the texture
   * @param size Size of desired texture
   * @param pixels Pixel data to fill the texture from
   * @return Returns a unsigned int handle to the texture
   */
  unsigned int CreateTexture(const ShaderPrograms shader_program,
                             const _3D::PixelFormat format,
                             const glm::ivec2 size, const void* pixels) const {
    return this->Underlying().CreateTexture(shader_program, format, size,
                                            pixels);
  }
  /**
   * @brief Create a cubemap
   * @param format Format of the pixels in the cubemap
   * @param size Size of desired cubemap
   * @param buffers Image data to fill the cubemap faces from
   * @return Returns a unsigned int handle to the cubemap
   */
  unsigned int CreateCubemap(const ShaderPrograms shader_program,
                             const _3D::PixelFormat format,
                             const glm::ivec2 size,
                             const _3D::CubemapBuffers& buffers) const {
    return this->Underlying().CreateCubemap(shader_program, format, size,
                                            buffers);
  }
  /**
   * @brief Sets the swizzle mask for texture colors
   * @param swizzle_r Color channel to be used for the red channel
   * @param swizzle_g Color channel to be used for the green channel
   * @param swizzle_b Color channel to be used for the blue channel
   * @param swizzle_a Color channel to be used for the alpha channel
   */
  void SetSwizzleMask(const GLint swizzle_r, const GLint swizzle_g,
                      const GLint swizzle_b, const GLint swizzle_a) const {
    this->Underlying().SetSwizzleMask(swizzle_r, swizzle_g, swizzle_b,
                                      swizzle_a);
  }

  /**
   * @brief Disable byte alignment restriction
   */
  void DisableByteAlignementRestriction() const {
    this->Underlying().DisableByteAlignementRestriction();
  }
  /**
   * @brief Enable byte alignment restriction
   */
  void EnableByteAlignementRestriction() const {
    this->Underlying().EnableByteAlignementRestriction();
  }
  /**
   * @brief Clear the screen
   * @param color Color to set the screen to
   */
  void Clear(const glm::vec4 color) const { this->Underlying().Clear(color); }
  /**
   * @brief Swap the screen buffers
   */
  void Swap() const { this->Underlying().Swap(); }

  /**
   * @brief Set a uniform to a bool
   * @param shader_program Shader to set uniform for
   * @param name Name of the uniform to set
   * @param value Bool to set uniform to
   */
  void SetUniform(const ShaderPrograms shader_program, const std::string& name,
                  const bool value) const {
    this->Underlying().SetUniform(shader_program, name, value);
  }
  /**
   * @brief Set a uniform to a int
   * @param shader_program Shader to set uniform for
   * @param name Name of the uniform to set
   * @param value Int to set uniform to
   */
  void SetUniform(const ShaderPrograms shader_program, const std::string& name,
                  const int value) const {
    this->Underlying().SetUniform(shader_program, name, value);
  }
  /**
   * @brief Set a uniform to a float
   * @param shader_program Shader to set uniform for
   * @param name Name of the uniform to set
   * @param value Float to set uniform to
   */
  void SetUniform(const ShaderPrograms shader_program, const std::string& name,
                  const float value) const {
    this->Underlying().SetUniform(shader_program, name, value);
  }
  /**
   * @brief Set a uniform to a vec2
   * @param shader_program Shader to set uniform for
   * @param name Name of the uniform to set
   * @param value Vec2 to set uniform to
   */
  void SetUniform(const ShaderPrograms shader_program, const std::string& name,
                  const glm::vec2& value) const {
    this->Underlying().SetUniform(shader_program, name, value);
  }
  /**
   * @brief Set a uniform to a vec2
   * @param shader_program Shader to set uniform for
   * @param name Name of the uniform to set
   * @param x x component of vec2 to set uniform to
   * @param y y component of vec2 to set uniform to
   */
  void SetUniform(const ShaderPrograms shader_program, const std::string& name,
                  const float x, const float y) const {
    this->Underlying().SetUniform(shader_program, name, x, y);
  }
  /**
   * @brief Set a uniform to a vec3
   * @param shader_program Shader to set uniform for
   * @param name Name of the uniform to set
   * @param value Vec3 to set uniform to
   */
  void SetUniform(const ShaderPrograms shader_program, const std::string& name,
                  const glm::vec3& value) const {
    this->Underlying().SetUniform(shader_program, name, value);
  }
  /**
   * @brief Set a uniform to a vec3
   * @param shader_program Shader to set uniform for
   * @param name Name of the uniform to set
   * @param x x component of vec3 to set uniform to
   * @param y y component of vec3 to set uniform to
   * @param z z component of vec3 to set uniform to
   */
  void SetUniform(const ShaderPrograms shader_program, const std::string& name,
                  const float x, const float y, const float z) const {
    this->Underlying().SetUniform(shader_program, name, x, y, z);
  }
  /**
   * @brief Set a uniform to a vec4
   * @param shader_program Shader to set uniform for
   * @param name Name of the uniform to set
   * @param value Vec4 to set uniform to
   */
  void SetUniform(const ShaderPrograms shader_program, const std::string& name,
                  const glm::vec4& value) const {
    this->Underlying().SetUniform(shader_program, name, value);
  }
  /**
   * @brief Set a uniform to a vec4
   * @param shader_program Shader to set uniform for
   * @param name Name of the uniform to set
   * @param x x component of vec4 to set uniform to
   * @param y y component of vec4 to set uniform to
   * @param z z component of vec4 to set uniform to
   * @param w w component of vec4 to set uniform to
   */
  void SetUniform(const ShaderPrograms shader_program, const std::string& name,
                  const float x, const float y, const float z,
                  const float w) const {
    this->Underlying().SetUniform(shader_program, name, x, y, z, w);
  }
  /**
   * @brief Set a uniform to a mat2
   * @param shader_program Shader to set uniform for
   * @param name Name of the uniform to set
   * @param mat Mat2 to set uniform to
   */
  void SetUniform(const ShaderPrograms shader_program, const std::string& name,
                  const glm::mat2& mat) const {
    this->Underlying().SetUniform(shader_program, name, mat);
  }
  /**
   * @brief Set a uniform to a mat3
   * @param shader_program Shader to set uniform for
   * @param name Name of the uniform to set
   * @param mat Mat3 to set uniform to
   */
  void SetUniform(const ShaderPrograms shader_program, const std::string& name,
                  const glm::mat3& mat) const {
    this->Underlying().SetUniform(shader_program, name, mat);
  }
  /**
   * @brief Set a uniform to a mat4
   * @param shader_program Shader to set uniform for
   * @param name Name of the uniform to set
   * @param mat Mat4 to set uniform to
   */
  void SetUniform(const ShaderPrograms shader_program, const std::string& name,
                  const glm::mat4& mat) const {
    this->Underlying().SetUniform(shader_program, name, mat);
  }
};

} /* namespace game_engine */

#include "Renderer.tpp"

#endif /* SRC_RENDERER_HPP_ */
