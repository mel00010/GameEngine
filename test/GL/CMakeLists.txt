add_library(GL_test INTERFACE)

#target_sources(GL_test
#  INTERFACE
#    ${CMAKE_CURRENT_SOURCE_DIR}/UUID_test.cpp
#)
target_link_libraries(GL_test
  INTERFACE
    GL
)
