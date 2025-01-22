#include <cassert>
#include <string>

/*
Description:

1.  Class Cat:
    •   Inherits from both Animal and Pet, just like Dog.
    •   Adds a unique member attribute color to differentiate it from Dog.
2.  Setting Attributes:
    •   The Cat object has access to:
    •   age (from Animal).
    •   name (from Pet).
    •   color (unique to Cat).
    •   Each attribute is explicitly set in main() to match the test requirements.
3.  Tests in main():
    •   Verify the values of color, age, and name for the Cat object using assert.
*/


#include <iostream>
#include <string>
#include <cassert>

// Base class Animal
class Animal {
public:
    double age;
};

// Base class Pet
class Pet {
public:
    std::string name;
};

// Dog class inherits from both Animal and Pet
class Dog : public Animal, public Pet {
public:
    std::string breed;
};

// Cat class inherits from both Animal and Pet
class Cat : public Animal, public Pet {
public:
    std::string color; // Unique member attribute
};

int main() {
    // Instantiate a Cat object
    Cat cat;
    cat.color = "black";  // Set Cat-specific attribute
    cat.age = 10;         // Set Animal attribute
    cat.name = "Max";     // Set Pet attribute

    // Tests
    assert(cat.color == "black");
    assert(cat.age == 10);
    assert(cat.name == "Max");

    std::cout << "All tests passed successfully.\n";
    return 0;
}