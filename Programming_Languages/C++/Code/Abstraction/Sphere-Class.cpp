#include <cassert>
#include <cmath>
#include <stdexcept>
#include <iostream>

class Sphere {
public:
    // Constructor
    Sphere(int radius) {
        SetRadius(radius);
    }

    // Accessor methods
    int Radius() const { return radius_; }
    float Volume() const { return volume_; }

    // Mutator method
    void SetRadius(int radius) {
        ValidateRadius(radius);
        radius_ = radius;
        UpdateVolume();
    }

private:
    float const pi_{3.14159};
    int radius_;
    float volume_;

    // Private validation function
    void ValidateRadius(int radius) const {
        if (radius <= 0) {
            throw std::invalid_argument("radius must be positive");
        }
    }

    // Private method to update volume
    void UpdateVolume() {
        volume_ = (4.0 / 3.0) * pi_ * std::pow(radius_, 3);
    }
};

// Test
int main() {
    // Create a sphere with radius 5
    Sphere sphere(5);
    assert(sphere.Radius() == 5);
    assert(std::abs(sphere.Volume() - 523.6) < 1);

    // Change radius to 3
    sphere.SetRadius(3);
    assert(sphere.Radius() == 3);
    assert(std::abs(sphere.Volume() - 113.1) < 1);

    // Test invalid radius
    bool caught{false};
    try {
        sphere.SetRadius(-1);
    } catch (const std::invalid_argument&) {
        caught = true;
    }
    assert(caught);

    std::cout << "All tests passed successfully.\n";

    return 0;
}




/*

Explanations to static member float const pi_{3.14159}:

1. float const pi_{3.14159}; 
Works correctly: const means the value of pi_ is constant for 
each object and cannot be modified after it is initialized. 
However, each instance of the Sphere class will have its own copy of pi_.
Why it works: const guarantees immutability but doesn’t provide global or 
compile-time access. Every object of Sphere gets its own version of pi_, 
but its value is constant for that object.

2. constexpr float pi_{3.14159};
Breaks: constexpr implies that pi_ is both immutable and must be evaluated 
at compile time. It cannot be used as a non-static member because 
non-static members are tied to an instance of the class, and their 
initialization is deferred to runtime when an object is constructed.
Why it breaks: constexpr is only valid for compile-time constants. 
A constexpr variable in this context must be declared static because 
constexpr at the class level requires the variable to be shared among 
all instances and evaluated at compile time.

3. static const float pi_;
Define the static member outside the class: const float Sphere::pi_{3.14159};
Works correctly: static const means pi_ is shared across all instances of the 
Sphere class and remains immutable. 
Why it works: static ensures the variable is shared across all instances of the class.
const ensures immutability. The initialization outside the class definition provides a 
single definition for the variable.

4. static constexpr float pi_{3.14159};
Works correctly:    static constexpr allows pi_ to be a compile-time constant and shared 
across all instances.
Why it works: constexpr ensures compile-time evaluation. static ensures the value is shared 
among all objects. Unlike static const, static constexpr can be initialized directly within 
the class definition (no need for external definition).


*** Recommended Approach ***
    •   Use static constexpr if:
        •   You need a compile-time constant.
        •   You want to avoid an external definition.
    •   Use static const if:
        •   Compile-time evaluation isn’t strictly necessary.
        •   You prefer more traditional constant declaration with an external definition.

*/



// Change Sphere class by adding Static methods:

#include <cassert>
#include <cmath>
#include <stdexcept>
#include <iostream>

class Sphere {
 public:
  // Constructor
  Sphere(int radius) : radius_(radius), volume_(CalculateVolume(radius)) {
    if (radius <= 0) throw std::invalid_argument("radius must be positive");
  }

  // Accessors
  int Radius() const { return radius_; }
  float Volume() const { return volume_; }

  // Mutator
  void Radius(int radius) {
    if (radius <= 0) throw std::invalid_argument("radius must be positive");
    radius_ = radius;
    volume_ = CalculateVolume(radius);
  }

  // Static function to calculate the volume of a sphere
  static float CalculateVolume(int radius) {
    if (radius <= 0) throw std::invalid_argument("radius must be positive");
    return (4.0 / 3.0) * pi_ * std::pow(radius, 3);
  }

 private:
  static constexpr float pi_{3.14159};
  int radius_;
  float volume_;
};

// Test
int main() {
  // Test the static CalculateVolume function directly
  assert(std::abs(Sphere::CalculateVolume(5) - 523.6) < 1);

  // Test creating a Sphere object
  Sphere sphere(5);
  assert(sphere.Radius() == 5);
  assert(std::abs(sphere.Volume() - 523.6) < 1);

  // Test modifying radius
  sphere.Radius(3);
  assert(sphere.Radius() == 3);
  assert(std::abs(sphere.Volume() - 113.1) < 1);

  // Test invalid radius in constructor
  bool caught = false;
  try {
    Sphere invalid(-1);
  } catch (const std::invalid_argument&) {
    caught = true;
  }
  assert(caught);

  // Test invalid radius in CalculateVolume
  caught = false;
  try {
    Sphere::CalculateVolume(-1);
  } catch (const std::invalid_argument&) {
    caught = true;
  }
  assert(caught);

  std::cout << "All tests passed successfully.\n";

  return 0;
}



/* Explanations: 

1.  Moved Volume Calculation to CalculateVolume:
    •   The formula for the volume of a sphere is now 
        encapsulated in the static function CalculateVolume.
    •   This function is independent of any specific Sphere 
        instance and can be called directly from the class.
2.  Constructor Calls CalculateVolume:
    •   The constructor uses CalculateVolume to compute the 
        volume of the sphere when it is instantiated.
3.  Mutator Calls CalculateVolume:
    •   The Radius mutator also uses CalculateVolume to update 
        the volume when the radius changes.
4.  Static Function Is Public:
    •   The CalculateVolume function is declared public so it can 
        be called directly from outside the class.
5.  Direct Static Call in main:
    •   The CalculateVolume function is directly called in main() 
        to compute the volume of a hypothetical sphere with radius 5 without instantiating a Sphere object.

*/

