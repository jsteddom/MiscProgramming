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
    if (!file.is_open())
    {
        std::cout << "Failed to open file\n";
        return 1;
    }
    std::cout << "File opened successfully\n";
    std::string itemName;
    std::string id;
    std::string price;
    std::string quantity;
    std::string line;
    //std::getline(file, itemName, ',');
    //std::getline(file, id, ',');
    //std::getline(file, price, ',');
    //std::getline(file, quantity, ',');
    std::cout << "Starting read loop\n";
    while (std::getline(file, line)) {
        std::cout << "File opened successfully\n";
        std::stringstream ss(line);
        std::getline(ss, itemName, ',');
        std::getline(ss, id, ',');
        std::getline(ss, price, ',');
        std::getline(ss, quantity, ',');
        std::cout << itemName << id << price << quantity << "\n";
    }
    std::ofstream output("inventory.csv", std::ios::app);
    output << "\ncomputer" << "," << 325 << "," << 1000.00 << "," << 5; 
    output.close();

   

    return 0;
}