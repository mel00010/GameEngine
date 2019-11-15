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
		DVD::Resources
		
		Logger
)
include(CMakeRC)

cmrc_add_resource_library(DVD-Resources ALIAS DVD::Resources NAMESPACE DVD)
cmrc_add_resources(DVD-Resources
	WHENCE resources
	
	resources/dvd.png
	resources/wall.jpg
)