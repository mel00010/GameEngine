/******************************************************************************
 * VBO_handle.hpp
 * Copyright (C) 2019  Mel McCalla <melmccalla@gmail.com>
 *
 * This file is part of GameEngineMin.
 *
 * GameEngineMin is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GameEngineMin is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GameEngineMin.  If not, see <http://www.gnu.org/licenses/>.
 *****************************************************************************/
#ifndef SRC_VBO_HANDLE_HPP_
#define SRC_VBO_HANDLE_HPP_

#include <Util/UUID.hpp>

#include <Log.hpp>

namespace GameEngine {

/**
 * @brief Handle class for VBO objects
 */
class VBO_handle {
	public:
		/**
		 * @brief UUID of the referenced VBO
		 */
		UUID uuid = UUID(0);
		/**
		 * @brief Bool representing the validity of the handle
		 */
		bool valid = false;

	public:
		VBO_handle() : uuid(0), valid(false) {}
		VBO_handle(UUID _uuid, bool _valid) : uuid(_uuid), valid(_valid) {}
};

inline bool operator==(const VBO_handle lhs, const VBO_handle rhs) {
	return (lhs.uuid == rhs.uuid) && (lhs.valid == rhs.valid);
}
inline bool operator!=(const VBO_handle lhs, const VBO_handle rhs) {
	return !(lhs == rhs);
}
inline bool operator<(const VBO_handle lhs, const VBO_handle rhs) {
	return lhs.uuid < rhs.uuid;
}
inline bool operator<=(const VBO_handle lhs, const VBO_handle rhs) {
	return (lhs == rhs) || (lhs < rhs);
}
inline bool operator>(const VBO_handle lhs, const VBO_handle rhs) {
	return lhs.uuid > rhs.uuid;
}
inline bool operator>=(const VBO_handle lhs, const VBO_handle rhs) {
	return (lhs == rhs) || (lhs > rhs);
}

inline std::ostream& operator<<(std::ostream& os, const VBO_handle handle) {
	os << "VBO_handle {" << push_indent << std::endl;
	os << "UUID uuid = " << handle.uuid << std::endl;
	os << "bool valid = " << std::boolalpha << handle.valid << std::endl;
	os << pop_indent << "}";
	return os;
}


} /* namespace GameEngine */




#endif /* SRC_VBO_HANDLE_HPP_ */
