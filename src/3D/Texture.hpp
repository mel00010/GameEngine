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
#ifndef SRC_TEXTURE_HPP_
#define SRC_TEXTURE_HPP_

#include <Util/ResourceDefs.hpp>

#include <GL/glew.h>
#include <Log.hpp>
#include <SDL2/SDL.h>

#include <string>

namespace GameEngine {
namespace _3D {

using InternalFormat = GLint;
using Format = GLenum;

struct GLFormat {
		InternalFormat i_format;
		Format e_format;
};

enum TextureType {
	DIFFUSE,
	SPECULAR,
	NORMAL,
	HEIGHT
};

inline std::ostream& operator<<(std::ostream& os, TextureType type) {
	switch(type) {
		case TextureType::DIFFUSE: 	return os << "TextureType::DIFFUSE";
		case TextureType::SPECULAR:	return os << "TextureType::SPECULAR";
		case TextureType::NORMAL:	return os << "TextureType::NORMAL";
		case TextureType::HEIGHT:	return os << "TextureType::HEIGHT";
	}
	return os;
}

class Texture {
	public:
		Texture() : id(-1), type(TextureType::DIFFUSE) {};
		Texture(GLuint _id, TextureType _type, std::string _path) : id(_id), type(_type), path(_path) {}
		Texture(const std::string file_path, const TextureType type) {
			loadTexture(file_path, type);
		}
		template <Enum ResourceID> Texture(const Resource<ResourceID> resource, TextureType _type = TextureType::DIFFUSE)
				: id(-1), type(_type) {
			loadTexture(resource);
		}


		Texture(const Texture& other) // copy constructor
				: Texture(other.id, other.type, other.path){}

		Texture(Texture&& other) noexcept // move constructor
				: Texture(other.id, other.type, other.path){
			other.id = -1;
			other.path = "";
		}

		Texture& operator=(const Texture& other) { // copy assignment
			 return *this = Texture(other);
		}

		Texture& operator=(Texture&& other) noexcept { // move assignment
			id = other.id;
			type = other.type;
			std::swap(path, other.path);
			return *this;
		}

		template <Enum ResourceID> GLuint loadTexture(const Resource<ResourceID> resource,
													  const TextureType _type = TextureType::DIFFUSE) {
			std::string file_location;
			char *base_path = SDL_GetBasePath();
			if (base_path) {
				file_location = base_path;
			} else {
				file_location = "./";
			}
			file_location += resource.file_path;
			return loadTexture(file_location, _type);
		}

		GLuint loadTexture(const std::string file_path, const TextureType _type = TextureType::DIFFUSE);

	protected:
		GLFormat determinePixelFormat(SDL_PixelFormat* format);


	public:
		GLuint id;
		TextureType type;
		std::string path;


};

inline std::ostream& operator<<(std::ostream& os, Texture text) {
	return os << "Texture {" << push_indent << "\n"
			<< "GLuint id = "<< text.id << "\n"
			<< "TextureType type = " << text.type << "\n"
			<< "std::string path = \"" << text.path << "\"\n"
			<< pop_indent << " }";
}

} /* namespace _3D */
} /* namespace GameEngine */


#endif /* SRC_TEXTURE_HPP_ */
