/******************************************************************************
 * Texture.cpp
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

#include "Texture.hpp"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <SDL2/SDL_image.h>
#include <Log.hpp>

#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>

namespace GameEngine {
namespace _3D {

Texture::Texture() :
		id(-1), type(TextureType::DIFFUSE) {

};
Texture::Texture(GLuint _id, TextureType _type, std::string _path) :
		id(_id), type(_type), path(_path) {

}

Texture::Texture(const Texture& other) // copy constructor
		: Texture(other.id, other.type, other.path){}

Texture::Texture(Texture&& other) noexcept // move constructor
		: Texture(other.id, other.type, other.path){
	other.id = -1;
	other.path = "";
}

Texture& Texture::operator=(const Texture& other) { // copy assignment
	 return *this = Texture(other);
}

Texture& Texture::operator=(Texture&& other) noexcept { // move assignment
	id = other.id;
	type = other.type;
	std::swap(path, other.path);
	return *this;
}


enum Color {
		EMPTY = -1,
		RED = 0,
		GREEN = 1,
		BLUE = 2,
		ALPHA = 3
};

bool isRed(Color color) {	return (color == RED);   }
bool isGreen(Color color) {	return (color == GREEN); }
bool isBlue(Color color) {	return (color == BLUE);  }
bool isAlpha(Color color) {	return (color == ALPHA); }
bool isEmpty(Color color) {	return (color == EMPTY); }

PixelFormat Texture::determinePixelFormat(SDL_PixelFormat* format) {
	PixelFormat f;

	Color bytes[4] = {EMPTY, EMPTY, EMPTY, EMPTY};

	if(format->Rmask & 0x000000FF) { bytes[0] = RED; }
	if(format->Rmask & 0x0000FF00) { bytes[1] = RED; }
	if(format->Rmask & 0x00FF0000) { bytes[2] = RED; }
	if(format->Rmask & 0xFF000000) { bytes[3] = RED; }

	if(format->Gmask & 0x000000FF) { bytes[0] = GREEN; }
	if(format->Gmask & 0x0000FF00) { bytes[1] = GREEN; }
	if(format->Gmask & 0x00FF0000) { bytes[2] = GREEN; }
	if(format->Gmask & 0xFF000000) { bytes[3] = GREEN; }

	if(format->Bmask & 0x000000FF) { bytes[0] = BLUE; }
	if(format->Bmask & 0x0000FF00) { bytes[1] = BLUE; }
	if(format->Bmask & 0x00FF0000) { bytes[2] = BLUE; }
	if(format->Bmask & 0xFF000000) { bytes[3] = BLUE; }

	if(format->Amask & 0x000000FF) { bytes[0] = ALPHA; }
	if(format->Amask & 0x0000FF00) { bytes[1] = ALPHA; }
	if(format->Amask & 0x00FF0000) { bytes[2] = ALPHA; }
	if(format->Amask & 0xFF000000) { bytes[3] = ALPHA; }

	if(     isRed(bytes[0])  && isGreen(bytes[1]) && isBlue(bytes[2])  && isAlpha(bytes[3])) { f.e_format = GL_RGBA; f.i_format = GL_RGBA; }
	else if(isRed(bytes[0])  && isGreen(bytes[1]) && isBlue(bytes[2])  && isEmpty(bytes[3])) { f.e_format = GL_RGB;  f.i_format = GL_RGB;  }
	else if(isBlue(bytes[0]) && isGreen(bytes[1]) && isRed(bytes[2])   && isAlpha(bytes[3])) { f.e_format = GL_BGRA; f.i_format = GL_RGBA; }
	else if(isBlue(bytes[0]) && isGreen(bytes[1]) && isRed(bytes[2])   && isEmpty(bytes[3])) { f.e_format = GL_BGR;  f.i_format = GL_RGB;  }
	else if(isRed(bytes[0])  && isGreen(bytes[1]) && isEmpty(bytes[2]) && isEmpty(bytes[3])) { f.e_format = GL_RG;   f.i_format = GL_RG;   }
	else if(isRed(bytes[0])  && isEmpty(bytes[1]) && isEmpty(bytes[2]) && isEmpty(bytes[3])) { f.e_format = GL_RED;  f.i_format = GL_RED;  }
	else {
		LOG_E("Unsupported pixel format in file!");
		LOG_E("format->Rmask = " << hex(format->Rmask));
		LOG_E("format->Gmask = " << hex(format->Gmask));
		LOG_E("format->Bmask = " << hex(format->Bmask));
		LOG_E("format->Amask = " << hex(format->Amask));
		f.e_format = GL_RGBA; f.i_format = GL_RGBA;
		throw EXIT_FAILURE;
	}
	return f;
}

std::ostream& operator<<(std::ostream& os, const Texture& text) {
	return os << "Texture {" << push_indent << "\n"
			<< "GLuint id = "<< text.id << "\n"
			<< "TextureType type = " << text.type << "\n"
			<< "std::string path = \"" << text.path << "\"\n"
			<< pop_indent << " }";
}
std::ostream& operator<<(std::ostream& os, const TextureType type) {
	switch(type) {
		case TextureType::DIFFUSE: 	return os << "TextureType::DIFFUSE";
		case TextureType::SPECULAR:	return os << "TextureType::SPECULAR";
		case TextureType::NORMAL:	return os << "TextureType::NORMAL";
		case TextureType::HEIGHT:	return os << "TextureType::HEIGHT";
	}
	return os;
}

} /* namespace _3D */
} /* namespace GameEngine */
