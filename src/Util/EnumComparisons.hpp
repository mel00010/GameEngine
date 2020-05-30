/******************************************************************************
 * EnumComparisons.hpp
 * Copyright (C) 2020  Mel McCalla <melmccalla@gmail.com>
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
#ifndef SRC_UTIL_ENUMCOMPARISONS_HPP_
#define SRC_UTIL_ENUMCOMPARISONS_HPP_

#include <type_traits>

/**
 * @brief Enable the usual bitwise operators on an enum class
 */
#define ENABLE_COMPARISON_OPERATORS(x)                     \
  template <>                                              \
  struct game_engine::util::EnableComparisonOperators<x> { \
    static const bool enable = true;                       \
  }

namespace game_engine {
namespace util {

/**
 * @brief Struct defining whether comparison operators should be defined on an
 * enum class
 */
template <typename Enumerator>
struct EnableComparisonOperators {
  static const bool enable = false;
};

/**
 * @brief Less than overload for a generic enum, defined iff
 * EnableComparisonOperators<Enumerator>::enable is true.
 * @param lhs An enum of class Enumerator
 * @param rhs An enum of class Enumerator
 * @return Returns lhs < rhs
 */
template <typename Enumerator>
typename std::enable_if<EnableComparisonOperators<Enumerator>::enable,
                        bool>::type
operator<(const Enumerator lhs, const Enumerator rhs) {
  using underlying = typename std::underlying_type<Enumerator>::type;
  return static_cast<const underlying>(lhs) <
         static_cast<const underlying>(rhs);
}

/**
 * @brief Less than overload for a generic enum, defined iff
 * EnableComparisonOperators<Enumerator>::enable is true.
 * @param lhs An enum of class Enumerator
 * @param rhs An integer of type Integer
 * @return Returns lhs < rhs
 */
template <typename Enumerator, typename Integer>
typename std::enable_if<EnableComparisonOperators<Enumerator>::enable,
                        bool>::type
operator<(const Enumerator lhs, const Integer rhs) {
  using underlying = typename std::underlying_type<Enumerator>::type;
  return static_cast<const underlying>(lhs) < rhs;
}

/**
 * @brief Less than overload for a generic enum, defined iff
 * EnableComparisonOperators<Enumerator>::enable is true.
 * @param lhs An integer of type Integer
 * @param rhs An enum of class Enumerator
 * @return Returns lhs < rhs
 */
template <typename Enumerator, typename Integer>
typename std::enable_if<EnableComparisonOperators<Enumerator>::enable,
                        bool>::type
operator<(const Integer lhs, const Enumerator rhs) {
  using underlying = typename std::underlying_type<Enumerator>::type;
  return lhs < static_cast<const underlying>(rhs);
}

/**
 * @brief Greater than overload for a generic enum, defined iff
 * EnableComparisonOperators<Enumerator>::enable is true.
 * @param lhs An enum of class Enumerator
 * @param rhs An enum of class Enumerator
 * @return Returns lhs > rhs
 */
template <typename Enumerator>
typename std::enable_if<EnableComparisonOperators<Enumerator>::enable,
                        bool>::type
operator>(const Enumerator lhs, const Enumerator rhs) {
  using underlying = typename std::underlying_type<Enumerator>::type;
  return static_cast<const underlying>(lhs) >
         static_cast<const underlying>(rhs);
}
/**
 * @brief Greater than overload for a generic enum, defined iff
 * EnableComparisonOperators<Enumerator>::enable is true.
 * @param lhs An enum of class Enumerator
 * @param rhs An integer of type Integer
 * @return Returns lhs > rhs
 */
template <typename Enumerator, typename Integer>
typename std::enable_if<EnableComparisonOperators<Enumerator>::enable,
                        bool>::type
operator>(const Enumerator lhs, const Integer rhs) {
  using underlying = typename std::underlying_type<Enumerator>::type;
  return static_cast<const underlying>(lhs) > rhs;
}

/**
 * @brief Greater than overload for a generic enum, defined iff
 * EnableComparisonOperators<Enumerator>::enable is true.
 * @param lhs An integer of type Integer
 * @param rhs An enum of class Enumerator
 * @return Returns lhs > rhs
 */
template <typename Enumerator, typename Integer>
typename std::enable_if<EnableComparisonOperators<Enumerator>::enable,
                        bool>::type
operator>(const Integer lhs, const Enumerator rhs) {
  using underlying = typename std::underlying_type<Enumerator>::type;
  return lhs > static_cast<const underlying>(rhs);
}

/**
 * @brief Less than or equal overload for a generic enum, defined iff
 * EnableComparisonOperators<Enumerator>::enable is true.
 * @param lhs An enum of class Enumerator
 * @param rhs An enum of class Enumerator
 * @return Returns lhs <= rhs
 */
template <typename Enumerator>
typename std::enable_if<EnableComparisonOperators<Enumerator>::enable,
                        bool>::type
operator<=(const Enumerator lhs, const Enumerator rhs) {
  using underlying = typename std::underlying_type<Enumerator>::type;
  return static_cast<const underlying>(lhs) <=
         static_cast<const underlying>(rhs);
}

/**
 * @brief Less than or equal overload for a generic enum, defined iff
 * EnableComparisonOperators<Enumerator>::enable is true.
 * @param lhs An enum of class Enumerator
 * @param rhs An integer of type Integer
 * @return Returns lhs <= rhs
 */
template <typename Enumerator, typename Integer>
typename std::enable_if<EnableComparisonOperators<Enumerator>::enable,
                        bool>::type
operator<=(const Enumerator lhs, const Integer rhs) {
  using underlying = typename std::underlying_type<Enumerator>::type;
  return static_cast<const underlying>(lhs) <= rhs;
}

/**
 * @brief Less than or equal verload for a generic enum, defined iff
 * EnableComparisonOperators<Enumerator>::enable is true.
 * @param lhs An integer of type Integer
 * @param rhs An enum of class Enumerator
 * @return Returns lhs <= rhs
 */
template <typename Enumerator, typename Integer>
typename std::enable_if<EnableComparisonOperators<Enumerator>::enable,
                        bool>::type
operator<=(const Integer lhs, const Enumerator rhs) {
  using underlying = typename std::underlying_type<Enumerator>::type;
  return lhs <= static_cast<const underlying>(rhs);
}

/**
 * @brief Greater than or equal overload for a generic enum, defined iff
 * EnableComparisonOperators<Enumerator>::enable is true.
 * @param lhs An enum of class Enumerator
 * @param rhs An enum of class Enumerator
 * @return Returns lhs >= rhs
 */
template <typename Enumerator>
typename std::enable_if<EnableComparisonOperators<Enumerator>::enable,
                        bool>::type
operator>=(const Enumerator lhs, const Enumerator rhs) {
  using underlying = typename std::underlying_type<Enumerator>::type;
  return static_cast<const underlying>(lhs) >=
         static_cast<const underlying>(rhs);
}

/**
 * @brief Greater than or equal for a generic enum, defined iff
 * EnableComparisonOperators<Enumerator>::enable is true.
 * @param lhs An enum of class Enumerator
 * @param rhs An integer of type Integer
 * @return Returns lhs >= rhs
 */
template <typename Enumerator, typename Integer>
typename std::enable_if<EnableComparisonOperators<Enumerator>::enable,
                        bool>::type
operator>=(const Enumerator lhs, const Integer rhs) {
  using underlying = typename std::underlying_type<Enumerator>::type;
  return static_cast<const underlying>(lhs) >= rhs;
}

/**
 * @brief Greater than or equal for a generic enum, defined iff
 * EnableComparisonOperators<Enumerator>::enable is true.
 * @param lhs An integer of type Integer
 * @param rhs An enum of class Enumerator
 * @return Returns lhs >= rhs
 */
template <typename Enumerator, typename Integer>
typename std::enable_if<EnableComparisonOperators<Enumerator>::enable,
                        bool>::type
operator>=(const Integer lhs, const Enumerator rhs) {
  using underlying = typename std::underlying_type<Enumerator>::type;
  return lhs >= static_cast<const underlying>(rhs);
}

/**
 * @brief Equality overload for a generic enum, defined iff
 * EnableComparisonOperators<Enumerator>::enable is true.
 * @param lhs An enum of class Enumerator
 * @param rhs An enum of class Enumerator
 * @return Returns lhs == rhs
 */
template <typename Enumerator>
typename std::enable_if<EnableComparisonOperators<Enumerator>::enable,
                        bool>::type
operator==(const Enumerator lhs, const Enumerator rhs) {
  using underlying = typename std::underlying_type<Enumerator>::type;
  return static_cast<const underlying>(lhs) ==
         static_cast<const underlying>(rhs);
}

/**
 * @brief Equality overload for a generic enum, defined iff
 * EnableComparisonOperators<Enumerator>::enable is true.
 * @param lhs An enum of class Enumerator
 * @param rhs An integer of type Integer
 * @return Returns lhs == rhs
 */
template <typename Enumerator, typename Integer>
typename std::enable_if<EnableComparisonOperators<Enumerator>::enable,
                        bool>::type
operator==(const Enumerator lhs, const Integer rhs) {
  using underlying = typename std::underlying_type<Enumerator>::type;
  return static_cast<const underlying>(lhs) == rhs;
}

/**
 * @brief Equality overload for a generic enum, defined iff
 * EnableComparisonOperators<Enumerator>::enable is true.
 * @param lhs An integer of type Integer
 * @param rhs An enum of class Enumerator
 * @return Returns lhs == rhs
 */
template <typename Enumerator, typename Integer>
typename std::enable_if<EnableComparisonOperators<Enumerator>::enable,
                        bool>::type
operator==(const Integer lhs, const Enumerator rhs) {
  using underlying = typename std::underlying_type<Enumerator>::type;
  return lhs == static_cast<const underlying>(rhs);
}

/**
 * @brief Not equal overload for a generic enum, defined iff
 * EnableComparisonOperators<Enumerator>::enable is true.
 * @param lhs An enum of class Enumerator
 * @param rhs An enum of class Enumerator
 * @return Returns lhs != rhs
 */
template <typename Enumerator>
typename std::enable_if<EnableComparisonOperators<Enumerator>::enable,
                        bool>::type
operator!=(const Enumerator lhs, const Enumerator rhs) {
  using underlying = typename std::underlying_type<Enumerator>::type;
  return static_cast<const underlying>(lhs) !=
         static_cast<const underlying>(rhs);
}

/**
 * @brief Not equal overload for a generic enum, defined iff
 * EnableComparisonOperators<Enumerator>::enable is true.
 * @param lhs An enum of class Enumerator
 * @param rhs An integer of type Integer
 * @return Returns lhs != rhs
 */
template <typename Enumerator, typename Integer>
typename std::enable_if<EnableComparisonOperators<Enumerator>::enable,
                        bool>::type
operator!=(const Enumerator lhs, const Integer rhs) {
  using underlying = typename std::underlying_type<Enumerator>::type;
  return static_cast<const underlying>(lhs) != rhs;
}

/**
 * @brief Not equal overload for a generic enum, defined iff
 * EnableComparisonOperators<Enumerator>::enable is true.
 * @param lhs An integer of type Integer
 * @param rhs An enum of class Enumerator
 * @return Returns lhs != rhs
 */
template <typename Enumerator, typename Integer>
typename std::enable_if<EnableComparisonOperators<Enumerator>::enable,
                        bool>::type
operator!=(const Integer lhs, const Enumerator rhs) {
  using underlying = typename std::underlying_type<Enumerator>::type;
  return lhs != static_cast<const underlying>(rhs);
}

} /* namespace util */
} /* namespace game_engine */

using namespace game_engine::util;

#endif /* SRC_UTIL_ENUMCOMPARISONS_HPP_ */
