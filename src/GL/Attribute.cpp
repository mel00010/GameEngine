/******************************************************************************
 * Attribute.cpp
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

#include "Attribute.hpp"

#include <Log.hpp>

namespace GameEngine {
namespace GL {

Attribute::Attribute(std::string _name) : name(_name), location(-1), valid(false) { }

bool Attribute::init(ProgramRef program) {
	if(isValid()) {
		return isValid();
	}

	if( (location = glGetAttribLocation(program->getProgramHandle(), name.c_str()) ) < 0) {
		LOG_E("glGetAttribLocation(program, "<< name << ") returned " << location << "!  Could not bind attribute!");
		return (valid = false);
	}

	GLenum err;
	if((err = glGetError()) != GL_NO_ERROR && err == GL_INVALID_OPERATION) {
		LOG_E("glGetAttribLocation(program, "<< name << ") generated error GL_INVALID_OPERATION!  program is not a valid program object!");
		return (valid = false);
	}
	return (valid = true);
}

bool Attribute::isValid() 			{ return valid;	}
std::string Attribute::getName()	{ return name;		}
GLint Attribute::getLocation()		{ return location;	}

} /* namespace GL */
} /* namespace GameEngine */


