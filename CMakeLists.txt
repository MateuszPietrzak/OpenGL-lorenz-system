cmake_minimum_required(VERSION 3.28)
project(instancing)

set(CMAKE_CXX_STANDARD 17)

find_package(glm REQUIRED)
find_package(glfw3 3.3 REQUIRED)
include_directories("${CMAKE_SOURCE_DIR}/src" "${CMAKE_SOURCE_DIR}/lib")

add_executable(instancing src/main.cpp
        src/glad.c
        src/Graphics.cpp
        src/Graphics.h
        src/GraphicsShader.cpp
        src/GraphicsShader.h
        src/Shader.cpp
        src/Shader.h
        src/ComputeShader.cpp
        src/ComputeShader.h
)

target_link_libraries(instancing PRIVATE glfw)
