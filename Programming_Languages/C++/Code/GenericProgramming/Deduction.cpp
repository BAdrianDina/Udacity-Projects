#include <cassert>

/*
Explanations:

1.  Template Function:
    •   The template <typename T> allows the average function to accept 
        arguments of any numeric type (T).
    •   T is the type placeholder, which is resolved at compile time based 
        on the input arguments.
2.  Function Definition:
    •   average takes two parameters of type T, computes their sum, and divides 
        by 2 to calculate the average.
3.  Testing in main:
    •   Confirms the average of 2.0 and 5.0 is 3.5.
    •   Additional tests verify the function works with integers and doubles.

*/

// Declare a generic, templatized average function
template <typename T>
T average(T a, T b) {
    return (a + b) / 2;
}

int main() {
    // Test the average function
    assert(average(2.0, 5.0) == 3.5);

    // Additional tests (optional)
    assert(average(10, 20) == 15); // Works with integers
    assert(average(4.5, 3.5) == 4.0); // Works with doubles

    return 0;
}