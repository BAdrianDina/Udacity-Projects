#include <cassert>
#include <stdexcept>
#include <iostream>
#include <cmath>

class Pyramid {
public:
    // Constructor
    Pyramid(double length, double width, double height) 
        : length_(length), width_(width), height_(height) {
        ValidateDimensions();
    }

    // Accessors
    double Length() const;
    double Width() const;
    double Height() const;

    // Mutators
    void Length(double length);
    void Width(double width);
    void Height(double height);

    // Calculate Volume
    double Volume() const;

    // Optional: Calculate Surface Area
    double SurfaceArea() const;

private:
    double length_, width_, height_;

    // Validate dimensions to ensure they are positive
    void ValidateDimensions() const;
};


// Accessors:
double Pyramid::Length() const { return length_; }
double Pyramid::Width() const { return width_; }
double Pyramid::Height() const { return height_; }

// Mutators
void Pyramid::Length(double length) {
    length_ = length;
    ValidateDimensions();
}

void Pyramid::Width(double width) {
    width_ = width;
    ValidateDimensions();
}

void Pyramid::Height(double height) {
    height_ = height;
    ValidateDimensions();
}


// Calculate Volume
double Pyramid::Volume() const {
    return (length_ * width_ * height_) / 3.0;
}

// Optional: Calculate Surface Area
double Pyramid::SurfaceArea() const {
    double base_area = length_ * width_;
    double slant_height_a = std::sqrt(std::pow(height_, 2) + std::pow(width_ / 2.0, 2));
    double slant_height_b = std::sqrt(std::pow(height_, 2) + std::pow(length_ / 2.0, 2));
    double side_area_a = length_ * slant_height_a / 2.0;
    double side_area_b = width_ * slant_height_b / 2.0;
    return base_area + 2 * side_area_a + 2 * side_area_b;
}

// Validate dimensions to ensure they are positive
void Pyramid::ValidateDimensions() const {
    if (length_ <= 0 || width_ <= 0 || height_ <= 0) {
        throw std::invalid_argument("Length, width, and height must be positive.");
    }
}


// Test
int main() {
    // Valid Pyramid
    Pyramid pyramid(4, 5, 6);
    assert(pyramid.Length() == 4);
    assert(pyramid.Width() == 5);
    assert(pyramid.Height() == 6);
    assert(pyramid.Volume() == 40);

    // Invalid Pyramid
    bool caught{false};
    try {
        Pyramid invalid(-1, 2, 3);
    } catch (const std::invalid_argument &e) {
        caught = true;
    }
    assert(caught);

    // Testing Surface Area (Optional)
    std::cout << "Surface Area: " << pyramid.SurfaceArea() << "\n";
    std::cout << "All tests passed.\n";

    return 0;
}