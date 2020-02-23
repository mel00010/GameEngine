add_library(Logging STATIC "")
add_library(GameEngine::Logging ALIAS Logging)

target_sources(Logging
	PRIVATE
		Client.cpp
		Log.cpp
		Telemetry.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/Client.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Log.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Telemetry.hpp
)
target_link_libraries(Logging
	PUBLIC
		P7
		gflags

		GameEngine::Util
)