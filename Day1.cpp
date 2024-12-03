#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <tuple>
#include <string>
#include <filesystem>
#include <map>

std::tuple<std::vector<int>, std::vector<int>> parseInputFile(const std::string &filename);

int distanceBetweenVectors(std::vector<int> v1, std::vector<int> v2);

int similarityScore(const std::vector<int> &v1, std::vector<int> v2);

int main() {

    auto [v1, v2] = parseInputFile("input1.txt");
    //std::vector<int> v1 = {3, 4, 2, 1, 3, 3};
    //std::vector<int> v2 = {4, 3, 5, 3, 9, 3};

    if (v1.empty() || v2.empty()) {
        std::cout << "One of both of the lists are empty. Please check the input file." << std::endl;
        return 0;
    }

    auto totalDistance = distanceBetweenVectors(v1, v2);
    std::cout << "Total distance between lists: " << totalDistance << std::endl;

    auto simScore = similarityScore(v1, v2);
    std::cout << "SimilarityScore: " << simScore << std::endl;
    return 0;
}


std::tuple<std::vector<int>, std::vector<int>> parseInputFile(const std::string &filename) {
    std::vector<int> v1, v2;
    std::ifstream file(filename);


    if (!file.is_open()) {
        return {v1, v2};
    }

    std::string line;
    while (std::getline(file, line)) {
        int col1, col2;
        std::istringstream ss{line};

        ss >> col1 >> col2;

        v1.push_back(col1);
        v2.push_back(col2);
    }

    file.close();
    return {v1, v2};
}

int distanceBetweenVectors(std::vector<int> v1, std::vector<int> v2) {
    auto totalDistance{0};
    while (!v1.empty() && !v2.empty()) {
        auto minIt1 = std::min_element(v1.begin(), v1.end());
        auto minIt2 = std::min_element(v2.begin(), v2.end());
        auto min1 = *minIt1;
        auto min2 = *minIt2;

        totalDistance += std::abs(min1 - min2);

        v1.erase(minIt1);
        v2.erase(minIt2);
    }

    return totalDistance;
}

int similarityScore(const std::vector<int> &v1, std::vector<int> v2) {
    auto totalScore{0};
    std::map<int, int> scoreValueMap;

    for (auto num: v1) {
        if (scoreValueMap.find(num) != scoreValueMap.end()) {
            totalScore += scoreValueMap[num] * num;
        } else {
            auto numFrequency = std::count(v2.begin(), v2.end(), num);
            auto scoreValue = numFrequency * num;
            totalScore += scoreValue;
            scoreValueMap[num] = scoreValue;
        }
    }

    return totalScore;
}
