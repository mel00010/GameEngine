add_executable(SlangTest "")
target_sources(SlangTest
  PRIVATE
    main.cpp
    SlangTest.cpp
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/SlangTest.hpp
)
#set_target_properties(SlangTest PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
if(NOT DISABLE_PCH)
  if(NOT CMAKE_POSITION_INDEPENDENT_CODE)
    target_precompile_headers(SlangTest REUSE_FROM GameEngine::GameEngine)
  endif()
endif()

target_link_libraries(SlangTest
  PUBLIC
    GameEngine::GameEngine
    SlangTest::Resources

    Slang
    glm
)
include(CMakeRC)

cmrc_add_resource_library(SlangTest-Resources ALIAS SlangTest::Resources NAMESPACE slang_test)
cmrc_add_resources(SlangTest-Resources
  WHENCE resources

  resources/oof.ogg
  resources/ouch.ogg
  resources/rickroll.ogg
)