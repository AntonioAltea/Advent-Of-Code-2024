#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <map>
#include <regex>

namespace patterns {
    const std::string DO_PATTERN_STR{R"(do\(\))"};
    const std::string DONT_PATTERN_STR{R"(don\'t\(\))"};
    const std::string MUL_PATTERN_STR{R"(mul\((\d+),(\d+)\))"};
    const std::string COMBINED_PATTERN_STR{DO_PATTERN_STR + "|" + DONT_PATTERN_STR + "|" + MUL_PATTERN_STR};
}

void processInstructions(const std::sregex_iterator &it, bool &processMul, int &totalValue) {
    const auto &match{*it};
    auto instruction{match.str()};

    if (std::regex_match(instruction, std::regex(patterns::DO_PATTERN_STR))) {
        processMul = true;
    } else if (std::regex_match(instruction, std::regex(patterns::DONT_PATTERN_STR))) {
        processMul = false;
    } else if (std::regex_match(instruction, std::regex(patterns::MUL_PATTERN_STR)) && processMul) {
        auto num1{std::stoi(match[1].str())};
        auto num2{std::stoi(match[2].str())};

        totalValue += num1 * num2;
    }
}

int processInput(std::ifstream &inputFile) {
    std::string line;
    std::regex instruction_pattern{patterns::COMBINED_PATTERN_STR};

    int totalValue{0};
    bool processMul{true};
    while (std::getline(inputFile, line)) {
        // for each line tries to match the regex
        auto matches_begin{std::sregex_iterator(
                                                line.begin(),
                                                line.end(),
                                                instruction_pattern)};
        auto matches_end{std::sregex_iterator()};

        for (auto it{matches_begin}; it != matches_end; ++it) {
            processInstructions(it, processMul, totalValue);
        }
    }

    return totalValue;
}

int main() {
    std::cout << "Advent of Code 2024 - Day 3" << std::endl;
    std::ifstream inputFile("input3.txt"); // Open the file
    if (!inputFile) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return 1;
    }

    auto totalValue{processInput(inputFile)};
    std::cout << "Total value: " << totalValue << std::endl;

    inputFile.close();
    return 0;
}