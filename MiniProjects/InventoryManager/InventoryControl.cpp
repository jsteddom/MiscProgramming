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
    while (std::getline(myInventory, currentLine)) {
        std::stringstream ss(currentLine);
        std::getline(ss, id, ',');
        itemID = static_cast<uint16_t>(std::stoi(id));
        std::getline(ss, itemName, ',');
        std::getline(ss, price, ',');
        itemPrice = static_cast<double>(std::stoi(price));
        std::getline(ss, quantity, ',');
        itemQuantity = static_cast<int>(std::stoi(quantity));
        Item itemRead {itemID, itemName, itemPrice, itemQuantity};
        warehouse->addItem(itemRead, itemID);
    }
    myInventory.close();
}
void saveAddedItem(Item& item) {
    std::ofstream file("inventory.csv", std::ios::app);
    file << "\n" << item.getItemID() << "," << item.getName() << ","  << item.getPrice() << ","  << item.getQuantity();
    file.close();
}

void printMyWarehouse(Warehouse* warehouse) {
    for (auto& item : warehouse->getInventory()) {
        printItemInfo(item.second);
    }
}

void updateItemQuantity(Warehouse* warehouse) {
    int searchID;
    std::cout << "Enter ID of item to update: ";
    std::cin >> searchID;
    std::optional<Item> itemToUpdate = warehouse->searchWarehouse(searchID);
    if(itemToUpdate.has_value()) {
        int newQuantity;
        std::cout << "Enter new quantity: ";
        std::cin >> newQuantity;
        Item& updateItem {warehouse->getItem(itemToUpdate->getItemID())};
        updateItem.updateQuantity(newQuantity);
    }
}



void printWarehouseMenu() {
    std::cout << "What would you like to do? \n";
    std::cout << "1.    Add an Item\n";
    std::cout << "2.    Look up an Item\n";
    std::cout << "3.    Update an Item quantity\n";
    std::cout << "4.    Display Inventory\n";
    std::cout << "5.    Remove an Item\n";
    std::cout << "0.    Quit\n";
}
void handleMenuChoice(Warehouse* warehouse,int menuChoice) {
    switch(menuChoice) {
        case 1:
            createItem(warehouse);  
            break;
        case 2:
            int searchID;
            std::cout << "Enter ID to search by: ";
            std::cin >> searchID;
            warehouse->searchWarehouse(searchID);
            break;
        case 3:
            updateItemQuantity(warehouse);
            break;
        case 4:
            break;
        case 5:
            break;
        case 0:
            break;
        default:
            std::cout << "Invalid choice.\n";
            break;
    }
}
void saveAndQuit(Warehouse* warehouse){
    std::ofstream file("inventory.csv");
    for (auto& itemIndex : warehouse->getInventory()) {
        Item item {itemIndex.second};
        file << item.getItemID() << "," << item.getName() << ","  << item.getPrice() << ","  << item.getQuantity() << "\n";
    }
    //file << "\n" << item.getItemID() << "," << item.getName() << ","  << item.getPrice() << ","  << item.getQuantity();
    file.close();
}


void ManageInventory() {
    std::cout << "--------Welcome to your warehouse--------\n\n";
    Warehouse* myWarehouse {new Warehouse};
    readInventoryFile(myWarehouse);
    printMyWarehouse(myWarehouse);
    std::optional<Item> itemSearch = myWarehouse->searchWarehouse(301);
    int menuChoice {1};
    while (menuChoice != 0) {
        printWarehouseMenu();
        std::cout << "Enter choice: ";
        std::cin >> menuChoice;
        handleMenuChoice(myWarehouse, menuChoice);
    }
    saveAndQuit(myWarehouse);


    delete myWarehouse;
}






int main() {
    ManageInventory();
}