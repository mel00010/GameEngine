add_library(GameEngine_GL_test INTERFACE)
add_library(GameEngine::GL::test ALIAS GameEngine_GL_test)

target_sources(GameEngine_GL_test
  INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/GL_test.cpp
)
target_link_libraries(GameEngine_GL_test
  INTERFACE
    GameEngine::GL
)
