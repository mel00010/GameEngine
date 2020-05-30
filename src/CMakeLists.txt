add_library(GameEngine STATIC "")
add_library(GameEngine::GameEngine ALIAS GameEngine)
#set_target_properties(GameEngine PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)

target_sources(GameEngine
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
cmrc_add_resource_library(GameEngine-Resources ALIAS GameEngine::Resources NAMESPACE GameEngine)

target_link_libraries(GameEngine
  PUBLIC
    GameEngine::2D
    GameEngine::3D
    GameEngine::GL
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
target_precompile_headers(GameEngine
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

target_include_directories(GameEngine
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/
)
add_subdirectory(2D)
add_subdirectory(3D)
add_subdirectory(GL)
add_subdirectory(Sound)
add_subdirectory(Util)
add_subdirectory(Vulkan)