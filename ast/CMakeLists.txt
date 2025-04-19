set(CMAKE_CXX_STANDARD 17)
add_library(ast STATIC ast.cc ../token/token.cc ../lexer/lexer.cc ../parser/parser.cc)
target_include_directories(ast PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
