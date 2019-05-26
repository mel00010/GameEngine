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
		GameEngine
		DVD_Resources
		
		Logger
)
include(ConfigureResources)

#				 Target 	Top Directory					Namespace
target_resources(DVD		${CMAKE_CURRENT_BINARY_DIR}		DVD
#	Path												ID				Type	Main File
	${CMAKE_CURRENT_SOURCE_DIR}/resources/vertex.glsl	VERTEX_SHADER	SHADER	vertex.glsl
	${CMAKE_CURRENT_SOURCE_DIR}/resources/fragment.glsl	FRAGMENT_SHADER	SHADER	fragment.glsl
	${CMAKE_CURRENT_SOURCE_DIR}/resources/wall.jpg		WALL			IMAGE	wall.jpg
	${CMAKE_CURRENT_SOURCE_DIR}/resources/dvd.png		DVD				IMAGE	dvd.png
)