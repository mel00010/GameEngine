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
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <Log.hpp>

#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>


enum class ResourceID : size_t;
enum class ResourceType : size_t;
class Resource {
	public:
		ResourceID id;
		ResourceType type;
		const char* file_path;
};

using InternalFormat = GLint;
using Format = GLenum;

namespace GameEngine {

struct GLFormat {
		InternalFormat i_format;
		Format e_format;
};

enum Color {
		EMPTY = -1,
		RED = 0,
		GREEN = 1,
		BLUE = 2,
		ALPHA = 3
};


bool isRed(Color color) {
	return (color == RED);
}
bool isGreen(Color color) {
	return (color == GREEN);
}
bool isBlue(Color color) {
	return (color == BLUE);
}
bool isAlpha(Color color) {
	return (color == ALPHA);
}
bool isEmpty(Color color) {
	return (color == EMPTY);
}

GLFormat determinePixelFormat(SDL_PixelFormat* format) {
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

//	for(size_t i = 0; i < 4 ; i++) {
//		switch(bytes[i]) {
//			case EMPTY:
//				LOG_D("bytes[" << i << "] = EMPTY");
//				break;
//			case RED:
//				LOG_D("bytes[" << i << "] = RED" );
//				break;
//			case GREEN:
//				LOG_D("bytes[" << i << "] = GREEN");
//				break;
//			case BLUE:
//				LOG_D("bytes[" << i << "] = BLUE");
//				break;
//			case ALPHA:
//				LOG_D("bytes[" << i << "] = ALPHA");
//				break;
//		}
//	}

	if(isRed(bytes[0]) && isGreen(bytes[1]) && isBlue(bytes[2])  && isAlpha(bytes[3])) {
		f.e_format = GL_RGBA;
		f.i_format = GL_RGBA;
		return f;
	}
	if(isRed(bytes[0]) && isGreen(bytes[1]) && isBlue(bytes[2])  && isEmpty(bytes[3])) {
		f.e_format = GL_RGB;
		f.i_format = GL_RGB;
		return f;
	}
	if(isBlue(bytes[0]) && isGreen(bytes[1]) && isRed(bytes[2])  && isAlpha(bytes[3])) {
		f.e_format = GL_BGRA;
		f.i_format = GL_RGBA;
		return f;
	}
	if(isBlue(bytes[0]) && isGreen(bytes[1]) && isRed(bytes[2])  && isEmpty(bytes[3])) {
		f.e_format = GL_BGR;
		f.i_format = GL_RGB;
		return f;
	}

	if(isRed(bytes[0]) && isGreen(bytes[1]) && isEmpty(bytes[2]) && isEmpty(bytes[3])) {
		f.e_format = GL_RG;
		f.i_format = GL_RG;
	}
	if(isRed(bytes[0]) && isEmpty(bytes[1]) && isEmpty(bytes[2]) && isEmpty(bytes[3])) {
		f.e_format = GL_RED;
		f.i_format = GL_RED;
	}


	LOG_F("Unsupported pixel format!");
	throw EXIT_FAILURE;
}

Texture::Texture(Resource resource) {
	loadTexture(resource);
}

GLuint Texture::loadTexture(Resource resource) {
	std::string file_location;
	char *base_path = SDL_GetBasePath();
	if (base_path) {
		file_location = base_path;
	} else {
		file_location = SDL_strdup("./");
	}
	file_location+=resource.file_path;
//	LOG_D("Loading texture at " << file_location);

	//New SDL surface
	SDL_Surface *surface;

	//Load the image
	surface = IMG_Load(file_location.c_str());

	//Check if image data loaded ok
	if(surface == 0) {
		LOG_E("surface == 0");
		throw EXIT_FAILURE;
	}

	//Get dimensions
	int width = surface->w;
	int height = surface->h;

	// Check that the image's width is a power of 2
	if ( (width & (width - 1)) != 0 ) {
		LOG_W("Non power-of-two texture loaded: " + file_location);
	} else if ( (height & (height - 1)) != 0 ) { // Also check if the height is a power of 2
		LOG_W("Non power-of-two texture loaded: " + file_location);
	}

	GLFormat f = determinePixelFormat(surface->format);

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, f.i_format, width, height, 0, f.e_format, GL_UNSIGNED_BYTE, surface->pixels);
	glGenerateMipmap(GL_TEXTURE_2D);

	//Free SDL surface
	SDL_FreeSurface(surface);

	return id;
}



} /* namespace GameEngine */


