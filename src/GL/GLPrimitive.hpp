/******************************************************************************
 * GLPrimitive.hpp
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
#ifndef SRC_GL_GLPRIMITIVE_HPP_
#define SRC_GL_GLPRIMITIVE_HPP_

#include <3D/Primitive.hpp>

#include <GL/glew.h>
#include <ostream>

namespace GameEngine {
namespace GL {

enum class GLPrimitive : GLenum {
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

inline std::ostream& operator<<(std::ostream& os, const GLPrimitive p) {
	switch(p) {
		case GLPrimitive::POINTS:			return os << "GLPrimitive::POINTS";
		case GLPrimitive::LINES:			return os << "GLPrimitive::LINES";
		case GLPrimitive::LINE_STRIP:		return os << "GLPrimitive::LINE_STRIP";
		case GLPrimitive::LINE_LOOP:		return os << "GLPrimitive::LINE_LOOP";
		case GLPrimitive::TRIANGLES:		return os << "GLPrimitive::TRIANGLES";
		case GLPrimitive::TRIANGLE_STRIP:	return os << "GLPrimitive::TRIANGLE_STRIP";
		case GLPrimitive::TRIANGLE_FAN:		return os << "GLPrimitive::TRIANGLE_FAN";
		case GLPrimitive::QUADS:			return os << "GLPrimitive::QUADS";
		case GLPrimitive::QUAD_STRIP:		return os << "GLPrimitive::QUAD_STRIP";
		case GLPrimitive::PATCHES:			return os << "GLPrimitive::PATCHES";
	}
	return os;
}

inline GLPrimitive convert(const _3D::Primitive p) {
	switch(p) {
		case _3D::Primitive::POINTS:			return GLPrimitive::POINTS;
		case _3D::Primitive::LINES:				return GLPrimitive::LINES;
		case _3D::Primitive::LINE_STRIP:		return GLPrimitive::LINE_STRIP;
		case _3D::Primitive::LINE_LOOP:			return GLPrimitive::LINE_LOOP;
		case _3D::Primitive::TRIANGLES:			return GLPrimitive::TRIANGLES;
		case _3D::Primitive::TRIANGLE_STRIP:	return GLPrimitive::TRIANGLE_STRIP;
		case _3D::Primitive::TRIANGLE_FAN:		return GLPrimitive::TRIANGLE_FAN;
		case _3D::Primitive::QUADS:				return GLPrimitive::QUADS;
		case _3D::Primitive::QUAD_STRIP:		return GLPrimitive::QUAD_STRIP;
		case _3D::Primitive::PATCHES:			return GLPrimitive::PATCHES;
	}
	return GLPrimitive::TRIANGLES;
}

} /* namespace GL */
} /* namespace GameEngine */



#endif /* SRC_GL_GLPRIMITIVE_HPP_ */
