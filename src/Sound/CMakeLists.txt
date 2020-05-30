add_library(Sound STATIC "")
add_library(GameEngine::Sound ALIAS Sound)
#set_target_properties(Sound PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)

target_sources(Sound
  PRIVATE
    Music.cpp
    Sound.cpp
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Music.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sound.hpp
)

target_include_directories(Sound
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(Sound
  PUBLIC
    SDL2
    SDL2_mixer

    Logging::Logging

    GameEngine::Util
    GameEngine::Resources
)
#target_precompile_headers(Sound REUSE_FROM Logging::Logging)
