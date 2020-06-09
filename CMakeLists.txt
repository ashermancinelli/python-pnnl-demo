cmake_minimum_required(VERSION 3.12)

project(ParLeastSquares CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(pybind11)

pybind11_add_module(linear_algebra src/linear_algebra.cpp)
target_include_directories(linear_algebra PRIVATE ${PROJECT_SOURCE_DIR}/eigen)
