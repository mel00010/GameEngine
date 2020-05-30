add_library(3D STATIC "")
add_library(GameEngine::3D ALIAS 3D)

target_sources(3D
  PRIVATE
    Camera.cpp
    Cube.cpp
    Cubemap.cpp
    EmbeddedIOHandler.cpp
    EmbeddedIOStream.cpp
    Mesh.cpp
    Model.cpp
    Texture.cpp
    Transformations.cpp
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Camera.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Cube.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Cubemap.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/EmbeddedIOHandler.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/EmbeddedIOStream.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Mesh.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Model.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/PixelFormat.hpp
    #include <Log.hpp>
    ${CMAKE_CURRENT_SOURCE_DIR}/Primitive.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Scene.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Skybox.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Texture.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Transformations.hpp
)
#set_target_properties(3D PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
#target_precompile_headers(3D REUSE_FROM Logging::Logging)

target_include_directories(3D
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(3D
  PUBLIC
    Logging::Logging
    GameEngine::3D::Resources
    GameEngine::GL
    GameEngine::Util

    assimp::assimp
)

include(CMakeRC)

cmrc_add_resource_library(GameEngine-3D-Resources ALIAS GameEngine::3D::Resources NAMESPACE _3D)
cmrc_add_resources(GameEngine-3D-Resources
  WHENCE resources

  resources/cube/cube.mtl
  resources/cube/cube.obj
)