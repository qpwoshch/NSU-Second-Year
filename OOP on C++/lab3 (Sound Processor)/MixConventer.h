#ifndef LAB3_MIXCONVENTER_H
#define LAB3_MIXCONVENTER_H
#include "ExecutionOfInstruction.h"
#include "Conventer.h"

class MixConverter : public Conventer {
private:
    std::vector<std::string> Vector;
    int File;

public:
    MixConverter(std::vector<std::string>& WavFiles, int secondFile);
    void process(std::vector<short>& product, int sampleRate, int numChannels, int second) override;
};


#endif //LAB3_MIXCONVENTER_H