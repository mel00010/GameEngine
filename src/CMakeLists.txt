add_library(GameEngine STATIC "")
target_sources(GameEngine
	PRIVATE
		Attribute.cpp
		CallbackHandler.cpp
		FPSRenderer.cpp
		GameCore.cpp
		InputHandler.cpp
		Mesh.cpp
		Model.cpp
		Program.cpp
		Shader.cpp
		TextRenderer.cpp
		Texture.cpp
		WindowManager.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/Attribute.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/CallbackHandler.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Camera.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/FPSRenderer.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/GameCore.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/GL.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/InputHandler.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Mesh.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Model.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Program.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/ResourceDefs.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Shader.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/TextRenderer.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Texture.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Vertex.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/WindowManager.hpp
		
)

target_link_libraries(GameEngine
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
		Freetype::Freetype
		boost_program_options
		boost_filesystem
)

target_include_directories(GameEngine 
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/
)

add_subdirectory(Util)