add_library(2D_test INTERFACE)

#target_sources(2D_test
#  INTERFACE
#    ${CMAKE_CURRENT_SOURCE_DIR}/2D_test.cpp
#)
target_link_libraries(2D_test
  INTERFACE
    2D
)
