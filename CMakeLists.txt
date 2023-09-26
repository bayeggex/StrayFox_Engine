# needed for CMake to work properly
cmake_minimum_required(VERSION 3.26.1)

# sets the project name
project(BAL_Engine)

# sets include directories
include_directories(src)

# creates an executable
add_executable(${PROJECT_NAME} src/main.c)

# adds a subdirectory for finding other CMakeLists.txt files
add_subdirectory(src)