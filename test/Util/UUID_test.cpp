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

#include "Util/Uuid.hpp"

#include <ostream>

#include "gtest/gtest.h"

using game_engine::util::Uuid;

TEST(Util, UUID) {
  EXPECT_TRUE(Uuid(0, 0) == Uuid(0, 0));
  EXPECT_FALSE(Uuid(0, 0) == Uuid(0, 1));
  EXPECT_FALSE(Uuid(0, 0) == Uuid(1, 0));
  EXPECT_FALSE(Uuid(0, 1) == Uuid(0, 0));
  EXPECT_FALSE(Uuid(1, 0) == Uuid(0, 0));
  EXPECT_FALSE(Uuid() == Uuid(0, 0));

  EXPECT_FALSE(Uuid(0, 0) != Uuid(0, 0));
  EXPECT_TRUE(Uuid(0, 0) != Uuid(0, 1));
  EXPECT_TRUE(Uuid(0, 0) != Uuid(1, 0));
  EXPECT_TRUE(Uuid(0, 1) != Uuid(0, 0));
  EXPECT_TRUE(Uuid(1, 0) != Uuid(0, 0));
  EXPECT_TRUE(Uuid() != Uuid(0, 0));

  EXPECT_FALSE(Uuid(0, 0) < Uuid(0, 0));
  EXPECT_TRUE(Uuid(0, 0) < Uuid(0, 1));
  EXPECT_TRUE(Uuid(0, 0) < Uuid(1, 0));
  EXPECT_FALSE(Uuid(0, 1) < Uuid(0, 0));
  EXPECT_FALSE(Uuid(1, 0) < Uuid(0, 0));

  EXPECT_TRUE(Uuid(0, 0) <= Uuid(0, 0));
  EXPECT_TRUE(Uuid(0, 0) <= Uuid(0, 1));
  EXPECT_TRUE(Uuid(0, 0) <= Uuid(1, 0));
  EXPECT_FALSE(Uuid(0, 1) <= Uuid(0, 0));
  EXPECT_FALSE(Uuid(1, 0) <= Uuid(0, 0));

  EXPECT_FALSE(Uuid(0, 0) > Uuid(0, 0));
  EXPECT_FALSE(Uuid(0, 0) > Uuid(0, 1));
  EXPECT_FALSE(Uuid(0, 0) > Uuid(1, 0));
  EXPECT_TRUE(Uuid(0, 1) > Uuid(0, 0));
  EXPECT_TRUE(Uuid(1, 0) > Uuid(0, 0));

  EXPECT_TRUE(Uuid(0, 0) >= Uuid(0, 0));
  EXPECT_FALSE(Uuid(0, 0) >= Uuid(0, 1));
  EXPECT_FALSE(Uuid(0, 0) >= Uuid(1, 0));
  EXPECT_TRUE(Uuid(0, 1) >= Uuid(0, 0));
  EXPECT_TRUE(Uuid(1, 0) >= Uuid(0, 0));

  EXPECT_EQ(Uuid(0, 0), Uuid(0, 0));

  EXPECT_NE(Uuid(0, 0), Uuid(0, 1));
  EXPECT_NE(Uuid(0, 0), Uuid(1, 0));
  EXPECT_NE(Uuid(0, 1), Uuid(0, 0));
  EXPECT_NE(Uuid(1, 0), Uuid(0, 0));
  EXPECT_NE(Uuid(), Uuid(0, 0));
  EXPECT_NE(Uuid(), Uuid());

  EXPECT_LT(Uuid(0, 0), Uuid(0, 1));
  EXPECT_LT(Uuid(0, 0), Uuid(1, 0));

  EXPECT_LE(Uuid(0, 0), Uuid(0, 0));
  EXPECT_LE(Uuid(0, 0), Uuid(0, 1));
  EXPECT_LE(Uuid(0, 0), Uuid(1, 0));

  EXPECT_GT(Uuid(0, 1), Uuid(0, 0));
  EXPECT_GT(Uuid(1, 0), Uuid(0, 0));

  EXPECT_GE(Uuid(0, 0), Uuid(0, 0));
  EXPECT_GE(Uuid(0, 1), Uuid(0, 0));
  EXPECT_GE(Uuid(1, 0), Uuid(0, 0));
}
