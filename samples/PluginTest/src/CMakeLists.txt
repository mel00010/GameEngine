add_executable(PluginTest "")
target_sources(PluginTest
  PRIVATE
    main.cpp
)

target_link_libraries(PluginTest
  PUBLIC
    Logging::Logging
    Boost::boost
    Boost::filesystem
    Boost::system
    ${CMAKE_DL_LIBS}
)

add_subdirectory(plugin1)