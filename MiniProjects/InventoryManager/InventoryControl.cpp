#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "InventoryItems.h"

void readInventoryFile(Warehouse*  warehouse) {
    std::ifstream myInventory("inventory.csv");
    std::string currentLine;

    std::string itemName;
    std::string id;
    std::string price;
    std::string quantity;

    u_int16_t itemID;
    double itemPrice;
    int itemQuantity;
    std::cout << "before loop\n";
    while (std::getline(myInventory, currentLine)) {
        std::stringstream ss(currentLine);
        std::getline(ss, id, ',');
        //std::cout << "string id: " << id;
        itemID = static_cast<uint16_t>(std::stoi(id));
        std::cout << "Item ID: " << itemID;
        std::getline(ss, itemName, ',');
        std::getline(ss, price, ',');
        itemPrice = static_cast<double>(std::stoi(price));
        std::getline(ss, quantity, ',');
        itemQuantity = static_cast<int>(std::stoi(quantity));
        Item itemRead {itemID, itemName, itemPrice, itemQuantity};
        warehouse->addItem(itemRead, itemID);
    }
    std::cout << "after loop\n";
}

void printMyWarehouse(Warehouse* warehouse) {
    for (auto& item : warehouse->getInventory()) {
        printItemInfo(item.second);
    }
}

void ManageInventory() {
    Warehouse* myWarehouse {new Warehouse};
    readInventoryFile(myWarehouse);
    printMyWarehouse(myWarehouse);
    Item itemSearch = myWarehouse->searchWarehouse(300);
    std::cout << "--Item looked up--";
    printItemInfo(itemSearch);

    delete myWarehouse;
}






int main() {
    ManageInventory();
}