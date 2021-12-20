cmake_minimum_required(VERSION 3.8)

set(test_lib ~/devs/tasks/taskz/unit_testing)
include_directories(${test_lib})

add_executable(main main.cpp)

