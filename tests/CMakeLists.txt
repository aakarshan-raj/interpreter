if(BUILD_TESTING) 
	add_executable(test_lexer test_lexer.cc)
	target_link_libraries(test_lexer PRIVATE GTest::gtest_main lexer) 
	                                            
	include(GoogleTest)
	gtest_discover_tests(test_lexer)
endif()