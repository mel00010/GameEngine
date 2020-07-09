add_executable(CameraTest "")
target_sources(CameraTest
  PRIVATE
    main.cpp
    CameraTest.cpp
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/CameraTest.hpp
)
#set_target_properties(CameraTest PROPERTIES INTERPROCEDURAL_OPTIMIZATION FALSE)
if(NOT DISABLE_PCH)
  if(NOT CMAKE_POSITION_INDEPENDENT_CODE)
    target_precompile_headers(CameraTest REUSE_FROM GameEngine::GameEngine)
  endif()
endif()

target_link_libraries(CameraTest
  PUBLIC
    GameEngine::GameEngine
    CameraTest::Resources

    Logging::Logging
    Boost::DI
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
  setup_target_for_coverage(NAME CameraTest_coverage EXECUTABLE samples/CameraTest/src/CameraTest DEPENDENCIES CameraTest)
endif()

cmrc_add_resource_library(CameraTest_Resources ALIAS CameraTest::Resources NAMESPACE camera_test)
cmrc_add_resources(CameraTest_Resources
  WHENCE resources

  resources/cube/cube.mtl
  resources/cube/cube.obj
  resources/cube/wall.jpg

  resources/grid/grid.mtl
  resources/grid/grid.obj
  resources/grid/grid.png

  resources/nanosuit/arm_dif.png
  resources/nanosuit/arm_showroom_ddn.png
  resources/nanosuit/arm_showroom_spec.png
  resources/nanosuit/body_dif.png
  resources/nanosuit/body_showroom_ddn.png
  resources/nanosuit/body_showroom_spec.png
  resources/nanosuit/glass_ddn.png
  resources/nanosuit/glass_dif.png
  resources/nanosuit/hand_dif.png
  resources/nanosuit/hand_showroom_ddn.png
  resources/nanosuit/hand_showroom_spec.png
  resources/nanosuit/helmet_diff.png
  resources/nanosuit/helmet_showroom_ddn.png
  resources/nanosuit/helmet_showroom_spec.png
  resources/nanosuit/leg_dif.png
  resources/nanosuit/leg_showroom_ddn.png
  resources/nanosuit/leg_showroom_spec.png
  resources/nanosuit/LICENSE.txt
  resources/nanosuit/nanosuit.blend
  resources/nanosuit/nanosuit.mtl
  resources/nanosuit/nanosuit.obj

  resources/skybox/back.png
  resources/skybox/bottom.png
  resources/skybox/front.png
  resources/skybox/left.png
  resources/skybox/right.png
  resources/skybox/top.png

  resources/orbital/back.png
  resources/orbital/bottom.png
  resources/orbital/front.png
  resources/orbital/left.png
  resources/orbital/right.png
  resources/orbital/top.png

  resources/nebula/back.png
  resources/nebula/bottom.png
  resources/nebula/front.png
  resources/nebula/left.png
  resources/nebula/right.png
  resources/nebula/top.png

  resources/axes/axes.mtl
  resources/axes/axes.obj
  resources/axes/red.png
  resources/axes/green.png
  resources/axes/blue.png


)