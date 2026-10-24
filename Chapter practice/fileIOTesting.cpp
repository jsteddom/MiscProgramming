#include <iostream>

#include <fstream>

int main()
{
    std::ofstream file("output.txt");

    file << "Hello, world!\n";
    file << "This is my first file.";

    return 0;
}