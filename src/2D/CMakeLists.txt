add_library(GameEngine_2D STATIC "")
add_library(GameEngine::2D ALIAS GameEngine_2D)
#set_target_properties(2D PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)

target_sources(GameEngine_2D
  PRIVATE
    FpsRenderer.cpp
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/FpsRenderer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TextRenderer.hpp
)
#target_precompile_headers(2D REUSE_FROM Logging::Logging)

target_include_directories(GameEngine_2D
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(GameEngine_2D
  PUBLIC
    Logging::Logging
    Freetype::Freetype

    GameEngine::GL
    GameEngine::Resources
)