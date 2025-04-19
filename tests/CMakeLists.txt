if(BUILD_TESTING) 
	add_executable(test_lexer test_lexer.cc)
	add_executable(test_parser test_parser.cc)
	add_executable(test_ast test_ast.cc)

	target_link_libraries(test_lexer PRIVATE GTest::gtest_main lexer) 
	target_link_libraries(test_parser PRIVATE GTest::gtest_main parser) 
	target_link_libraries(test_ast PRIVATE GTest::gtest_main ast) 
	                                            
	include(GoogleTest)
	gtest_discover_tests(test_lexer)
	gtest_discover_tests(test_parser)
	gtest_discover_tests(test_ast)

endif()