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

#include "ResourceDefs.hpp"

#include <GL/glew.h>
#include <string>

namespace GameEngine {

enum TextureType {
	DIFFUSE,
	SPECULAR
};

class Texture {
	public:
		Texture() : id(-1), type(TextureType::DIFFUSE) {};
		Texture(const std::string resource_id);
		template <Enum ResourceID> Texture(const Resource<ResourceID> resource) : id(-1), type(TextureType::DIFFUSE) {
			loadTexture(resource);
		}
		template <Enum ResourceID> GLuint loadTexture(const Resource<ResourceID> resource_id) {
			return loadTexture(resource_id.file_path);
		}
		GLuint loadTexture(const std::string resource_id);

	public:
		GLuint id;
		TextureType type;
};

} /* namespace GameEngine */



#endif /* SRC_TEXTURE_HPP_ */
