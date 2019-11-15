/******************************************************************************
 * MineTest.hpp
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
#ifndef SAMPLES_MINETEST_MINETEST_HPP_
#define SAMPLES_MINETEST_MINETEST_HPP_

#include <3D/Camera.hpp>
#include <3D/Model.hpp>
#include <Sound/Sound.hpp>
#include <Sound/Music.hpp>
#include <GameCore.hpp>

#include <cmrc/cmrc.hpp>

CMRC_DECLARE(MineTest);

using namespace GameEngine;

namespace MineTest {

class MineTest : public GameEngine::GameCore<MineTest> {
	public:
		const std::string program_name = "MineTest";
		void setup();
		void tick();
		void render();
		void registerCallbacks();

	protected:
		cmrc::embedded_filesystem fs = cmrc::MineTest::get_filesystem();

		glm::vec3 line_color = glm::vec3(1.0, 1.0, 0.0);

		_3D::Camera camera;
		_3D::Model grid;
		_3D::Model dirt_block;
		_3D::Model grass_block;
		_3D::Model cobblestone_block;
		_3D::Model obsidian_block;
		_3D::Model wood_block;
		Sound::Sound oof;
		Sound::Sound ouch;
		Sound::Music rickroll;
};

} /* namespace MineTest */




#endif /* SAMPLES_SOUNDTEST_SOUNDTEST_HPP_ */
