#include <cassert>

/*
Explanations:

1.  Template Function:
    •   template <typename T> declares a generic template function.
    •   T is the type placeholder, allowing the Max function to work with 
        any type that supports the comparison operator (>).
2.  Function Definition:
    •   The Max function takes two parameters of type T.
    •   It compares the two values using the ternary operator (? :) and 
        returns the larger value.
3.  Testing in main:
    •   Verifies that Max works correctly with int by asserting that the 
        maximum of 10 and 50 is 50.
    •   Verifies that Max works correctly with double by asserting that the 
        maximum of 5.7 and 1.436246 is 5.7.

*/

// Declare a generic, templatized function Max
template <typename T>
T Max(T a, T b) {
    return (a > b) ? a : b;
}

int main() { 
    // Test Max with integers
    assert(Max<int>(10, 50) == 50);

    // Test Max with doubles
    assert(Max<double>(5.7, 1.436246) == 5.7);

    return 0;
}