cmake_minimum_required(VERSION 3.20)
project(lab2 CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenMP REQUIRED)

add_executable(main main.cpp)

add_executable(openmp_prog OpenMP1.cpp OpenMP2.cpp OpenMPWithSchelude.cpp)

if(OpenMP_CXX_FOUND)
    target_link_libraries(openmp_prog PRIVATE OpenMP::OpenMP_CXX)
endif()