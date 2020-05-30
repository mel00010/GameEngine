add_library(Vulkan_test INTERFACE)

#target_sources(Vulkan_test
#  INTERFACE
#    ${CMAKE_CURRENT_SOURCE_DIR}/UUID_test.cpp
#)
target_link_libraries(Vulkan_test
  INTERFACE
    Vulkan
)
