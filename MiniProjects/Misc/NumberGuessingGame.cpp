#include <iostream>
#include <cstdint>

uint16_t g_state{ 0 };

uint16_t randomNumGenerator() {
    g_state = (g_state * 782839) + 42501;
    std::cout << g_state;
    return g_state;
}


int main() {

    std::cout << "----------Number Generator----------" << std::endl;
    std::cout << "Enter a seed number: ";
    std::cin >> g_state;
    std::cout << "\n---Generating Number---\n";
    uint16_t genedNum {(randomNumGenerator())};
    //return 1;
    genedNum = (genedNum % 100) + 1;
    std::cout << "Enter your guess: ";
    unsigned int guess {};
    std::cin >> guess;

    int numAttempts { 1 };
    while (guess != genedNum) {
        numAttempts++;
        if (guess > genedNum) {
            std::cout << "Guess lower\n";
        }
        else {
            std::cout << "Guess higher\n";
        }
        std::cout << "Enter another guess: ";
        std::cin >> guess;
    }
    std::cout << "Correct! It took you: " << numAttempts << " many attempts to guess!";
    return 0;
}