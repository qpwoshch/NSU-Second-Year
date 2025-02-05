#include <string>
#include <vector>
#include "Conventer.h"
#ifndef LAB3_MUTECONVENTER_H
#define LAB3_MUTECONVENTER_H


class MuteConverter : public Conventer {
public:
    MuteConverter();
    void process(std::vector<short>& product, int sampleRate, int numChannels, int second) override;
};


#endif //LAB3_MUTECONVENTER_H