cmake_minimum_required(VERSION 3.14)
project(task_4)

add_executable(task_4)

target_sources(task_4
    PRIVATE
        code/01_functions.cpp
        code/Definition.cpp
	code/source1.cpp
	code/source2.cpp
)