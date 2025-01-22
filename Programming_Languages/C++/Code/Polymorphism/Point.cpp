#include <cassert>
#include <iostream>



/*
Explanations:

1.  Attributes:
    •   x and y are public attributes representing the coordinates of a Point.
2.  Constructor:
    •   Initializes the x and y attributes with given values.
3.  Overloaded + Operator:
    •   Defined as a member function.
    •   Takes a Point object as an argument.
    •   Creates and returns a new Point object with the x and y coordinates being 
        the sum of the respective coordinates of the two points.
4. Tests in main:
    •   Two Point objects (p1 and p2) are created.
    •   The overloaded + operator is used to compute a new Point (p3).
    •   Assertions verify that the new point’s coordinates are correct.
*/

class Point {
public:
    // Attributes
    int x;
    int y;

    // Constructor
    Point(int x_val, int y_val) : x(x_val), y(y_val) {}

    // Overload + operator
    Point operator+(const Point& other) const {
        return Point(this->x + other.x, this->y + other.y);
    }
};

// Test in main
int main() {
    // Create two points
    Point p1(10, 5), p2(2, 4);

    // Add points using the overloaded + operator
    Point p3 = p1 + p2;

    // Verify results
    assert(p3.x == p1.x + p2.x);
    assert(p3.y == p1.y + p2.y);

    // Optional: Print the results to confirm
    std::cout << "p3.x: " << p3.x << ", p3.y: " << p3.y << std::endl;

    std::cout << "All tests passed successfully." << std::endl;

    return 0;
}