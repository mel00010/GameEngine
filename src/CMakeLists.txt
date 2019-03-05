add_library(GameEngine STATIC "")
target_sources(GameEngine
	PRIVATE
		Attribute.cpp
		CallbackRegistration.cpp
		GameCore.cpp
		Program.cpp
		Shader.cpp
		Texture.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/Attribute.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/GameCore.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Main_Loop.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Program.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Shader.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Texture.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Triangle.hpp
)

target_link_libraries(GameEngine
	PUBLIC
		Logger
		OpenGL::OpenGL
		OpenGL::GLX
		glm
		GLUT
		GLEW
		SDL2
		SDL2_image
		Freetype::Freetype
		boost_program_options
		boost_filesystem
)

target_include_directories(GameEngine 
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/
)