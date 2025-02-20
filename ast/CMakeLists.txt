set(CMAKE_CXX_STANDARD 17)
add_library(ast STATIC ast.cc)
target_include_directories(parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
