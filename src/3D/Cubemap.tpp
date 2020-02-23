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

namespace game_engine {
namespace _3D {

template<typename Renderer>
Cubemap::Cubemap(const Renderer& renderer,
		const cmrc::embedded_filesystem& fs,
		const std::string& path,
		const ShaderPrograms shader_program) {
	LOG_D("Cubemap id_ = " << id_);
	id_ = -1;
	LoadCubemap(renderer, fs, path, shader_program);
}

template<typename Renderer>
GLuint Cubemap::LoadCubemap(const Renderer& renderer,
		const cmrc::embedded_filesystem& fs,
		const std::string& path,
		const ShaderPrograms shader_program) {
	renderer.UseShader(shader_program);
	struct CubeSurfaces {
			SDL_Surface *right, *left, *top, *bottom, *back, *front;
	};
	CubeSurfaces surfaces {};
	surfaces.right = OpenImage(CubeFace::RIGHT, fs, path);
	surfaces.left = OpenImage(CubeFace::LEFT, fs, path);
	surfaces.top = OpenImage(CubeFace::TOP, fs, path);
	surfaces.bottom =OpenImage(CubeFace::BOTTOM, fs, path);
	surfaces.back = OpenImage(CubeFace::BACK, fs, path);
	surfaces.front = OpenImage(CubeFace::FRONT, fs, path);

	// Get dimensions
	glm::ivec2 size(surfaces.right->w, surfaces.right->h);
	PixelFormat format = Texture::DeterminePixelFormat(surfaces.right->format);

	CubemapBuffers buffers;
	buffers.right = static_cast<uint8_t*>(surfaces.right->pixels);
	buffers.left = static_cast<uint8_t*>(surfaces.left->pixels);
	buffers.top = static_cast<uint8_t*>(surfaces.top->pixels);
	buffers.bottom = static_cast<uint8_t*>(surfaces.bottom->pixels);
	buffers.back = static_cast<uint8_t*>(surfaces.back->pixels);
	buffers.front = static_cast<uint8_t*>(surfaces.front->pixels);

	id_ = LoadCubemapFromMemory(renderer, size, format, buffers, shader_program);

	// Free SDL surface
	SDL_FreeSurface(surfaces.right);
	SDL_FreeSurface(surfaces.left);
	SDL_FreeSurface(surfaces.top);
	SDL_FreeSurface(surfaces.bottom);
	SDL_FreeSurface(surfaces.back);
	SDL_FreeSurface(surfaces.front);

	LOG_D("Cubemap id_ = " << id_);
	return id_;
}

template<typename Renderer>
GLuint Cubemap::LoadCubemapFromMemory(const Renderer& renderer,
		const glm::ivec2 size,
		const _3D::PixelFormat pixel_format,
		const CubemapBuffers& buffers,
		const ShaderPrograms shader_program) {
	if(path_ == "") {
		path_ = "N/A";
	}
	id_ = renderer.CreateCubemap(shader_program, pixel_format, size, buffers);
	LOG_D("Cubemap id_ = " << id_);
	return id_;
}
} /* namespace _3D */
} /* namespace game_engine */

#endif /* SRC_3D_CUBEMAP_TPP_ */
