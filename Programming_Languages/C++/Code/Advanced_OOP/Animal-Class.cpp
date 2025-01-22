#include <iostream>
#include <string>


/*
Code explanation: 

    1.  Base Class Animal:
        •   Has three member variables: color, name, and age.
        •   A constructor initializes these variables.
        •   A PrintInfo function displays the animal’s basic details.
    2.  Derived Class Snake:
        •   Inherits from Animal.
        •   Adds a unique member variable length specific to snakes.
        •   Implements a MakeSound function for hissing.
        •   Overrides PrintInfo to include the length attribute.
    3.  Derived Class Cat:
        •   Inherits from Animal.
        •   Adds a unique member variable height specific to cats.
        •   Implements a MakeSound function for meowing.
        •   Overrides PrintInfo to include the height attribute.
    4.  Main Function:
        •   Instantiates Snake and Cat objects.
        •   Initializes their unique and derived attributes.
        •   Calls PrintInfo and MakeSound for each object.


*/




class Animal {
public:
    // Base class constructor
    Animal(const std::string& color, const std::string& name, int age)
        : color_(color), name_(name), age_(age) {}

    // Accessor to print Animal info
    void PrintInfo() const {
        std::cout << "Animal Info: " << name_ << ", Color: " << color_ << ", Age: " << age_ << "\n";
    }

protected:
    std::string color_;
    std::string name_;
    int age_;
};

class Snake : public Animal {
public:
    // Constructor
    Snake(const std::string& color, const std::string& name, int age, double length)
        : Animal(color, name, age), length_(length) {}

    // MakeSound function
    void MakeSound() const {
        std::cout << name_ << " (a snake) hisses: Ssss...\n";
    }

    // Accessor to print Snake-specific info
    void PrintInfo() const {
        Animal::PrintInfo();
        std::cout << "Length: " << length_ << " meters\n";
    }

private:
    double length_;
};

class Cat : public Animal {
public:
    // Constructor
    Cat(const std::string& color, const std::string& name, int age, double height)
        : Animal(color, name, age), height_(height) {}

    // MakeSound function
    void MakeSound() const {
        std::cout << name_ << " (a cat) meows: Meow...\n";
    }

    // Accessor to print Cat-specific info
    void PrintInfo() const {
        Animal::PrintInfo();
        std::cout << "Height: " << height_ << " meters\n";
    }

private:
    double height_;
};

int main() {
    // Create Snake object
    Snake snake("Green", "Slither", 5, 2.5);
    snake.PrintInfo();
    snake.MakeSound();

    // Create Cat object
    Cat cat("Black", "Whiskers", 3, 0.35);
    cat.PrintInfo();
    cat.MakeSound();

    return 0;
}