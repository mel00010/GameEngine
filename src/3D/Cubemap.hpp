/******************************************************************************
 * Cubemap.hpp
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
#ifndef SRC_3D_CUBEMAP_HPP_
#define SRC_3D_CUBEMAP_HPP_

#include "PixelFormat.hpp"

#include <ShaderPrograms.hpp>

#include <Log.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include <cmrc/cmrc.hpp>

#include <string>


namespace GameEngine {
namespace _3D {

struct CubemapBuffers {
	public:
		union {
			struct { uint8_t *positive_x, *negative_x, *positive_y, *negative_y, *positive_z, *negative_z; };
			struct { uint8_t *right, *left, *top, *bottom, *back, *front; };
		};
};

enum class CubeFace : GLuint {
	RIGHT = 0,
	LEFT,
	TOP,
	BOTTOM,
	BACK,
	FRONT,
	POSITIVE_X = RIGHT,
	NEGATIVE_X = LEFT,
	POSITIVE_Y = TOP,
	NEGATIVE_Y = BOTTOM,
	POSITIVE_Z = BACK,
	NEGATIVE_Z = FRONT
};

class Cubemap {
	public:
		Cubemap();
		Cubemap(GLuint _id, std::string _path);

		template< typename Renderer >
		Cubemap( Renderer& renderer, const ShaderPrograms shader_program, cmrc::embedded_filesystem& fs, const std::string& path);

		Cubemap(const Cubemap& other); // copy constructor
		Cubemap(Cubemap&& other) noexcept; // move constructor
		Cubemap& operator=(const Cubemap& other); // copy assignment
		Cubemap& operator=(Cubemap&& other) noexcept;// move assignment

		template<typename Renderer>
		GLuint loadCubemap(Renderer& renderer, const ShaderPrograms shader_program, cmrc::embedded_filesystem& fs, const std::string& path);
		template<typename Renderer>
		GLuint loadCubemapFromMemory(Renderer& renderer, const ShaderPrograms shader_program, glm::ivec2 size,
				_3D::PixelFormat pixel_format, CubemapBuffers& buffers);


	protected:
		PixelFormat determinePixelFormat(SDL_PixelFormat* format);
		SDL_Surface* openImage(const CubeFace face, cmrc::embedded_filesystem& fs, const std::string& path);


	public:
		GLuint id;
		std::string path;
};

std::ostream& operator<<(std::ostream& os, const Cubemap& text);

} /* namespace _3D */
} /* namespace GameEngine */

#include "Cubemap.tpp"

#endif /* SRC_3D_CUBEMAP_HPP_ */
