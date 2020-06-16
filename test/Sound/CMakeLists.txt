add_library(GameEngine_Sound_test INTERFACE)
add_library(GameEngine::Sound::test ALIAS GameEngine_Sound_test)

target_sources(GameEngine_Sound_test
  INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/Sound_test.cpp
)
target_link_libraries(GameEngine_Sound_test
  INTERFACE
    GameEngine::Sound
)
