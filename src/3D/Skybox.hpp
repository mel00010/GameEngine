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
#include <utility>

#include "Cube.hpp"

namespace game_engine {
namespace _3D {

class Skybox {
	public:
		Skybox() = default;
		Skybox& operator=(const Skybox& rhs) = default;
		Skybox(const Skybox& rhs) = default;
		Skybox& operator=(Skybox&& rhs) noexcept = default;
		Skybox(Skybox&& rhs) noexcept = default;
		~Skybox() noexcept = default;

		template<typename Renderer>
		Skybox(Renderer& renderer, const cmrc::embedded_filesystem& fs, const std::string& path);

		template<typename Renderer>
		void LoadSkybox(Renderer& renderer, const cmrc::embedded_filesystem& fs, const std::string& path);

		template<typename Renderer>
		void Draw(const Renderer& renderer, const ShaderPrograms shaders = ShaderPrograms::SKYBOX);

		void swap(Skybox& other) noexcept {
			using std::swap;

			swap(other.cube_, cube_);
		}
	protected:
		Cube cube_;
};

inline void swap(Skybox& a, Skybox& b) noexcept {
	a.swap(b);
}

} /* namespace _3D */
} /* namespace game_engine */

#include "Skybox.tpp"

#endif /* SRC_3D_SKYBOX_HPP_ */
