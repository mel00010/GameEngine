add_library(GameEngine_Util STATIC "")
add_library(GameEngine::Util ALIAS GameEngine_Util)
#set_target_properties(Util PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)

target_sources(GameEngine_Util
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
target_link_libraries(GameEngine_Util
  PUBLIC
    GameEngine::GameEngine
    Logging::Logging
    glm
)
target_include_directories(GameEngine_Util
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)