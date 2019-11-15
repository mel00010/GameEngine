add_library(GameEngine STATIC "")
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
		${CMAKE_CURRENT_SOURCE_DIR}/VBO_handle.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Vertex.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/WindowManager.hpp
)

cmrc_add_resource_library(GameEngine-Resources ALIAS GameEngine::Resources NAMESPACE GameEngine)

target_link_libraries(GameEngine
	PUBLIC
		2D
		3D
		GL
		Sound
		Util
		
		GameEngine::Resources
		
		Logger
		boost_program_options
		pthread
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