#ifndef LAB2_GAMEMODEL_H
#define LAB2_GAMEMODEL_H
#include <vector>
#include <string>
#include "GameView.h"
#include "Field.h"

class GameModel{
private:
    std::string rules;
    Field field;
public:
    Field& getField();
    std::string NameOfUniverse;
    std::string getRules();
    bool offlineVersion(int modeNumber, char* argv[], Field& field, std::string& NameOfUniverse);
    void loadFromFile(const std::string& file, Field& field, std::string& NameOfUniverse);
    void transformationmatrix(std::string rules, Field& field, std::string& NameOfUniverse);
    void loadToFile(const std::string &file, Field& field, std::string& NameOfUniverse);
};


#endif
