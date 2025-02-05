#include "GameModel.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>





void GameModel::loadFromFile(const std::string& file, Field& field, std::string& NameOfUniverse) {
    std::ifstream input(file);
    if (!input.is_open()) {
        throw std::runtime_error("Не удалось открыть файл \" " + file + "\"");
    }
    std::string line;
    std::getline(input, NameOfUniverse);
    std::getline(input, rules);
    std::getline(input, line);
    std::stringstream ss1(line);
    int columnOfMatrix, rowsOfMatrix;
    ss1 >> columnOfMatrix >> rowsOfMatrix;
    if (ss1.fail()) {
        std::cerr <<"Ошибка в чтении размера вселенной" << std::endl;
    }
    field.setSize({static_cast<size_t>(columnOfMatrix), static_cast<size_t>(rowsOfMatrix)});
    int x, y;
    while (std::getline(input, line)) {
        std::stringstream ss2(line);
        ss2 >> x >> y;
        if (ss2.fail()) {
            std::cerr << "Ошибка в чтении координат живых точек" << std::endl;
        }
        field.setCell({x % columnOfMatrix, y % rowsOfMatrix}, Cell::Alive);
    }
}



void GameModel::transformationmatrix(std::string rules, Field& field, std::string& NameOfUniverse) {
    std::vector<int> Survival;
    std::vector<int> Birth;
    int indexStart = rules.find("B");
    int indexEnd = rules.find("/");
    indexStart++;
    while (indexStart < indexEnd) {
        if (std::isdigit(rules[indexStart])) {
            int value = rules[indexStart] - '0';
            Birth.push_back(value);
        }
        indexStart++;
    }
    indexStart = rules.find("S");
    while (indexStart != std::string::npos) {
        indexStart++;
        while (indexStart < rules.size() && std::isdigit(rules[indexStart])) {
            int value = rules[indexStart] - '0';
            Survival.push_back(value);
            indexStart++;
        }
    }
    int directions[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    Field newField = field;
    for (int rows = 0; rows < field.getSize().height; rows++) {
        for (int column = 0; column < field.getSize().width; column++) {
            int live_neighbors = 0;
            for (auto& direction : directions) {
                int new_rows = rows + direction[0];
                int new_column = column + direction[1];
                if (new_rows >= 0 && new_rows < field.getSize().width && new_column >= 0 && new_column < field.getSize().height && field.getCell({new_rows, new_column}) == Cell::Alive) {
                    ++live_neighbors;
                }
            }
            if (field.getCell({rows, column}) == Cell::Alive) {
                newField.setCell({rows, column}, Cell::Dead);
                for (auto x : Survival) {
                    if (live_neighbors == x) {
                        newField.setCell({rows, column}, Cell::Alive);
                    }
                }
            }
            else {
                for (auto x : Birth) {
                    if (live_neighbors == x) {
                        newField.setCell({rows, column}, Cell::Alive);
                    }
                }

            }
        }
    }
    field = newField;
}

void GameModel::loadToFile(const std::string &file, Field& field, std::string& NameOfUniverse) {
    std::ofstream output(file);
    if (!output.is_open()) {
        throw std::runtime_error("Не удалось открыть файл \" " + file + "\"");
    }
    output << NameOfUniverse << std::endl << rules << std::endl << field.getSize().width << " " << field.getSize().height << std::endl;
    for (int column = 0; column < field.getSize().height; column++) {
        for (int rows = 0; rows < field.getSize().width; rows++) {
            if (field.getCell({rows, column}) == Cell::Alive) {
                output << column << " " << rows << std::endl;
            }
        }
    }
}

bool GameModel::offlineVersion(int modeNumber, char* argv[], Field& field, std::string& NameOfUniverse) {
    if (modeNumber != 3) {
        return false;
    }
    std::string command = static_cast<std::string>(argv[2]);
    std::string Iteration = static_cast<std::string>(argv[3]);
    int checkPositionInCMD = 4;
    if(command.rfind("--iteration=", 0) == 0) {
        Iteration = command.substr(12);
        checkPositionInCMD = 3;
    }
    else if(command != "-i") {
        std::cerr<<"Ошибка, введите -i N или --iteration=N, где N - количество нужных итераций"<<std::endl;
        return true;
    }
    transformationmatrix(rules, field, NameOfUniverse);
    command = static_cast<std::string>(argv[checkPositionInCMD]);
    if (command != "-o") {
        std::cerr<<"Ошибка, введите -o output.txt, где ouput.txt - файл для вывода"<<std::endl;
        return true;
    }
    command = static_cast<std::string>(argv[checkPositionInCMD+1]);
    loadToFile(command, field, NameOfUniverse);
    return true;
}

std::string GameModel::getRules() {
    return rules;
}

Field& GameModel::getField() {
    return field;
}

