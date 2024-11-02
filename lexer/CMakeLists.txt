set(CMAKE_CXX_STANDARD 17)
add_library(lexer STATIC lexer.cc ../token/token.cc)
target_include_directories(lexer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
