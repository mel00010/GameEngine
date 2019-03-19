add_executable(DVD "")
target_sources(DVD
	PRIVATE
		DVD.cpp
		DVDCore.cpp
		main.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/DVD.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/DVDCore.hpp
)

target_link_libraries(DVD
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
		GameEngine
		DVD_Resources
)
include(ConfigureResources)

target_resources(DVD ${CMAKE_CURRENT_BINARY_DIR}
#	Path												ID				Type	
	${CMAKE_CURRENT_SOURCE_DIR}/resources/vertex.glsl	VERTEX_SHADER	SHADER	
	${CMAKE_CURRENT_SOURCE_DIR}/resources/fragment.glsl	FRAGMENT_SHADER	SHADER	
	${CMAKE_CURRENT_SOURCE_DIR}/resources/wall.jpg		WALL			IMAGE	
	${CMAKE_CURRENT_SOURCE_DIR}/resources/dvd.png		DVD				IMAGE	
)