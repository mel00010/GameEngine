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
#include <utility>


namespace game_engine {
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
		Cubemap() = default;
		Cubemap& operator=(const Cubemap& rhs) = default;
		Cubemap(const Cubemap& rhs) = default;
		Cubemap& operator=(Cubemap&& rhs) noexcept = default;
		Cubemap(Cubemap&& rhs) noexcept = default;
		~Cubemap() noexcept = default;

		Cubemap(const GLuint _id, const std::string _path) : id_(_id), path_(_path) {}

		template< typename Renderer >
		Cubemap( const Renderer& renderer, const cmrc::embedded_filesystem& fs, const std::string& path, const ShaderPrograms shader_program);

		template<typename Renderer>
		GLuint LoadCubemap(const Renderer& renderer, const cmrc::embedded_filesystem& fs, const std::string& path, const ShaderPrograms shader_program);
		template<typename Renderer>
		GLuint LoadCubemapFromMemory(const Renderer& renderer, const glm::ivec2 size,
				const _3D::PixelFormat pixel_format, const CubemapBuffers& buffers, const ShaderPrograms shader_program);


	protected:
		PixelFormat DeterminePixelFormat(const SDL_PixelFormat* format);
		SDL_Surface* OpenImage(const CubeFace face, const cmrc::embedded_filesystem& fs, const std::string& path);


	public:
		GLuint id_ { };
		std::string path_ { };

		void swap(Cubemap& other) noexcept {
			using std::swap;
			swap(other.id_, id_);
			swap(other.path_, path_);
		}
};

std::ostream& operator<<(std::ostream& os, const Cubemap& text);

inline void swap(Cubemap& a, Cubemap& b) noexcept {
	a.swap(b);
}

} /* namespace _3D */
} /* namespace game_engine */

#include "Cubemap.tpp"

#endif /* SRC_3D_CUBEMAP_HPP_ */
