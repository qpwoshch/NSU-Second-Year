cmake_minimum_required(VERSION 3.15)
project(matrix_multiplication_comparison)


set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -march=native")


add_executable(BLAS BLAS.c)
add_executable(default default.c)
add_executable(vectorized vectorized.c)


target_link_libraries(BLAS m /lib/x86_64-linux-gnu/libopenblas.so)
target_link_libraries(default m /lib/x86_64-linux-gnu/libopenblas.so)
target_link_libraries(vectorized m /lib/x86_64-linux-gnu/libopenblas.so)
