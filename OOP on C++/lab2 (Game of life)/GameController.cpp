#include "GameController.h"
#include <string>
#include <iostream>
#include <sstream>

GameController::GameController()
        : view(), model() {}

int GameController::start(int argc, char* argv[]) {
    int modeNumber = ModeOptionNumber(argc);
    const std::string filename = NameOfFile(argv, modeNumber);
    model.loadFromFile(filename,model.getField() , model.NameOfUniverse);
    if (model.offlineVersion(modeNumber, argv, model.getField(), model.NameOfUniverse) == true) {
        return 0;
    }
    return 1;
}

int GameController::ModeOptionNumber(int argc) {
    if (argc > 2) {
        return 3;
    } else if (argc > 1) {
        return 1;
    }
    return 2;
}

const std::string GameController::NameOfFile(char* argv[], int ModeOptionNumber) const {
    if (ModeOptionNumber == 1 || ModeOptionNumber == 3) {
        return argv[1];
    }
    return "defaultUniverse.txt";
}

void GameController::Console() {
    std::cout << "Привет, это игра в жизнь. Чтобы ознакомиться с коммандами, напишите \"help\"" << std::endl;
    std::string command;
    while (command != "exit") {
        std::getline(std::cin, command);
        if (command == "help") {
            std::cout << help << std::endl;
        }
        else if (command.rfind("tick", 0) == 0 || command.rfind("t", 0) == 0) {
            int iterations = 1;
            std::istringstream ss(command);
            std::string word;
            ss >> word >> iterations;
            view.displayimage(model.getField(), model.NameOfUniverse);
            for (int i = 0; i < iterations; i++) {
                model.transformationmatrix(model.getRules(), model.getField(), model.NameOfUniverse);
                view.displayimage(model.getField(), model.NameOfUniverse);
            }
        }
        else if (command.rfind("dump", 0) == 0) {
            std::string word;
            std::string filename;
            std::istringstream ss(command);
            ss >> word >> filename;
            model.loadToFile(filename, model.getField(), model.NameOfUniverse);
        }
        else if (command == "exit") {
            std::cout << "Завершение программы" << std::endl;
        }
        else {
            std::cout << "Я не понимаю этой команды, напишите help, для того, чтобы ознакомиться с документацией"
                      << std::endl;
        }
    }
}
