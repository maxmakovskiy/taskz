cmake_minimum_required(VERSION 3.8)

add_library(lib STATIC date.cpp db.cpp query.cpp)

add_executable(main main.cpp)

target_link_libraries(main lib)
