#include "./DEFINES.hpp"

using namespace std;

bool isLeapYear(int year)
{
    if (year % 400 == 0)
        return true;

    if (year % 100 == 0)
        return false;

    if (year % 4 == 0)
        return true;

    return false;
}

int noOfDaysInMonth(int year, int month)
{
    if (month == 4 || month == 6 || month == 9 || month == 11)
        return 30;
    else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
        return 31;
    else if (isLeapYear(year)) // month == 2
        return 29;
    else
        return 28;
}

int noOfRowsInMonth(int year, int month, int startDay)
{
    float totalCells = noOfDaysInMonth(year, month) + (startDay == 0 ? 6 : startDay - 1);
    return ceil(totalCells / 7);
}

int getDay(int year, int month, int date)
{
    int months[] = {0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5};
    int monthc, yearc, centuryc, centuryx, lyearc;

    monthc = months[month - 1];
    yearc = (year + (year / 4)) % 7;
    centuryx = (year - (year % 100));

    if (centuryx == 1700)
        centuryc = 4;
    else if (centuryx == 1800)
        centuryc = 2;
    else if (centuryx == 1900)
        centuryc = 0;
    else if (centuryx == 2000)
        centuryc = 6;
    else if (centuryx == 2100)
        centuryc = 4;
    else if (centuryx == 2200)
        centuryc = 8;
    else if (centuryx == 2300)
        centuryc = 0;

    lyearc = 0;

    if (isLeapYear(year) && (month == 1 || month == 2))
        lyearc = 1;

    return (yearc - lyearc + date + monthc + centuryc) % 7;
}

