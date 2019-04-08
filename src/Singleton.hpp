/******************************************************************************
 * Singleton.hpp
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
#ifndef SRC_SINGLETON_HPP_
#define SRC_SINGLETON_HPP_

#include <type_traits>

template<class> struct sfinae_true: std::true_type {};

namespace detail {
	template<class T> constexpr static auto parent_test(int)  -> sfinae_true<typename T::SubClass_T>;
	template<class>   constexpr static auto parent_test(long) -> std::false_type;
} /* namespace detail */


template<class T> struct has_derived: decltype(detail::parent_test<T>(0)){};;

template <class SC, typename Enable = void> class Singleton;
template <class SC>																					// primary
class Singleton<SC, typename std::enable_if_t<!has_derived<SC>::value>> {
	public:
		static_assert(has_derived<SC>() == false, "fail primary");
		friend SC;
		/** Singleton creation function */
		static inline SC& getInstance() {
			static SC sc;
			return sc;
		}
		static inline SC& instance() { return getInstance(); }
};

template <class SC>																					// Has Subclass
class Singleton<SC, typename std::enable_if_t<has_derived<SC>::value>> {
	public:
		static_assert(has_derived<SC>() == true, "fail derived");
		using s_class_t = typename SC::SubClass_T;
		friend SC;
		friend s_class_t;

		/** Singleton creation function */
		static inline s_class_t& getInstance() {
			static SC sc;
			return sc.derived();
		}
		static inline s_class_t& instance() { return getInstance(); }
};
#endif /* SRC_SINGLETON_HPP_ */
