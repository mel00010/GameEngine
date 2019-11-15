add_library(GL STATIC "")
target_sources(GL
	PRIVATE
		GLRenderer.cpp
		GLWindowManager.cpp
		Shader.cpp
		ShaderProgram.cpp
		VBO.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/GLPrimitive.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/GLRenderer.hpp	
		${CMAKE_CURRENT_SOURCE_DIR}/GLWindowManager.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Shader.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/ShaderProgram.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/VBO.hpp
)


target_include_directories(GL 
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(GL
	PUBLIC
		Util
		Logger
		OpenGL::OpenGL
		OpenGL::GLX
		glm
		GLUT
		GLEW
		SDL2
		SDL2_image
		
		GL::Resources
)

include(CMakeRC)

cmrc_add_resource_library(GL-Resources ALIAS GL::Resources NAMESPACE GL)
cmrc_add_resources(GL-Resources
	WHENCE resources
	
	resources/default.fs.glsl
	resources/default.vs.glsl
	resources/skybox.fs.glsl
	resources/skybox.vs.glsl
	resources/text.fs.glsl
	resources/text.vs.glsl
)

