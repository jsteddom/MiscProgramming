#include "InventoryItems.h"
#include <iostream>
#include <vector>
#include <string>

void Warehouse::addItem(Item newItem, u_int16_t itemID) {
    currentSupply.insert({itemID, newItem});
}
Item Warehouse::searchWarehouse(u_int16_t itemID){
    return currentSupply.at(itemID);
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