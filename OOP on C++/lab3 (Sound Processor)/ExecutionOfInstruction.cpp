#include <iostream>
#include "factory.h"
#include "ExecutionOfInstruction.h"
#include "WAV.h"
#include <fstream>
#include <vector>



void ExecutionOfInstruction::ExecInstruction(int argc, char **argv) {
    std::vector<std::string> WavFiles;
    config = argv[2];
    output = argv[3];
    input = argv[4];
    WavFiles.push_back(input);
    int aargv = 5;
    while (aargv != argc) {
        std::string wav = argv[aargv];
        WavFiles.push_back(wav);
        aargv++;
    }
    std::fstream file(config);
    std::string line;
    WAV wav(input);
    std::vector<short int> product = wav.parse();
    int sampleRate = wav.header->sample_rate;
    int numChannels = wav.header->num_channels;
    while (std::getline(file, line)) {
        std::vector<int> helpInformation;
        std::string command;
        std::string time;
        int first_value = 0;
        int second_value = 0;
        if (line[0] == '#') {
            continue;
        }
        else if (line.find("mute") == 0) {
            command = line.substr(0, 4);
            time = line.substr(5);
            helpInformation.push_back(0);
            std::istringstream timestr(time);
            timestr >> first_value >> second_value;
            helpInformation.push_back(first_value);
            helpInformation.push_back(second_value);
        }
        else if (line.find("mix") == 0) {
            std::string NameOfSecondFile;
            command = line.substr(0, 3);
            time = line.substr(4);
            std::istringstream timestr(time);
            timestr >> NameOfSecondFile >> second_value;
            NameOfSecondFile = NameOfSecondFile.substr(1);
            first_value = std::stoi(NameOfSecondFile);
            helpInformation.push_back(first_value);
            helpInformation.push_back(second_value);
            helpInformation.push_back(product.size() / sampleRate / numChannels / 2);
        }
        else if (line.find("inverse") == 0) {
            command = line.substr(0, 7);
            time = line.substr(8);
            helpInformation.push_back(0);
            std::istringstream timestr(time);
            timestr >> first_value >> second_value;
            helpInformation.push_back(first_value);
            helpInformation.push_back(second_value);
        }
        else {
            throw::std::logic_error("Первым параметром в конфигурации передается не команда(mute, mix или inverse");
        }
        std::unique_ptr<Conventer> conventer = factory::createConventer(command, helpInformation[0], WavFiles);

        for (int j = helpInformation[1]; j < helpInformation[2]; j++) {
            std::vector<short int> product2;
            int size = 1 * numChannels * sampleRate;
            product2.resize(size);
            for (int i = j * sampleRate * numChannels;
                 i < (j + 1) * sampleRate * numChannels; i++) {
                product2[i - j * sampleRate * numChannels] = product[i];
            }
            conventer->process(product2, sampleRate, numChannels, j);
            for (int i = j * sampleRate * numChannels; i < (j + 1) * sampleRate * numChannels; i++) {
                product[i] = product2[i - j * sampleRate * numChannels];
            }
        }
    }
    WAV wavWrite(output);
    wavWrite.write(product, *wav.header);
}