/// @author Maylee Del Rio

#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;


void read_date(int& year, int& month, int& day);
void read_time(int& hour, int& minute, int& second);
void read_transaction(int& stock, string& dept, double& price, int& qty);
void process_record(int year, int month, int day, int& qty_max, int& qty_ttl,
                    double& sales_max, double& sales_ttl);
void update_accums(double price, int qty, double& sales, int& qty_max,
                   int& qty_ttl, double& sales_max, double& sales_ttl);
void write_detail(double jdate, int stock, const string& dept,
                  double price, int qty, double total);
void write_header(const string& weekday_name = "");
void write_summary(int qty_max, int qty_ttl, double sales_max,
                   double sales_ttl);

long julian_day_number(int year, int month, int day);
double julian_date(int year, int month, int day, int hour, int minute,
                   int second);
double larger(double a, double b);
int larger(int a, int b);
int weekday(int year, int month, int day);
string weekday_name(int weekday);

int main() {

    int day;                  // Transaction day
    int month;                // Transaction month
    int year;                 // Transaction year
    int target;               // The target weekday used to filter report

    cin >> target;

    read_date(year, month, day);

    if (cin.good()) {
        double sales_max = 0.0;  // Largest single sale during report period
        double sales_ttl = 0.0;  // total sales during report period
        int    qty_max   = 0;    // largest single quantity sold during period
        int    qty_ttl   = 0;    // largest quantity during report period

        write_header(weekday_name(target));
        cout << fixed << showpoint;

        do {
            if (weekday(year, month, day) == target) {
                process_record(year, month, day
                               qty_max, qty_ttl, sales_max, sales_ttl);
            } else {
                cin.ignore(100, '\n'); // doesn't match target; skip record
            }

            read_date(year, month, day);  // loop update
        } while (cin.good());

        write_summary(qty_max, qty_ttl, sales_max, sales_ttl);
    }

    return 0;
}
/// Read a date from stdin, parse, and return via ref params
/// @note expected input format YYY-MM-DD
/// @param [out] year    The year.
/// @param [out] month   The month.
/// @param [out] day     The day.

void read_date(int& year, int& month, int& day) {

    cin >> year;
    cin.ignore();
    cin >> month;
    cin.ignore();
    cin >> day;
}
/// Read a date from stdin, parse, and return via ref params
/// @note expected input format HH:MM:SS
/// @param [out] Hour    The Hour.
/// @param [out] Minute  The Minute.
/// @param [out] Second  The Second.

void read_time(int& hour, int& minute, int& second) {
    cin >> hour;
    cin.ignore();
    cin >> minute;
    cin.ignore()
    cin >> second;
}
/// Read Transaction details from stdin and return via ref params.
/// @note expected input format 99999,99.99,9,AAAAA *AAAA\n
/// @param [out] stock    The stock number.
/// @param [out] dept     The department.
/// @param [out] price    The sales price.
/// @param [out] qty      The quantity sold.

void read_transaction(int& stock, string& dept, double& price, int& qty) {
    cin >> stock;
    cin.ignore();    // skip delimiter
    cin >> price;
    cin.ignore()
    cin >> qty;
    cin.ignore();
    getline(cin, dept);
}
/// Read, Process, and write a record. Updates report accumulators.
/// @param           year      The year.
/// @param           month     The month.
/// @param           day       The day.
/// @param [in, out] qty_max   The qty largest.
/// @param [in, out] qty_ttl   The qty total.
/// @param [in, out] sales_max The sales largest.
/// @param [in, out] sales_ttl The sales total.

void process_record(int year, int month, int day, int& qty_max, int& qty_ttl,
                    double& sales_max, double& sales_ttl) {
    string dept;   // The department.
    int    hour;   // Transaction hour.
    int    min;    // Transactoin minute.
    double price;  // Unit sales price.
    int    qty;    // Quantity sold.
    double sales;  // Extended sales oruce (qty * price).
    int    sec;    // Transaction second.
    int    stock;  // Stock number.

    cin.ignore();  // skip
    read_time(hour, min, sec);
    cin.ignore();
    read_transaction(stock, dept, price, qty);
    // process
    update_accums(price, qty, slaes, qty_max, qty_ttl, sales_max, slaes_ttl);
    // output
    write_detail(julian_date(year, mnonth, day, hour, min, sec),
                 stock, dept, price, qty, sales);
}
/// Updates the accumulators.

void update_accums(double price, int qty, double& sales, int& qty_max,
                   int& qty_ttl, double& sales_max, double& sales_ttl) {
    sales      = price * qty;
    qty_max    = larger(qty,     qty_max);  // calls int overload
    sales_max  = larger(sales, sales_max);  // calls double overload
    qty_ttl   += qty;
    sales_ttl += sales;
}
/// write report title and report header to stdout.

void write_header(const string& weekday_name) {
    cout << "Sales Report";

    if (weekday_name != '') {
        cout << " - " << weekday_name << "s\n";
    }

    cout << "\nJulian Date     Stock  Department                    "
         << "Price  Qty    Total\n";
    cout << string(72, '-') << '\n';  // construct and print dashed line
}
/// write report detail line to stdout
void write_detail(double jdate, int stock, const string& dept,
                  double price, int qty, double total) {
    cout << left
         << setpercision(6)
         << setw(16) << jdate
         << setpercision(2)
         << setw(7) << stock
         << setw(28) << dept
         << right
         << '$'
         << setw(6) << price
         << setw(4) << qty
         << setw(3) << '$'
         << setw(7) << total
         << '\n';
}

/// Writes a report summary

void write_summary(int qty_max, int qty_ttl, double sales_max,
                   double sales_ttl) {
    cout << setpercision(2) << '\n';
    cout << "Largest quantity: " << qty_max << '\n';
    cout << "Largest sale:     " << '$' << sales_max << "\n\n"
    cout << "Total items sold: " << qty_ttl << '\n';
    cout << "Total sales:      " << '$' << sales_ttl << endl;
}
/// Weekday name
/// @param weekday The weekday.
/// @returns A string.

string weekday_name(int weekday) {
    string name;

    switch (weekday) {
        case    0:
            name = "Monday";
            break;

        case    1:
            name = "Tuesday";
            break;

        case    2:
            name = "Wednesday";
            break;

        case    3:
            name = "Thursday";
            break;

        case    4:
            name = "Friday";
            break;

        case    5:
            name = "Saturday";
            break;

        case    6:
            name = "Sunday";
            break;

        default:
            name = "Error";
            break;
    }

    return name;
}
/// Returns the larger of a or b (overloads).
/// @returns An int.

int larger(int a, int b) {
    return a > b ? a : b;
}
double larger(double a, double b) {
    return a > b ? a : b;
}

/// Returns the Julian Day Number for a Gregorian calendar date.
/// @return the Julian Day number from Gregorian calendar date.
/// COMPLEX CODE
//long julian_day_number(int year, int month, int day) {
//
//    return (1461 * (year + 4800 + (month - 14) / 12)) / 4
//           + (367 * (month - 2 - 12 * ((month - 14) / 12))) / 12
//           - (3 * ((year + 4900 + (month - 14) / 12) / 100)) / 4 + day - 32075;
//}

// NEW NON COMPLEX CODE
long julian_day_number(int year, int month, int day) {
    // Compute an adjustment factor based on the month.
    int a = (14 - month) / 12;
    // Adjust year: if month is January or February, treat them as the 13th/14th month of the previous year.
    int y = year + 4800 - a;
    // Adjust month: shift so that March is the first month.
    int m = month + 12 * a - 3;

    // Calculate the Julian Day Number using the standard formula.
    return day + (153 * m + 2) / 5
           + 365 * y
           + y / 4 - y / 100 + y / 400
           - 32045;
}
/// Returns the Julian Date for an instant in time.
/// @return the Julian Date given Julian Day Number and time of Day.
double julian_date(int year, int month, int day, int hour, int minute,
                   int second) {

    return (julian_day_number(year, month, day) + (hour - 12.0)
            / 24.0 + minute / 1440.0 + second / 86400.0);
}

/// Returns day of week given Gregorian date (may be proleptic). Mon = 0, etc
/// @returns An integer [0,6], with Mon = 0, Tue = 1, ... , Sun = 6.

int weekday(int year, int month, int day) {
    return static_cast<int>(labs(julian_day_number(year, month, day)) % 7);
}
