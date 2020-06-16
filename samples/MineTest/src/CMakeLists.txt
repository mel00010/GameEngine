add_executable(MineTest "")
target_sources(MineTest
  PRIVATE
    main.cpp
    MineTest.cpp
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/MineTest.hpp
)
#set_target_properties(MineTest PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
if(NOT DEFINED DISABLE_PCH)
  if(NOT CMAKE_POSITION_INDEPENDENT_CODE)
    target_precompile_headers(MineTest REUSE_FROM GameEngine::GameEngine)
  endif()
endif()

target_link_libraries(MineTest
  PUBLIC
    GameEngine::GameEngine

    MineTest::Blocks
    MineTest::Resources
    glm
)

if(CMAKE_BUILD_TYPE STREQUAL "Coverage")
  # coverage target setup
  include(CodeCoverage)
  append_coverage_compiler_flags()
  set(COVERAGE_EXCLUDES
    '${PROJECT_SOURCE_DIR}/test/*'
    '/usr/include/c++/6/*'
    '/usr/include/c++/7/*'
    '/usr/include/c++/8/*'
    '/usr/include/c++/9/*'
    '/usr/include/c++/10/*'
    '/usr/local/include/boost/*'
  )
  setup_target_for_coverage(NAME MineTest_coverage EXECUTABLE samples/MineTest/src/MineTest DEPENDENCIES MineTest)
endif()

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