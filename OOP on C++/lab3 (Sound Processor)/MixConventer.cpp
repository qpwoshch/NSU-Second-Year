#include "MixConventer.h"
#include "WAV.h"

MixConverter::MixConverter(std::vector<std::string>& WavFiles, int secondFile)
        : Vector(WavFiles), File(secondFile){}

void MixConverter::process(std::vector<short>& product, int sampleRate, int numChannels, int second) {
    std::string NameOfSecondFile = Vector[File-1];
    WAV Wav(NameOfSecondFile);
    std::vector<short> secondProduct = Wav.parse();
    if (secondProduct.size() > second * sampleRate * numChannels) {
        size_t start_index = static_cast<size_t>(second * sampleRate * numChannels);
        for (size_t i = 0; i < 1 * sampleRate * numChannels; ++i) {
            product[i] = (product[i] + secondProduct[start_index + i]) / 2;
        }
    }
}