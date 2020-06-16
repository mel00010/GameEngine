add_library(GameEngine_GameEngine STATIC "")
add_library(GameEngine::GameEngine ALIAS GameEngine_GameEngine)
#set_target_properties(GameEngine_GameEngine PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)

target_sources(GameEngine_GameEngine
  PRIVATE
    CallbackHandler.cpp
    GameCore.cpp
    InputHandler.cpp
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/CallbackHandler.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GameCore.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/InputHandler.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ShaderPrograms.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/VboHandle.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Vertex.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/WindowManager.hpp
)
include(CMakeRC)
cmrc_add_resource_library(GameEngine_Resources ALIAS GameEngine::Resources NAMESPACE game_engine)

target_link_libraries(GameEngine_GameEngine
  PUBLIC
    GameEngine::2D
    GameEngine::3D
    GameEngine::GL
    GameEngine::Plugin
    GameEngine::Sound
    GameEngine::Util
    GameEngine::Resources

    Logging::Logging

    pthread
    absl::flags
    absl::flags_usage
    absl::flags_parse
    absl::strings
)
if(NOT DEFINED DISABLE_PCH)
    target_precompile_headers(GameEngine_GameEngine
      PUBLIC
        CallbackHandler.hpp
        GameCore.hpp
        InputHandler.hpp
        Renderer.hpp
        ShaderPrograms.hpp
        VboHandle.hpp
        Vertex.hpp
        WindowManager.hpp
    )
endif()

target_include_directories(GameEngine_GameEngine
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/
)
add_subdirectory(2D)
add_subdirectory(3D)
add_subdirectory(GL)
add_subdirectory(Plugin)
add_subdirectory(Sound)
add_subdirectory(Util)
add_subdirectory(Vulkan)