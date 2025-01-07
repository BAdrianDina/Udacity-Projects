#include <cassert>

class Date {
public:
  Date(int day, int month, int year);
  int Day() const { return day_; }
  void Day(int day);
  int Month() const { return month_; }
  void Month(int month);
  int Year() const { return year_; }
  void Year(int year);

private:
  int day_{1};
  int month_{1};
  int year_{0};
    
  // Private helper function to calculate the number of days in a month
  int DaysInMonth(int month, int year) const;
  bool IsLeapYear(int year) const;
    
};

Date::Date(int day, int month, int year) {
  Year(year);
  Month(month);
  Day(day);
}

void Date::Day(int day) {
  if (day >= 1 && day <= DaysInMonth(month_, year_))
    day_ = day;
}

void Date::Month(int month) {
  if (month >= 1 && month <= 12) {
    month_ = month;
    // Adjust the day if it exceeds the number of days in the new month
    if (day_ > DaysInMonth(month_, year_)) {
      day_ = DaysInMonth(month_, year_);
    }
  }
}

void Date::Year(int year) { 
    year_ = year;
    // Adjust the day if it exceeds the number of days in the current month and year
    if (day_ > DaysInMonth(month_, year_)) {
        day_ = DaysInMonth(month_, year_);
    }
}


// Private function to calculate the number of days in a month
int Date::DaysInMonth(int month, int year) const {
  const int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  // February adjustment for leap years
  if (month == 2 && IsLeapYear(year)) {
    return 29;
  }

  return days_in_month[month - 1];
}

// Private function to determine if a year is a leap year
bool Date::IsLeapYear(int year) const {
  return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}






// Test
int main() {
  Date date(29, 8, 1981);
  assert(date.Day() == 29);
  assert(date.Month() == 8);
  assert(date.Year() == 1981);
}