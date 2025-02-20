set(CMAKE_CXX_STANDARD 17)
add_library(parser STATIC parser.cc ../token/token.cc ../lexer/lexer.cc ../ast/ast.cc)
target_include_directories(parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
