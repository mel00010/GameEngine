/******************************************************************************
 * VboHandle.hpp
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
#ifndef SRC_VBOHANDLE_HPP_
#define SRC_VBOHANDLE_HPP_

#include <Util/Uuid.hpp>

#include <Log.hpp>
#include <utility>

namespace game_engine {

/**
 * @brief Handle class for VBO objects
 */
class VboHandle {
	public:
		/**
		 * @brief UUID of the referenced VBO
		 */
		Uuid uuid_ = Uuid(0);
		/**
		 * @brief Bool representing the validity of the handle
		 */
		bool valid_ = false;

	public:
		VboHandle() : uuid_(), valid_(true) {}
		VboHandle(Uuid uuid, bool valid) : uuid_(uuid), valid_(valid) {}

		void swap(VboHandle& other) noexcept {
			using std::swap;
			swap(other.uuid_, uuid_);
			swap(other.valid_, valid_);
		}
};

inline bool operator==(const VboHandle lhs, const VboHandle rhs) {
	return (lhs.uuid_ == rhs.uuid_) && (lhs.valid_ == rhs.valid_);
}
inline bool operator!=(const VboHandle lhs, const VboHandle rhs) {
	return !(lhs == rhs);
}
inline bool operator<(const VboHandle lhs, const VboHandle rhs) {
	return lhs.uuid_ < rhs.uuid_;
}
inline bool operator<=(const VboHandle lhs, const VboHandle rhs) {
	return (lhs == rhs) || (lhs < rhs);
}
inline bool operator>(const VboHandle lhs, const VboHandle rhs) {
	return lhs.uuid_ > rhs.uuid_;
}
inline bool operator>=(const VboHandle lhs, const VboHandle rhs) {
	return (lhs == rhs) || (lhs > rhs);
}

inline std::ostream& operator<<(std::ostream& os, const VboHandle handle) {
	os << "VboHandle {" << push_indent << std::endl;
	os << "Uuid uuid_ = " << handle.uuid_ << std::endl;
	os << "bool valid_ = " << std::boolalpha << handle.valid_ << std::endl;
	os << pop_indent << "}";
	return os;
}

inline void swap(VboHandle& a, VboHandle& b) noexcept {
	a.swap(b);
}

} /* namespace game_engine */




#endif /* SRC_VBOHANDLE_HPP_ */
