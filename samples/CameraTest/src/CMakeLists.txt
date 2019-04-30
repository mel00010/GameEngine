add_executable(CameraTest "")
target_sources(CameraTest
	PRIVATE
		main.cpp
		CameraTestCore.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/CameraTestCore.hpp
)

target_link_libraries(CameraTest
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
		CameraTest_Resources
)
include(ConfigureResources)
#				 Target			Top Directory				Namespace
target_resources(CameraTest		${CMAKE_CURRENT_BINARY_DIR}	CameraTest
#	Path												ID				Type	
	${CMAKE_CURRENT_SOURCE_DIR}/resources/vertex.glsl	VERTEX_SHADER	SHADER
	${CMAKE_CURRENT_SOURCE_DIR}/resources/fragment.glsl	FRAGMENT_SHADER	SHADER
	${CMAKE_CURRENT_SOURCE_DIR}/resources/wall.jpg		WALL			IMAGE
)