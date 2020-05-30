add_library(3D_test INTERFACE)

#target_sources(3D_test
#  INTERFACE
#    ${CMAKE_CURRENT_SOURCE_DIR}/UUID_test.cpp
#)
target_link_libraries(3D_test
  INTERFACE
    3D
)
