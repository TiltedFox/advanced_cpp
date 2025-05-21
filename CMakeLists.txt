cmake_minimum_required(VERSION 3.30)
project(cpp_hw)

set(CMAKE_CXX_STANDARD 20)

add_executable(task_1
        "task1/User.cpp"
        "task1/task_1.cpp"
        "task1/User.h"
        "task1/Group.cpp"
        "task1/Group.h"
        "task1/Util.cpp"
        "task1/Util.h")

add_executable(task_2
        "task2/task_2.cpp"
        "task2/TypeList.hpp")

add_executable(task_3
        "task3/TypeMap.hpp"
        "task3/task_3.cpp")

add_executable(task_4
        "task4/task_4.cpp"
        "task4/lcs.hpp"
        "task4/counter.hpp")
add_executable(task_5
        "task5/task_5.cpp"
        "task5/Log.cpp"
        "task5/Log.h")
add_executable(task_6
        "task6/task_6.cpp"
)
add_executable(task_7
        "task7/task_7.cpp"
)
add_executable(task_8
        "task8/task_8.cpp"
)