add_library(GameEngine_3D_test INTERFACE)
add_library(GameEngine::3D::test ALIAS GameEngine_3D_test)

target_sources(GameEngine_3D_test
  INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/3D_test.cpp
)

target_link_libraries(GameEngine_3D_test
  INTERFACE
    GameEngine::3D
)
