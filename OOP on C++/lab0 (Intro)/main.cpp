#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>

void map_insert(double &sizeOfInput, std::string &data, std::map<std::string, int> &words) {
    if (!data.empty()) {
        sizeOfInput++;
        auto it = words.find(data);
        if (it != words.end()) {
            it->second++;
        } else {
            words.insert({data, 1});
        }
        data.clear();
    }
}

int main() {
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    std::ifstream in("input.txt");
    if (!in) {
        std::cerr << "Не удалось открыть input" << std::endl;
        return -1;
    }
    std::string dataInput;
    std::string data;
    double sizeOfInput = 0;
    std::map<std::string, int> words;
    std::map<std::string, int>::iterator it;
    while (std::getline(in, dataInput, ' ')) {
        for (int i = 0; i < dataInput.size(); i++) {
            if ((dataInput[i] <= 'z' && dataInput[i] >= 'a') || (dataInput[i] >= 'A' && dataInput[i] <= 'Z') ||
                (dataInput[i] >= '0' && dataInput[i] <= '9')) {
                data.push_back(dataInput[i]);
            } else {
                map_insert(sizeOfInput, data, words);
            }
        }
        map_insert(sizeOfInput, data, words);
    }
    std::list<std::list<std::pair<int, std::string>>> biglist;
    std::list<std::list<std::pair<int, std::string>>>::reverse_iterator its;
    std::list<std::pair<int, std::string>> smalllist;
    for (it = words.begin(); it != words.end(); it++) {
        smalllist.clear();
        smalllist.emplace_front(it->second, it->first);
        biglist.push_back(smalllist);
    }
    biglist.sort([](const std::list<std::pair<int, std::string>>& a, const std::list<std::pair<int, std::string>>& b) {
        return a.front().first < b.front().first;
    });
    std::ofstream out("output.csv");
    if (!out) {
        std::cerr << "Не удалось открыть output" << std::endl;
        return -1;
    }
    double percent;
    out << "word" << ";count" << ";%" << std::endl;
    for (its = biglist.rbegin(); its != biglist.rend(); ++its) {
        for (auto small_it = its->begin(); small_it != its->end(); ++small_it) {
            percent = (double) small_it->first / (sizeOfInput / 100);
            out << small_it->second << ";" << small_it->first << ";" << percent << "%" << std::endl;
        }
    }
    return 0;
}