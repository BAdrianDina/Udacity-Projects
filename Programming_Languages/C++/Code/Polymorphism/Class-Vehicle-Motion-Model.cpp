#include <cassert>
#include <cmath>
#include <iostream>

/*
Explanations: 

1.  Abstract Class VehicleModel:
    •   Defines the pure virtual function Move(double v, double phi) 
        to be implemented by derived classes.
2.  Class ParticleModel:
    •   Inherits publicly from VehicleModel.
    •   Includes state variables x, y, and theta to represent the position 
        and heading of the vehicle.
3.  Class BicycleModel:
    •   Inherits publicly from ParticleModel.
    •   Adds an additional state variable L to represent the length of the bicycle.

Key Concepts:
1.  Pure Virtual Functions:
    •   Enforces implementation of Move() in derived classes.
2.  Function Overriding:
    •   BicycleModel and ParticleModel both override the base class’s Move() 
        function with unique implementations.
3.  Polymorphism:
    •   The overridden Move() function is dynamically bound at runtime based 
        on the derived class object.
*/



// Define PI
#define PI 3.14159

// Abstract class VehicleModel
class VehicleModel {
public:
    virtual void Move(double v, double phi) = 0; // Pure virtual function
    virtual ~VehicleModel() = default;          // Virtual destructor
};

// Class ParticleModel derived from VehicleModel
class ParticleModel : public VehicleModel {
public:
    // State variables
    double x = 0.0;
    double y = 0.0;
    double theta = 0.0;

    // Override Move() function
    void Move(double v, double phi) override {
        theta += phi;
        x += v * std::cos(theta);
        y += v * std::sin(theta);
    }
};

// Class BicycleModel derived from ParticleModel
class BicycleModel : public ParticleModel {
public:
    // Vehicle length
    double L = 1.0;

    // Override Move() function
    void Move(double v, double phi) override {
        theta += (v / L) * std::tan(phi);
        x += v * std::cos(theta);
        y += v * std::sin(theta);
    }
};

// Test in main
int main() {
    // Create objects
    ParticleModel particle;
    BicycleModel bicycle;

    // Move both models
    particle.Move(10, PI / 9);
    bicycle.Move(10, PI / 9);

    // Test that states differ due to different Move implementations
    assert(particle.x != bicycle.x);
    assert(particle.y != bicycle.y);
    assert(particle.theta != bicycle.theta);

    // Optional: Print the results
    std::cout << "ParticleModel - x: " << particle.x << ", y: " << particle.y << ", theta: " << particle.theta << "\n";
    std::cout << "BicycleModel - x: " << bicycle.x << ", y: " << bicycle.y << ", theta: " << bicycle.theta << "\n";

    std::cout << "All tests passed successfully.\n";
    return 0;
}
