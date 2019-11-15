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
#include "VBO.hpp"

#include <3D/Texture.hpp>
#include <Util/UUID.hpp>

#include <map>
#include <vector>
#include <variant>

namespace GameEngine {
namespace GL {

class GLRenderer : public Renderer<GLRenderer, GLWindowManager> {
	public:
		void init(std::string program_name);
		void useShader(const ShaderPrograms shader_program);

		void render(const VBO_handle vbo_handle, _3D::Primitive mode);

		VBO_handle generateVBO(const ShaderPrograms shader_program,
				const std::vector<Vertex>& vertices,
				const std::vector<GLuint>& indices);
		VBO_handle updateVBO(const VBO_handle vbo_handle,
				const std::vector<Vertex>& vertices,
				const std::vector<GLuint>& indices);

		bool has_vbo(const VBO_handle vbo_handle);

		void setMatrices(const ShaderPrograms shader_program, const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection);
		void bindTexture(const ShaderPrograms shader_program, const std::string& name, const _3D::Texture& texture, const GLuint texture_unit);
		void bindCubemap(const ShaderPrograms shader_program, const std::string& name, const _3D::Cubemap& cube_map, const GLuint texture_unit);
		void enable_blending();
		void disable_blending();
		void enable_depth_testing();
		void disable_depth_testing();
		void setColor(const ShaderPrograms shader_program, glm::vec3 color);
		unsigned int createTexture(const ShaderPrograms shader_program, _3D::PixelFormat format, glm::ivec2 size, void* pixels);
		unsigned int createCubemap(const ShaderPrograms shader_program, _3D::PixelFormat format, glm::ivec2 size, _3D::CubemapBuffers& buffers);
		void setSwizzleMask(GLint swizzle_r, GLint swizzle_g, GLint swizzle_b, GLint swizzle_a);
		void disable_byte_alignement_restriction();
		void enable_byte_alignement_restriction();
		void clear(glm::vec4 color);
		void swap();

		void setUniform(const ShaderPrograms shader_program, const std::string& name, bool value) const;
		void setUniform(const ShaderPrograms shader_program, const std::string& name, int value) const;
		void setUniform(const ShaderPrograms shader_program, const std::string& name, float value) const;
		void setUniform(const ShaderPrograms shader_program, const std::string& name, const glm::vec2& value) const;
		void setUniform(const ShaderPrograms shader_program, const std::string& name, float x, float y) const;
		void setUniform(const ShaderPrograms shader_program, const std::string& name, const glm::vec3& value) const;
		void setUniform(const ShaderPrograms shader_program, const std::string& name, float x, float y, float z) const;
		void setUniform(const ShaderPrograms shader_program, const std::string& name, const glm::vec4& value) const;
		void setUniform(const ShaderPrograms shader_program, const std::string& name, float x, float y, float z, float w) const;
		void setUniform(const ShaderPrograms shader_program, const std::string& name, const glm::mat2& mat) const;
		void setUniform(const ShaderPrograms shader_program, const std::string& name, const glm::mat3& mat) const;
		void setUniform(const ShaderPrograms shader_program, const std::string& name, const glm::mat4& mat) const;

		ShaderProgram* default_shader = nullptr;
		ShaderProgram* skybox_shader = nullptr;
		ShaderProgram* text_shader = nullptr;

		std::map<VBO_handle, VBO> vbos;

	protected:
		ShaderProgram* setupShader(const std::string& vertex, const std::string& fragment);
		ShaderProgram* getShader(const ShaderPrograms shader_program) const;
};

} /* namespace GL */
} /* namespace GameEngine */

#include "GLRenderer.tpp"

#endif /* SRC_GL_GLRENDERER_HPP_ */
