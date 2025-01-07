#include <iostream>
#include <string>

class BankAccount
{
  private:
    // TODO: declare member variables:
    std::string account_number;
    std::string owner_name;
    double available_funds;

  public:
    // TODO: declare setters & getters:
    BankAccount(const std::string &account_number, const std::string &owner_name, double available_funds)
        : account_number(account_number), owner_name(owner_name), available_funds(available_funds) {}

    // Setter for account_number
    void setAccountNumber(const std::string &account_number);

    // Getter for account_number
    std::string getAccountNumber() const;

    // Setter for owner_name
    void setOwnerName(const std::string &owner_name);

    // Getter for owner_name
    std::string getOwnerName() const;
    
    // Setter for available_funds
    void setAvailableFunds(double funds); 

    // Getter for available_funds
    double getAvailableFunds() const; 
    
    // Display account information
    void displayAccountInfo() const;
    
};

// TODO: implement setters
void BankAccount::setAccountNumber(const std::string &account_number) {
        this->account_number = account_number;
}

void BankAccount::setOwnerName(const std::string &owner_name) {
        this->owner_name = owner_name; 
}

void BankAccount::setAvailableFunds(double funds) {
        if (funds >= 0) { // Ensure funds are non-negative
            available_funds = funds;
        } else {
            std::cerr << "Funds cannot be negative.\n";
        }
}

void BankAccount::displayAccountInfo() const {
        std::cout << "Account Number: " << account_number << "\n";
        std::cout << "Owner Name: " << owner_name << "\n";
        std::cout << "Available Funds: $" << available_funds << "\n";
    }

// TODO: implement getters
std::string BankAccount::getAccountNumber() const { return account_number; }
std::string BankAccount::getOwnerName() const { return owner_name; }
double BankAccount::getAvailableFunds() const { return available_funds; }





int main(){
    // TODO: instantiate and output a bank account
    
    // Create a bank account instance
    BankAccount account("123456789", "Alice Johnson", 1500.75);

    // Display account information
    account.displayAccountInfo();

    // Update account details
    account.setOwnerName("Alice J.");
    account.setAvailableFunds(2000.50);

    // Display updated account information
    std::cout << "\nUpdated Account Information:\n";
    account.displayAccountInfo();
    
    return 0;
    
}