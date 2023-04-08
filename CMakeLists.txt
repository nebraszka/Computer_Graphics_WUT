cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_CXX_STANDARD 11)

# Add source files
set(SOURCE_FILES main.cpp)

# Add executable
add_executable(MyProject ${SOURCE_FILES} glad/glad.o)

# Add libraries
target_link_libraries(MyProject glfw dl)