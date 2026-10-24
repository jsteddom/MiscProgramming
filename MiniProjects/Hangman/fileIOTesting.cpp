#include <iostream>
#include <sstream>
#include <fstream>

int main()
{
    /*
    std::ifstream fileOp("output.txt");
    std::string hi;
    fileOp >> hi;
    std::cout << hi; 
    */
    std::ifstream file("inventory.csv");
    std::string itemName;
    std::string id;
    std::string price;
    std::string quantity;
    std::string line;
    //std::getline(file, itemName, ',');
    //std::getline(file, id, ',');
    //std::getline(file, price, ',');
    //std::getline(file, quantity, ',');

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::getline(ss, itemName, ',');
        std::getline(ss, id, ',');
        std::getline(ss, price, ',');
        std::getline(ss, quantity, ',');
        std::cout << itemName << id << price << quantity;
    }

   

    return 0;
}