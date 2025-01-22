#include <cassert>

/*
Explanation: 

1.  Template Function:
    •   The template <typename T> declaration allows the Product 
        function to work with any data type (T) that supports multiplication (*).
    •   The T parameter is a placeholder for the type, which is replaced at 
        compile time.
2.  Function Definition:
    •   The Product function takes two parameters of type T and returns their product.
3.  Testing in main:
    •   Calls Product with integers (int), verifying that the function 
        computes the correct result.
    •   Optionally tests Product with other types, like double, to demonstrate 
        flexibility.

*/


// Create a generic function Product
template <typename T>
T Product(T a, T b) {
    return a * b;
}

int main() { 
    // Test Product with integers
    assert(Product<int>(10, 2) == 20);

    // Test Product with doubles (optional additional test)
    assert(Product<double>(2.5, 4.0) == 10.0);

    return 0;
}