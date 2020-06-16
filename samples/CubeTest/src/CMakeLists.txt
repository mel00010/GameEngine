add_executable(CubeTest "")
target_sources(CubeTest
  PRIVATE
    main.cpp
    CubeTestCore.cpp
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/CubeTestCore.hpp
)

#set_target_properties(CubeTest PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
if(NOT DEFINED DISABLE_PCH)
    target_precompile_headers(CubeTest REUSE_FROM GameEngine::GameEngine)
endif()

target_link_libraries(CubeTest
  PUBLIC
    GameEngine::GameEngine
    CubeTest::Resources
)
include(CMakeRC)

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
  setup_target_for_coverage(NAME CubeTest_coverage EXECUTABLE samples/CubeTest/src/CubeTest DEPENDENCIES CubeTest)
endif()

cmrc_add_resource_library(CubeTest_Resources ALIAS CubeTest::Resources NAMESPACE cube_test)
cmrc_add_resources(CubeTest_Resources
  WHENCE resources

  resources/cube/back.png
  resources/cube/bottom.png
  resources/cube/front.png
  resources/cube/left.png
  resources/cube/right.png
  resources/cube/top.png
)