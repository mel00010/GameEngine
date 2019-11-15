/******************************************************************************
 * Texture.hpp
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
#ifndef SRC_3D_TEXTURE_HPP_
#define SRC_3D_TEXTURE_HPP_

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

enum class TextureType {
	DIFFUSE,
	SPECULAR,
	NORMAL,
	HEIGHT
};
std::ostream& operator<<(std::ostream& os, const TextureType type);


class Texture {
	public:
		Texture();
		Texture(GLuint _id, TextureType _type, std::string _path);

		template< typename Renderer >
		Texture( Renderer& renderer, cmrc::file file, const ShaderPrograms shader_program, const TextureType type);

		Texture(const Texture& other); // copy constructor
		Texture(Texture&& other) noexcept; // move constructor
		Texture& operator=(const Texture& other); // copy assignment
		Texture& operator=(Texture&& other) noexcept;// move assignment

		template<typename Renderer>
		GLuint loadTexture(Renderer& renderer, cmrc::file file,
				const ShaderPrograms shader_program,
				const TextureType _type = TextureType::DIFFUSE);
		template<typename Renderer>
		GLuint loadTextureFromMemory(Renderer& renderer, glm::ivec2 size, _3D::PixelFormat pixel_format,
				void* buffer,
				const ShaderPrograms shader_program,
				const TextureType _type = TextureType::DIFFUSE);


	protected:
		static PixelFormat determinePixelFormat(SDL_PixelFormat* format);
		friend class Cubemap;

	public:
		unsigned int id;
		TextureType type;
		std::string path;
};

std::ostream& operator<<(std::ostream& os, const Texture& text);

} /* namespace _3D */
} /* namespace GameEngine */

#include "Texture.tpp"

#endif /* SRC_3D_TEXTURE_HPP_ */
