/******************************************************************************
 * ShaderPrograms.hpp
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
#ifndef SRC_SHADERPROGRAMS_HPP_
#define SRC_SHADERPROGRAMS_HPP_

#include <Util/EnumBitMask.hpp>

#include <GL/glew.h>
#include <Log.hpp>

namespace GameEngine {

enum class ShaderPrograms : GLuint {
		NULL_SHADER = 0,
		DEFAULT = (1 << 0),
		TEXT = (1 << 1),
		SKYBOX = (1 << 2)
};
ENABLE_BITMASK_OPERATORS(ShaderPrograms);

inline std::ostream& operator<<(std::ostream& os, const ShaderPrograms sp) {
	std::string out;
	if(sp == ShaderPrograms::NULL_SHADER) {
		return os << "ShaderPrograms::NULL_SHADER";
	}
	if((sp & ShaderPrograms::DEFAULT) != ShaderPrograms::NULL_SHADER) {
		if(out.length() != 0) {
				out += " | ";
		}
		out += "DEFAULT";
	}
	if((sp & ShaderPrograms::TEXT) != ShaderPrograms::NULL_SHADER) {
		if(out.length() != 0) {
				out += " | ";
		}
		out += "TEXT";
	}
	if((sp & ShaderPrograms::SKYBOX) != ShaderPrograms::NULL_SHADER) {
		if(out.length() != 0) {
				out += " | ";
		}
		out += "SKYBOX";
	}
	return os << out;
}

} /* namespace GameEngine */

#endif /* SRC_SHADERPROGRAMS_HPP_ */
