cmake_minimum_required(VERSION 3.20.0)
project(RayTracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(src)

set(SRC_FILES
    src/main.cpp
)

# build executables
add_executable(ray-tracer ${SRC_FILES})

