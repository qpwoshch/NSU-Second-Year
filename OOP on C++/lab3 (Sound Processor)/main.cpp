#include <iostream>
#include <cstring>
#include <fstream>
#include "ExecutionOfInstruction.h"

int main(int argc,char* argv[]) {
    if (strcmp(argv[1], "-h") == 0) {
        std::ifstream help("helper.txt");
        std::string line;
        while (std::getline(help, line)) {
            std::cout << line << std::endl;
        }
        return 0;
    }
    ExecutionOfInstruction execInstr;
    execInstr.ExecInstruction(argc, argv);
    return 0;
}