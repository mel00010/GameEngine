/******************************************************************************
 * main.cpp
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

#include "CameraTest.hpp"

#include <gflags/gflags.h>

int main(int argc, char** argv) {
//	using namespace std::literals::string_literals;
//
//	::gflags::SetUsageMessage("Sample usage:\n\t"s
//			+ (*argv)[0] + " [flags...]");
//	::gflags::SetVersionString("0.0.1");
//	::gflags::ParseCommandLineFlags(&argc, &argv, true);

	camera_test::CameraTest::Main(&argc, &argv);
}
