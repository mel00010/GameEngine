add_library(GameEngine_Util_test INTERFACE)
add_library(GameEngine::Util::test ALIAS GameEngine_Util_test)


target_sources(GameEngine_Util_test
  INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/Util_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/UUID_test.cpp
)
target_link_libraries(GameEngine_Util_test
  INTERFACE
    GameEngine::Util
)
