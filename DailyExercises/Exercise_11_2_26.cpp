#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cctype>

bool checkPunct(const std::string& s) {
    switch (s.back()) {
        case '.':
        case '!':
        case '?':
        case ',':
            return true;
        default:
            return false;
    }
    return false;
}
void lowerWord(std::string& word) {
    for (char& c : word) {
        c = std::tolower(c);
    }
}

int main() {
    std::unordered_map<std::string, int> wordCount;
    std::stringstream sentance {"The cat sat on the mat.\nThe dog saw the cat!"};
    std::string currentLine;
    std::string currentWord;
    while(std::getline(sentance, currentLine)) {
        std::stringstream sent {currentLine};
        while (std::getline(sent, currentWord, ' ')) {
            std::cout << "\nCurrent Word: " << currentWord;
            lowerWord(currentWord);
            if (checkPunct(currentWord)) {
                wordCount[currentWord.substr(0, currentWord.length() - 1)]++;
            }
            else {
                wordCount[currentWord]++;
            }
            
        }
        std::cout << "\n" << currentLine << "\n";
    }
    std::vector<std::pair<std::string, int>> sortVec {wordCount.begin(), wordCount.end()};
    std::sort(sortVec.begin(), sortVec.end(), [](const auto& a, const auto& b) { return a.second > b.second; });
    for (auto index {0}; index < 5; ++index) {
        std::cout << sortVec[index].first << " "<< sortVec[index].second << "\n";
    }
    return 0;
}

/*
Day 1: Word Frequency Counter (~45 min)

Goal: Read text and report the most frequently used words. This practices strings, streams, containers, and sorting with custom comparators.

Requirements

Read lines from standard input until EOF (std::getline).
Normalize each word: lowercase it and strip leading and trailing punctuation, so "Hello," and hello count as the same word.
Count occurrences using std::unordered_map<std::string, int>.
Copy the entries into a std::vector<std::pair<std::string, int>> and sort by count descending, with ties broken alphabetically.
Print the top 5 words in the format word: count.



*/