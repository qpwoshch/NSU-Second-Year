#include <vector>
#include <string>
#include "ExecutionOfInstruction.h"
#ifndef LAB3_CONVENTER_H
#define LAB3_CONVENTER_H

class Conventer {
public:
    virtual void process(std::vector<short>& product, int sampleRate, int numChannels, int second) = 0;
    virtual ~Conventer() = default;
};




#endif //LAB3_CONVENTER_H