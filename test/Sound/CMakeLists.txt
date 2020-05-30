add_library(Sound_test INTERFACE)

#target_sources(Sound_test
#  INTERFACE
#    ${CMAKE_CURRENT_SOURCE_DIR}/UUID_test.cpp
#)
target_link_libraries(Sound_test
  INTERFACE
    Sound
)
