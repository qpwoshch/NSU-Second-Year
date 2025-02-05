#include <iostream>
#include <fstream>
#include "parser.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Error: no input or output\n";
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open input file " << argv[1] << "\n";
        return 1;
    }

    std::ofstream outputFile(argv[2]);
    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not open output file " << argv[2] << "\n";
        return 1;
    }

    try {
        CSVParser<std::string, int, float> parser(inputFile);
        for (const auto& row : parser) {
            outputFile << std::get<0>(row) << ", " << std::get<1>(row) << ", " << std::get<2>(row) << "\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
