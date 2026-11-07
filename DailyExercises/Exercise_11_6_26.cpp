#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cctype>
#include <limits>

class Tracer {
private:
    std::string m_name;
public:
    Tracer(const std::string& name)
    : m_name {name}
    {
        std::cout << "Constructing: " << name << "\n";
    };
    ~Tracer() {
        std::cout << "Destructing: " << m_name << "\n";
    }
    std::string& getName() { return m_name; };

};

class Box {
private:
    int* m_data;
public:
    Box(int someInt = 0)
    : m_data { new int(someInt)}
    {
        std::cout << "Creating Box: " << someInt << "\n";
    } 
    Box(const Box&) = delete;
    Box& operator=(const Box&) = delete;
    ~Box() {
        std::cout << "Deleting Box: " << *m_data << "\n";
        delete m_data;
    }
    int get() const {
        return *m_data;
    }
    void set(int value) {
        *m_data = value;
    }



};

class Pair {
private:
    Tracer m_first;
    Tracer m_second;
public:
    //Pair(Tracer first, Tracer second)
    Pair(const std::string& first, const std::string& second) 
    : m_first { first }
    , m_second { second } 
    {
        std::cout << "Constructing Pair: " << m_first.getName() << ", " << m_second.getName() << "\n";
    }
    ~Pair() {
        std::cout << "Destructing Pair: " << m_first.getName() << ", " << m_second.getName() << "\n";
    }
};


int main() {
    //Tracer a { "a" };
    /*{
        Tracer b { "b" };
        Tracer c { "c" };
        std::cout << "inner scope ending\n";
    }
    //Tracer d { "d" };
    //Pair pr {{"a"}, {"d"}};
    Tracer* p { new Tracer { "heap" } };
    std::cout << "before delete\n";
    //delete p;
    std::cout << "after delete\n";
    Box mybox{42};
    std::cout << "Getting myBox: " << mybox.get() << "\n";
    {
        Box inner {1};
    }
    Box* newBox {new Box{19}};

    std::cout << "main ending\n";
    */
    Pair pr {"a", "d"};
    Tracer* p { new Tracer { "heap" } };
    std::cout << "before delete\n";
    delete p;
    std::cout << "after delete\n";
    

    return 0;
}

/*
Day 3: Constructors, Destructors, and One Heap Allocation (~45 min)

Goal: See exactly when constructors and destructors run, then manage a single heap-allocated value by hand. No arrays, no resizing, no copying.

Part 1: Watch the lifecycle (~15 min)

Write a class Tracer:

private std::string m_name
constructor Tracer(const std::string& name) that stores the name and prints Constructing <name>
destructor that prints Destroying <name>

In main(), write this and predict the output on paper before running it:

cpp
Tracer a { "a" };
{
    Tracer b { "b" };
    Tracer c { "c" };
    std::cout << "inner scope ending\n";
}
Tracer d { "d" };
std::cout << "main ending\n";

Then run it and compare. Questions to answer in a comment: In what order were b and c destroyed, and why? When was a destroyed relative to d?

Part 2: Members and the heap (~10 min)
Write a class Pair with two Tracer members, m_first and m_second. Its constructor takes two names and initializes the members with a member initializer list. It should also print Constructing Pair and Destroying Pair. Create one in main() and predict the order: does Pair’s constructor body run before or after its members are constructed? And the destructor?
Create a Tracer on the heap and clean it up:
cpp
   Tracer* p { new Tracer { "heap" } };
   std::cout << "before delete\n";
   delete p;
   std::cout << "after delete\n";

Then try removing the delete line and see what happens to the “Destroying heap” message. That’s what a leak looks like from the object’s point of view.

Part 3: A class that owns memory (~20 min)

Write a class Box that owns one int on the heap:

private member int* m_value
Box(int value = 0): allocates with new int { value }
~Box(): frees it with delete
int get() const
void set(int value)
Box(const Box&) = delete; and Box& operator=(const Box&) = delete;: write these exactly as shown. They stop you from copying a Box, which would cause two objects to delete the same memory. We’ll fix that properly in a later exercise.

Add a std::cout line in the constructor and destructor so you can see them run.

Test in main():

Create a Box { 42 }, print get(), call set(7), print again.
Create a Box in an inner scope { } and confirm the destructor message appears at the closing brace.
Create a Box on the heap with new Box { 5 }, use it with ->, then delete it.
Compile with -Wall -Wextra -std=c++17 -g -fsanitize=address,undefined and run. A correct solution prints no sanitizer output. Then comment out the delete m_value; in the destructor, rerun, and read the leak report (on Linux; support varies elsewhere). Put it back.

Constraints

Member functions that don’t modify the object are const.
Initialize every variable and member when you declare it.
No std::vector, smart pointers, or arrays.



*/