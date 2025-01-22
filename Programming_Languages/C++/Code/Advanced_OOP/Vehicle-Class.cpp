#include <iostream>
#include <string>
using std::string;


/* 
    1.  Public Inheritance (Car):
        •   Members of the base class retain their original access levels
            (e.g., public stays public, protected stays protected).
        •   wheels (public in Vehicle) is accessible from main() through car.wheels.
        •   Members of the base class can also be accessed from within the derived class.
    2.  Protected Inheritance (Bicycle):
        •   Members of the base class become protected in the derived class, 
            regardless of their original access levels.
        •   wheels is not accessible from main() because it’s protected in Bicycle.
        •   However, members of the base class are accessible from within Bicycle itself.
    3.  Private Inheritance (Scooter):
        •   Members of the base class become private in the derived class, 
            regardless of their original access levels.
        •   wheels is not accessible from main() because it’s private in Scooter.
        •   However, members of the base class are accessible from within Scooter itself.


    Results of the Experiment
    1.  Access a Protected Member from main():
        •   wheels is not accessible from main() for Bicycle, because Bicycle uses protected 
            inheritance.
    2.  Access a Private Member from main():
        •   wheels is not accessible from main() for Scooter, because Scooter uses 
            private inheritance.
    3.  Access a Base Class Member from a Derived Class with Protected Inheritance (Bicycle):
        •   color is accessible within Bicycle, because protected inheritance allows access 
            to base class members within the derived class.
    4.  Access a Base Class Member from a Derived Class with Private Inheritance (Scooter):
        •   wheels is accessible within Scooter, because private inheritance allows access to 
            base class members within the derived class, though it restricts access from outside.
*/





class Vehicle {
public:
    int wheels = 0;
    string color = "blue";
    
    void Print() const {
        std::cout << "This " << color << " vehicle has " << wheels << " wheels!\n";
    }
};

// Public Inheritance
class Car : public Vehicle {
public:
    bool sunroof = false;

    void AccessBaseClassMember() {
        std::cout << "Accessing base class member from Car: " << wheels << "\n"; // Allowed
    }
};

// Protected Inheritance
class Bicycle : protected Vehicle {
public:
    bool kickstand = true;

    void AccessBaseClassMember() {
        std::cout << "Accessing base class member from Bicycle: " << color << "\n"; // Allowed
    }
};

// Private Inheritance
class Scooter : private Vehicle {
public:
    bool electric = false;

    void AccessBaseClassMember() {
        std::cout << "Accessing base class member from Scooter: " << wheels << "\n"; // Allowed
    }
};

int main() {
    Car car;
    car.wheels = 4;            // Accessible because Car inherits publicly
    car.sunroof = true;        // Accessible because sunroof is a public member of Car
    car.Print();               // Accessible because Print() is a public member of Vehicle
    car.AccessBaseClassMember();

    Bicycle bicycle;
    // bicycle.wheels = 2;     // Not accessible because Bicycle inherits Vehicle as protected
    bicycle.AccessBaseClassMember(); // Accessible because it's within the derived class

    Scooter scooter;
    // scooter.wheels = 2;     // Not accessible because Scooter inherits Vehicle as private
    scooter.AccessBaseClassMember(); // Accessible because it's within the derived class

    return 0;
}