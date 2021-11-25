cmake_minimum_required(VERSION 3.8)

set(THREAD_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(test_utils ~/devs/tasks/taskz/unit_testing)
set(profiler_utils ~/devs/tasks/taskz/profiler)
include_directories(${test_utils})
include_directories(${profiler_utils})

add_executable(main main.cpp)
target_link_libraries(main PRIVATE Threads::Threads)
