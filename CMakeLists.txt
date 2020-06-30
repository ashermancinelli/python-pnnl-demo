cmake_minimum_required(VERSION 3.12)

project(ParLeastSquares CUDA CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CUDA_SEPERABLE_COMPILATION ON)
add_subdirectory(pybind11)

find_package(OpenMP)

add_library(dummycu STATIC src/add_vec.cu)
set_target_properties(dummycu PROPERTIES 
    POSITION_INDEPENDENT_CODE ON
    CUDA_VISIBILITY_PRESET "hidden"
    # CUDA_SEPARABLE_COMPILATION ON
)

pybind11_add_module(linear_algebra src/linear_algebra.cpp)
set_target_properties(linear_algebra PROPERTIES 
    CXX_VISIBILITY_PRESET "hidden"
    INTERPROCEDURAL_OPTIMIZATION TRUE
    PREFIX "${PYTHON_MODULE_PREFIX}"
    SUFFIX "${PYTHON_MODULE_EXTENSION}"
    )
target_link_libraries(linear_algebra PUBLIC dummycu)

target_include_directories(linear_algebra PRIVATE ${PROJECT_SOURCE_DIR}/eigen)
if(OpenMP_CXX_FOUND)
  target_link_libraries(linear_algebra PUBLIC OpenMP::OpenMP_CXX)
else()
  message(FATAL_ERROR "Could not find openmp")
endif()
