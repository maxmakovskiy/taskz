cmake_minimum_required(VERSION 3.8)

set(utils ~/devs/tasks/taskz/unit_testing)
include_directories(${utils})

add_executable(main main.cpp ini.cpp)

