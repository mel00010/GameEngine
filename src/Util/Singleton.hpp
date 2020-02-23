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
#ifndef SRC_UTIL_SINGLETON_HPP_
#define SRC_UTIL_SINGLETON_HPP_

namespace game_engine {
namespace util {

/**
 * @brief Wrapper ensuring only one object of a class exists at a time
 * @tparam ActualClass The class to protect
 */
template<class ActualClass> struct Singleton {
	public:
		/**
		 * @brief Gets the instance of the encapsulated object
		 * @return Returns a reference to the encapsulated object
		 */
		static inline ActualClass& GetInstance() {
			static ActualClass obj;
			return obj;
		}
		/**
		 * @brief Alias for getInstance
		 * @return Returns a reference to the encapsulated object
		 */
		static inline ActualClass& Instance() {
			return GetInstance();
		}
	protected:
		Singleton(){}
	private:
		Singleton(Singleton const &);
		Singleton& operator = (Singleton const &);
};

} /* namespace util */
} /* namespace game_engine */

using namespace game_engine::util;

#endif /* SRC_UTIL_SINGLETON_HPP_ */
