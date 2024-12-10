cmake_minimum_required(VERSION 3.20.0)
project(RayTracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(src)

set(SRC_FILES
    src/main.cpp
    src/camera/camera.cpp
    src/elements/color.cpp
    src/elements/ray.cpp
    src/hittables/sphere.cpp
    src/hittables/hittable-list.cpp
    src/utils/vec3.cpp
    src/utils/interval.cpp
)

# build executables
add_executable(ray-tracer ${SRC_FILES})

