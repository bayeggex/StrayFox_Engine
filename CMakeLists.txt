# needed for CMake to work properly
cmake_minimum_required(VERSION 3.26.1)

# sets the project name
project(BAL_Engine)

# sets include directories
include_directories(src)

# creates an executable
add_executable(${PROJECT_NAME} src/main.c)

# link libraries to executable
target_link_libraries(${PROJECT_NAME} X11)

# adds a subdirectory for finding other CMakeLists.txt files
add_subdirectory(src)