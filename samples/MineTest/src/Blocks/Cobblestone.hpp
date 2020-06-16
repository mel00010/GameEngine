/******************************************************************************
 * Cobblestone.hpp
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
#ifndef SAMPLES_MINETEST_SRC_BLOCKS_COBBLESTONE_HPP_
#define SAMPLES_MINETEST_SRC_BLOCKS_COBBLESTONE_HPP_

#include "Block.hpp"

namespace mine_test {
namespace blocks {

class Cobblestone final : public Block<Cobblestone, Cobblestone> {
 public:
  static constexpr std::string_view name = "Cobblestone";
};

} /* namespace blocks */
} /* namespace mine_test */

#endif /* SAMPLES_MINETEST_SRC_BLOCKS_COBBLESTONE_HPP_ */
