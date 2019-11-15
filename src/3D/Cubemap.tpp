/******************************************************************************
 * Cubemap.tpp
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
#ifndef SRC_3D_CUBEMAP_TPP_
#define SRC_3D_CUBEMAP_TPP_

#include "Cubemap.hpp"
#include "Texture.hpp"

namespace GameEngine {
namespace _3D {

template<typename Renderer>
Cubemap::Cubemap(Renderer& renderer,
		const ShaderPrograms shader_program,
		cmrc::embedded_filesystem& fs,
		const std::string& path) {
	LOG_D("Cubemap id = " << id);
	id = -1;
	loadCubemap(renderer, shader_program, fs, path);
}

template<typename Renderer>
GLuint Cubemap::loadCubemap(Renderer& renderer,
		const ShaderPrograms shader_program,
		cmrc::embedded_filesystem& fs,
		const std::string& path) {
	renderer.useShader(shader_program);
	struct CubeSurfaces {
			SDL_Surface *right, *left, *top, *bottom, *back, *front;
	};
	CubeSurfaces surfaces;
	surfaces.right = openImage(CubeFace::RIGHT, fs, path);
	surfaces.left = openImage(CubeFace::LEFT, fs, path);
	surfaces.top = openImage(CubeFace::TOP, fs, path);
	surfaces.bottom =openImage(CubeFace::BOTTOM, fs, path);
	surfaces.back = openImage(CubeFace::BACK, fs, path);
	surfaces.front = openImage(CubeFace::FRONT, fs, path);

	// Get dimensions
	glm::ivec2 size(surfaces.right->w, surfaces.right->h);
	PixelFormat format = Texture::determinePixelFormat(surfaces.right->format);

	CubemapBuffers buffers;
	buffers.right = static_cast<uint8_t*>(surfaces.right->pixels);
	buffers.left = static_cast<uint8_t*>(surfaces.left->pixels);
	buffers.top = static_cast<uint8_t*>(surfaces.top->pixels);
	buffers.bottom = static_cast<uint8_t*>(surfaces.bottom->pixels);
	buffers.back = static_cast<uint8_t*>(surfaces.back->pixels);
	buffers.front = static_cast<uint8_t*>(surfaces.front->pixels);

	id = loadCubemapFromMemory(renderer, shader_program, size, format, buffers);

	// Free SDL surface
	SDL_FreeSurface(surfaces.right);
	SDL_FreeSurface(surfaces.left);
	SDL_FreeSurface(surfaces.top);
	SDL_FreeSurface(surfaces.bottom);
	SDL_FreeSurface(surfaces.back);
	SDL_FreeSurface(surfaces.front);

	LOG_D("Cubemap id = " << id);
	return id;
}

template<typename Renderer>
GLuint Cubemap::loadCubemapFromMemory(Renderer& renderer,
		const ShaderPrograms shader_program,
		glm::ivec2 size,
		_3D::PixelFormat pixel_format,
		CubemapBuffers& buffers) {
	if(path == "") {
		path = "N/A";
	}
	id = renderer.createCubemap(shader_program, pixel_format, size, buffers);
	LOG_D("Cubemap id = " << id);
	return id;
}
} /* namespace _3D */
} /* namespace GameEngine */

#endif /* SRC_3D_CUBEMAP_TPP_ */
