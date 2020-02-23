/******************************************************************************
 * Cube.hpp
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
#ifndef SRC_3D_CUBE_HPP_
#define SRC_3D_CUBE_HPP_

#include <glm/glm.hpp>

#include "Cubemap.hpp"
#include "Transformations.hpp"
#include "Vertex.hpp"

#include <VboHandle.hpp>

#include <cmrc/cmrc.hpp>
#include <GL/glew.h>

#include <vector>
#include <utility>

namespace game_engine {
namespace _3D {

class Cube : public Transformations {
	public:
		Cube() = default;
		Cube& operator=(const Cube& rhs) = default;
		Cube(const Cube& rhs) = default;
		Cube& operator=(Cube&& rhs) noexcept = default;
		Cube(Cube&& rhs) noexcept = default;
		~Cube() noexcept = default;

		template<typename Renderer>
		Cube(Renderer& renderer, const cmrc::embedded_filesystem& fs, const std::string& path,
				const ShaderPrograms shaders = ShaderPrograms::CUBE);

		template<typename Renderer>
		void LoadCube(Renderer& renderer, const cmrc::embedded_filesystem& fs, const std::string& path,
				const ShaderPrograms shaders = ShaderPrograms::CUBE);

		template<typename Renderer>
		void Draw(const Renderer& renderer, const ShaderPrograms shaders) const;

		void swap(Cube& other) noexcept {
			using std::swap;
			swap(other.cube_mesh_, cube_mesh_);
		}

	private:
		class CubeMesh {
			public:
				VboHandle handle_ { };
				std::vector<Vertex> vertices_ { };
				std::vector<GLuint> indices_ { };
				Cubemap cube_map_ { };

				CubeMesh() = default;
				CubeMesh& operator=(const CubeMesh& rhs) = default;
				CubeMesh(const CubeMesh& rhs) = default;
				CubeMesh& operator=(CubeMesh&& rhs) noexcept = default;
				CubeMesh(CubeMesh&& rhs) noexcept = default;
				~CubeMesh() noexcept = default;

				CubeMesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, const Cubemap& cube_map)
						: vertices_(vertices), indices_(indices), cube_map_(cube_map) {
				};

				template<typename Renderer> void Draw(const Renderer& renderer, const ShaderPrograms shaders) const;

				void swap(CubeMesh& other) noexcept {
					using std::swap;
					swap(other.handle_, handle_);
					swap(other.vertices_, vertices_);
					swap(other.indices_, indices_);
					swap(other.cube_map_, cube_map_);
				}
		};

		CubeMesh cube_mesh_;

		friend void swap(Cube::CubeMesh& a, Cube::CubeMesh& b) noexcept;
		friend std::ostream& operator<<(std::ostream& os, const Cube& m);
		friend std::ostream& operator<<(std::ostream& os, const Cube::CubeMesh& m);
};

inline void swap(Cube::CubeMesh& a, Cube::CubeMesh& b) noexcept {
	a.swap(b);
}

inline void swap(Cube& a, Cube& b) noexcept {
	a.swap(b);
}

} /* namespace _3D */
} /* namespace game_engine */

#include "Cube.tpp"

#endif /* SRC_3D_CUBE_HPP_ */
