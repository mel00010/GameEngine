add_executable(DVD_model "")
target_sources(DVD_model
  PRIVATE
    Dvd.cpp
    DvdCore.cpp
    main.cpp
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Dvd.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/DvdCore.hpp
)
#set_target_properties(DVD_model PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
if(NOT DISABLE_PCH)
  if(NOT CMAKE_POSITION_INDEPENDENT_CODE)
    target_precompile_headers(DVD_model REUSE_FROM GameEngine::GameEngine)
  endif()
endif()

target_link_libraries(DVD_model
  PUBLIC
    GameEngine::GameEngine
    DVD_model::Resources

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
  setup_target_for_coverage(NAME DVD_model_coverage EXECUTABLE samples/dvd_model/src/DVD_model DEPENDENCIES DVD_model)
endif()

cmrc_add_resource_library(DVD_model_Resources ALIAS DVD_model::Resources NAMESPACE dvd)
cmrc_add_resources(DVD_model_Resources
  WHENCE resources

  resources/dvd/dvd.mtl
  resources/dvd/dvd.obj
  resources/dvd/dvd.png
)