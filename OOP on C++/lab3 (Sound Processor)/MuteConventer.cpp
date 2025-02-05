#include "MuteConventer.h"

MuteConverter::MuteConverter() {}

void MuteConverter::process(std::vector<short>& product, int sampleRate, int numChannels, int second) {
    size_t start_index = static_cast<size_t>(0);
    size_t end_index = static_cast<size_t>(1 * sampleRate * numChannels);
    std::fill(product.begin() + start_index, product.begin() + end_index, 0);
}