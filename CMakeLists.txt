cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
project(monkey_lang_cpp_implementation)
include(CTest)
add_subdirectory(external)
add_subdirectory(tests)
add_subdirectory(lexer)
add_subdirectory(parser)
add_subdirectory(ast)

add_executable(monkey main.cc lexer/lexer.cc token/token.cc repl/repl.cc parser/parser.cc ast/ast.cc)
