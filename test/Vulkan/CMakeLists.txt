add_library(GameEngine_Vulkan_test INTERFACE)
add_library(GameEngine::Vulkan::test ALIAS GameEngine_Vulkan_test)

target_sources(GameEngine_Vulkan_test
  INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/Vulkan_test.cpp
)

target_link_libraries(GameEngine_Vulkan_test
  INTERFACE
    GameEngine::Vulkan
)
