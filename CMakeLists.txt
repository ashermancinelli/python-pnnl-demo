cmake_minimum_required(VERSION 3.12)

project(ParLeastSquares CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(pybind11)

find_package(Eigen3 3.3 REQUIRED NO_MODULE)

if(NOT TARGET Eigen3::Eigen)
    message(FATAL_ERROR "Did not find Eigen3. You may specify eigen directory with -DEigen3_DIR")
endif()

add_subdirectory(src)