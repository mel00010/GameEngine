add_library(Util INTERFACE)

target_sources(Util
	INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/ResourceDefs.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Singleton.hpp
)
target_link_libraries(Util
	INTERFACE
		Logger
)