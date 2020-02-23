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
		GameEngine::GameEngine
		CubeTest::Resources

		Logger::Logger
)
include(CMakeRC)

cmrc_add_resource_library(CubeTest-Resources ALIAS CubeTest::Resources NAMESPACE cube_test)
cmrc_add_resources(CubeTest-Resources
	WHENCE resources

	resources/cube/back.png
	resources/cube/bottom.png
	resources/cube/front.png
	resources/cube/left.png
	resources/cube/right.png
	resources/cube/top.png
)