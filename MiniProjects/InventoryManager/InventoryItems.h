#ifndef INVENTORYITEMS_H
#define INVENTORYITEMS_H
#include <unordered_map>
#include <string>
class Item;

using Inventory = std::unordered_map<u_int16_t, Item>;

class Warehouse {
private:
    Inventory currentSupply;

public:
    std::optional<Item> searchWarehouse(uint16_t itemID);
    void validateRetrieval(std::optional<Item> item);
    void addItem(Item newItem, u_int16_t itemID);
    void removeItem(u_int16_t itemID);
    Item& getItem(uint16_t itemID) { return currentSupply.at(itemID);}
    Inventory getInventory() { return currentSupply; }
};

class Item {
private:
    u_int16_t m_id;
    std::string m_name;
    double m_price;
    int m_quantity;
public:
    Item(u_int16_t id, std::string name, double price, int quantity)
    : m_id { id }
    , m_name { name }
    , m_price { price }
    , m_quantity { quantity }
    {

    }
    u_int16_t getItemID() { return m_id; }
    std::string getName() { return m_name; }
    double getPrice() { return m_price; }
    int getQuantity() { return m_quantity; }
    void updatePrice(double newPrice);
    void updateQuantity(int newQuantity);
    friend void printItemInfo(Item& item);
};

void createItem(Warehouse* warehouse);
void saveAddedItem(Item& item);

#endif