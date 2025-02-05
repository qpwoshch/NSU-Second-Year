cmake_minimum_required(VERSION 3.10)
project(lab2)

set(CMAKE_CXX_STANDARD 17)


find_package(SDL2 REQUIRED)


add_executable(lab2
        main.cpp
        GameController.cpp
        GameModel.cpp
        GameView.cpp
        Field.cpp
)

target_include_directories(lab2 PRIVATE ${SDL2_INCLUDE_DIRS})


target_link_libraries(lab2 PRIVATE ${SDL2_LIBRARIES})

