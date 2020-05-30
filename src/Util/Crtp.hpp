/******************************************************************************
 * CRTP.hpp
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
#ifndef SRC_UTIL_CRTP_HPP_
#define SRC_UTIL_CRTP_HPP_

namespace game_engine {
namespace util {

/**
 * @brief A helper class to make CRTP more convenient
 * @tparam Derived Class to be derived from base class.
 * @tparam Base Base class to do deriving from.
 *
 * It is used in the declaration of the base class like this:
 *
 * template<typename Derived>
 * class Base : CRTP<Derived, Base> { ...
 */
template <template <typename...> class Base, typename Derived,
          typename... Base_Args>
struct Crtp {
 public:
  /**
   * @brief Get a reference to the derived class Derived
   * @return Returns a reference to the derived class Derived
   */
  Derived& Underlying() { return static_cast<Derived&>(*this); }
  /**
   * @brief Get a const reference to the derived class Derived
   * @return Returns a const reference to the derived class Derived
   */
  Derived const& Underlying() const {
    return static_cast<Derived const&>(*this);
  }

 private:
  Crtp() noexcept = default;
  Crtp& operator=(const Crtp& rhs) = default;
  Crtp(const Crtp& rhs) = default;
  Crtp& operator=(Crtp&& rhs) noexcept = default;
  Crtp(Crtp&& rhs) noexcept = default;
  ~Crtp() noexcept = default;

  friend Base<Derived, Base_Args...>;
};

} /* namespace util */
} /* namespace game_engine */

using namespace game_engine::util;

#endif /* SRC_UTIL_CRTP_HPP_ */
