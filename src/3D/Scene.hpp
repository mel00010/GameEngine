/******************************************************************************
 * Scene.hpp
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
#ifndef SRC_3D_SCENE_HPP_
#define SRC_3D_SCENE_HPP_

#include <vector>

#include "3D/Camera.hpp"
#include "3D/Mesh.hpp"
#include "3D/Model.hpp"

namespace game_engine::_3D {

class Scene {
 public:
  template <typename Renderer>
  void Draw(Renderer renderer);

 protected:
  std::vector<Model> models_;
  Camera camera_;
};

} /* namespace game_engine::_3D */

#include "3D/Scene.tpp"

#endif /* SRC_3D_SCENE_HPP_ */
