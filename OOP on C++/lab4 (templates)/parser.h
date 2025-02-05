#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>
#include <stdexcept>
#include <iterator>

template<typename... ColumnTypes>
class CSVParser {
public:
    explicit CSVParser(std::istream& input, size_t skipLines = 0, char delimiter = ';', char text = '"')
            : input(input), delimiter(delimiter), text(text) {
        skipInitialLines(skipLines);
    }

    class Iterator {
    public:
        using value_type = std::tuple<ColumnTypes...>;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;
        using iterator_category = std::input_iterator_tag;

        Iterator(std::istream* input, char delimiter, char text, bool end = false)
                : input(input), delimiter(delimiter), text(text), end(end) {
            if (!end) {
                ++(*this);
            }
        }

        value_type operator*() const {
            return current;
        }

        Iterator& operator++() {
            if (!input || !std::getline(*input, line)) {
                end = true;
                return *this;
            }

            try {
                current = parseLine<ColumnTypes...>(line, delimiter, text);
            } catch (const std::exception& e) {
                throw std::runtime_error("Error parsing line: " + line + "\n" + e.what());
            }

            return *this;
        }

        bool operator==(const Iterator& other) const {
            return end == other.end;
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }

    private:
        std::istream* input;
        std::string line;
        value_type current;
        char delimiter;
        char text;
        bool end = false;
        
        template<typename T>
        static T convert(const std::string& token) {
            std::istringstream iss(token);
            T value;
            if (!(iss >> value)) {
                throw std::runtime_error("Failed to convert token: " + token);
            }
            return value;
        }

        static std::string convert(const std::string& token) {
            return token;
        }

        template<typename... Types, size_t... Indices>
        static std::tuple<Types...> parseLineImpl(const std::string& line, char delimiter, char text,
                                                  std::index_sequence<Indices...>) {
            std::vector<std::string> tokens = split(line, delimiter, text);
            if (tokens.size() != sizeof...(Types)) {
                throw std::runtime_error("Column count mismatch: expected " +
                                         std::to_string(sizeof...(Types)) + ", got " +
                                         std::to_string(tokens.size()));
            }
            return std::make_tuple(convert<Types>(tokens[Indices])...);
        }

        template<typename... Types>
        static std::tuple<Types...> parseLine(const std::string& line, char delimiter, char text) {
            return parseLineImpl<Types...>(line, delimiter, text, std::index_sequence_for<Types...>{});
        }

        static std::vector<std::string> split(const std::string& line, char delimiter, char text) {
            std::vector<std::string> tokens;
            std::string token;
            bool inText = false;

            for (char c : line) {
                if (c == text) {
                    inText = !inText;
                } else if (c == delimiter && !inText) {
                    tokens.push_back(token);
                    token.clear();
                } else {
                    token += c;
                }
            }
            tokens.push_back(token);
            return tokens;
        }
    };

    Iterator begin() {
        return Iterator(&input, delimiter, text);
    }

    Iterator end() {
        return Iterator(nullptr, delimiter, text, true);
    }

private:
    std::istream& input;
    char delimiter;
    char text;

    void skipInitialLines(size_t skipLines) {
        std::string temp;
        for (size_t i = 0; i < skipLines; ++i) {
            std::getline(input, temp);
        }
    }
};

#endif // PARSER_H
