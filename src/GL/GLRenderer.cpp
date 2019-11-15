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

#include <variant>


CMRC_DECLARE(GL);

namespace GameEngine {
namespace GL {

void glLogCallback(GLenum msg_source, GLenum msg_type, GLuint id, GLenum msg_severity,
		[[maybe_unused]] GLsizei length, const GLchar* msg_message, [[maybe_unused]] const void* userParam) {
	std::string source;
	std::string type;
	std::string severity;
	std::string message(msg_message);
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

void GLRenderer::init(std::string program_name) {
	/* SDL-related initialising functions */
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		LOG_F("SDL_init:  " << SDL_GetError());
		throw EXIT_FAILURE;
	}
	int image_flags = IMG_INIT_JPG
					| IMG_INIT_PNG;
	if( !( IMG_Init( image_flags ) & image_flags ) ) {
		LOG_F( "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() );
		throw EXIT_FAILURE;
	}

	int mixer_flags = MIX_INIT_FLAC
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
	setWindow(SDL_CreateWindow(program_name.c_str(),
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		1920, 1080,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL));
	SDL_GL_CreateContext(getWindow());
	enableVSync();
	/* Extension wrangler initialising */
	glewExperimental = GL_TRUE;
	GLenum glew_status = glewInit();
	if (glew_status != GLEW_OK) {
		LOG_F("Error: glewInit: " << glewGetErrorString(glew_status));
		throw EXIT_FAILURE;
	}
	glDisable( GL_CULL_FACE );
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	setSwizzleMask(GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA);

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(glLogCallback, NULL);

	default_shader = setupShader("default.vs.glsl", "default.fs.glsl");
	skybox_shader = setupShader("skybox.vs.glsl", "skybox.fs.glsl");
	text_shader = setupShader("text.vs.glsl", "text.fs.glsl");

	useShader(ShaderPrograms::DEFAULT);
}

void GLRenderer::useShader(const ShaderPrograms shader_program) {
//	LOG_D("Using shader " << shader_program);
	return getShader(shader_program)->use();
}

void GLRenderer::render(const VBO_handle vbo_handle, _3D::Primitive mode) {
	auto it = vbos.find(vbo_handle);
	if(it == vbos.end()) {
		LOG_E("VBO_handle " << vbo_handle << " not in map!");
		return;
	}
	VBO vbo = it->second;

	auto draw = [](VBO vbo_, _3D::Primitive mode) {
		vbo_.bind();

		// draw mesh
		if(vbo_.n_indices != 0) {
			glDrawElements(static_cast<GLenum>(convert(mode)), vbo_.n_indices, GL_UNSIGNED_INT, 0);
		} else {
			glDrawArrays(static_cast<GLenum>(convert(mode)), 0, vbo_.n_vertices);
		}
	};

//	LOG_D("VBO.shaders = " << vbo.shaders);
	if((vbo.shaders & ShaderPrograms::DEFAULT) != ShaderPrograms::NULL_SHADER) {
		default_shader->use();
		draw(vbo, mode);
	}
	if((vbo.shaders & ShaderPrograms::TEXT) != ShaderPrograms::NULL_SHADER) {
		text_shader->use();
		draw(vbo, mode);
	}
	if((vbo.shaders & ShaderPrograms::SKYBOX) != ShaderPrograms::NULL_SHADER) {
		skybox_shader->use();
		draw(vbo, mode);
	}

//	LOG_D("p = " << p);

//	LOG_D("vbo_handle.uuid = " << vbo_handle.uuid);
}

VBO_handle GLRenderer::generateVBO(const ShaderPrograms shader_program,
		const std::vector<Vertex>& vertices,
		const std::vector<GLuint>& indices) {
	VBO vbo;

	vbo.init(shader_program);
	vbo.bind();
	vbo.allocate(vertices, indices);
	VBO_handle vbo_handle = {UUID(), true};
//	LOG_D("vbo_handle.uuid = " << vbo_handle.uuid);
	vbos.emplace(vbo_handle, vbo);
	return vbo_handle;
}

VBO_handle GLRenderer::updateVBO(const VBO_handle vbo_handle,
		const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices) {
	VBO vbo = vbos.find(vbo_handle)->second;
	vbo.bind();
	vbo.update(vertices, indices);
	return vbo_handle;
}

bool GLRenderer::has_vbo(const VBO_handle vbo_handle) {
	return (vbos.count(vbo_handle) != 0);
}

void GLRenderer::setMatrices(const ShaderPrograms shader_program, const glm::mat4& model,
		const glm::mat4& view, const glm::mat4& projection) {
	// pass them to the shaders
	useShader(shader_program);
	getShader(shader_program)->setMat4("model", model);
	getShader(shader_program)->setMat4("view", view);
	getShader(shader_program)->setMat4("projection", projection);
}
void GLRenderer::bindTexture(const ShaderPrograms shader_program, const std::string& name,
		const _3D::Texture& texture, const GLuint texture_unit) {
//	LOG_D("Binding texture id " << texture.id << " to texture unit " << texture_unit << " with name " << name);
	useShader(shader_program);
	glActiveTexture(GL_TEXTURE0 + texture_unit); // activate proper texture unit before binding
	getShader(shader_program)->setInt(name, texture_unit);
	glBindTexture(GL_TEXTURE_2D, texture.id);
}
void GLRenderer::bindCubemap(const ShaderPrograms shader_program, const std::string& name,
		const _3D::Cubemap& cube_map, const GLuint texture_unit) {
	useShader(shader_program);
	glActiveTexture(GL_TEXTURE0 + texture_unit); // activate proper texture unit before binding
	getShader(shader_program)->setInt(name, texture_unit);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cube_map.id);
}
void GLRenderer::enable_blending() {
	glEnable(GL_BLEND);
}
void GLRenderer::disable_blending() {
	glDisable(GL_BLEND);
}
void GLRenderer::enable_depth_testing() {
	glEnable(GL_DEPTH_TEST);
}
void GLRenderer::disable_depth_testing() {
	glDisable(GL_DEPTH_TEST);
}

void GLRenderer::setColor(const ShaderPrograms shader_program, glm::vec3 color) {
	getShader(shader_program)->setVec3("color", color);
}

unsigned int GLRenderer::createTexture(const ShaderPrograms shader_program, _3D::PixelFormat format, glm::ivec2 size, void* pixels) {
	useShader(shader_program);


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
unsigned int GLRenderer::createCubemap(const ShaderPrograms shader_program, _3D::PixelFormat format, glm::ivec2 size, _3D::CubemapBuffers& buffers) {
	getShader(shader_program)->use();

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

void GLRenderer::setSwizzleMask(GLint swizzle_r, GLint swizzle_g, GLint swizzle_b, GLint swizzle_a) {
	GLint swizzle_mask[] = {swizzle_r, swizzle_g, swizzle_b, swizzle_a};
	glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzle_mask);
}

void GLRenderer::disable_byte_alignement_restriction() {
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction
}
void GLRenderer::enable_byte_alignement_restriction() {
	glPixelStorei(GL_UNPACK_ALIGNMENT, 0); // Disable byte-alignment restriction}
}
void GLRenderer::clear(glm::vec4 color) {
	glClearColor(color.r, color.g, color.b, color.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void GLRenderer::swap() {
	SDL_GL_SwapWindow(window);
}

ShaderProgram* GLRenderer::setupShader(const std::string& vertex, const std::string& fragment) {
	ShaderProgram* shader = new ShaderProgram();

	shader->init();

	auto fs = cmrc::GL::get_filesystem();
	auto vertex_file = fs.open(vertex);
	auto fragment_file = fs.open(fragment);

	std::string vertex_source(vertex_file.begin(), vertex_file.size());
	std::string fragment_source(fragment_file.begin(), fragment_file.size());

	Shader vertex_shader(vertex_source, ShaderType::VERTEX);
	Shader fragment_shader(fragment_source, ShaderType::FRAGMENT);
	vertex_shader.init();
	fragment_shader.init();
	shader->attachShader(vertex_shader);
	shader->attachShader(fragment_shader);
	shader->link();

	/* When all init functions run without errors,
	   the glsl_program can initialize the resources */
	if (!shader->isValid()) {
		throw EXIT_FAILURE;
	}
//	shader->useProgram();
//	LOG_D("p = " << p);
	return shader;
}

ShaderProgram* GLRenderer::getShader(const ShaderPrograms shader_program) const {
	switch(shader_program) {
		case ShaderPrograms::DEFAULT:
			return default_shader;
		case ShaderPrograms::SKYBOX:
			return skybox_shader;
		case ShaderPrograms::TEXT:
			return text_shader;
		default:
			return default_shader;
	}
	return default_shader;
}

void GLRenderer::setUniform(const ShaderPrograms shader_program, const std::string& name, bool value) const {
	getShader(shader_program)->setBool(name, value);
};
void GLRenderer::setUniform(const ShaderPrograms shader_program, const std::string& name, int value) const {
	getShader(shader_program)->setInt(name, value);
};
void GLRenderer::setUniform(const ShaderPrograms shader_program, const std::string& name, float value) const {
	getShader(shader_program)->setFloat(name, value);
};
void GLRenderer::setUniform(const ShaderPrograms shader_program, const std::string& name, const glm::vec2& value) const {
	getShader(shader_program)->setVec2(name, value);
};
void GLRenderer::setUniform(const ShaderPrograms shader_program, const std::string& name, float x, float y) const {
	getShader(shader_program)->setVec2(name, x, y);
};
void GLRenderer::setUniform(const ShaderPrograms shader_program, const std::string& name, const glm::vec3& value) const {
	getShader(shader_program)->setVec3(name, value);
};
void GLRenderer::setUniform(const ShaderPrograms shader_program, const std::string& name, float x, float y, float z) const {
	getShader(shader_program)->setVec3(name, x, y, z);
};
void GLRenderer::setUniform(const ShaderPrograms shader_program, const std::string& name, const glm::vec4& value) const {
	getShader(shader_program)->setVec4(name, value);
};
void GLRenderer::setUniform(const ShaderPrograms shader_program, const std::string& name, float x, float y, float z, float w) const {
	getShader(shader_program)->setVec4(name, x, y, z, w);
};
void GLRenderer::setUniform(const ShaderPrograms shader_program, const std::string& name, const glm::mat2& mat) const {
	getShader(shader_program)->setMat2(name, mat);
};
void GLRenderer::setUniform(const ShaderPrograms shader_program, const std::string& name, const glm::mat3& mat) const {
	getShader(shader_program)->setMat3(name, mat);
};
void GLRenderer::setUniform(const ShaderPrograms shader_program, const std::string& name, const glm::mat4& mat) const {
	getShader(shader_program)->setMat4(name, mat);
};

} /* namespace GL */
} /* namespace GameEngine */



