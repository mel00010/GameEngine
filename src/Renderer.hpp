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

#include <ShaderPrograms.hpp>
#include <VBO_handle.hpp>
#include <Vertex.hpp>
#include <WindowManager.hpp>

#include <3D/Cubemap.hpp>
#include <3D/PixelFormat.hpp>
#include <3D/Primitive.hpp>
#include <3D/Texture.hpp>

#include <Util/EnumBitMask.hpp>
#include <Util/UUID.hpp>

#include <glm/glm.hpp>
#include <GL/glew.h>

#include <string>
#include <vector>

namespace GameEngine {

/**
 * @brief Base class for Renderer objects
 * @tparam R_Derived Derived renderer class
 * @tparam W_Derived Window Manager
 */
template <typename R_Derived, typename W_Derived> class Renderer : public W_Derived {
	public:
		/**
		 * @brief Initialize the renderer
		 */
		void init(std::string program_name) {
			r_derived().init(program_name);
		}

		void useShader(const ShaderPrograms shader_program) {
			r_derived().useShader(shader_program);
		}
		/**
		 * @brief Generate a VBO
		 * @param shader_program Shader with which to render object with
		 * @param vertices Vector containing the vertices for the VBO
		 * @param indices Vector containing the indices for the VBO
		 * @return Returns a handle to the generated VBO
		 */
		VBO_handle generateVBO(const ShaderPrograms shader_program,
				const std::vector<Vertex>& vertices,
				const std::vector<GLuint>& indices) {
			return r_derived().generateVBO(shader_program, vertices, indices);
		}
		/**
		 * @brief Update a VBO
		 * @param vbo_handle Handle of the VBO to update
		 * @param vertices Vector containing the vertices for the VBO
		 * @param indices Vector containing the indices for the VBO
		 * @return Returns a handle to the updated VBO
		 */
		VBO_handle updateVBO(const VBO_handle vbo_handle,
				const std::vector<Vertex>& vertices,
				const std::vector<GLuint>& indices) {
			return r_derived().updateVBO(vbo_handle, vertices, indices);
		}
		/**
		 * @brief Test whether a handle references a valid VBO
		 * @param vbo_handle Handle to test
		 * @return Returns true if the handle references a valid VBO, false otherwise.
		 */
		bool has_vbo(const VBO_handle vbo_handle) {
			return r_derived().has_vbo(vbo_handle);
		}
		/**
		 * @brief Render a given VBO
		 * @param vbo_handle Handle of VBO to render
		 * @param mode Primitive type of objects inside VBO
		 */
		void render(const VBO_handle vbo_handle, _3D::Primitive mode) {
			r_derived().render(vbo_handle, mode);
		}
		/**
		 * @brief Set the matrix uniforms
		 * @param shader_program Shader to set uniforms for
		 * @param model Model matrix
		 * @param view View matrix
		 * @param projection Projection matrix
		 */
		void setMatrices(const ShaderPrograms shader_program, const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) {
			r_derived().setMatrices(shader_program, model, view, projection);
		}
		/**
		 * @brief Bind a texture
		 * @param shader_program Shader to bind texture to
		 * @param name Name of uniform to bind to
		 * @param texture Texture to bind
		 * @param texture_unit Texture unit to bind to
		 */
		void bindTexture(const ShaderPrograms shader_program, const std::string& name, const _3D::Texture& texture, const GLuint texture_unit) {
			r_derived().bindTexture(name, texture, texture_unit);
		}
		/**
		 * @brief Bind a cube map
		 * @param shader_program Shader to bind texture to
		 * @param name Name of uniform to bind to
		 * @param cube_map Cube map to bind
		 * @param texture_unit C unit to bind to
		 */
		void bindCubemap(const ShaderPrograms shader_program, const std::string& name, const _3D::Cubemap& cube_map, const GLuint texture_unit) {
			r_derived().bindCubeMap(name, cube_map, texture_unit);
		}

		/**
		 * @brief Enable blending
		 */
		void enable_blending() {
			r_derived().enable_blending();
		}
		/**
		 * @brief Disable blending
		 */
		void disable_blending() {
			r_derived().disable_blending();
		}
		/**
		 * @brief Enable depth testing
		 */
		void enable_depth_testing() {
			r_derived().enable_depth_testing();
		}
		/**
		 * @brief Disable depth testing
		 */
		void disable_depth_testing() {
			r_derived().disable_depth_testing();
		}


		/**
		 * @brief Set the color uniform
		 * @param color Color to set it to
		 */
		void setColor(const glm::vec3 color) {
			r_derived().setColor(color);
		}
		/**
		 * @brief Create a texture
		 * @param format Format of the pixels in the texture
		 * @param size Size of desired texture
		 * @param pixels Pixel data to fill the texture from
		 * @return Returns a unsigned int handle to the texture
		 */
		unsigned int createTexture(const ShaderPrograms shader_program, _3D::PixelFormat format, glm::ivec2 size, void* pixels) {
			return r_derived().createTexture(format, size, pixels);
		}
		/**
		 * @brief Create a cubemap
		 * @param format Format of the pixels in the cubemap
		 * @param size Size of desired cubemap
		 * @param buffers Image data to fill the cubemap faces from
		 * @return Returns a unsigned int handle to the cubemap
		 */
		unsigned int createCubemap(const ShaderPrograms shader_program, _3D::PixelFormat format, glm::ivec2 size, _3D::CubemapBuffers& buffers) {
			return r_derived().createTexture(format, size, buffers);
		}
		/**
		 * @brief Sets the swizzle mask for texture colors
		 * @param swizzle_r Color channel to be used for the red channel
		 * @param swizzle_g Color channel to be used for the green channel
		 * @param swizzle_b Color channel to be used for the blue channel
		 * @param swizzle_a Color channel to be used for the alpha channel
		 */
		void setSwizzleMask(GLint swizzle_r, GLint swizzle_g, GLint swizzle_b, GLint swizzle_a) {
			r_derived().setSwizzleMask(swizzle_r, swizzle_g, swizzle_b, swizzle_a);
		}


		/**
		 * @brief Disable byte alignment restriction
		 */
		void disable_byte_alignement_restriction() {
			r_derived().disable_byte_alignement_restriction();
		}
		/**
		 * @brief Enable byte alignment restriction
		 */
		void enable_byte_alignement_restriction() {
			r_derived().enable_byte_alignement_restriction();
		}
		/**
		 * @brief Clear the screen
		 * @param color Color to set the screen to
		 */
		void clear(glm::vec4 color) {
			r_derived().clear(color);
		}
		/**
		 * @brief Swap the screen buffers
		 */
		void swap() {
			r_derived().swap();
		}

		/**
		 * @brief Set a uniform to a bool
		 * @param shader_program Shader to set uniform for
		 * @param name Name of the uniform to set
		 * @param value Bool to set uniform to
		 */
		void setUniform(const ShaderPrograms shader_program, const std::string& name, bool value) const {
			r_derived().setUniform(shader_program, name, value);
		}
		/**
		 * @brief Set a uniform to a int
		 * @param shader_program Shader to set uniform for
		 * @param name Name of the uniform to set
		 * @param value Int to set uniform to
		 */
		void setUniform(const ShaderPrograms shader_program, const std::string& name, int value) const {
			r_derived().setUniform(shader_program, name, value);
		}
		/**
		 * @brief Set a uniform to a float
		 * @param shader_program Shader to set uniform for
		 * @param name Name of the uniform to set
		 * @param value Float to set uniform to
		 */
		void setUniform(const ShaderPrograms shader_program, const std::string& name, float value) const {
			r_derived().setUniform(shader_program, name, value);
		}
		/**
		 * @brief Set a uniform to a vec2
		 * @param shader_program Shader to set uniform for
		 * @param name Name of the uniform to set
		 * @param value Vec2 to set uniform to
		 */
		void setUniform(const ShaderPrograms shader_program, const std::string& name, const glm::vec2& value) const {
			r_derived().setUniform(shader_program, name, value);
		}
		/**
		 * @brief Set a uniform to a vec2
		 * @param shader_program Shader to set uniform for
		 * @param name Name of the uniform to set
		 * @param x x component of vec2 to set uniform to
		 * @param y y component of vec2 to set uniform to
		 */
		void setUniform(const ShaderPrograms shader_program, const std::string& name, float x, float y) const {
			r_derived().setUniform(shader_program, name, x, y);
		}
		/**
		 * @brief Set a uniform to a vec3
		 * @param shader_program Shader to set uniform for
		 * @param name Name of the uniform to set
		 * @param value Vec3 to set uniform to
		 */
		void setUniform(const ShaderPrograms shader_program, const std::string& name, const glm::vec3& value) const {
			r_derived().setUniform(shader_program, name, value);
		}
		/**
		 * @brief Set a uniform to a vec3
		 * @param shader_program Shader to set uniform for
		 * @param name Name of the uniform to set
		 * @param x x component of vec3 to set uniform to
		 * @param y y component of vec3 to set uniform to
		 * @param z z component of vec3 to set uniform to
		 */
		void setUniform(const ShaderPrograms shader_program, const std::string& name, float x, float y, float z) const {
			r_derived().setUniform(shader_program, name, x, y, z);
		}
		/**
		 * @brief Set a uniform to a vec4
		 * @param shader_program Shader to set uniform for
		 * @param name Name of the uniform to set
		 * @param value Vec4 to set uniform to
		 */
		void setUniform(const ShaderPrograms shader_program, const std::string& name, const glm::vec4& value) const {
			r_derived().setUniform(shader_program, name, value);
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
		void setUniform(const ShaderPrograms shader_program, const std::string& name, float x, float y, float z, float w) const {
			r_derived().setUniform(shader_program, name, x, y, z, w);
		}
		/**
		 * @brief Set a uniform to a mat2
		 * @param shader_program Shader to set uniform for
		 * @param name Name of the uniform to set
		 * @param mat Mat2 to set uniform to
		 */
		void setUniform(const ShaderPrograms shader_program, const std::string& name, const glm::mat2& mat) const {
			r_derived().setUniform(shader_program, name, mat);
		}
		/**
		 * @brief Set a uniform to a mat3
		 * @param shader_program Shader to set uniform for
		 * @param name Name of the uniform to set
		 * @param mat Mat3 to set uniform to
		 */
		void setUniform(const ShaderPrograms shader_program, const std::string& name, const glm::mat3& mat) const {
			r_derived().setUniform(shader_program, name, mat);
		}
		/**
		 * @brief Set a uniform to a mat4
		 * @param shader_program Shader to set uniform for
		 * @param name Name of the uniform to set
		 * @param mat Mat4 to set uniform to
		 */
		void setUniform(const ShaderPrograms shader_program, const std::string& name, const glm::mat4& mat) const {
			r_derived().setUniform(shader_program, name, mat);
		}
	public:
		/**
		 * @brief A convenience function for CRTP
		 * @return Returns a reference to the renderer derived class
		 */
		inline R_Derived& r_derived() {
			return *static_cast<R_Derived*>(this);
		}
};

} /* namespace GameEngine */

#include "Renderer.tpp"

#endif /* SRC_RENDERER_HPP_ */
