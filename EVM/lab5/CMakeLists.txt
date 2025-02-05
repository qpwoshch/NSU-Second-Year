cmake_minimum_required(VERSION 3.29)
project(lab5)

set(CMAKE_CXX_STANDARD 17)

set(OpenCV_DIR "C:/Users/User/CLionProjects/evm/lab5/opencv/build")  # Укажите путь до сборки OpenCV, если необходимо

find_package(OpenCV REQUIRED)

add_executable(lab5 main.cpp)

target_link_libraries(lab5 ${OpenCV_LIBS})

include_directories(${OpenCV_INCLUDE_DIRS})
