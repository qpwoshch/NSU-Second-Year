
#ifndef LAB3_FACTORY_H
#define LAB3_FACTORY_H
#include <memory>
#include <string>
#include <sstream>
#include "Conventer.h"

class factory {
public:
    static std::unique_ptr<Conventer> createConventer(const std::string& action, int secondFile, std::vector<std::string>& WavFiles);
};


#endif //LAB3_FACTORY_H