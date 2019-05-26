add_library(3D STATIC "")
target_sources(3D
	PRIVATE
		Mesh.cpp
		Model.cpp
		Texture.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/Camera.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Mesh.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Model.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Texture.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Vertex.hpp
)

target_include_directories(3D 
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(3D
	PUBLIC
		GL
		Util
		Logger
		assimp
)