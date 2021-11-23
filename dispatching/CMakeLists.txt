cmake_minimum_required(VERSION 3.8)

set(utils ~/devs/tasks/taskz/unit_testing)
include_directories(${utils})
add_library(geo_lib STATIC geo2d.cpp game_object.cpp)

add_executable(main main.cpp)
target_link_libraries(main geo_lib)
