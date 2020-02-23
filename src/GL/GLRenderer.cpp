/******************************************************************************
 * GLRenderer.cpp
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

#include "GLRenderer.hpp"

#include "Shader.hpp"

#include <Vertex.hpp>

#include <boost/mpl/for_each.hpp>
#include <cmrc/cmrc.hpp>
#include <GL/glew.h>
#include <Log.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include <string>
#include <variant>


CMRC_DECLARE(gl);

namespace game_engine {
namespace gl {

void GlLogCallback(const GLenum msg_source, const GLenum msg_type, const GLuint id, const GLenum msg_severity,
		[[maybe_unused]] const GLsizei length, const GLchar* msg_message, [[maybe_unused]] const void* userParam) {
	std::string source = "";
	std::string type = "";
	const std::string severity = "";
	const std::string message(msg_message);
	switch(msg_source) {
		case GL_DEBUG_SOURCE_API:
			source = "OpenGL API";
			break;
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
			source = "Window System";
			break;
		case GL_DEBUG_SOURCE_SHADER_COMPILER:
			source = "Shader Compiler";
			break;
		case GL_DEBUG_SOURCE_THIRD_PARTY:
			source = "Third Party";
			break;
		case GL_DEBUG_SOURCE_APPLICATION:
			source = "Application";
			break;
		case GL_DEBUG_SOURCE_OTHER:
			source = "an other source";
			break;
	}

	switch(msg_type) {
		case GL_DEBUG_TYPE_ERROR:
			type = "Error";
			break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			type = "Deprecated behavior";
			break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			type = "Undefined behavior";
			break;
		case GL_DEBUG_TYPE_PORTABILITY:
			type = "Portability";
			break;
		case GL_DEBUG_TYPE_PERFORMANCE:
			type = "Performance";
			break;
		case GL_DEBUG_TYPE_MARKER:
			type = "Marker";
			break;
		case GL_DEBUG_TYPE_PUSH_GROUP:
			type = "Push";
			break;
		case GL_DEBUG_TYPE_POP_GROUP:
			type = "Pop";
			break;
		case GL_DEBUG_TYPE_OTHER:
			type = "Other";
			break;
	}
	switch(msg_severity) {
		case GL_DEBUG_SEVERITY_HIGH:
			::Log::Entry(::Log::Level::ERROR, ::Log::Location("OpenGL | " + source, source, id)) << type << ":  " << message;
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
			::Log::Entry(::Log::Level::WARNING, ::Log::Location("OpenGL | " + source, source, id)) << type << ":  " << message;
			break;
		case GL_DEBUG_SEVERITY_LOW:
			::Log::Entry(::Log::Level::INFO, ::Log::Location("OpenGL | " + source, source, id)) << type << ":  " << message;
			break;
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			::Log::Entry(::Log::Level::DEBUG, ::Log::Location("OpenGL | " + source, source, id)) << type << ":  " << message;
			break;
	}
}

void GLRenderer::Init(const std::string program_name) {
	/* SDL-related initialising functions */
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		LOG_F("SDL_init:  " << SDL_GetError());
		throw EXIT_FAILURE;
	}
	const int image_flags = IMG_INIT_JPG
					| IMG_INIT_PNG;
	if( !( IMG_Init( image_flags ) & image_flags ) ) {
		LOG_F( "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() );
		throw EXIT_FAILURE;
	}

	const int mixer_flags = MIX_INIT_FLAC
					| MIX_INIT_MOD
					| MIX_INIT_MP3
					| MIX_INIT_OGG;
	if( !( Mix_Init( mixer_flags ) & mixer_flags ) ) {
		LOG_F( "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() );
		throw EXIT_FAILURE;
	}

	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		LOG_F("Mix_OpenAudio:  " << Mix_GetError());
		throw EXIT_FAILURE;
	}
	Mix_AllocateChannels(1000);

	// Request an OpenGL 4.5 context (should be core)
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);

	// Also request a depth buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SetWindow(SDL_CreateWindow(program_name.c_str(),
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		1920, 1080,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL));
	SDL_GL_CreateContext(GetWindow());
	EnableVSync();
	/* Extension wrangler initialising */
	glewExperimental = GL_TRUE;
	const GLenum glew_status = glewInit();
	if (glew_status != GLEW_OK) {
		LOG_F("Error: glewInit: " << glewGetErrorString(glew_status));
		throw EXIT_FAILURE;
	}
	glDisable( GL_CULL_FACE );
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	SetSwizzleMask(GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA);

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(GlLogCallback, NULL);

	default_shader_ = SetupShader("default.vs.glsl", "default.fs.glsl");
	cube_shader_ = SetupShader("cube.vs.glsl", "cube.fs.glsl");
	skybox_shader_ = SetupShader("skybox.vs.glsl", "skybox.fs.glsl");
	text_shader_ = SetupShader("text.vs.glsl", "text.fs.glsl");

	UseShader(ShaderPrograms::DEFAULT);
}

void GLRenderer::UseShader(const ShaderPrograms shader_program) const {
//	LOG_D("Using shader " << shader_program);
	return GetShader(shader_program)->Use();
}

void GLRenderer::Render(const VboHandle vbo_handle, const _3D::Primitive mode) const {
	const auto it = vbos_.find(vbo_handle);
	if(it == vbos_.end()) {
		LOG_E("VBO_handle " << vbo_handle << " not in map!");
		return;
	}
	Vbo vbo = it->second;

//	LOG_D("VBO.shaders = " << vbo.shaders);
	GetShader(vbo.shaders_)->Use();
	vbo.Bind();

	// draw mesh
	if(vbo.n_indices_ != 0) {
		glDrawElements(static_cast<GLenum>(Convert(mode)), vbo.n_indices_, GL_UNSIGNED_INT, 0);
	} else {
		glDrawArrays(static_cast<GLenum>(Convert(mode)), 0, vbo.n_vertices_);
	}

//	LOG_D("p = " << p);

//	LOG_D("vbo_handle.uuid = " << vbo_handle.uuid);
}

VboHandle GLRenderer::GenerateVbo(const ShaderPrograms shader_program,
		const std::vector<Vertex>& vertices,
		const std::vector<GLuint>& indices) {
	Vbo vbo {};

	vbo.Init(shader_program);
	vbo.Bind();
	vbo.Allocate(vertices, indices);
	VboHandle vbo_handle;
//	LOG_D("vbo_handle.uuid = " << vbo_handle.uuid);
	vbos_.emplace(vbo_handle, vbo);
	return vbo_handle;
}

VboHandle GLRenderer::UpdateVbo(const VboHandle vbo_handle,
		const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices) const {
	Vbo vbo = vbos_.find(vbo_handle)->second;
	vbo.Bind();
	vbo.Update(vertices, indices);
	return vbo_handle;
}

bool GLRenderer::HasVbo(const VboHandle vbo_handle) const {
	return (vbos_.count(vbo_handle) != 0);
}

void GLRenderer::SetMatrices(const ShaderPrograms shader_program, const glm::mat4& model,
		const glm::mat4& view, const glm::mat4& projection) const {
	// pass them to the shaders
	UseShader(shader_program);
	GetShader(shader_program)->SetMat4("model", model);
	GetShader(shader_program)->SetMat4("view", view);
	GetShader(shader_program)->SetMat4("projection", projection);
}
void GLRenderer::BindTexture(const ShaderPrograms shader_program, const std::string& name,
		const _3D::Texture& texture, const GLuint texture_unit) const {
//	LOG_D("Binding texture id " << texture.id << " to texture unit " << texture_unit << " with name " << name);
	UseShader(shader_program);
	glActiveTexture(GL_TEXTURE0 + texture_unit); // activate proper texture unit before binding
	GetShader(shader_program)->SetInt(name, texture_unit);
	glBindTexture(GL_TEXTURE_2D, texture.id_);
}
void GLRenderer::BindCubemap(const ShaderPrograms shader_program, const std::string& name,
		const _3D::Cubemap& cube_map, const GLuint texture_unit) const {
	UseShader(shader_program);
	glActiveTexture(GL_TEXTURE0 + texture_unit); // activate proper texture unit before binding
	GetShader(shader_program)->SetInt(name, texture_unit);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cube_map.id_);
}
void GLRenderer::EnableBlending() const {
	glEnable(GL_BLEND);
}
void GLRenderer::DisableBlending() const {
	glDisable(GL_BLEND);
}
void GLRenderer::EnableDepthTesting() const {
	glEnable(GL_DEPTH_TEST);
}
void GLRenderer::DisableDepthTesting() const {
	glDisable(GL_DEPTH_TEST);
}

void GLRenderer::SetColor(const ShaderPrograms shader_program, const glm::vec3 color) const {
	GetShader(shader_program)->SetVec3("color", color);
}

unsigned int GLRenderer::CreateTexture(const ShaderPrograms shader_program, const _3D::PixelFormat format,
		const glm::ivec2 size, const void* pixels) const {
	UseShader(shader_program);

	unsigned int id;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	// Set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, format.i_format, size.x, size.y, 0, format.e_format, GL_UNSIGNED_BYTE, pixels);
	glGenerateMipmap(GL_TEXTURE_2D);
	return id;
}
unsigned int GLRenderer::CreateCubemap(const ShaderPrograms shader_program, const _3D::PixelFormat format,
		const glm::ivec2 size, const _3D::CubemapBuffers& buffers) const {
	GetShader(shader_program)->Use();

	unsigned int id;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, id);

	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, format.i_format,
				size.x, size.y, 0, format.e_format, GL_UNSIGNED_BYTE, buffers.positive_x);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, format.i_format,
				size.x, size.y, 0, format.e_format, GL_UNSIGNED_BYTE, buffers.negative_x);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, format.i_format,
				size.x, size.y, 0, format.e_format, GL_UNSIGNED_BYTE, buffers.positive_y);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, format.i_format,
				size.x, size.y, 0, format.e_format, GL_UNSIGNED_BYTE, buffers.negative_y);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, format.i_format,
				size.x, size.y, 0, format.e_format, GL_UNSIGNED_BYTE, buffers.positive_z);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, format.i_format,
				size.x, size.y, 0, format.e_format, GL_UNSIGNED_BYTE, buffers.negative_z);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, 0);
	return id;
}

void GLRenderer::SetSwizzleMask(const GLint swizzle_r, const GLint swizzle_g,
		const GLint swizzle_b, const GLint swizzle_a) const {
	GLint swizzle_mask[] = {swizzle_r, swizzle_g, swizzle_b, swizzle_a};
	glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzle_mask);
}

void GLRenderer::DisableByteAlignementRestriction() const {
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction
}
void GLRenderer::EnableByteAlignementRestriction() const {
	glPixelStorei(GL_UNPACK_ALIGNMENT, 0); // Disable byte-alignment restriction}
}
void GLRenderer::Clear(const glm::vec4 color) const {
	glClearColor(color.r, color.g, color.b, color.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void GLRenderer::Swap() const {
	SDL_GL_SwapWindow(window_);
}

ShaderProgram* GLRenderer::SetupShader(const std::string& vertex, const std::string& fragment) const {
	ShaderProgram* shader = new ShaderProgram();

	shader->Init();

	const cmrc::embedded_filesystem fs = cmrc::gl::get_filesystem();
	const cmrc::file vertex_file = fs.open(vertex);
	const cmrc::file fragment_file = fs.open(fragment);

	const std::string vertex_source(vertex_file.begin(), vertex_file.size());
	const std::string fragment_source(fragment_file.begin(), fragment_file.size());

	Shader vertex_shader(vertex_source, ShaderType::VERTEX);
	Shader fragment_shader(fragment_source, ShaderType::FRAGMENT);
	vertex_shader.Init();
	fragment_shader.Init();
	shader->AttachShader(vertex_shader);
	shader->AttachShader(fragment_shader);
	shader->Link();

	/* When all init functions run without errors,
	   the glsl_program can initialize the resources */
	if (!shader->IsValid()) {
		throw EXIT_FAILURE;
	}
//	shader->useProgram();
//	LOG_D("p = " << p);
	return shader;
}

ShaderProgram* GLRenderer::GetShader(const ShaderPrograms shader_program) const {
	switch(shader_program) {
		case ShaderPrograms::DEFAULT:
			return default_shader_;
		case ShaderPrograms::CUBE:
			return cube_shader_;
		case ShaderPrograms::SKYBOX:
			return skybox_shader_;
		case ShaderPrograms::TEXT:
			return text_shader_;
		default:
			return default_shader_;
	}
	return default_shader_;
}

void GLRenderer::SetUniform(const ShaderPrograms shader_program, const std::string& name, const bool value) const {
	GetShader(shader_program)->SetBool(name, value);
};
void GLRenderer::SetUniform(const ShaderPrograms shader_program, const std::string& name, const int value) const {
	GetShader(shader_program)->SetInt(name, value);
};
void GLRenderer::SetUniform(const ShaderPrograms shader_program, const std::string& name, const float value) const {
	GetShader(shader_program)->SetFloat(name, value);
};
void GLRenderer::SetUniform(const ShaderPrograms shader_program, const std::string& name, const glm::vec2& value) const {
	GetShader(shader_program)->SetVec2(name, value);
};
void GLRenderer::SetUniform(const ShaderPrograms shader_program, const std::string& name,
		const float x, const float y) const {
	GetShader(shader_program)->SetVec2(name, x, y);
};
void GLRenderer::SetUniform(const ShaderPrograms shader_program, const std::string& name, const glm::vec3& value) const {
	GetShader(shader_program)->SetVec3(name, value);
};
void GLRenderer::SetUniform(const ShaderPrograms shader_program, const std::string& name,
		const float x, const float y, const float z) const {
	GetShader(shader_program)->SetVec3(name, x, y, z);
};
void GLRenderer::SetUniform(const ShaderPrograms shader_program, const std::string& name, const glm::vec4& value) const {
	GetShader(shader_program)->SetVec4(name, value);
};
void GLRenderer::SetUniform(const ShaderPrograms shader_program, const std::string& name,
		const float x, const float y, const float z, const float w) const {
	GetShader(shader_program)->SetVec4(name, x, y, z, w);
};
void GLRenderer::SetUniform(const ShaderPrograms shader_program, const std::string& name, const glm::mat2& mat) const {
	GetShader(shader_program)->SetMat2(name, mat);
};
void GLRenderer::SetUniform(const ShaderPrograms shader_program, const std::string& name, const glm::mat3& mat) const {
	GetShader(shader_program)->SetMat3(name, mat);
};
void GLRenderer::SetUniform(const ShaderPrograms shader_program, const std::string& name, const glm::mat4& mat) const {
	GetShader(shader_program)->SetMat4(name, mat);
};

} /* namespace gl */
} /* namespace game_engine */



