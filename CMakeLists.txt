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
    src/elements/material.cpp
    
    src/hittables/hittable.cpp
    src/hittables/hittable-list.cpp
    src/hittables/sphere.cpp
    
    src/utils/vec3.cpp
    src/utils/interval.cpp
    src/utils/worldgen.cpp
    src/utils/io.cpp
)

# build executables
add_executable(ray-tracer ${SRC_FILES})

# link openmp
find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(ray-tracer PUBLIC OpenMP::OpenMP_CXX)
endif()

