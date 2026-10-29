#include "InventoryItems.h"
#include <iostream>
#include <vector>
#include <string>
#include <optional>

void Warehouse::addItem(Item newItem, u_int16_t itemID) {
    currentSupply.insert({itemID, newItem});
    std::cout << "Item added.\n";
}
std::optional<Item> Warehouse::searchWarehouse(u_int16_t itemID){
    auto doesIDExist = currentSupply.find(itemID);
    if (doesIDExist == currentSupply.end()) {
        std::cout << "That item ID does not exist!\n";
        return {};
    }
    else {
        printItemInfo(currentSupply.at(itemID));
    }
    return currentSupply.at(itemID);
}
void Warehouse::validateRetrieval(std::optional<Item> item) {
    if (item) {
        printItemInfo(*item);
    }

}
void Warehouse::removeItem(u_int16_t itemID) {
    currentSupply.erase(itemID);
}
void Item::updatePrice(double newPrice) {
    m_price = newPrice;
}
void Item::updateQuantity(int newQuantity) {
    m_quantity = newQuantity;
}
void printItemInfo(Item& item) {
    std::cout << "Item: " << item.m_name;
    std::cout << " ID: " << item.m_id;
    std::cout << " Price: " << item.m_price;
    std::cout << " Quanitity: " << item.m_quantity << "\n";
}
void createItem(Warehouse* warehouse) {
    std::string itemName;
    uint16_t itemID;
    double price;
    int quantity;

    std::cout << "Enter Item name: ";
    std::cin >> itemName;
    std::cout << "Enter Item ID: ";
    std::cin >> itemID;
    std::cout << "Enter Item price: ";
    std::cin >> price;
    std::cout << "Enter Item quantity: ";
    std::cin >> quantity;
    std::optional<Item> checkID {warehouse->searchWarehouse(itemID)};
    if(checkID) {
        std::cout << "That ID already exists! Item cannot be created.\n";
    }
    else {
        Item tempItem{itemID, itemName, price, quantity};
        warehouse->addItem(Item {itemID, itemName, price, quantity}, itemID);
        saveAddedItem(tempItem);
    }
}