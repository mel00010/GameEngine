add_executable(LogCTADTest "")
target_sources(LogCTADTest
  PRIVATE
    main.cpp
)

target_link_libraries(LogCTADTest
  PUBLIC
    absl::base
    absl::strings
    absl::hash
    absl::flags
    GameEngine
)