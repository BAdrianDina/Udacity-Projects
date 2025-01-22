#include <cassert>
#include <string>
#include <sstream>


/*
Description:
1.  Template Specification:
    •   The template <typename KeyType, typename ValueType> line specifies 
        the Mapping class as a template.
    •   KeyType and ValueType are placeholders for the types of the key and 
        value, respectively.
2.  Constructor:
    •   Accepts key and value of the specified types KeyType and ValueType and 
        initializes the corresponding member variables.
3.  Print Method:
    •   Uses std::ostringstream to concatenate the key and value into a 
        formatted string with the format key: value.
4.  Main Function:
    •   Instantiates the Mapping class with a std::string key and an int value.
    •   Uses assert to verify that the Print method outputs the expected string.
    •   Includes an additional test case to verify the flexibility of the template.

Key Concepts:
1. Class Templates:
    •   Enable the definition of classes that operate on generic types 
        (KeyType and ValueType in this example).
2. String Formatting:
    •   Uses std::ostringstream to format and concatenate strings and values.
3. Type Safety:
    •   Ensures that the class operates correctly with the specified types  
        during instantiation.


*/

// Add the correct template specification
template <typename KeyType, typename ValueType>
class Mapping {
public:
    // Constructor
    Mapping(KeyType key, ValueType value) : key(key), value(value) {}

    // Print function
    std::string Print() const {
        std::ostringstream stream;
        stream << key << ": " << value;
        return stream.str();
    }

    // Public attributes
    KeyType key;
    ValueType value;
};

// Test
int main() {
    Mapping<std::string, int> mapping("age", 20);
    assert(mapping.Print() == "age: 20");

    // Additional test
    Mapping<int, double> another_mapping(42, 3.14);
    assert(another_mapping.Print() == "42: 3.14");

    return 0;
}