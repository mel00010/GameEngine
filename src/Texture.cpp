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

namespace GameEngine {


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
//		LOG_D(result.data());

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

	//Check colour format
	if (surface->format->BytesPerPixel != 4 && surface->format->BytesPerPixel != 3) {
		//Unsupported type
		LOG_E("Unsupported texture colour format: " << file_location
				<< " with " << surface->format->BytesPerPixel << " bytes per pixel");
		SDL_FreeSurface(surface);
		throw EXIT_FAILURE;
	}
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
	glGenerateMipmap(GL_TEXTURE_2D);

	//Free SDL surface
	SDL_FreeSurface(surface);

	return texture;
}



} /* namespace GameEngine */


