cmake_minimum_required(VERSION 3.17)
project(rsp)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME}
    Source/Platform.hpp
    Source/rsp.hpp
    Source/rsp.cpp
)