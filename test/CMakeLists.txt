include(GetGoogleTest)

if(CMAKE_BUILD_TYPE STREQUAL "Coverage")
	# coverage target setup
	include(CodeCoverage)
	append_coverage_compiler_flags()
	set(COVERAGE_EXCLUDES
		'${PROJECT_SOURCE_DIR}/test/*'
		'${PROJECT_BINARY_DIR}/googletest-src/*'
		'${PROJECT_BINARY_DIR}/googletest-build/*'
		'/usr/include/c++/6/*'
		'/usr/include/c++/7/*'
		'/usr/include/c++/8/*'
		'/usr/local/include/boost/*'
	)
	setup_target_for_coverage(NAME coverage EXECUTABLE test/tests DEPENDENCIES tests)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
	add_executable(tests EXCLUDE_FROM_ALL "")
else()
	add_executable(tests "")	
endif()
target_sources(tests
	PRIVATE
		main_test.cpp
)

target_include_directories(tests
	PRIVATE
		${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(tests
	gtest
	gmock
	gmock_main
	pthread
)

