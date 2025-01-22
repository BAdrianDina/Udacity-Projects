#include <cassert>
#include <stdexcept>
#include <string>
#include <iostream>

class Student {
public:
    // Constructor
    Student(const std::string& name, int grade, double gpa) 
        : name_(name), grade_(grade), gpa_(gpa) {
        ValidateGrade(grade_);
        ValidateGPA(gpa_);
    }

    // Accessors
    std::string GetName() const { return name_; }
    int GetGrade() const { return grade_; }
    double GetGPA() const { return gpa_; }

    // Mutators
    void SetName(const std::string& name) { name_ = name; }
    void SetGrade(int grade) {
        ValidateGrade(grade);
        grade_ = grade;
    }

    void SetGPA(double gpa) {
        ValidateGPA(gpa);
        gpa_ = gpa;
    }

private:
    std::string name_;
    int grade_;
    double gpa_;

    // Private validation functions
    void ValidateGrade(int grade) const {
        if (grade < 0 || grade > 12) {
            throw std::invalid_argument("Grade must be between 0 (kindergarten) and 12.");
        }
    }

    void ValidateGPA(double gpa) const {
        if (gpa < 0.0 || gpa > 4.0) {
            throw std::invalid_argument("GPA must be between 0.0 and 4.0.");
        }
    }
};

// Test
int main() {
    try {
        // Create a valid Student object
        Student student("Alice", 10, 3.8);
        
        assert(student.GetName() == "Alice");
        assert(student.GetGrade() == 10);
        assert(student.GetGPA() == 3.8);

        // Modify Student attributes
        student.SetName("Bob");
        student.SetGrade(12);
        student.SetGPA(4.0);

        assert(student.GetName() == "Bob");
        assert(student.GetGrade() == 12);
        assert(student.GetGPA() == 4.0);

        // Test invalid grade
        bool caught = false;
        try {
            student.SetGrade(13);  // Invalid grade
        } catch (const std::invalid_argument& e) {
            caught = true;
        }
        assert(caught);

        // Test invalid GPA
        caught = false;
        try {
            student.SetGPA(4.5);  // Invalid GPA
        } catch (const std::invalid_argument& e) {
            caught = true;
        }
        assert(caught);

        std::cout << "All tests passed successfully.\n";

    } catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << "\n";
    }

    return 0;
}