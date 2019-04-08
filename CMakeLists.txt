cmake_minimum_required (VERSION 3.9)

project (GameEngine)


include(GNUInstallDirs)
INCLUDE(FindPkgConfig)


list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set( CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_DEBUG}" CACHE STRING
    "Flags used by the C++ compiler during coverage builds."
    FORCE )
set( CMAKE_C_FLAGS_COVERAGE "${CMAKE_C_FLAGS_DEBUG}" CACHE STRING
    "Flags used by the C compiler during coverage builds."
    FORCE )
set( CMAKE_EXE_LINKER_FLAGS_COVERAGE
    "${CMAKE_EXE_LINKER_FLAGS_COVERAGE}" CACHE STRING
    "Flags used for linking binaries during coverage builds."
    FORCE )
set( CMAKE_SHARED_LINKER_FLAGS_COVERAGE
    "${CMAKE_SHARED_LINKER_FLAGS_COVERAGE}" CACHE STRING
    "Flags used by the shared libraries linker during coverage builds."
    FORCE )
mark_as_advanced(
    CMAKE_CXX_FLAGS_COVERAGE
    CMAKE_C_FLAGS_COVERAGE
    CMAKE_EXE_LINKER_FLAGS_COVERAGE
    CMAKE_SHARED_LINKER_FLAGS_COVERAGE )
# Update the documentation string of CMAKE_BUILD_TYPE for GUIs
set( CMAKE_BUILD_TYPE "${CMAKE_BUILD_TYPE}" CACHE STRING
    "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel Coverage."
    FORCE )

set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_COVERAGE} -Wno-unused-result -Wsign-compare -fstack-protector-strong")
set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_COVERAGE} -Wformat -Werror=format-security -fwrapv")
set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_COVERAGE} -Wall -Wextra -std=c++2a -g -O0")
set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_COVERAGE} --coverage -fprofile-arcs -ftest-coverage -fdiagnostics-color=always -D_DEBUG_BUILD=1 -DMIN_LOG_LEVEL=0")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wno-unused-result -Wsign-compare -fstack-protector-strong")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wformat -Werror=format-security -fwrapv")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -std=c++2a")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fdiagnostics-color=always -D_DEBUG_BUILD=1 -DMIN_LOG_LEVEL=0")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wno-unused-result -Wsign-compare -fstack-protector-strong")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wformat -Werror=format-security -fwrapv")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wextra -std=c++2a")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fdiagnostics-color=always -D_DEBUG_BUILD=0 -DMIN_LOG_LEVEL=0")

cmake_policy(SET CMP0072 NEW)
set(OpenGL_GL_PREFERENCE "GLVND")

include(GetLogger)
include(GetAssimp)


find_package(OpenGL REQUIRED COMPONENTS OpenGL)

find_package(GLUT REQUIRED)
add_library(GLUT INTERFACE)
target_link_libraries(GLUT INTERFACE ${GLUT_LIBRARIES})
target_include_directories(GLUT INTERFACE ${GLUT_INCLUDE_DIRS})
target_compile_definitions(GLUT INTERFACE ${GLUT_DEFINITIONS})

find_package(GLEW REQUIRED)
add_library(GLEW INTERFACE)
target_link_libraries(GLEW INTERFACE ${GLEW_LIBRARIES})
target_include_directories(GLEW INTERFACE ${GLEW_INCLUDE_DIRS})
target_compile_definitions(GLEW INTERFACE ${GLEW_DEFINITIONS})

find_package(glm REQUIRED)

find_file(SDL2_INCLUDE_DIR NAME SDL.h HINTS SDL2)
find_package(SDL2 REQUIRED)
add_library(SDL2 INTERFACE)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image)
target_link_libraries(SDL2 INTERFACE ${SDL2_LIBRARIES})
target_include_directories(SDL2 INTERFACE ${SDL2_INCLUDE_DIRS})


find_package(Freetype REQUIRED)

find_package (Boost REQUIRED)

add_library(boost INTERFACE IMPORTED)

# The version number.
set(GameEngine_VERSION_MAJOR 0)
set(GameEngine_VERSION_MINOR 1)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#Subdirectories
add_subdirectory(samples)
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(docs)

# uninstall target
if(NOT TARGET uninstall)

	configure_file(
		"${CMAKE_SOURCE_DIR}/cmake/Uninstall.cmake.in"
		"${CMAKE_CURRENT_BINARY_DIR}/Uninstall.cmake"
		IMMEDIATE @ONLY)
	
	add_custom_target(uninstall
		COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/Uninstall.cmake)
endif()

