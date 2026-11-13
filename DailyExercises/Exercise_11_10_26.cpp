#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <ranges>


struct Car {
    std::string licensePlate {};
    double tickCount;
};


class Garage {
private:
    std::unordered_map<int, Car> m_garage;
    double tickCounter { 0 };
public:
    void enterGarage(std::string& licensePlate, int spotNum) {
        if (m_garage.contains(spotNum)) {
            std::cout << "Spot is taken. Please select a new spot\n";
            return;
        }
        bool carInGarage = std::ranges::any_of(std::views::iota(0,100), [&] (int i) {
            auto it = m_garage.find(i);
            return it != m_garage.end() && it->second.licensePlate == licensePlate;
        });
        if (carInGarage) {
            std::cout << "Care is already in the garage.\n";
            return;
        } else {
            m_garage.insert({spotNum, Car {licensePlate, tickCounter}});
            std::cout << "Car has been parked.\n";
            return;
        }

    }
    void leaveGarage(std::string& licensePlate) {
        /*
        This was suggested by Claude. Deleting the key while in the for loop is dangerous. 

        auto it { m_garage.begin() };
        while (it != m_garage.end() && it->second.licensePlate != licensePlate) ++it;
            if (it == m_garage.end()) {  not in garage  }
            else {  compute fee from it->second  m_garage.erase(it); }
        */


        bool carInGarage = std::ranges::any_of(std::views::iota(0,100), [&] (int i) {
            auto it = m_garage.find(i);
            return it != m_garage.end() && it->second.licensePlate == licensePlate;
        });
        if (!carInGarage) {
            std::cout << "Your car is not in this garage!\n";
            return;
        } else {
            double timeSpent { 0 };
            for (const auto& spot : m_garage) {
                if (spot.second.licensePlate == licensePlate) {
                    timeSpent = tickCounter - spot.second.tickCount;
                    m_garage.erase(spot.first);
                    break;
                }
            }
            std::cout << "Your car is ready. You were parked here for "<< timeSpent << " hours. Your total is: $" << chargeTime(timeSpent) << " dollars\n"; 
            
        }
    }
    void displayParking(bool parking) {
        if (parking) {
            for(auto spot { 0 }; spot < 100; spot++) {
                auto findSpot {m_garage.find(spot)};
                if (findSpot != m_garage.end()) {
                    std::cout << "Spot: " << spot << " -> " << findSpot->second.licensePlate << "\n";
                }
            }
        } else {
            for(auto spot { 0 }; spot < 100; spot++) {
                auto findSpot {m_garage.find(spot)};
                if (findSpot == m_garage.end()) {
                    std::cout << "Spot: " << spot << " -> Available\n";
                }
            }
        }
        
    }
    void incrementTime() {
        tickCounter += .25;
        std::cout << "Time incremented. Tick: " << tickCounter << "\n";
    }
    double chargeTime(double timeSpent) {
        if (timeSpent <= 1) {
            return 5;
        } else if (timeSpent <= 2) {
            return 10;
        } else if (timeSpent <= 4) {
            return 15;
        } else {
            return 20;
        }
    }
    bool isGarageFull() const{
        return std::ranges::all_of(std::views::iota(0,100), 
        [&](int i) {
            return m_garage.contains(i);
        }
        );
    }
    


};

void garageMenu() {
    std::cout << "1. Park a guest vehicle\n2. Retrieve a guest vehicle\n3. Increment time\n4. Show parking\n0. Quit\n";
}
void ignoreLine() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
bool handleInput(int choice) {
    if (std::cin.fail()) // If the previous extraction failed
        {       
            std::cout << "Bad input, try again.\n";
            std::cin.clear(); 
            ignoreLine();
            return false;  
        }
    else if (choice > 4 || choice < 0) {
        std::cout << "Invald choice, try again\n";
        return false;
    }
    return true;
}



int main() {
    Garage myGarage;
    int choice { -1 };
    std::string licensePlate {};
    int spot { 0 };
    int parkChoice { 0 };
    //bool checkGarage { false };
    std::cout << "-----The Garage-----\n\n";
    std::string str {"a"};
    for (auto index {0}; index < 100; index++) {
        myGarage.enterGarage(str, index);
        str.append("a");
    }



    do {
        garageMenu();
        std::cout << "Enter a choice: ";
        std::cin >> choice;
        if(!handleInput(choice)) {
            continue;
        }
        switch (choice) {
            case 1:
                if (myGarage.isGarageFull()) {
                    std::cout << "Garage is full!\n";
                    break;
                }
                std::cout << "Enter license plate: ";
                std::cin >> licensePlate;
                std::cout << "Enter spot to park: ";
                std::cin >> spot;
                if (spot < 0 || spot > 100) {
                    std::cout << "Invalid spot number\n";
                    break;
                }
                myGarage.enterGarage(licensePlate, spot);
                break;
            case 2:
                std::cout << "Enter license plate: ";
                std::cin >> licensePlate;
                myGarage.leaveGarage(licensePlate);
                break;
            case 3:
                myGarage.incrementTime();
                break;
            case 4:
                std::cout << "See available spots (0) or unavailable (1)?\nChoice: ";
                std::cin >> parkChoice;
                if (!handleInput(parkChoice)) {
                    std::cout << "Invalid choice\n";
                    break;
                }
                myGarage.displayParking(parkChoice);
                break;
            case 0:
                break;
            default:
                break;
        }
        
    } while (choice != 0);
    return 0;
}
/*
Day 5: Parking Garage (~45 min)

The scenario: You’re writing the software for a small parking garage. Cars drive in, park, and leave. The attendant needs to know what’s going on at any moment, and the garage charges by the time a car has been parked.

What it should do

Let a car enter, identified by its license plate.
Let a car leave and report how much it owes.
Show which spots are free and which are taken (and by whom).
Tell the attendant whether the garage is full.
Let the attendant look up which spot a given car is in.

Rules

The garage has a fixed number of spots, chosen when it’s created.
A car can’t enter if the garage is full, or if that plate is already inside.
A car that isn’t in the garage can’t leave.
Pricing: the first hour costs a flat rate. Every additional hour (or part of one) costs a smaller rate. Time is advanced by the attendant calling a “tick” or “advance time” operation rather than reading a real clock.
Each operation should let the caller know whether it worked, and for a departure, what the fee was.

Your job

Decide your types, what each one owns, and where each fact lives (remember the single-source-of-truth question from last time).
Decide the signatures, including const, references, and return types.
Write a main() that exercises every rule, including each failure case.

Constraints

Private data members where it makes sense.
Compile with -Wall -Wextra -std=c++17, no warnings.
Include the headers you actually use, and only those.
Nothing beyond what you’ve covered (no lambdas, smart pointers, or templates).

Stretch goals

Handle a “lost ticket” flat fee.
Reserve the lowest-numbered free spot automatically, versus letting the attendant pick.
*/

/*
std::string myStr{ "Hello" };
    auto myLambda = [myStr] (std::string str) {
        std::cout << myStr << " " << str << "\n"; 
    };
    std::string input;
    std::cout << "Enter a string: ";
    std::cin >> input;
    myLambda(input);
*/