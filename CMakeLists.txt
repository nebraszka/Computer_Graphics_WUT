cmake_minimum_required(VERSION 3.10)
project(VirtualCameraMN)

set(CMAKE_CXX_STANDARD 11)

# Add source files
set(SOURCE_FILES main.cpp Shader.hpp)

# Add executable
add_executable(VirtualCameraMN ${SOURCE_FILES} glad/glad.o)

# To make Shader.hpp visible
target_include_directories(VirtualCameraMN PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Add libraries
target_link_libraries(VirtualCameraMN glfw dl m)