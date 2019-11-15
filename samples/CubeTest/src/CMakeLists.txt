add_executable(CubeTest "")
target_sources(CubeTest
	PRIVATE
		main.cpp
		CubeTestCore.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/CubeTestCore.hpp
)

target_link_libraries(CubeTest
	PUBLIC
		GameEngine
		CubeTest::Resources
		
		Logger
)
include(CMakeRC)

cmrc_add_resource_library(CubeTest-Resources ALIAS CubeTest::Resources NAMESPACE CubeTest)
cmrc_add_resources(CubeTest-Resources
	WHENCE resources
	
	resources/cube/cube.mtl
	resources/cube/cube.obj
	resources/cube/wall.jpg
)