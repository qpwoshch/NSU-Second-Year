#ifndef LAB3_INVERSE_H
#define LAB3_INVERSE_H
#include "Conventer.h"

class Inverse : public Conventer {
public:
    Inverse();
    void process(std::vector<short>& product, int sampleRate, int numChannels, int second) override;
};


#endif //LAB3_INVERSE_H