add_library(GameEngine_GL STATIC "")
add_library(GameEngine::GL ALIAS GameEngine_GL)
target_sources(GameEngine_GL
  PRIVATE
    GLRenderer.cpp
    GLWindowManager.cpp
    Shader.cpp
    ShaderProgram.cpp
    Vbo.cpp
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/GLPrimitive.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GLRenderer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GLWindowManager.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Shader.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ShaderProgram.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Vbo.hpp
)
#set_target_properties(GameEngine_GL PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)

target_include_directories(GameEngine_GL
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(GameEngine_GL
  PUBLIC
    GameEngine::GL::Resources
    GameEngine::Util
    Logging::Logging

    OpenGL::OpenGL
    OpenGL::GLX
    glm
    GLUT
    GLEW
    SDL2
    SDL2_image
#    Slang
)

include(CMakeRC)

cmrc_add_resource_library(GameEngine_GL_Resources ALIAS GameEngine::GL::Resources NAMESPACE gl)
cmrc_add_resources(GameEngine_GL_Resources
  WHENCE resources

  resources/default.fs.glsl
  resources/default.vs.glsl
  resources/cube.fs.glsl
  resources/cube.vs.glsl
  resources/skybox.fs.glsl
  resources/skybox.vs.glsl
  resources/text.fs.glsl
  resources/text.vs.glsl
)

