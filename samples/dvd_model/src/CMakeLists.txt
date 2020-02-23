add_executable(DVD_model "")
target_sources(DVD_model
	PRIVATE
		Dvd.cpp
		DvdCore.cpp
		main.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/Dvd.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/DvdCore.hpp
)

target_link_libraries(DVD_model
	PUBLIC
		GameEngine
		DVD_model::Resources

		Logger::Logger
)
include(CMakeRC)

cmrc_add_resource_library(DVD_model-Resources ALIAS DVD_model::Resources NAMESPACE dvd)
cmrc_add_resources(DVD_model-Resources
	WHENCE resources

	resources/dvd/dvd.mtl
	resources/dvd/dvd.obj
	resources/dvd/dvd.png
)