/*
In C++, friend classes provide an alternative inheritance 
mechanism to derived classes. The main difference between 
classical inheritance and friend inheritance is that a friend 
class can access private members of the base class, which isn't 
the case for classical inheritance. In classical inheritance, 
a derived class can only access public and protected members of 
the base class.

Explanations: 

1.	Friend Relationship:
	•	Square declares Rectangle as a friend class, allowing Rectangle to 
		access its private attributes.
	•	This relationship is explicitly defined using the friend keyword inside 
		the Square class.
2.	Square Class:
	•	Contains a private attribute side_ representing the length of the square’s side.
	•	Provides a public constructor to initialize side_.
3.	Rectangle Class:
	•	Contains private attributes width_ and height_.
	•	Provides a public constructor that accepts a Square object and initializes 
		width_ and height_ using Square’s private attribute side_.
	•	Provides an Area() method to calculate the rectangle’s area as  
		width * height.
4. Constructor of Rectangle:
	•	Defined outside the class using the scope resolution operator (::).
	•	Accesses the private attribute side_ of the Square object (allowed due to 
		the friend relationship).
5.	Area Method:
	•	Calculates the area of the rectangle using the formula:
		Area = width * height.
6. Main Function:
	•	Creates a Square object with side 4.
	•	Uses the Square object to initialize a Rectangle.
	•	Asserts that the rectangle’s area is 16.
*/



#include <cassert>

// Declare class Rectangle
class Rectangle;

// Define class Square
class Square {
public:
    // Constructor to initialize side
    Square(int side) : side_(side) {}

    // Declare Rectangle as a friend class
    friend class Rectangle;

private:
    int side_; // Private attribute for Square
};

// Define class Rectangle
class Rectangle {
public:
    // Constructor that takes a Square
    Rectangle(const Square& square);

    // Method to compute the area of the Rectangle
    int Area() const;

private:
    int width_;
    int height_;
};

// Define Rectangle's constructor that takes a Square
Rectangle::Rectangle(const Square& square)
    : width_(square.side_), height_(square.side_) {}

// Define Area() method for Rectangle
int Rectangle::Area() const {
    return width_ * height_;
}

// Test in main
int main() {
    Square square(4);               // Create a Square with side 4
    Rectangle rectangle(square);    // Create a Rectangle from the Square
    assert(rectangle.Area() == 16); // Verify the area is correct
    return 0;
}