#include "WAV.h"
#include <fstream>

WAV::WAV(const std::string filename) : filename(filename) {}

std::vector<short int> WAV::parse() {
    std::ifstream file(filename, std::ios::binary);
    if(!file.is_open()) {
        throw std::runtime_error("Unable to open and parse WAV file " + filename);
    }
    header = std::make_unique<wav_header>();
    file.read(reinterpret_cast<char*>(header.get()), sizeof(wav_header));
    std::unique_ptr<char[]> garbage = std::make_unique<char[]>(header->subchunk2_size + 4);
    file.read(garbage.get(), sizeof(char) * (header->subchunk2_size + 4));
    int dataSize;
    file.read(reinterpret_cast<char *>(&dataSize), sizeof(dataSize));
    std::vector<short int> data;
    data.resize(dataSize);
    file.read((char *)data.data(), dataSize);
    return data;
}

void WAV::write(std::vector<short> data, wav_header header) {
    header.subchunk2_id[0] = 'd'; header.subchunk2_id[1] = 'a'; header.subchunk2_id[2] = 't'; header.subchunk2_id[3] = 'a';
    header.subchunk2_size = data.size() * 2;
    std::ofstream file(filename, std::ios::binary);
    file.write((char *)&header, sizeof(header));
    file.write((char *)data.data(), data.size());

}

WAV::~WAV() {}