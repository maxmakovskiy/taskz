cmake_minimum_required(VERSION 3.8)

add_library(lib STATIC query.cpp responses.cpp bus_manager.cpp)

add_executable(main main.cpp)

target_link_libraries(main lib)
