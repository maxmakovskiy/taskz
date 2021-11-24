cmake_minimum_required(VERSION 3.8)

set(THREAD_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(utils ~/devs/tasks/taskz/unit_testing)
include_directories(${utils})

add_executable(main main.cpp)

target_link_libraries(main PRIVATE Threads::Threads)
