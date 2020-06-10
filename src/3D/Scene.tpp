/******************************************************************************
 * Scene.tpp
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
#ifndef SRC_3D_SCENE_TPP_
#define SRC_3D_SCENE_TPP_

#include "3D/Scene.hpp"

namespace game_engine::_3D {

template <typename RealRenderer, typename RealWindowManager>
void Scene::Draw(Renderer<RealRenderer, RealWindowManager>& renderer) {
  for (auto& model : models_) {
    camera_.DrawModel(renderer, model);
  }
}

}  // namespace game_engine::_3D

#endif /* SRC_3D_SCENE_TPP_ */
