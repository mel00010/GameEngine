add_library(Util_test INTERFACE)

target_sources(Util_test
  INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/UUID_test.cpp
)
target_link_libraries(Util_test
  INTERFACE
    Util
)
