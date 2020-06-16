add_library(GameEngine_Vulkan STATIC "")
add_library(GameEngine::Vulkan ALIAS GameEngine_Vulkan)
#set_target_properties(GameEngine_Vulkan PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)

target_sources(GameEngine_Vulkan
  PRIVATE
    VulkanRenderer.cpp
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/VulkanRenderer.cpp
)

target_include_directories(GameEngine_Vulkan
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(GameEngine_Vulkan
  PUBLIC
    Logging::Logging

    GameEngine::Util
    GameEngine::Resources
)
#target_precompile_headers(Sound REUSE_FROM Logging::Logging)
