cmake_minimum_required(VERSION 3.14)
project(task_3)

add_executable(task_3)

target_sources(task_3
    PRIVATE
        code/01_raii.cpp
        code/MatrixInt.cpp
)