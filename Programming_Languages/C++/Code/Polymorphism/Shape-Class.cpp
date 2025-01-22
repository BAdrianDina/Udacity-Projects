#include <cassert>
#include <cmath>
#include <iostream>


/*
Explanations:

1.  Abstract Class Shape:
    •   Serves as the base class for all shapes.
    •   Contains two pure virtual functions:
    •   Area(): Computes the area of the shape.
    •   Perimeter(): Computes the perimeter of the shape.
    •   Declares a virtual destructor to ensure proper cleanup of derived class objects.
2.  Class Rectangle:
    •   Inherits publicly from Shape.
    •   Adds private attributes width_ and height_.
    •   Implements the Area() and Perimeter() methods to compute the respective values.
3.  Class Circle:
    •   Inherits publicly from Shape.
    •   Adds a private attribute radius_.
    •   Implements the Area() and Perimeter() methods using the formulas:
    •   Area:  \pi r^2 
    •   Perimeter:  2\pi r 
4.  Main Function Tests:
    •   Creates a Circle object and verifies its Area() and Perimeter() using 
        assertions with a floating-point tolerance (epsilon).
    •   Creates a Rectangle object and verifies its Area() and Perimeter() with 
        exact comparisons.

Key Concepts: 
1.Pure Virtual Functions:
    •   Used to enforce a contract in the base class (Shape) for derived classes 
        to implement specific functionality.
2. Polymorphism:
    •   The Area() and Perimeter() methods are called dynamically on derived class 
        objects through the overridden implementations.
3. Floating-Point Comparisons:
    •   Used a small epsilon value to compare floating-point results due to precision 
        issues in calculations.

*/


// Define pi
#define PI 3.14159

// Define the abstract class Shape
class Shape {
public:
    // Pure virtual functions for Area and Perimeter
    virtual double Area() const = 0;
    virtual double Perimeter() const = 0;

    // Virtual destructor for proper cleanup of derived classes
    virtual ~Shape() {}
};

// Define Rectangle to inherit publicly from Shape
class Rectangle : public Shape {
public:
    // Constructor
    Rectangle(double width, double height) : width_(width), height_(height) {}

    // Override Area()
    double Area() const override {
        return width_ * height_;
    }

    // Override Perimeter()
    double Perimeter() const override {
        return 2 * (width_ + height_);
    }

private:
    double width_;
    double height_;
};

// Define Circle to inherit from Shape
class Circle : public Shape {
public:
    // Constructor
    Circle(double radius) : radius_(radius) {}

    // Override Area()
    double Area() const override {
        return PI * std::pow(radius_, 2);
    }

    // Override Perimeter()
    double Perimeter() const override {
        return 2 * PI * radius_;
    }

private:
    double radius_;
};

// Test in main
int main() {
    double epsilon = 0.1; // Useful for floating-point equality comparisons

    // Test Circle
    Circle circle(12.31);
    assert(std::abs(circle.Perimeter() - 77.35) < epsilon);
    assert(std::abs(circle.Area() - 476.06) < epsilon);

    // Test Rectangle
    Rectangle rectangle(10, 6);
    assert(rectangle.Perimeter() == 32);
    assert(rectangle.Area() == 60);

    std::cout << "All tests passed successfully.\n";
    return 0;
}