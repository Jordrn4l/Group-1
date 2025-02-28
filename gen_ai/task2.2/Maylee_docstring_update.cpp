/// @author Maylee Del Rio

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;


int main() {
// OLD COMMENTS
//    // local constant  definiton(s)
//    const int JAN = 1;
//    const int FEB = 2;
//    const int DEC = 12;
//    const int MON = 0;
//    const int TUE = 1;
//    const int WED = 2;
//    const int THU = 3;
//    const int FRI = 4;
//    const int SAT = 5;
//    const int SUN = 6;
//
//    // local variable declaration(s)
//    int year;
//    int month;
//    int day;
//    int weekday;
//    string name;
//    bool valid;
//    bool is_leapyear;
//
//
//    do {                                               // do while loop
//        cout << "Enter year: ";
//        cin >> year;
//        valid = year > 1752;
//
//       } while (!valid);
//        cout << endl;
//
//       if (!(year % 4 == 0)) {
//        is_leapyear = false;
//    } else if (!(year % 100 == 0)) {
//        is_leapyear = true;
//    } else if (!(year % 400 == 0)) {
//        is_leapyear = false;
//    } else {
//        is_leapyear = true;
//    }
//
//   if  (month == JAN || month == FEB )
//        { month = month + 12;
//        year = year - 1; }
//
//    weekday = (day + (13 * ((month + 1)) / 5) + year +
//              (year / 4) - (year / 100) + (year / 400) +5)% 7;
//
//
//    return 0;

// UPDATED COMMENTS
    // Define local constants representing months and days to be used in calendar calculations.
    const int JAN = 1;  // JAN is set to 1 to represent January
    const int FEB = 2;  // FEB is set to 2 to represent February
    const int DEC = 12; // DEC is set to 12 to represent December

    // Define constants for weekdays with assigned numerical values for potential use in weekday calculations.
    const int MON = 0;  // MON represents Monday with a value of 0
    const int TUE = 1;  // TUE represents Tuesday with a value of 1
    const int WED = 2;  // WED represents Wednesday with a value of 2
    const int THU = 3;  // THU represents Thursday with a value of 3
    const int FRI = 4;  // FRI represents Friday with a value of 4
    const int SAT = 5;  // SAT represents Saturday with a value of 5
    const int SUN = 6;  // SUN represents Sunday with a value of 6

    // Declare local variables to hold user input and computed values.
    int year;         // Variable to store the input year
    int month;        // Variable to store the month (used later in weekday calculation)
    int day;          // Variable to store the day (used later in weekday calculation)
    int weekday;      // Variable to hold the computed day of the week as an integer (0-6)
    string name;      // Variable to hold a string, purpose not explicitly defined in this code snippet
    bool valid;       // Boolean flag to indicate whether the entered year is valid (must be greater than 1752)
    bool is_leapyear; // Boolean flag to indicate whether the entered year is a leap year

    // Input loop: Continues to prompt the user for a year until a valid year (> 1752) is entered.
    do {
        cout << "Enter year: ";      // Prompt the user to enter a year
        cin >> year;                 // Read the user input and store it in the variable 'year'
        valid = year > 1752;         // Check if the year is greater than 1752 (to account for calendar reforms)
    } while (!valid);                // If the year is not valid, the loop repeats
    cout << endl;                    // Output a newline for cleaner formatting

    // Determine whether the provided year is a leap year using conditional statements.
    // The logic follows these rules:
    // 1. If the year is not divisible by 4, it's not a leap year.
    // 2. If it is divisible by 4 but not by 100, it's a leap year.
    // 3. If it is divisible by 100 but not by 400, it's not a leap year.
    // 4. If it is divisible by 400, it is a leap year.
    if (!(year % 4 == 0)) {            // Check if the year is not divisible by 4.
        is_leapyear = false;           // If true, the year is not a leap year.
    } else if (!(year % 100 == 0)) {     // Otherwise, if the year is not divisible by 100.
        is_leapyear = true;            // It is a leap year.
    } else if (!(year % 400 == 0)) {     // Otherwise, if the year is not divisible by 400.
        is_leapyear = false;           // It is not a leap year.
    } else {
        is_leapyear = true;            // If none of the above conditions apply, the year is a leap year.
    }

    // Adjust the month and year if the month is January or February.
    // This adjustment is required for the algorithm (similar to Zeller's Congruence) used to calculate the day of the week.
    if (month == JAN || month == FEB) {
        month = month + 12;          // For calculation, January and February are treated as the 13th and 14th month of the previous year.
        year = year - 1;             // Decrease the year by 1 to reflect the shift of January and February to the previous year.
    }

    // Calculate the day of the week using an algorithm similar to Zeller's Congruence.
    // The formula factors in the day, month, year, and leap year corrections, and then applies modulus 7 to map it to a weekday.
    weekday = (day + (13 * ((month + 1)) / 5) + year +
              (year / 4) - (year / 100) + (year / 400) + 5) % 7;

    return 0;   // End of the main function. Return 0 to indicate that the program executed successfully.
}

