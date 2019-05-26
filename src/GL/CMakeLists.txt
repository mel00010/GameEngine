add_library(GL STATIC "")
target_sources(GL
	PRIVATE
		Attribute.cpp
		Program.cpp
		Shader.cpp
		WindowManager.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/Attribute.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/GL.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Program.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Shader.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/WindowManager.hpp
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
)