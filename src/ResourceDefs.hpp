/******************************************************************************
 * ResourceDefs.hpp
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
#ifndef SRC_RESOURCEDEFS_HPP_
#define SRC_RESOURCEDEFS_HPP_

#include <cstddef>
#include <type_traits>

enum class ResourceType : size_t {
		SHADER,
		IMAGE,
		MODEL,
		OTHER
};

template <typename T> concept Enum = std::is_enum<T>::value;

template<Enum ResourceID> class Resource {
	public:
		ResourceID id;
		ResourceType type;
		const char* file_path;
};



#endif /* SRC_RESOURCEDEFS_HPP_ */
