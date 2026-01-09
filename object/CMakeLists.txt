set(CMAKE_CXX_STANDARD 17)
add_library(object STATIC object.cxx)
target_include_directories(object PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
