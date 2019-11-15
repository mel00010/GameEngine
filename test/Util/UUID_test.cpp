/******************************************************************************
 * UUID_test.cpp
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

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <Util/UUID.hpp>
#include <ostream>

using namespace GameEngine;

TEST(Util, UUID) {
	EXPECT_TRUE (UUID(0, 0) == UUID(0, 0));
	EXPECT_FALSE(UUID(0, 0) == UUID(0, 1));
	EXPECT_FALSE(UUID(0, 0) == UUID(1, 0));
	EXPECT_FALSE(UUID(0, 1) == UUID(0, 0));
	EXPECT_FALSE(UUID(1, 0) == UUID(0, 0));
	EXPECT_FALSE(UUID()     == UUID(0, 0));

	EXPECT_FALSE(UUID(0, 0) != UUID(0, 0));
	EXPECT_TRUE (UUID(0, 0) != UUID(0, 1));
	EXPECT_TRUE (UUID(0, 0) != UUID(1, 0));
	EXPECT_TRUE (UUID(0, 1) != UUID(0, 0));
	EXPECT_TRUE (UUID(1, 0) != UUID(0, 0));
	EXPECT_TRUE (UUID()     != UUID(0, 0));

	EXPECT_FALSE(UUID(0, 0) <  UUID(0, 0));
	EXPECT_TRUE (UUID(0, 0) <  UUID(0, 1));
	EXPECT_TRUE (UUID(0, 0) <  UUID(1, 0));
	EXPECT_FALSE(UUID(0, 1) <  UUID(0, 0));
	EXPECT_FALSE(UUID(1, 0) <  UUID(0, 0));

	EXPECT_TRUE (UUID(0, 0) <= UUID(0, 0));
	EXPECT_TRUE (UUID(0, 0) <= UUID(0, 1));
	EXPECT_TRUE (UUID(0, 0) <= UUID(1, 0));
	EXPECT_FALSE(UUID(0, 1) <= UUID(0, 0));
	EXPECT_FALSE(UUID(1, 0) <= UUID(0, 0));

	EXPECT_FALSE(UUID(0, 0) >  UUID(0, 0));
	EXPECT_FALSE(UUID(0, 0) >  UUID(0, 1));
	EXPECT_FALSE(UUID(0, 0) >  UUID(1, 0));
	EXPECT_TRUE (UUID(0, 1) >  UUID(0, 0));
	EXPECT_TRUE (UUID(1, 0) >  UUID(0, 0));

	EXPECT_TRUE (UUID(0, 0) >= UUID(0, 0));
	EXPECT_FALSE(UUID(0, 0) >= UUID(0, 1));
	EXPECT_FALSE(UUID(0, 0) >= UUID(1, 0));
	EXPECT_TRUE (UUID(0, 1) >= UUID(0, 0));
	EXPECT_TRUE (UUID(1, 0) >= UUID(0, 0));


	EXPECT_EQ(UUID(0, 0), UUID(0, 0));

	EXPECT_NE(UUID(0, 0), UUID(0, 1));
	EXPECT_NE(UUID(0, 0), UUID(1, 0));
	EXPECT_NE(UUID(0, 1), UUID(0, 0));
	EXPECT_NE(UUID(1, 0), UUID(0, 0));
	EXPECT_NE(UUID(),     UUID(0, 0));
	EXPECT_NE(UUID(),     UUID());

	EXPECT_LT(UUID(0, 0), UUID(0, 1));
	EXPECT_LT(UUID(0, 0), UUID(1, 0));

	EXPECT_LE(UUID(0, 0), UUID(0, 0));
	EXPECT_LE(UUID(0, 0), UUID(0, 1));
	EXPECT_LE(UUID(0, 0), UUID(1, 0));

	EXPECT_GT(UUID(0, 1), UUID(0, 0));
	EXPECT_GT(UUID(1, 0), UUID(0, 0));

	EXPECT_GE(UUID(0, 0), UUID(0, 0));
	EXPECT_GE(UUID(0, 1), UUID(0, 0));
	EXPECT_GE(UUID(1, 0), UUID(0, 0));
}
