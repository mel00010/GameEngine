add_executable(MineTest "")
target_sources(MineTest
	PRIVATE
		main.cpp
		MineTest.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/MineTest.hpp
)

target_link_libraries(MineTest
	PUBLIC
		GameEngine
		MineTest::Resources
		
		Logger
)
include(CMakeRC)

cmrc_add_resource_library(MineTest-Resources ALIAS MineTest::Resources NAMESPACE MineTest)
cmrc_add_resources(MineTest-Resources
	WHENCE resources
	
	resources/cube/cube.mtl
	resources/cube/cube.obj
	resources/cube/wall.jpg
	
	resources/grid/grid.mtl
	resources/grid/grid.obj
	resources/grid/grid.png
	
	resources/nanosuit/arm_dif.png
	resources/nanosuit/arm_showroom_ddn.png
	resources/nanosuit/arm_showroom_spec.png
	resources/nanosuit/body_dif.png
	resources/nanosuit/body_showroom_ddn.png
	resources/nanosuit/body_showroom_spec.png
	resources/nanosuit/glass_ddn.png
	resources/nanosuit/glass_dif.png
	resources/nanosuit/hand_dif.png
	resources/nanosuit/hand_showroom_ddn.png
	resources/nanosuit/hand_showroom_spec.png
	resources/nanosuit/helmet_diff.png
	resources/nanosuit/helmet_showroom_ddn.png
	resources/nanosuit/helmet_showroom_spec.png
	resources/nanosuit/leg_dif.png
	resources/nanosuit/leg_showroom_ddn.png
	resources/nanosuit/leg_showroom_spec.png
	resources/nanosuit/LICENSE.txt
	resources/nanosuit/nanosuit.blend
	resources/nanosuit/nanosuit.mtl
	resources/nanosuit/nanosuit.obj
	
	resources/oof.ogg
	resources/ouch.ogg
	resources/rickroll.ogg
)