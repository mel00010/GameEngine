add_library(Util STATIC "")
add_library(GameEngine::Util ALIAS Util)
#set_target_properties(Util PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)

target_sources(Util
  PRIVATE
    Rng.cpp
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Bind.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Crtp.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/EnumBitMask.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/EnumComparisons.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Rng.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Singleton.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Uuid.hpp
)
target_link_libraries(Util
  PUBLIC
    GameEngine
    Logging::Logging
    glm
)
target_include_directories(Util
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)