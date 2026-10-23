#include <iostream>
#include <vector>
#include <random>
enum class Items {
    Sword,
    Knife,
    HealthPotion,
    //Key,
    ManaPotiion,
    Empty,
    Max
};

enum class Enemies {
    Skeleton,
    Knight,
    Ghoul,
    Goblin,
    None,
};

namespace Trackers {
    bool swordAvailable { true };
    bool knifeAvailable { true };
    int healthPots { 2 };
    int manaPots { 2 };
    int monsters { 5 };
}

class Room {
private:
    Items m_item;
    Enemies m_mob;
public:
    Enemies getMob() {return m_mob;}
    Items getItem() {return m_item;}
    void itemPickedUp() {m_item = Items::Empty;}
    void setItems(Items item, Enemies enemy) {
        m_item = item;
        m_mob = enemy;
    };
};

class Player {
private:
    std::string m_playerName {"You"};
    double healthPoints { 100.0 };
    Items itemOne { Items::HealthPotion };
    Items itemTwo { Items::Empty};
public:
    Player() = default;
    void displayItems();
    void dropItem(int itemSlot);
    void pickUpItem(int itemSlot, Room& room);
    Items getItemOne() {return itemOne;};
    Items getItemTwo() {return itemTwo;};
    void healPlayer();
    double getPlayerHealth() {return healthPoints;}
    void receiveDamage(double damage);
    void printItems();
    void setItem(Room& room, int itemSlot);
};
void Player::setItem(Room& room, int itemSlot) {
    if (itemSlot == 1) {
        itemOne = room.getItem();
    }
    else {
        itemTwo = room.getItem();
    }
}
std::string convertItemEnum(Items item);
void Player::printItems() {
    std::cout << "Current Items: " << convertItemEnum(itemOne) << ", " << convertItemEnum(itemTwo);
}

void Player::receiveDamage(double damage) {
    healthPoints = healthPoints - damage;
}

void Player::healPlayer() {
    if (itemOne == Items::HealthPotion) {
        itemOne = Items::Empty;
        healthPoints += 5;
    } else if (itemTwo == Items::HealthPotion) {
        itemTwo = Items::Empty;
        healthPoints += 5;
    }
    else {
        std::cout << "No health potions available\n";
    }
}
void Player::dropItem(int itemSlot) {
    if (itemSlot == 1) {
        itemOne = Items::Empty;
    }
    else {
        itemTwo = Items::Empty;
    }
}

void Player::pickUpItem(int itemSlot, Room& room) {
    if (room.getItem() == Items::Empty) {
        std::cout << "No items in the room\n";
        return;
    }
    if (itemSlot == 1) {
        itemOne = room.getItem();
        room.itemPickedUp();
        return;
    }
    else {
        itemTwo = room.getItem();
        room.itemPickedUp();
        return;
    }
}
std::string convertItemEnum(Items item) {
    switch (item) {
        case Items::Sword:
            return "Sword";
        case Items::Knife:
            return "Knife";
        case Items::HealthPotion:
            return "Health Potion";
        case Items::ManaPotiion:
            return "Mana Potion";
        case Items::Empty:
            return "Empty";
        case Items::Max:
            return "Invalid Item";
    }
    return "Unknown Item";
}


Enemies setMonster() {
    std::mt19937 gen{std::random_device{}()};
    std::uniform_int_distribution<int> dist{0, 7};
    int monsterIndex {dist(gen)};

    switch (monsterIndex) {
        case 0:
            --Trackers::monsters;
            return Enemies::Skeleton;
            break;
        case 1:
            --Trackers::monsters;
            return Enemies::Knight;
            break;
        case 2:
            --Trackers::monsters;
            return Enemies::Ghoul;
            break;
        case 3:
            --Trackers::monsters;
            return Enemies::Goblin;
            break;
        case 4:
            return Enemies::None;
            break;
        case 5:
            return Enemies::None;
            break;
        case 6:
            return Enemies::None;
            break;
        case 7:
            return Enemies::None;
            break;
    }
    return Enemies::None;
}

std::string printMonsterType(Room& room) {
    switch (room.getMob()) {
        case Enemies::Skeleton:
            return "Skeleton";
        case Enemies::Knight:
            return "Knight";
        case Enemies::Ghoul:
            return "Ghoul";
        case Enemies::Goblin:
            return "Goblin";
        case Enemies::None:
            return "No enemy";
    }

    return "Unknown enemy";
}

double enemyHealth(Room& room) {
    switch (room.getMob()) {
        case Enemies::Skeleton:
            return 20;
        case Enemies::Knight:
            return 30;
        case Enemies::Ghoul:
            return 10;
        case Enemies::Goblin:
            return 7;
        case Enemies::None:
            return 0;
    }

    return 0;
}



std::string printItemType(Room& room) {
    switch (room.getItem()) {
        case Items::Sword:
            return "Sword";
        case Items::Knife:
            return "Knife";
        case Items::HealthPotion:
            return "Health Potion";
        case Items::ManaPotiion:
            return "Mana Potion";
        case Items::Empty:
            return "Empty";
        case Items::Max:
            return "Invalid Item";
    }
    return "Unknown Item";
}

Items setItems(int room) {
    std::mt19937 gen{std::random_device{}()};
    std::uniform_int_distribution<int> dist{0, 7};
    int itemIndex {dist(gen)};
    if (room < 3) {
        return Items::Empty;
    }
    if (itemIndex <= 1 && Trackers::healthPots > 0) {
        --Trackers::healthPots;
        return Items::HealthPotion;
    }
    return Items::Empty;
}




void setStage(std::vector<Room>& rooms, int roomCount) {
    for (int i { 0 } ; i < roomCount; i++) {
        Enemies monst { Enemies::None };
        Items item { Items::Empty};
        if (Trackers::monsters > 0) {
            monst = setMonster();
        }
        if (Trackers::healthPots > 0 || Trackers::manaPots > 0) {
            item = setItems(i);
        }
        Room createRoom;
        createRoom.setItems(item, monst);
        rooms.push_back(createRoom);
    }
}
double enemyAttack() {
    std::mt19937 gen{std::random_device{}()};
    std::uniform_int_distribution<int> dist{0, 9};
    int monsterIndex {dist(gen)};
    switch (monsterIndex) {
    case 0:
        return 0;
        break;
    case 1:
        return 1;
        break;
    case 2:
        return 3;
        break;
    case 3:
        return 4;
        break;
    case 4:
        return 5;
        break;
    case 5:
        return 5;
        break;
    case 6:
        return 7;
        break;
    case 7:
        return 7;
        break;
    case 8:
        return 9;
        break;
    case 9:
        return 12;
        break;
    default:
        break;
    }
    return 1;
}

void fightEnemy(Room& room, Player& player) {
    double eHealth {0};
    if (room.getMob() != Enemies::None) {
        eHealth = enemyHealth(room);            
        std::cout << "A " << printMonsterType(room) << " is in your way. You must fight!\n";   
        int choice {0}; 
        while (eHealth > 0 && player.getPlayerHealth() > 0) {
            
            std::cout << "Moves: \n 1. Attack\n 2. Use health potion \nyour choice: ";
            std::cin >> choice;
            if (choice == 1) {
                eHealth = eHealth - 5;
                std::cout << "You did 5 damage. The " << printMonsterType(room) << " has " << eHealth << " health points remaining\n";
            }
            else if (choice == 2) {
                std::cout << "Healing!";
                player.healPlayer();
            }
            double hit = enemyAttack();
            std::cout << "The " << printMonsterType(room) << " is attacking!\nYou are hit for " << hit << " points\n";
            player.receiveDamage(hit);
            std::cout << "You have " << player.getPlayerHealth() << " health points remaning\n";
            
        }
        std::cout << "You defeated an enemy!\n";       
    }
    else {
        std::cout << "No enemies\n";
    }
}
void checkRoom(Room& room, Player player) {
    char c {' '};
    if (room.getItem() == Items::Empty) {
        std::cout << "No items, moving on\n";
        return;
    }
    std::cout << "There is a " << printItemType(room) << " in the room\n";
    std::cout << "Would you like to pick it up? Y or N: ";
    std::cin >> c;
    if (c == 'Y') {
        player.printItems();
        if (player.getItemOne() != Items::Empty && player.getItemTwo() != Items::Empty) {
            std::cout << "\nInventory Full!\n 1) drop item 1\n2) drop item 2\n3) move on\nchoice: ";
            int choice { 0 };
            std::cin >> choice;
            if (choice == 1  || choice == 2) {
                player.dropItem(choice);
                player.pickUpItem(choice, room);
            }
            else {
                std::cout << "\nMoving on\n\n";
            }
        }
        else if (player.getItemTwo() == Items::Empty) {
            player.pickUpItem(2, room);
        }
        else {
            player.pickUpItem(1, room);
        }
    }
    player.printItems();
}


int main() {
    Player playerOne;
    std::cout << "---Welcome to the Dungeon---\n";
    std::cout << "How many rooms would you like to try?\nEnter number (0<x<20): ";
    int roomCount { 1 };
    std::cin >> roomCount;

    std::vector<Room> dungeonRooms;
    setStage(dungeonRooms, roomCount);
    for (auto room: dungeonRooms) {
        std::cout << "\n--Room--\nItem: " << printItemType(room) << "\nEnemy: " << printMonsterType(room) << "\n";
        if (room.getMob() != Enemies::None) {
            fightEnemy(room, playerOne);
        }
        if (playerOne.getPlayerHealth() < 0) {
            std::cout << "You have been defeated!\n";
            break;
        }
        checkRoom(room, playerOne);
    }

    
    return 0;
}