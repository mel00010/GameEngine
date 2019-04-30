add_library(Util INTERFACE)

target_sources(Util
	INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/Singleton.hpp
)