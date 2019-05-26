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
		GameEngine
		CameraTest_Resources
		
		Logger
)
include(ConfigureResources)
#				 Target			Top Directory				Namespace
target_resources(CameraTest		${CMAKE_CURRENT_BINARY_DIR}	CameraTest
#	Path												ID				Type	Main File
	${CMAKE_CURRENT_SOURCE_DIR}/resources/vertex.glsl	VERTEX_SHADER	SHADER	vertex.glsl
	${CMAKE_CURRENT_SOURCE_DIR}/resources/fragment.glsl	FRAGMENT_SHADER	SHADER	fragment.glsl
	${CMAKE_CURRENT_SOURCE_DIR}/resources/cube			CUBE			MODEL	cube.obj
	${CMAKE_CURRENT_SOURCE_DIR}/resources/grid			GRID			MODEL	grid.obj
	${CMAKE_CURRENT_SOURCE_DIR}/resources/nanosuit		NANOSUIT		MODEL	nanosuit.obj
)