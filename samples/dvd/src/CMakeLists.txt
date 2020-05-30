add_executable(DVD "")
target_sources(DVD
  PRIVATE
    Dvd.cpp
    DvdCore.cpp
    main.cpp
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Dvd.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/DvdCore.hpp
)
#set_target_properties(DVD PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
target_precompile_headers(DVD REUSE_FROM GameEngine::GameEngine)

target_link_libraries(DVD
  PUBLIC
    GameEngine::GameEngine
    DVD::Resources

    glm
)
include(CMakeRC)

cmrc_add_resource_library(DVD-Resources ALIAS DVD::Resources NAMESPACE dvd)
cmrc_add_resources(DVD-Resources
  WHENCE resources

  resources/dvd.png
  resources/wall.jpg
)