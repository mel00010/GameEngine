add_executable(DVD_model "")
target_sources(DVD_model
	PRIVATE
		DVD.cpp
		DVDCore.cpp
		main.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/DVD.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/DVDCore.hpp
)

target_link_libraries(DVD_model
	PUBLIC
		GameEngine
		DVD_model::Resources
		
		Logger
)
include(CMakeRC)

cmrc_add_resource_library(DVD_model-Resources ALIAS DVD_model::Resources NAMESPACE DVD)
cmrc_add_resources(DVD_model-Resources
	WHENCE resources
	
	resources/dvd/dvd.mtl
	resources/dvd/dvd.obj
	resources/dvd/dvd.png
)