/******************************************************************************
 * SoundTest.hpp
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
#ifndef SAMPLES_SOUNDTEST_SOUNDTEST_HPP_
#define SAMPLES_SOUNDTEST_SOUNDTEST_HPP_

#include <3D/Camera.hpp>
#include <3D/Model.hpp>
#include <Sound/Sound.hpp>
#include <Sound/Music.hpp>
#include <GameCore.hpp>

#include <cmrc/cmrc.hpp>

CMRC_DECLARE(sound_test);

using namespace game_engine;

namespace sound_test {

class SoundTest : public game_engine::GameCore<SoundTest> {
	public:
		static constexpr std::string_view program_name_ = "SoundTest";
		void Setup();
		void Tick();
		void Render();
		void RegisterCallbacks();

	protected:
		cmrc::embedded_filesystem fs_ = cmrc::sound_test::get_filesystem();

		glm::vec3 line_color_ = glm::vec3(1.0, 1.0, 0.0);

		_3D::Camera camera_;
		_3D::Model grid_;
		Sound::Sound oof_;
		Sound::Sound ouch_;
		Sound::Music rickroll_;
};

} /* namespace SoundTest */




#endif /* SAMPLES_SOUNDTEST_SOUNDTEST_HPP_ */
