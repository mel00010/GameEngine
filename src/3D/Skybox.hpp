/******************************************************************************
 * Skybox.hpp
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
#ifndef SRC_3D_SKYBOX_HPP_
#define SRC_3D_SKYBOX_HPP_

#include "Cube.hpp"

namespace GameEngine {
namespace _3D {

class Skybox {
	public:
		Skybox() {}

		template<typename Renderer>
		Skybox(Renderer& renderer, cmrc::embedded_filesystem& fs, const std::string& path);

		template<typename Renderer>
		void loadSkybox(Renderer& renderer, cmrc::embedded_filesystem& fs, const std::string& path);

		template<typename Renderer>
		void draw(Renderer& renderer);

	protected:
		Cube cube;
};

} /* namespace _3D */
} /* namespace GameEngine */

#include "Skybox.tpp"

#endif /* SRC_3D_SKYBOX_HPP_ */
