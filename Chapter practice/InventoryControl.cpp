#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "InventoryItems.h"

void readInventoryFile(Warehouse&  warehouse) {
    std::ifstream myInventory("inventory.csv");
    std::string currentLine;
    while (std::getline(myInventory, currentLine)) {
        std::stringstream ss(currentLine);
        
    }
}

void ManageInventory() {
    Warehouse myWarehouse;
    readInventoryFile(myWarehouse);
}






int main() {
    ManageInventory();
}