add_executable(EmmaTest "")
target_sources(EmmaTest
  PRIVATE
    main.cpp
)

target_link_libraries(EmmaTest
  PUBLIC
    absl::base
    absl::strings
    absl::hash
    absl::flags
    GameEngine
)