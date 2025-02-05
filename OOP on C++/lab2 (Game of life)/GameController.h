#ifndef LAB2_GAMECONTROLLER_H
#define LAB2_GAMECONTROLLER_H

#include <string>
#include "GameView.h"
#include "GameModel.h"
#include "Field.h"

class GameController {
private:
    std::string help = "Вот команды, которые вы можете использовать:\n"
                       "1)dump <filename> - сохранить вселенную в файл\n"
                       "2)tick <n=1> (и сокращено t <n=1>  - рассчитать n (по умолчанию 1) итераций и напечатать результат. На экране перед распечатанным полем должно отображаться имя вселенной, правило перехода и номер текущей итерации.\n"
                       "3)exit - завершить игру\n"
                       "4)help - распечатать справку о командах";
    GameView view;
    GameModel model;
    int ModeOptionNumber(int argc);
    const std::string NameOfFile(char* argv[], int ModeOptionNumber) const;
public:
    GameController();
    int start(int argc, char* argv[]);
    void Console();
};

#endif
