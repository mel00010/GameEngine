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

#include <iomanip>
#include <ostream>
#include <sstream>
#include <string>
#include <utility>

#include "LoggerV2/Log.hpp"

#include "Util/Rng.hpp"

namespace game_engine::util {

class Uuid {
 public:
  Uuid() : first_half(Rng::get()), second_half(Rng::get()) {}
  Uuid& operator=(const Uuid& rhs) = default;
  Uuid(const Uuid& rhs) = default;
  Uuid& operator=(Uuid&& rhs) noexcept = default;
  Uuid(Uuid&& rhs) noexcept = default;
  ~Uuid() noexcept = default;

  explicit Uuid(const uint64_t _first_half, const uint64_t _second_half = 0)
      : first_half(_first_half), second_half(_second_half) {}

 public:
  uint64_t first_half{0};   // most significant half
  uint64_t second_half{0};  // least significant half

  void swap(Uuid& other) noexcept {
    using std::swap;
    swap(other.first_half, first_half);
    swap(other.second_half, second_half);
  }
};

inline bool operator==(const Uuid lhs, const Uuid rhs) {
  return (lhs.first_half == rhs.first_half) &&
         (lhs.second_half == rhs.second_half);
}
inline bool operator!=(const Uuid lhs, const Uuid rhs) { return !(lhs == rhs); }
inline bool operator<(const Uuid lhs, const Uuid rhs) {
  return (lhs.first_half < rhs.first_half) ||
         ((lhs.first_half == rhs.first_half) &&
          (lhs.second_half < rhs.second_half));
}
inline bool operator<=(const Uuid lhs, const Uuid rhs) {
  return (lhs == rhs) || (lhs < rhs);
}
inline bool operator>(const Uuid lhs, const Uuid rhs) {
  return (lhs.first_half > rhs.first_half) ||
         ((lhs.first_half == rhs.first_half) &&
          (lhs.second_half > rhs.second_half));
}
inline bool operator>=(const Uuid lhs, const Uuid rhs) {
  return (lhs == rhs) || (lhs > rhs);
}

inline std::ostream& operator<<(std::ostream& os, const Uuid uuid) {
  std::stringstream ss;
  ss << std::setfill('0') << std::setw(16) << std::hex << uuid.first_half;
  ss << std::setfill('0') << std::setw(16) << std::hex << uuid.second_half;

  size_t j = 0;
  std::string s;
  for (auto& i : ss.str()) {
    if (j == 8 || j == 12 || j == 16 || j == 20) {
      s.push_back('-');
    }
    s.push_back(i);
    j++;
  }
  return os << s;
}

inline void swap(Uuid& a, Uuid& b) noexcept { a.swap(b); }

} /* namespace game_engine::util */

using namespace game_engine::util;

#endif /* SRC_UTIL_UUID_HPP_ */
