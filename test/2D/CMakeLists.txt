add_library(GameEngine_2D_test INTERFACE)
add_library(GameEngine::2D::test ALIAS GameEngine_2D_test)

target_sources(GameEngine_2D_test
  INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/2D_test.cpp
)

target_link_libraries(GameEngine_2D_test
  INTERFACE
    GameEngine::2D
)
