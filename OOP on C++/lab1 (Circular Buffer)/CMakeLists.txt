
cmake_minimum_required(VERSION 3.29)
project(lab1)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(googletest)


add_executable(lab1
        main.cpp
        CircularBuffer.cpp
        CircularBuffer.h
        test_cb.cpp
)


target_link_libraries(lab1 gtest gtest_main)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")