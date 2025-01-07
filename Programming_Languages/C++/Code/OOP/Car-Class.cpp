#include <string>
#include <cstring>
#include <iostream>

class Car {
    // TODO: Declare private attributes
    private:
    // Member variables
    int horsepower;
    float weight;
    char brand[50]; // Brand as a C-style string (character array)
        
    // TODO: Declare getter and setter for brand
    public:
    void SetHorsepower(int hp);
    void SetWeight(float wt);
    void SetBrand(const std::string &b);
    
    int GetHorsepower() const;
    float GetWeight() const;
    std::string GetBrand() const;
    
        
};

// Define setters
void Car::SetHorsepower(int hp) {
    horsepower = hp;
}
// Setter for weight
void Car::SetWeight(float wt) {
    weight = wt;
}

// Setter for brand
void Car::SetBrand(const std::string &b) {
    // Convert std::string to C-style string (character array)
    std::strncpy(brand, b.c_str(), sizeof(brand) - 1);
    brand[sizeof(brand) - 1] = '\0'; // Ensure null-termination
}

    

// Define getters
int Car::GetHorsepower() const { return horsepower; }

// Getter for weight
float Car::GetWeight() const { return weight; }

// Getter for brand
std::string Car::GetBrand() const { return std::string(brand); }


// Test in main()
int main() 
{
    Car car;
    car.SetBrand("Peugeot");
    std::cout << car.GetBrand() << "\n";   
}