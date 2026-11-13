#include <iostream>
#include <vector>
#include <string>
#include <limits>


enum class Status {
    OK,
    INVALID,
    ALREADY_EXISTS,
    INVALID_INPUT,
    INSUFFICIENT_STOCK,
    ITEM_NOT_FOUND,
    BAD_INPUT,
    INVALID_QUANITITY,
    INVALID_PRICE
};

struct Product {
    std::string p_name {};
    double p_price {};
    int p_quantity {};
};

struct SalesLog {
    std::string itemName {};
    double aggregatePrice {};
    int soldQuantity {};
};

class Inventory {
private:
    std::vector<Product> m_stock;
    std::vector<SalesLog> m_salesLog;
public:
    Status addInventory(Product& newProduct) {
        auto findName {m_stock.begin()};
        while (findName != m_stock.end() && findName->p_name != newProduct.p_name) findName++;
        if (findName != m_stock.end()) {
            return Status::ALREADY_EXISTS;
        } else if (newProduct.p_quantity <= 0) {
            return Status::INVALID_QUANITITY;
        } else if (newProduct.p_price <= 0) {
            return Status::INVALID_PRICE;
        }
        else {
            m_stock.push_back(newProduct);
            return Status::OK;
        }
    }
    Status receiveStock(const std::string& productName, int quantityToAdd) {
        if (quantityToAdd <= 0) {
            return Status::INVALID_INPUT;
        }
        auto findItem {m_stock.begin()};
        while (findItem != m_stock.end() && findItem->p_name != productName) findItem++;
        if (findItem == m_stock.end()) {
            return Status::ITEM_NOT_FOUND;
        } else {
            findItem->p_quantity += quantityToAdd;
            return Status::OK;
        }
    }
    Status makeSale(const std::string& productName, const int quantityToSell) {
        auto findItem {m_stock.begin()};
        while (findItem != m_stock.end() && findItem->p_name != productName) findItem++;
        if (findItem == m_stock.end()) {
            return Status::ITEM_NOT_FOUND;
        } else if (findItem->p_quantity < quantityToSell) {
            return Status::INSUFFICIENT_STOCK;
        } else if (quantityToSell <= 0) {
            return Status::INVALID_QUANITITY;
        } else {
            findItem->p_quantity -= quantityToSell;
            m_salesLog.push_back(SalesLog {findItem->p_name, findItem->p_price, quantityToSell});
            return Status::OK;
        }
    }
    void displayInventory() const {
        for (const auto& product : m_stock) {
            std::string formatstring = std::format("Item: {}    Price: {}   Quantity: {}\n", product.p_name, product.p_price, product.p_quantity);
            std::cout << formatstring;
        }
    }
    void displayLowInvetory(int queryQuantity) const {
        std::cout << "\n---Low Quantity Items---\n";
        for (const auto& product : m_stock) {
            if (product.p_quantity < queryQuantity) {
                std::string formatstring = std::format("Item: {}    Price: {}   Quantity: {}\n", product.p_name, product.p_price, product.p_quantity);
                std::cout << formatstring;
            }         
        }
        std::cout << "\n";
    }
    double getInventoryTotalValue() const {
        double inventoryValue { 0 };
        for (const auto& product : m_stock) {
            inventoryValue += (product.p_price * product.p_quantity);
        }
        return inventoryValue;
    }
    void printLastTransaction() const {
        if (m_stock.size() <= 0) {
            std::cout << "No Transactions in system.\n";
            return;
        }
        SalesLog lastItem = m_salesLog.back();
        std::cout << "\n\n---Previous Transaction---\n";
        std::cout << "Item sold: " << lastItem.itemName << ",\nItem price: " << lastItem.aggregatePrice << ",\nQuantity sold: " << lastItem.soldQuantity << "\n\n";
    }

};

void printStatus(Status action_status) {
    switch(action_status) {
        case Status::OK:
            std::cout << "Action succsesful!\n";
            break;
        case Status::INVALID_INPUT:
            std::cout << "Invalid input was given.\n";
            break;
        case Status::ALREADY_EXISTS:
            std::cout << "An item with this name already exists!\n";
            break;
        case Status::INSUFFICIENT_STOCK:
            std::cout << "Insufficient stock to fulfill order.\n";
            break;
        case Status::ITEM_NOT_FOUND:
            std::cout << "Item not found in inventory.\n";
            break;
        case Status::BAD_INPUT:
            std::cout << "Could not read input!\n";
            break;
        case Status::INVALID_QUANITITY:
            std::cout << "Invalid quantity for operation.\n";
            break;
        case Status::INVALID_PRICE:
            std::cout << "Invalid price for new item.\n";
            break;
        default:
            std::cout << "Unknow Input\n";
            break;
    }
}
void ignoreLine() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


Status handleInput(int choice) {
    if (std::cin.fail()) // If the previous extraction failed
        {       
            //std::cout << "Bad input, try again.\n";
            std::cin.clear(); 
            ignoreLine();
            return Status::BAD_INPUT;  
        }
    else if (choice > 6 || choice < 0) {
        //std::cout << "Invald choice, try again\n";
        return Status::INVALID_INPUT;
    }
    return Status::OK;
}

Status handleBadInput() {
    if (std::cin.fail()) {       
        std::cin.clear(); 
        ignoreLine();
        return Status::BAD_INPUT;  
    }
    else {
        return Status::OK;
    }
}






void printMenu() {
    std::cout << "1. Add Item to Inventory\n";
    std::cout << "2. Recieve Inventory\n";
    std::cout << "3. Make Sale\n";
    std::cout << "4. Display Inventory\n";
    std::cout << "5. Display low quantity products\n";
    std::cout << "6. Get total inventory value\n";
    std::cout << "0. Quit\n";
}

int main() {
    Inventory myInventory;
    int choice { -1 };
    Status validateChoice {Status::OK};
    std::string itemname {};
    double itemPrice {};
    int itemQuantity {};
    int lowQuantity {};
    double inventoryValue {};
    Product newProduct {itemname, itemPrice, itemQuantity};
    std::cout << "--------Inventory Management System--------\n\n";
    do {
        printMenu();
        std::cout << "Enter choice: ";
        std::cin >> choice;
        validateChoice = handleBadInput();
        printStatus(validateChoice);
        if (validateChoice != Status::OK) {
            choice = -1;
            continue;
        }
        switch (choice) {
            case 1:
                std::cout << "Enter item name: ";
                std::cin >> itemname;
                std::cout << "Enter item price: ";
                std::cin >> itemPrice;
                std::cout << "Enter item quantity: ";
                std::cin >> itemQuantity;
                validateChoice = handleBadInput();
                if (validateChoice != Status::OK) {
                    printStatus(validateChoice);
                    break;
                }
                validateChoice = handleBadInput();
                if (validateChoice != Status::OK) {
                    printStatus(validateChoice);
                    break;
                }

                newProduct.p_name = itemname;
                newProduct.p_price = itemPrice;
                newProduct.p_quantity = itemQuantity;
                validateChoice = myInventory.addInventory(newProduct);
                printStatus(validateChoice);
                break;
            case 2:
                std::cout << "Enter item name: ";
                std::cin >> itemname;
                std::cout << "Enter quantity to be received: ";
                std::cin >> itemQuantity;
                validateChoice = handleBadInput();
                if (validateChoice != Status::OK) {
                    printStatus(validateChoice);
                    break;
                }
                validateChoice = myInventory.receiveStock(itemname, itemQuantity);
                printStatus(validateChoice);
                break;
            case 3:
                std::cout << "Enter item name: ";
                std::cin >> itemname;
                std::cout << "Enter quantity to sell: ";
                std::cin >> itemQuantity;
                validateChoice = handleBadInput();
                if (validateChoice != Status::OK) {
                    printStatus(validateChoice);
                    break;
                }
                validateChoice = myInventory.makeSale(itemname, itemQuantity);
                printStatus(validateChoice);
                if (validateChoice == Status::OK) {
                    myInventory.printLastTransaction();
                }
                break;
            case 4:
                myInventory.displayInventory();
                break;
            case 5:
                std::cout << "Enter low item quantity threshold: ";
                std::cin >> lowQuantity;
                validateChoice = handleBadInput();
                if (validateChoice != Status::OK) {
                    printStatus(validateChoice);
                    break;
                } else if (lowQuantity <= 0) {
                    printStatus(Status::INVALID_INPUT);
                } else {
                    myInventory.displayLowInvetory(lowQuantity);
                }
                
                break;
            case 6:
                inventoryValue = myInventory.getInventoryTotalValue();
                std::cout << "Value of inventory: $" << inventoryValue << ".\n";
                break;
            case 0:
                std::cout << "--------Quitting Program--------\n\n";
            default:
                break;
        }
        

    } while (choice != 0);
    return 0;
}
/*
Day 6: Inventory Tracker (~45 min)

The scenario: A small shop needs software to track its stock. Items come in from suppliers, get sold to customers, and the owner wants to know what’s running low and what the stock is worth.

What it should do

Add a new product with a name, a price, and a starting quantity.
Receive more stock of an existing product.
Sell some quantity of a product and report the sale total.
Show every product with its quantity and price.
List the products that are running low (below a threshold the owner chooses).
Report the total value of everything in stock.

Rules

Product names are unique.
You can’t sell a product that doesn’t exist, or sell more than is in stock.
Quantities and prices can’t be negative, and a sale or restock of 0 or less is rejected.
Selling the last unit is fine, and the product stays in the inventory at quantity 0.
Each operation lets the caller know whether it worked. A sale also reports the total, and a failure should say why (not found, not enough stock, bad amount), so think about how a function can return more than a yes/no.

Your job

Decide your types, what each owns, and where each fact lives.
Decide the signatures, including const, references, and return types.
Write a main() that exercises every rule, including each failure case, before you add any menu. Make the tests print PASS/FAIL by comparing against the result you expect.

Constraints

Private data members where it makes sense.
Compile with -Wall -Wextra -std=c++20, no warnings.
Include only the headers you use.
No lambdas, ranges, or smart pointers. Plain loops are fine.
Printing happens in main(), not inside the class.

*/