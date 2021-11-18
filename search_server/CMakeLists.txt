cmake_minimum_required(VERSION 3.8)

add_library(search_lib STATIC search_server.cpp)

add_executable(main main.cpp)

target_link_libraries(main search_lib)
