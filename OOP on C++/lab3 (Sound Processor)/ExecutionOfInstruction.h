#ifndef LAB3_EXECUTIONOFINSTRUCTION_H
#define LAB3_EXECUTIONOFINSTRUCTION_H
#include <vector>
#include <string>


class ExecutionOfInstruction {
public:
    void ExecInstruction(int argc, char *argv[]);
private:
    std::string config;
    std::string input;
    std::string output;
};

#endif //LAB3_EXECUTIONOFINSTRUCTION_H