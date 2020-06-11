include(GetGoogleTest)

if(CMAKE_BUILD_TYPE STREQUAL "Coverage")
  # coverage target setup
  include(CodeCoverage)
  set(COVERAGE_EXCLUDES
    '${PROJECT_SOURCE_DIR}/test/*'
    '/usr/include/c++/6/*'
    '/usr/include/c++/7/*'
    '/usr/include/c++/8/*'
    '/usr/local/include/boost/*'
  )
  setup_target_for_coverage(NAME coverage EXECUTABLE test/tests DEPENDENCIES tests)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  add_executable(tests "")

else()
  add_executable(tests "")
endif()
target_sources(tests
  PRIVATE
    main_test.cpp
)

target_include_directories(tests
  PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)
#target_precompile_headers(tests REUSE_FROM GameEngine::GameEngine)
#set_target_properties(tests PROPERTIES INTERPROCEDURAL_OPTIMIZATION FALSE)

set(CMAKE_FIND_LIBRARY_SUFFIXES .a)
message("$ENV{LD_LIBRARY_PATH}")
target_link_libraries(tests
#  2D_test
#  3D_test
#  GL_test
#  Sound_test
  Util_test
#  Vulkan_test

  # $<TARGET_FILE> is used to prevent shared linking of gtest
  gtest
  gmock
  gmock_main
  pthread
)
#add_subdirectory(2D)
#add_subdirectory(3D)
#add_subdirectory(GL)
#add_subdirectory(Sound)
add_subdirectory(Util)
#add_subdirectory(Vulkan)