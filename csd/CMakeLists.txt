cmake_minimum_required(VERSION 4.0)
project(csd)

set(CMAKE_CXX_STANDARD 20)

find_package(LAPACK REQUIRED)
find_package(BLAS REQUIRED)
add_executable(csd main.cpp
        csd.cpp
        csd.h)
target_link_libraries(csd -llapacke)



