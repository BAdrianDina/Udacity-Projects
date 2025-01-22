#include <iostream>
#include <cmath>
#include <cassert>


/*
Explanations: 

    1.  Defining pi: The macro PI is defined as 3.14159.
    2.  LineSegment Struct:
        •   Represents a line segment with a single attribute length.
    3.  Circle Class:
        •   Composed of a LineSegment that represents the radius of the circle.
        •   Constructor:
        •   Accepts a LineSegment object and initializes the radius.
        •   setRadius Method:
        •   Updates the radius of the circle by setting a new LineSegment.
    4.  Main Function:
        •   Creates a LineSegment with a length of 3.
        •   Creates a Circle object using the LineSegment.
        •   Verifies the circle’s area is approximately  28  using an assert.
        •   Prints the area of the circle and confirms the test passed.
*/





// Define pi using a macro
#define PI 3.14159

// Define LineSegment struct
struct LineSegment {
    double length;
};

// Define Circle class
class Circle {
public:
    // Constructor
    Circle(const LineSegment& radius) : radius_(radius) {}

    // Setter for radius
    void setRadius(const LineSegment& radius) {
        radius_ = radius;
    }

    // Getter for area
    double Area() const {
        return PI * std::pow(radius_.length, 2);
    }

private:
    LineSegment radius_;
};

// Test in main()
int main() {
    // Create a LineSegment with length 3
    LineSegment radius{3};

    // Create a Circle with the LineSegment as its radius
    Circle circle(radius);

    // Test the area of the circle
    assert(int(circle.Area()) == 28); // Check if area is approximately 28
    std::cout << "Circle area: " << circle.Area() << "\n";

    std::cout << "All tests passed successfully.\n";
    return 0;
}