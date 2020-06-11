cmake_minimum_required (VERSION 3.16)

project (GameEngine)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(GNUInstallDirs)
INCLUDE(FindPkgConfig)
set(CMAKE_POLICY_DEFAULT_CMP0069 NEW)
cmake_policy(SET CMP0069 NEW)
include(CheckIPOSupported)

# Optional IPO. Do not use IPO if it's not supported by compiler.
check_ipo_supported(RESULT result OUTPUT output)
if(result)
  set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
else()
  message(WARNING "IPO is not supported: ${output}")
endif()

set(CMAKE_POLICY_DEFAULT_CMP0083 NEW)
cmake_policy(SET CMP0083 NEW)

include(CheckPIESupported)
check_pie_supported()
set(CMAKE_POSITION_INDEPENDENT_CODE FALSE)

set(CMAKE_LINK_WHAT_YOU_USE FALSE)

set(BUILD_SHARED_LIBS OFF)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--thinlto-cache-dir=${PROJECT_BINARY_DIR}/lto.cache")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--thinlto-cache-dir=${PROJECT_BINARY_DIR}/lto.cache")


list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(REDIRECTION_FLAGS "-ffile-prefix-map=../../samples/=")
set(REDIRECTION_FLAGS "${REDIRECTION_FLAGS} -ffile-prefix-map=../samples/=")
set(REDIRECTION_FLAGS "${REDIRECTION_FLAGS} -ffile-prefix-map=${CMAKE_SOURCE_DIR}=")
set(REDIRECTION_FLAGS "${REDIRECTION_FLAGS} -ffile-prefix-map=../src=GameEngine")
set(REDIRECTION_FLAGS "${REDIRECTION_FLAGS} -ffile-prefix-map=../../src=GameEngine")
set(REDIRECTION_FLAGS "${REDIRECTION_FLAGS} -ffile-prefix-map=_deps/=")

set(SHARED_FLAGS "-Wno-unused-result -Wsign-compare")
set(SHARED_FLAGS "${SHARED_FLAGS} -fstack-protector-strong -Wformat")
set(SHARED_FLAGS "${SHARED_FLAGS} -Werror=format-security -fwrapv")
set(SHARED_FLAGS "${SHARED_FLAGS} -Wall -Wextra")
set(SHARED_FLAGS "${SHARED_FLAGS} -fdiagnostics-color=always")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${SHARED_FLAGS}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SHARED_FLAGS}")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -ggdb")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG_BUILD=1 -DMIN_LOG_LEVEL=0")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -D_DEBUG_BUILD=0 -DMIN_LOG_LEVEL=0 ${REDIRECTION_FLAGS}")


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

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
  set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_COVERAGE} -fcoverage-mapping")
  set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_COVERAGE} -fprofile-instr-generate")
  # using Clang
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fconcepts")
  set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_COVERAGE} --coverage -fprofile-arcs")
  set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_COVERAGE} -ftest-coverage")
  # using GCC
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
  # using Intel C++
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  # using Visual Studio C++
endif()

cmake_policy(SET CMP0072 NEW)
set(OpenGL_GL_PREFERENCE "GLVND")
set_property(GLOBAL PROPERTY JOB_POOLS two_jobs=2 ten_jobs=10)
set(CMAKE_JOB_POOL_LINK two_jobs)

include(GetAssimp)
set_target_properties(assimp PROPERTIES COMPILE_FLAGS "-w")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

include(GetLoggerV2)
include(GetAbseil)
include(GetBoostDI)

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
add_library(glm INTERFACE)
target_link_libraries(glm INTERFACE ${glm_LIBRARIES})
target_include_directories(glm INTERFACE ${glm_INCLUDE_DIRS})
target_compile_definitions(glm INTERFACE ${glm_DEFINITIONS})

find_file(SDL2_INCLUDE_DIR NAME SDL.h HINTS SDL2)
find_package(SDL2 REQUIRED)
add_library(SDL2 INTERFACE)
target_link_libraries(SDL2 INTERFACE ${SDL2_LIBRARIES})
target_include_directories(SDL2 INTERFACE ${SDL2_INCLUDE_DIRS})

find_package(SDL2_image REQUIRED)
add_library(SDL2_image INTERFACE)
target_link_libraries(SDL2 INTERFACE ${SDL2_IMAGE_LIBRARIES} SDL2)
target_include_directories(SDL2 INTERFACE ${SDL2_IMAGE_INCLUDE_DIRS})

find_package(SDL2_mixer REQUIRED)
add_library(SDL2_mixer INTERFACE)
target_link_libraries(SDL2_mixer INTERFACE ${SDL2_MIXER_LIBRARIES} SDL2)
target_include_directories(SDL2_mixer INTERFACE ${SDL2_MIXER_INCLUDE_DIRS})

find_package(Freetype REQUIRED)

find_package (Boost REQUIRED)

add_library(boost INTERFACE IMPORTED)
target_link_libraries(boost ${boost_LIBRARIES})
target_include_directories(boost PUBLIC ${boost_INCLUDE_DIRS})

# The version number.
set(GameEngine_VERSION_MAJOR 0)
set(GameEngine_VERSION_MINOR 1)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#Subdirectories
add_subdirectory(src)
add_subdirectory(samples)
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

