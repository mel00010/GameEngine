add_library(GameEngine_Plugin STATIC "")
add_library(GameEngine::Plugin ALIAS GameEngine_Plugin)
#set_target_properties(GameEngine_Plugin PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)

target_sources(GameEngine_Plugin
  PRIVATE
    Plugin.cpp
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Plugin.hpp
)

target_include_directories(GameEngine_Plugin
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(GameEngine_Plugin
  PUBLIC
    Boost::boost
    Boost::filesystem
    Boost::system
    ${CMAKE_DL_LIBS}

    Logging::Logging

    GameEngine::Util
    GameEngine::Resources
)
#target_precompile_headers(Sound REUSE_FROM Logging::Logging)
