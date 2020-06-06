add_executable(SoundTest "")
target_sources(SoundTest
  PRIVATE
    main.cpp
    SoundTest.cpp
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/SoundTest.hpp
)
#set_target_properties(SoundTest PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)

target_link_libraries(SoundTest
  PUBLIC
    GameEngine
    SoundTest::Resources

    glm
)
include(CMakeRC)

if(NOT DEFINED DISABLE_PCH)
    target_precompile_headers(SoundTest REUSE_FROM GameEngine::GameEngine)
endif()

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
  setup_target_for_coverage(NAME SoundTest_coverage EXECUTABLE samples/SoundTest/src/SoundTest DEPENDENCIES SoundTest)
endif()

cmrc_add_resource_library(SoundTest-Resources ALIAS SoundTest::Resources NAMESPACE sound_test)
cmrc_add_resources(SoundTest-Resources
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

  resources/oof.ogg
  resources/ouch.ogg
  resources/rickroll.ogg
)