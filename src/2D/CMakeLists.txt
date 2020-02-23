add_library(2D STATIC "")
add_library(GameEngine::2D ALIAS 2D)

target_sources(2D
	PRIVATE
		FpsRenderer.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/FpsRenderer.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/TextRenderer.hpp
)

target_include_directories(2D
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(2D
	PUBLIC
		Logger::Logger
		Freetype::Freetype

		GameEngine::GL
		GameEngine::Resources
)