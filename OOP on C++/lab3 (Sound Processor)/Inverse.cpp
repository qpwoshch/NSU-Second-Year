#include "Inverse.h"

Inverse::Inverse() {}

void Inverse::process(std::vector<short>& product, int sampleRate, int numChannels, int second) {
    size_t start_index = static_cast<size_t>(0 * sampleRate * numChannels);
    size_t end_index = static_cast<size_t>(1 * sampleRate * numChannels);
    std::vector<short> copy = product;
    for (size_t i = start_index; i < end_index; ++i) {
        copy[i] = product[end_index - (i - start_index)];
    }
    for (size_t i = start_index; i < end_index; ++i) {
        product[i] = copy[i];
    }
}