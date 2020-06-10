/******************************************************************************
 * EnumBitMask.hpp
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
#ifndef SRC_UTIL_ENUMBITMASK_HPP_
#define SRC_UTIL_ENUMBITMASK_HPP_

#include <type_traits>

/**
 * @brief Enable the usual bitwise operators on an enum class
 */
#define ENABLE_BITMASK_OPERATORS(x)                     \
  template <>                                           \
  struct game_engine::util::EnableBitMaskOperators<x> { \
    static const bool enable = true;                    \
  }

namespace game_engine::util {

/**
 * @brief Struct defining whether bitwise operators should be defined on an enum
 * class
 */
template <typename Enumerator>
struct EnableBitMaskOperators {
  static const bool enable = false;
};

/**
 * @brief OR operator overload for a generic enum, defined iff
 * EnableBitMaskOperators<Enumerator>::enable is true.
 * @param lhs An enum of class Enumerator
 * @param rhs An enum of class Enumerator
 * @return Returns lhs | rhs
 */
template <typename Enumerator>
typename std::enable_if<EnableBitMaskOperators<Enumerator>::enable,
                        Enumerator>::type
operator|(Enumerator lhs, Enumerator rhs) {
  using underlying = typename std::underlying_type<Enumerator>::type;
  return static_cast<Enumerator>(static_cast<underlying>(lhs) |
                                 static_cast<underlying>(rhs));
}

/**
 * @brief AND operator overload for a generic enum, defined iff
 * EnableBitMaskOperators<Enumerator>::enable is true.
 * @param lhs An enum of class Enumerator
 * @param rhs An enum of class Enumerator
 * @return Returns lhs & rhs
 */
template <typename Enumerator>
typename std::enable_if<EnableBitMaskOperators<Enumerator>::enable,
                        Enumerator>::type
operator&(Enumerator lhs, Enumerator rhs) {
  using underlying = typename std::underlying_type<Enumerator>::type;
  return static_cast<Enumerator>(static_cast<underlying>(lhs) &
                                 static_cast<underlying>(rhs));
}

/**
 * @brief XOR operator overload for a generic enum class, defined iff
 * EnableBitMaskOperators<Enumerator>::enable is true.
 * @param lhs An enum of class Enumerator
 * @param rhs An enum of class Enumerator
 * @return Returns lhs ^ rhs
 */
template <typename Enumerator>
typename std::enable_if<EnableBitMaskOperators<Enumerator>::enable,
                        Enumerator>::type
operator^(Enumerator lhs, Enumerator rhs) {
  using underlying = typename std::underlying_type<Enumerator>::type;
  return static_cast<Enumerator>(static_cast<underlying>(lhs) ^
                                 static_cast<underlying>(rhs));
}

/**
 * @brief NOT operator overload for a generic enum, defined iff
 * EnableBitMaskOperators<Enumerator>::enable is true.
 * @param rhs An enum of class Enumerator
 * @return Returns ~rhs
 */
template <typename Enumerator>
typename std::enable_if<EnableBitMaskOperators<Enumerator>::enable,
                        Enumerator>::type
operator~(Enumerator rhs) {
  using underlying = typename std::underlying_type<Enumerator>::type;
  return static_cast<Enumerator>(~static_cast<underlying>(rhs));
}

/**
 * @brief OR equal operator overload for a generic enum, defined iff
 * EnableBitMaskOperators<Enumerator>::enable is true.
 * @param lhs An enum of class Enumerator
 * @param rhs An enum of class Enumerator
 * @return Returns lhs |= rhs
 */
template <typename Enumerator>
typename std::enable_if<EnableBitMaskOperators<Enumerator>::enable,
                        Enumerator>::type
operator|=(Enumerator lhs, Enumerator rhs) {
  using underlying = typename std::underlying_type<Enumerator>::type;
  return static_cast<Enumerator>(static_cast<underlying>(lhs) |=
                                 static_cast<underlying>(rhs));
}

/**
 * @brief AND equal operator overload for a generic enum, defined iff
 * EnableBitMaskOperators<Enumerator>::enable is true.
 * @param lhs An enum of class Enumerator
 * @param rhs An enum of class Enumerator
 * @return Returns lhs &= rhs
 */
template <typename Enumerator>
typename std::enable_if<EnableBitMaskOperators<Enumerator>::enable,
                        Enumerator>::type
operator&=(Enumerator lhs, Enumerator rhs) {
  using underlying = typename std::underlying_type<Enumerator>::type;
  return static_cast<Enumerator>(static_cast<underlying>(lhs) &=
                                 static_cast<underlying>(rhs));
}

/**
 * @brief XOR equal operator overload for a generic enum class, defined iff
 * EnableBitMaskOperators<Enumerator>::enable is true.
 * @param lhs An enum of class Enumerator
 * @param rhs An enum of class Enumerator
 * @return Returns lhs ^= rhs
 */
template <typename Enumerator>
typename std::enable_if<EnableBitMaskOperators<Enumerator>::enable,
                        Enumerator>::type
operator^=(Enumerator lhs, Enumerator rhs) {
  using underlying = typename std::underlying_type<Enumerator>::type;
  return static_cast<Enumerator>(static_cast<underlying>(lhs) ^=
                                 static_cast<underlying>(rhs));
}

} /* namespace game_engine::util */

using namespace game_engine::util;

#endif /* SRC_UTIL_ENUMBITMASK_HPP_ */
