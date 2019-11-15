add_library(3D STATIC "")
target_sources(3D
	PRIVATE
		Camera.cpp
		Cube.cpp
		Cubemap.cpp
		EmbeddedIOHandler.cpp
		EmbeddedIOStream.cpp
		Mesh.cpp
		Model.cpp
		Texture.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/Camera.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Cube.hpp	
		${CMAKE_CURRENT_SOURCE_DIR}/Cubemap.hpp	
		${CMAKE_CURRENT_SOURCE_DIR}/EmbeddedIOHandler.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/EmbeddedIOStream.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Mesh.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Model.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/PixelFormat.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Primitive.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Scene.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Skybox.hpp	
		${CMAKE_CURRENT_SOURCE_DIR}/Texture.hpp
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
		
		3D::Resources
)

include(CMakeRC)

cmrc_add_resource_library(3D-Resources ALIAS 3D::Resources NAMESPACE _3D)
cmrc_add_resources(3D-Resources
	WHENCE resources
	
	resources/cube/cube.mtl
	resources/cube/cube.obj
)