add_library(2D STATIC "")
target_sources(2D
	PRIVATE
		FPSRenderer.cpp
		TextRenderer.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/FPSRenderer.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/TextRenderer.hpp
)

target_include_directories(2D 
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(2D
	PUBLIC
		GL
		Logger
		Freetype::Freetype
)