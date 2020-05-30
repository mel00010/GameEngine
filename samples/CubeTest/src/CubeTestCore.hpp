/******************************************************************************
 * CubeTestCore.hpp
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
#ifndef SAMPLES_CUBETEST_SRC_CUBETESTCORE_HPP_
#define SAMPLES_CUBETEST_SRC_CUBETESTCORE_HPP_

#include <cmrc/cmrc.hpp>

#include "3D/Camera.hpp"
#include "3D/Cube.hpp"
#include "GameCore.hpp"

CMRC_DECLARE(cube_test);

using namespace game_engine;

namespace cube_test {

class CubeTestCore : public game_engine::GameCore<CubeTestCore> {
 public:
  static constexpr std::string_view program_name_ = "CubeTest";
  void Setup();
  void Tick();
  void Render();
  void RegisterCallbacks();

 protected:
  cmrc::embedded_filesystem fs_ = cmrc::cube_test::get_filesystem();

  glm::vec3 cube_color_ = glm::vec3(1.0, 1.0, 1.0);

  _3D::Camera camera_;
  _3D::Cube cube_;
};

} /* namespace cube_test */

#endif /* SAMPLES_CUBETEST_SRC_CUBETESTCORE_HPP_ */
