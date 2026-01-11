if(BUILD_TESTING) 
	add_executable(test_lexer test_lexer.cc)
	add_executable(test_parser test_parser.cc)
	add_executable(test_ast test_ast.cc)
	add_executable(test_eval test_eval.cc)

	target_link_libraries(test_lexer PRIVATE GTest::gtest_main lexer) 
	target_link_libraries(test_parser PRIVATE GTest::gtest_main parser) 
	target_link_libraries(test_ast PRIVATE GTest::gtest_main ast) 
	target_link_libraries(test_eval PRIVATE GTest::gtest_main evaluation) 
	                                            
	include(GoogleTest)
	gtest_discover_tests(test_lexer)
	gtest_discover_tests(test_parser)
	gtest_discover_tests(test_ast)
	gtest_discover_tests(test_eval)

endif()