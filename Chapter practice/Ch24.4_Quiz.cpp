#include <iostream>
#include <string>

class Fruit {
private:
    std::string m_name;
    std::string m_color;
public:
    Fruit(std::string_view name, std::string_view color) 
    : m_name {name}
    , m_color {color}
    {
        std::cout << "Fruit constructed!\n";
    }
    const std::string& getName() const {
        return m_name;
    }
    const std::string& getColor() const {
        return m_color;
    }
};

class Apple : public Fruit {
private:
    double m_fiber;
public:
    Apple(std::string_view name, std::string_view color, double fiber)
    : Fruit {name,color}
    , m_fiber {fiber}
    {
        std::cout << "Apple constructed!\n";
    }
    const double getFiber() const {
        return m_fiber;
    }
};

class Banana : public Fruit {
public:
    Banana(std::string_view name, std::string_view color)
    : Fruit {name,color}
    {
        std::cout << "Banana constructed!\n";
    }
};

std::ostream& operator<<(std::ostream& out, Fruit fruit) {
    out << fruit.getName() << fruit.getColor();
    return out;
}
std::ostream& operator<<(std::ostream& out, Apple apple) {
    out << apple.getName() << " " << apple.getColor() << " " << apple.getFiber();
    return out;
}



int main()
{
    
	const Apple a { "Red delicious", "red", 4.2 };
	std::cout << a << '\n';

	const Banana b { "Cavendish", "yellow" };
	std::cout << b << '\n';

	return 0;
}