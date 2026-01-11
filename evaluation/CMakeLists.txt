set(CMAKE_CXX_STANDARD 17)
add_library(evaluation STATIC evaluation.cc)
target_include_directories(evaluation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
