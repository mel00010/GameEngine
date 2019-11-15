add_library(Util STATIC "")

target_sources(Util
	PRIVATE
		RNG.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/EnumBitMask.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/RNG.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Singleton.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/UUID.hpp
)
target_link_libraries(Util
	PUBLIC
		Logger
)