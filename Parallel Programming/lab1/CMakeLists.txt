cmake_minimum_required(VERSION 3.29)
project(lab1)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab1 main.cpp)
find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})
add_executable(MPIr MPI.cpp)
target_link_libraries(MPIr ${MPI_LIBRARIES})