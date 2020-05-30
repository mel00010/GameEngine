add_executable(MineTest "")
target_sources(MineTest
  PRIVATE
    main.cpp
    MineTest.cpp
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/MineTest.hpp
)
#set_target_properties(MineTest PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
target_precompile_headers(MineTest REUSE_FROM GameEngine::GameEngine)

target_link_libraries(MineTest
  PUBLIC
    GameEngine

    MineTest::Blocks
    MineTest::Resources
    glm
)
include(CMakeRC)

cmrc_add_resource_library(MineTest-Resources ALIAS MineTest::Resources NAMESPACE mine_test)
cmrc_add_resources(MineTest-Resources
  WHENCE resources

  resources/grid/grid.mtl
  resources/grid/grid.obj
  resources/grid/grid.png

  resources/oof.ogg
  resources/ouch.ogg
  resources/rickroll.ogg
)

add_subdirectory(Blocks)