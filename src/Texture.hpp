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

#include <GL/glew.h>

class Resource;

namespace GameEngine {

enum TextureType {
	DIFFUSE,
	SPECULAR
};

class Texture {
	public:
		Texture() : id(-1), type(TextureType::DIFFUSE) {};
		Texture(Resource resource_id);
		GLuint loadTexture(Resource resource_id);

	public:
		GLuint id;
		TextureType type;
};

} /* namespace GameEngine */



#endif /* SRC_TEXTURE_HPP_ */
