add_executable(SlangTest "")
target_sources(SlangTest
	PRIVATE
		main.cpp
		SlangTest.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/SlangTest.hpp
)

target_link_libraries(SlangTest
	PUBLIC
		GameEngine
		SlangTest::Resources

		Slang
		Logger::Logger
)
include(CMakeRC)

cmrc_add_resource_library(SlangTest-Resources ALIAS SlangTest::Resources NAMESPACE slang_test)
cmrc_add_resources(SlangTest-Resources
	WHENCE resources

	resources/oof.ogg
	resources/ouch.ogg
	resources/rickroll.ogg
)