add_library(PluginTest_plugin1 SHARED "")
add_library(PluginTest::plugin1 ALIAS PluginTest_plugin1)
target_sources(PluginTest_plugin1
  PRIVATE
    plugin1.cpp
)
target_link_libraries(PluginTest_plugin1
  PUBLIC
    Logging::Logging
    Boost::boost
    Boost::filesystem
    Boost::system
    ${CMAKE_DL_LIBS}
)
target_compile_options(PluginTest_plugin1 PUBLIC -frtti)
