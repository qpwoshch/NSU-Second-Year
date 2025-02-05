#include "factory.h"
#include "MixConventer.h"
#include "MuteConventer.h"
#include "Inverse.h"

std::unique_ptr<Conventer> factory::createConventer(const std::string& action, int secondFile,  std::vector<std::string>& WavFiles) {
    if (action == "mute") {
        return std::make_unique<MuteConverter>();
    }
    else if(action == "mix") {
        return std::make_unique<MixConverter>(WavFiles, secondFile);
    }
    else if(action == "inverse") {
        return std::make_unique<Inverse>();
    }
    return nullptr;
}