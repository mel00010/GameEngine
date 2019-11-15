/******************************************************************************
 * UUID.hpp
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
#ifndef SRC_UTIL_UUID_HPP_
#define SRC_UTIL_UUID_HPP_

#include "RNG.hpp"

#include <iomanip>
#include <ostream>
#include <string>
#include <sstream>

#include <Log.hpp>

namespace GameEngine {
namespace Util {

class UUID {
	public:
		UUID() : first_half(RNG::get()), second_half(RNG::get()) {}
		UUID(const uint64_t _first_half, const uint64_t _second_half = 0) :
				first_half(_first_half), second_half(_second_half) {}
	public:
		uint64_t first_half;	// most significant half
		uint64_t second_half;	// least significant half
};


inline bool operator==(const UUID lhs, const UUID rhs) {
	return (lhs.first_half == rhs.first_half) && (lhs.second_half == rhs.second_half);
}
inline bool operator!=(const UUID lhs, const UUID rhs) {
	return !(lhs == rhs);
}
inline bool operator<(const UUID lhs, const UUID rhs) {
	return (lhs.first_half < rhs.first_half) || ((lhs.first_half == rhs.first_half) && (lhs.second_half < rhs.second_half));
}
inline bool operator<=(const UUID lhs, const UUID rhs) {
	return (lhs == rhs) || (lhs < rhs);
}
inline bool operator>(const UUID lhs, const UUID rhs) {
	return (lhs.first_half > rhs.first_half) || ((lhs.first_half == rhs.first_half) && (lhs.second_half > rhs.second_half));
}
inline bool operator>=(const UUID lhs, const UUID rhs) {
	return (lhs == rhs) || (lhs > rhs);
}

inline std::ostream& operator<<(std::ostream& os, const UUID uuid) {
	std::stringstream ss;
	ss 	<< std::setfill('0') << std::setw(16) << std::hex << uuid.first_half;
	ss 	<< std::setfill('0') << std::setw(16) << std::hex << uuid.second_half;

	size_t j = 0;
	std::string s;
	for(auto& i : ss.str()) {
		if(j == 8 || j == 12 || j == 16 || j == 20) {
			s.push_back('-');
		}
		s.push_back(i);
		j++;
	}
	return os << s;
}

} /* namespace Util */
} /* namespace GameEngine */

using namespace GameEngine::Util;

#endif /* SRC_UTIL_UUID_HPP_ */
