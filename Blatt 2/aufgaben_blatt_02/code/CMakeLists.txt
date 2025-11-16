cmake_minimum_required(VERSION 3.8)
project(ColorSpaces)
# Set CXX standard
set(CMAKE_CXX_STANDARD 11)

# Your application target
file(GLOB source_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "*.cpp")
file(GLOB header_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "*.hpp")
add_executable(ColorSpaces ${source_files} ${header_files})

# Install executable to the bin directory
install(TARGETS ColorSpaces RUNTIME DESTINATION bin)
