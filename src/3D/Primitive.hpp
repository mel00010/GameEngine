/******************************************************************************
 * Primitive.hpp
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
#ifndef SRC_PRIMITIVE_HPP_
#define SRC_PRIMITIVE_HPP_

#include <GL/glew.h>

namespace GameEngine {
namespace _3D {

enum class Primitive : GLenum {
	POINTS = GL_POINTS,
	LINES = GL_LINES,
	LINE_STRIP = GL_LINE_STRIP,
	LINE_LOOP = GL_LINE_LOOP,
	TRIANGLES = GL_TRIANGLES,
	TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
	TRIANGLE_FAN = GL_TRIANGLE_FAN,
	QUADS = GL_QUADS,
	QUAD_STRIP = GL_QUAD_STRIP,
	PATCHES = GL_PATCHES
};

inline std::ostream& operator<<(std::ostream& os, Primitive p) {
	switch(p) {
		case Primitive::POINTS: 		return os << "Primitive::POINTS";
		case Primitive::LINES: 			return os << "Primitive::LINES";
		case Primitive::LINE_STRIP: 	return os << "Primitive::LINE_STRIP";
		case Primitive::LINE_LOOP: 		return os << "Primitive::LINE_LOOP";
		case Primitive::TRIANGLES: 		return os << "Primitive::TRIANGLES";
		case Primitive::TRIANGLE_STRIP:	return os << "Primitive::TRIANGLE_STRIP";
		case Primitive::TRIANGLE_FAN: 	return os << "Primitive::TRIANGLE_FAN";
		case Primitive::QUADS:			return os << "Primitive::QUADS";
		case Primitive::QUAD_STRIP: 	return os << "Primitive::QUAD_STRIP";
		case Primitive::PATCHES: 		return os << "Primitive::PATCHES";
	}
	return os;
}

} /* namespace _3D */
} /* namespace GameEngine */



#endif /* SRC_PRIMITIVE_HPP_ */
