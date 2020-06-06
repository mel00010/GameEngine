add_executable(DVD "")
target_sources(DVD
  PRIVATE
    Dvd.cpp
    DvdCore.cpp
    main.cpp
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Dvd.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/DvdCore.hpp
)
#set_target_properties(DVD PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
if(NOT DEFINED DISABLE_PCH)
    target_precompile_headers(DVD REUSE_FROM GameEngine::GameEngine)
endif()

target_link_libraries(DVD
  PUBLIC
    GameEngine::GameEngine
    DVD::Resources

    glm
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
  setup_target_for_coverage(NAME DVD_coverage EXECUTABLE samples/dvd/src/DVD DEPENDENCIES DVD)
endif()

cmrc_add_resource_library(DVD-Resources ALIAS DVD::Resources NAMESPACE dvd)
cmrc_add_resources(DVD-Resources
  WHENCE resources

  resources/dvd.png
  resources/wall.jpg
)