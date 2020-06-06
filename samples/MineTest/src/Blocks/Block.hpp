/******************************************************************************
 * Block.hpp
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
#ifndef SAMPLES_MINETEST_SRC_BLOCKS_BLOCK_HPP_
#define SAMPLES_MINETEST_SRC_BLOCKS_BLOCK_HPP_

#include <3D/Cube.hpp>
#include <cmrc/cmrc.hpp>

#include "Util/Crtp.hpp"

CMRC_DECLARE(blocks);

using namespace game_engine;

namespace mine_test {
namespace blocks {

template <class Derived, class Renderer>
class Block : public Crtp<Block, Derived, Renderer>,
              public _3D::Transformations {
 public:
  using Renderer_t = Renderer;
  Block(Renderer_t& _renderer) : renderer_(_renderer) {
    name_ = std::string(this->underlying().name_);
  }

  void init() { cube_.LoadCube(renderer_, fs_, name_, ShaderPrograms::CUBE); }

 protected:
  cmrc::embedded_filesystem fs_{cmrc::blocks::get_filesystem()};

  Renderer_t& renderer_;
  std::string name_;

  _3D::Cube cube_;
};

} /* namespace blocks */
} /* namespace mine_test */

#endif /* SAMPLES_MINETEST_SRC_BLOCKS_BLOCK_HPP_ */
