#include <iostream>
#include "GameController.h"

int main(int argc, char* argv[]) {
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    GameController controller;
    if (controller.start(argc, argv) == 0) {
        return 0;
    }
    controller.Console();
    return 0;
}
