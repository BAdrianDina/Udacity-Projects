#include <cassert>


/*
Explanations: 

1.  Base Class Vehicle:
    •   Contains the wheels attribute, which is inherited by all derived classes.
2.  Derived Class Car:
    •   Inherits from Vehicle.
    •   Adds the seats attribute to represent the number of seats in a car.
3.  Derived Class Sedan:
    •   Inherits from Car.
    •   Adds the trunk attribute to represent the trunk status specific to a sedan.
4.  Main Function:
    •   Creates an object of the most derived class Sedan.
    •   Validates access to attributes from all levels of the inheritance hierarchy:
    •   trunk from Sedan.
    •   seats from Car.
    •   wheels from Vehicle.

Key Concepts
    •   Multi-Level Inheritance:
    •   Each class in the chain inherits attributes and behaviors from its 
        parent class.
    •   The most derived class (Sedan) has access to all attributes defined in 
        its inheritance tree.
    •   Attribute Resolution:
    •   Attributes are inherited and accessed as if they were defined directly 
        in the derived class.

*/


// Base class: Vehicle
class Vehicle {
public:
    int wheels = 4; // Default number of wheels
};

// Derived class: Car (inherits from Vehicle)
class Car : public Vehicle {
public:
    int seats = 4; // Default number of seats
};

// Derived class: Sedan (inherits from Car)
class Sedan : public Car {
public:
    bool trunk = true; // Default trunk status
};

// Test in main
int main() {
    // Create an object of the most derived class: Sedan
    Sedan sedan;

    // Tests to validate multi-level inheritance
    assert(sedan.trunk == true);  // From Sedan
    assert(sedan.seats == 4);     // From Car
    assert(sedan.wheels == 4);    // From Vehicle

    return 0;
}