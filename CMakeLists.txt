cmake_minimum_required(VERSION 3.12)

project(ParLeastSquares CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(pybind11)

find_package(Eigen3 3.3 REQUIRED NO_MODULE)

pybind11_add_module(linear_algebra src/linear_algebra.cpp)
target_link_libraries(linear_algebra PRIVATE Eigen3::Eigen)
