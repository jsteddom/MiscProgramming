#include <iostream>
#include <vector>
#include <random>

class Enemy;
class Item;

enum class Items {
    Sword,
    Knife,
    HealthPotion,
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

void printEnemy(Enemies enemy) {
    switch (enemy) {
        case Enemies::Skeleton:
            std::cout << "Skeleton";
            break;
        case Enemies::Knight:
            std::cout << "Knight";
            break;
        case Enemies::Ghoul:
            std::cout << "Ghoul";
            break;
        case Enemies::Goblin:
            std::cout << "Goblin";
            break;
    }
}

namespace Trackers {
    bool swordAvailable { true };
    bool knifeAvailable { true };
    int healthPots { 2 };
    int manaPots { 2 };
    int monsters { 5 };
}

class Room {
private:
    //Enemy
    //Item
    Enemy m_roomEnemy {};
    Item m_roomItem {};

};
class Item {
    //Item type

};

class Enemy {
    //Health Pts
    //Attack dmg
    //Enemy type
};

class Player {
    //Items 1,2
    //Health pts
};




int main() {
    
}