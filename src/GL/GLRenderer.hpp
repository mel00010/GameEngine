/******************************************************************************
 * GLRenderer.hpp
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
#ifndef SRC_GL_GLRENDERER_HPP_
#define SRC_GL_GLRENDERER_HPP_

#include <Renderer.hpp>
#include <Vertex.hpp>

#include "GLPrimitive.hpp"
#include "ShaderProgram.hpp"
#include "GLWindowManager.hpp"
#include "Vbo.hpp"
#include <3D/Texture.hpp>
#include <Util/Uuid.hpp>

#include <map>
#include <vector>
#include <variant>

namespace game_engine {
namespace gl {

class GLRenderer : public Renderer<GLRenderer, GLWindowManager> {
	public:
		void Init(const std::string program_name);
		void UseShader(const ShaderPrograms shader_program) const;

		void Render(const VboHandle vbo_handle, const _3D::Primitive mode) const;

		VboHandle GenerateVbo(const ShaderPrograms shader_program,
				const std::vector<Vertex>& vertices,
				const std::vector<GLuint>& indices);
		VboHandle UpdateVbo(const VboHandle vbo_handle,
				const std::vector<Vertex>& vertices,
				const std::vector<GLuint>& indices) const;

		bool HasVbo(const VboHandle vbo_handle) const;

		void SetMatrices(const ShaderPrograms shader_program, const glm::mat4& model,
				const glm::mat4& view, const glm::mat4& projection) const;
		void BindTexture(const ShaderPrograms shader_program, const std::string& name,
				const _3D::Texture& texture, const GLuint texture_unit) const;
		void BindCubemap(const ShaderPrograms shader_program, const std::string& name,
				const _3D::Cubemap& cube_map, const GLuint texture_unit) const;
		void EnableBlending() const;
		void DisableBlending() const;
		void EnableDepthTesting() const;
		void DisableDepthTesting() const;
		void SetColor(const ShaderPrograms shader_program, const glm::vec3 color) const;
		unsigned int CreateTexture(const ShaderPrograms shader_program, const _3D::PixelFormat format,
				const glm::ivec2 size, const void* pixels) const ;
		unsigned int CreateCubemap(const ShaderPrograms shader_program, const _3D::PixelFormat format,
				const glm::ivec2 size, const _3D::CubemapBuffers& buffers) const;
		void SetSwizzleMask(const GLint swizzle_r, const GLint swizzle_g, const GLint swizzle_b, const GLint swizzle_a) const;
		void DisableByteAlignementRestriction() const;
		void EnableByteAlignementRestriction() const;
		void Clear(glm::vec4 color) const;
		void Swap() const;

		void SetUniform(const ShaderPrograms shader_program, const std::string& name, const bool value) const;
		void SetUniform(const ShaderPrograms shader_program, const std::string& name, const int value) const;
		void SetUniform(const ShaderPrograms shader_program, const std::string& name, const float value) const;
		void SetUniform(const ShaderPrograms shader_program, const std::string& name, const glm::vec2& value) const;
		void SetUniform(const ShaderPrograms shader_program, const std::string& name, const float x, const float y) const;
		void SetUniform(const ShaderPrograms shader_program, const std::string& name, const glm::vec3& value) const;
		void SetUniform(const ShaderPrograms shader_program, const std::string& name, const float x, const float y,
				const float z) const;
		void SetUniform(const ShaderPrograms shader_program, const std::string& name, const glm::vec4& value) const;
		void SetUniform(const ShaderPrograms shader_program, const std::string& name, const float x, const float y,
				const float z, const float w) const;
		void SetUniform(const ShaderPrograms shader_program, const std::string& name, const glm::mat2& mat) const;
		void SetUniform(const ShaderPrograms shader_program, const std::string& name, const glm::mat3& mat) const;
		void SetUniform(const ShaderPrograms shader_program, const std::string& name, const glm::mat4& mat) const;

		ShaderProgram* default_shader_ = nullptr;
		ShaderProgram* cube_shader_ = nullptr;
		ShaderProgram* skybox_shader_ = nullptr;
		ShaderProgram* text_shader_ = nullptr;

		std::map<VboHandle, Vbo> vbos_;

	protected:
		ShaderProgram* SetupShader(const std::string& vertex, const std::string& fragment) const;
		ShaderProgram* GetShader(const ShaderPrograms shader_program) const;
};

} /* namespace gl */
} /* namespace game_engine */

#include "GLRenderer.tpp"

#endif /* SRC_GL_GLRENDERER_HPP_ */
