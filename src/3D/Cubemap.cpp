/******************************************************************************
 * Cubemap.cpp
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

#include "Cubemap.hpp"

namespace GameEngine {
namespace _3D {

Cubemap::Cubemap() :
		id(-1) {
};
Cubemap::Cubemap(GLuint _id, std::string _path) :
		id(_id), path(_path) {
}

Cubemap::Cubemap(const Cubemap& other) // copy constructor
		: Cubemap(other.id, other.path){}

Cubemap::Cubemap(Cubemap&& other) noexcept // move constructor
		: Cubemap(other.id, other.path){
	other.id = -1;
	other.path = "";
}

Cubemap& Cubemap::operator=(const Cubemap& other) { // copy assignment
	 return *this = Cubemap(other);
}

Cubemap& Cubemap::operator=(Cubemap&& other) noexcept { // move assignment
	id = other.id;
	std::swap(path, other.path);
	return *this;
}


SDL_Surface* Cubemap::openImage(const CubeFace face, cmrc::embedded_filesystem& fs, const std::string& path) {
	std::string file_name;
	switch(face) {
		case CubeFace::RIGHT:
			file_name = "right";
			break;
		case CubeFace::LEFT:
			file_name = "left";
			break;
		case CubeFace::TOP:
			file_name = "top";
			break;
		case CubeFace::BOTTOM:
			file_name = "bottom";
			break;
		case CubeFace::BACK:
			file_name = "back";
			break;
		case CubeFace::FRONT:
			file_name = "front";
			break;
	}

	cmrc::file file = fs.open(path + "/" + file_name + ".png");
	std::vector<uint8_t> file_contents(file.begin(), file.end());
	SDL_Surface* surface = IMG_LoadTyped_RW(SDL_RWFromMem(file_contents.data(), file_contents.size()), 1, ".png");
	// Check if image data loaded ok
	if(surface == 0) {
		LOG_E("Error!  surface == 0");
		LOG_E("file.path() = " << file.path());
		throw EXIT_FAILURE;
	}
	// Get dimensions
	glm::ivec2 size(surface->w, surface->h);

	// Check that the image's dimensions are powers of 2
	if ( (size.x & (size.x - 1)) != 0 ) { 		LOG_W("Non power-of-two texture loaded: " + file.path());	}
	else if ( (size.y & (size.y - 1)) != 0 ) {	LOG_W("Non power-of-two texture loaded: " + file.path());	}

	return surface;
}
std::ostream& operator<<(std::ostream& os, const Cubemap& cube) {
	return os << "Cubemap {" << push_indent << "\n"
			<< "GLuint id = "<< cube.id << "\n"
			<< "std::string path = \"" << cube.path << "\"\n"
			<< pop_indent << " }";
}

} /* namespace _3D */
} /* namespace GameEngine */
