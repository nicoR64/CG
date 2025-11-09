cmake_minimum_required(VERSION 3.14)
project(task_2)

add_executable(task_2)

target_sources(task_2
    PRIVATE
        code/01_stl.cpp
        code/LineStrip3D.cpp
)