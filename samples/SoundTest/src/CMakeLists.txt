add_executable(SoundTest "")
target_sources(SoundTest
	PRIVATE
		main.cpp
		SoundTest.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/SoundTest.hpp
)

target_link_libraries(SoundTest
	PUBLIC
		GameEngine
		SoundTest_Resources
		
		Logger
)
include(ConfigureResources)
#				 Target			Top Directory				Namespace
target_resources(SoundTest		${CMAKE_CURRENT_BINARY_DIR}	SoundTest
#	Path												ID				Type	Main File
	${CMAKE_CURRENT_SOURCE_DIR}/resources/vertex.glsl	VERTEX_SHADER	SHADER	vertex.glsl
	${CMAKE_CURRENT_SOURCE_DIR}/resources/fragment.glsl	FRAGMENT_SHADER	SHADER	fragment.glsl
	${CMAKE_CURRENT_SOURCE_DIR}/resources/cube			CUBE			MODEL	cube.obj
	${CMAKE_CURRENT_SOURCE_DIR}/resources/grid			GRID			MODEL	grid.obj
	${CMAKE_CURRENT_SOURCE_DIR}/resources/nanosuit		NANOSUIT		MODEL	nanosuit.obj
	${CMAKE_CURRENT_SOURCE_DIR}/resources/oof.ogg		OOF				SOUND	oof.obj
	${CMAKE_CURRENT_SOURCE_DIR}/resources/ouch.ogg		OUCH			SOUND	ouch.obj
	${CMAKE_CURRENT_SOURCE_DIR}/resources/rickroll.ogg	RICKROLL		SOUND	rickroll.obj
)