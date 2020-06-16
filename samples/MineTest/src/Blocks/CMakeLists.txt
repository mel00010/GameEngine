add_library(MineTest_Blocks "")
add_library(MineTest::Blocks ALIAS MineTest_Blocks)

target_link_libraries(MineTest_Blocks
  PUBLIC
    GameEngine::3D
    GameEngine::Util
)

target_sources(MineTest_Blocks
  PRIVATE
    Block.cpp
    Cobblestone.cpp
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Block.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Cobblestone.hpp
)

include(CMakeRC)

cmrc_add_resource_library(MineTest_Blocks_Resources ALIAS MineTest::Blocks::Resources NAMESPACE blocks)
cmrc_add_resources(MineTest_Blocks_Resources
  WHENCE resources

  resources/cobblestone/back.png
  resources/cobblestone/bottom.png
  resources/cobblestone/front.png
  resources/cobblestone/left.png
  resources/cobblestone/right.png
  resources/cobblestone/top.png
)