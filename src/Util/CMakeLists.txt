add_library(Util STATIC "")
add_library(GameEngine::Util ALIAS Util)

target_sources(Util
	PRIVATE
		Rng.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/Bind.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Crtp.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/EnumBitMask.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Rng.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Singleton.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Uuid.hpp
)
target_link_libraries(Util
	PUBLIC
		Logger::Logger
)
target_include_directories(Util
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/..
)