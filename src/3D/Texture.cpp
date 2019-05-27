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

GLFormat Texture::determinePixelFormat(SDL_PixelFormat* format) {
	GLFormat f;

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
		LOG_E("Unsupported pixel format in file " << path << "!");
		LOG_E("format->Rmask = " << hex(format->Rmask));
		LOG_E("format->Gmask = " << hex(format->Gmask));
		LOG_E("format->Bmask = " << hex(format->Bmask));
		LOG_E("format->Amask = " << hex(format->Amask));
		f.e_format = GL_RGBA; f.i_format = GL_RGBA;
		throw EXIT_FAILURE;
	}
	return f;
}

GLuint Texture::loadTexture(const std::string file_path, const TextureType _type) {
	path = file_path;

	// New SDL surface and load the image
	SDL_Surface *surface = IMG_Load(file_path.c_str());

	// Check if image data loaded ok
	if(surface == 0) {
		LOG_E("Error!  surface == 0");
		LOG_E("file_path = " << file_path);
		LOG_E("texture_type = " << _type);

		throw EXIT_FAILURE;
	}

	// Get dimensions
	int width = surface->w;
	int height = surface->h;

	// Check that the image's dimensions are powers of 2
	if ( (width & (width - 1)) != 0 ) { 		LOG_W("Non power-of-two texture loaded: " + file_path);	}
	else if ( (height & (height - 1)) != 0 ) {	LOG_W("Non power-of-two texture loaded: " + file_path);	}

	GLFormat f = determinePixelFormat(surface->format);

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	// Set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, f.i_format, width, height, 0, f.e_format, GL_UNSIGNED_BYTE, surface->pixels);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Free SDL surface
	SDL_FreeSurface(surface);

	return id;
}

} /* namespace _3D */
} /* namespace GameEngine */
