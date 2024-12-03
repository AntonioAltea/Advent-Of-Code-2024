#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include <map>
#include <algorithm>


std::vector<std::vector<int>> parseInputFile(const std::string &filename) {
    std::vector<std::vector<int>> reports{};
    std::ifstream file(filename);

    if (!file.is_open()) {
        return {};
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<int> report{};
        int num;
        std::istringstream ss{line};

        while (ss >> num) {
            report.push_back(num);
        }

        reports.push_back(report);
    }

    file.close();
    return reports;
}


bool isReportSafe(const std::vector<int> &report) {
    //list of differences
    std::vector<int> differences{};
    for (int i = 0; i < std::size(report) - 1; i++) {
        differences.push_back(report[i] - report[i + 1]);
    }

    int firstSign = (differences[0] > 0) - (differences[0] < 0);
    return std::ranges::all_of(differences, [firstSign](int num) {
        bool signIsSafe = ((num > 0) - (num < 0)) == firstSign;
        bool differenceSizeIsSafe = (std::abs(num) < 4);
        bool notZero = num != 0;

        return signIsSafe && differenceSizeIsSafe && notZero;
    });
}


int getNumberOfSafeReports(const std::vector<std::vector<int>> &reports) {
    int numberOfSafeReports{0};

    for (const auto &report: reports) {
        if (isReportSafe(report)) {
            numberOfSafeReports++;
            std::cout << "safe" << std::endl;
        } else {

            std::cout << "unsafe" << std::endl;
        }
    }

    return numberOfSafeReports;
}

int main() {
    std::cout << "Advent of Code 2024 - Day 2" << std::endl;

    auto vectors = parseInputFile("input2.txt");
    if (vectors.empty()) {
        std::cout << "No lists recorded. Please check the input file." << std::endl;
        return 0;
    }

    int numberOfSafeReports = getNumberOfSafeReports(vectors);
    std::cout << "Number of safe Reports: " << numberOfSafeReports << std::endl;

    return 0;
}