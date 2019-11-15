/******************************************************************************
 * RNG.hpp
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
#ifndef SRC_UTIL_RNG_HPP_
#define SRC_UTIL_RNG_HPP_

#include <limits>
#include <random>
#include <stdint.h>

namespace GameEngine {
namespace Util {

class RNG {
	public:
		static uint64_t get();
};

} /* namespace Util */
} /* namespace GameEngine */

using namespace GameEngine::Util;

#endif /* SRC_UTIL_RNG_HPP_ */
