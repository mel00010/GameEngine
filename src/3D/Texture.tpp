/******************************************************************************
 * Texture.tpp
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
#ifndef SRC_3D_TEXTURE_TPP_
#define SRC_3D_TEXTURE_TPP_

#include "Texture.hpp"

#include <glm/glm.hpp>

namespace GameEngine {
namespace _3D {

template<typename Renderer>
Texture::Texture(Renderer& renderer,
		cmrc::file file,
		const ShaderPrograms shader_program,
		const TextureType type) :
		id(-1), type(TextureType::DIFFUSE) {
	loadTexture(renderer, file, shader_program, type);
}

template<typename Renderer>
GLuint Texture::loadTexture(Renderer& renderer,
		cmrc::file file,
		const ShaderPrograms shader_program,
		const TextureType _type) {
//	LOG_D("Opening " << file.path());
	std::vector<uint8_t> file_contents(file.begin(), file.end());
	path = file.path();
	std::string ext;
	if(path.rfind('.') == std::string::npos) {
		ext = path;
	} else {
		ext = path.substr(path.rfind('.'));
	}

	// New SDL surface and load the image
	SDL_Surface *surface = IMG_LoadTyped_RW(SDL_RWFromMem(file_contents.data(), file_contents.size()), 1, ext.c_str());

	// Check if image data loaded ok
	if(surface == 0) {
		LOG_E("Error!  surface == 0");
		LOG_E("file.path() = " << file.path());
		LOG_E("texture_type = " << _type);

		throw EXIT_FAILURE;
	}

	// Get dimensions
	glm::ivec2 size(surface->w, surface->h);

	// Check that the image's dimensions are powers of 2
	if ( (size.x & (size.x - 1)) != 0 ) { 		LOG_W("Non power-of-two texture loaded: " + file.path());	}
	else if ( (size.y & (size.y - 1)) != 0 ) {	LOG_W("Non power-of-two texture loaded: " + file.path());	}

	PixelFormat format = determinePixelFormat(surface->format);

	loadTextureFromMemory(renderer, size, format, surface->pixels, shader_program, _type);

	// Free SDL surface
	SDL_FreeSurface(surface);

	return id;
}

template<typename Renderer>
GLuint Texture::loadTextureFromMemory(Renderer& renderer,
		glm::ivec2 size,
		_3D::PixelFormat pixel_format,
		void* buffer,
		const ShaderPrograms shader_program,
		const TextureType _type) {
	if(path == "") {
		path = "N/A";
	}
	type = _type;
	id = renderer.createTexture(shader_program, pixel_format, size, buffer);
	return id;
}
} /* namespace _3D */
} /* namespace GameEngine */

#endif /* SRC_3D_TEXTURE_TPP_ */
