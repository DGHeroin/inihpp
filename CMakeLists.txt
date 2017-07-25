cmake_minimum_required(VERSION 2.8)

project(inihpp)
add_executable(${PROJECT_NAME} "main.cpp")

set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g")
