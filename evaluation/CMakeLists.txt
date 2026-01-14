set(CMAKE_CXX_STANDARD 17)
add_library(evaluation STATIC evaluation.cc ../object/object.cxx ../token/token.cc ../lexer/lexer.cc ../ast/ast.cc ../parser/parser.cc)
target_include_directories(evaluation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
