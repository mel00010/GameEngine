add_library(Sound STATIC "")
target_sources(Sound
	PRIVATE
		Music.cpp
		Sound.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/Music.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Sound.hpp
)

target_include_directories(Sound
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(Sound
	PUBLIC
		Util
		Logger
		SDL2
		SDL2_mixer
)