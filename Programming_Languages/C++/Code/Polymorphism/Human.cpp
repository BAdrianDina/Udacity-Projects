#include <iostream>
#include <string>



/*
Explanations:

1.  Base Function:
    •   The base hello() function is defined to output "Hello, World!".
2.  Class Definitions:
    •   Three classes are defined: Human, Animal, and Robot. These serve as the parameter types for the overloaded hello function.
3.  Function Overloading:
    •   hello(Human) outputs "Hello, Human!".
    •   hello(Animal) outputs "Hello, Animal!".
    •   hello(Robot) outputs "Hello, Robot!".
4. Testing in main:
    •   The base hello() function is called with no arguments.
    •   Overloaded versions of hello() are called with instances of Human, 
        Animal, and Robot classes as arguments.

Function Overloading:
    •   Multiple versions of hello() are defined with different parameter types.
    •   The compiler determines which version of hello() to call based on the 
        argument passed.
Polymorphism Without Classes:
    •   Function overloading achieves polymorphic behavior outside an 
        object-oriented context.
Reusability:
    •   Overloading allows extending hello() to work with new types 
        (Animal and Robot) without modifying existing code.
*/



// Base hello function
void hello() {
    std::cout << "Hello, World!" << std::endl;
}

// Define class Human
class Human {};

// Overload hello() for Human
void hello(Human) {
    std::cout << "Hello, Human!" << std::endl;
}

// Define class Animal
class Animal {};

// Overload hello() for Animal
void hello(Animal) {
    std::cout << "Hello, Animal!" << std::endl;
}

// Define class Robot
class Robot {};

// Overload hello() for Robot
void hello(Robot) {
    std::cout << "Hello, Robot!" << std::endl;
}

// Main function to test the overloaded functions
int main() {
    hello(); // Outputs: Hello, World!

    Human human;
    hello(human); // Outputs: Hello, Human!

    Animal animal;
    hello(animal); // Outputs: Hello, Animal!

    Robot robot;
    hello(robot); // Outputs: Hello, Robot!

    return 0;
}