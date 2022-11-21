#include "DEFINES.hpp"
#include "./Console.cpp"
#include "./utils.cpp"

using namespace std;

class Calender
{
private:
    Console console;
    int selectedMonth, selectedYear, selectedDay;
    int perm_today_date;
public:
    int startDay, noOfRows, noOfDays,cycleLen=1;

public:
    void setCycleLen(int len){cycleLen = len;}
    void setDate(int year, int month, int day)
    {
        selectedMonth = month;
        selectedYear = year;
        selectedDay = day;

        startDay = getDay(year, month, 1);
        noOfRows = noOfRowsInMonth(year, month, startDay);
        noOfDays = noOfDaysInMonth(year, month);

        console.clear();
        showCalender();
    }

    void showCalender()
    {
        int calender[6][6] = {0};
        int lday = 1, i, j, shouldBreak = 0;

        console.print("\nCalendar of Month : " + to_string(selectedMonth) + " / " + to_string(selectedYear) + "\n");
        console.print("\n┏━━━━━━━━━━━┳━━━━━━━━━━━┳━━━━━━━━━━━┳━━━━━━━━━━━┳━━━━━━━━━━━┳━━━━━━━━━━━┳━━━━━━━━━━━┓");
        console.print("\n┃   Sunday  ┃  Monday   ┃  Tuesday  ┃ Wednesday ┃ Thursday  ┃  Friday   ┃ Saturday  ┃");
        console.print("\n┣━━━━━━━━━━━╋━━━━━━━━━━━╋━━━━━━━━━━━╋━━━━━━━━━━━╋━━━━━━━━━━━╋━━━━━━━━━━━╋━━━━━━━━━━━┫\n");

        int _day = 1;

        int offset = startDay > 0 ? startDay - 1 : 6;
        for (int i = 0; i < noOfRows; i++)
        {
            for (int k = 0; k <= 3; k++)
            {
                if (k == 3)
                    if (i == noOfRows - 1)
                        cout << "┗";
                    else
                        cout << "┣";
                else
                    cout << "┃";

                for (int j = 0; j < 7; j++)
                {
                    if (i == 0 && offset > j)
                    {
                        if (k == 3)
                            cout << "━━━━━━━━━━━┃";
                        else
                            cout << "           ┃";
                    }
                    else
                    {
                        if (k == 1)
                        {
                            if (_day <= 9)
                                cout << " ";

                            cout << "    ";

                            if (_day <= 31)
                            {
                                string text = to_string(_day);
                                // length of the cycle
                                int temp_cycleLen = cycleLen;

                                if ((selectedDay <= _day && _day < selectedDay+cycleLen)){
                                    temp_cycleLen--;
                                    console.print(text, Color::RED);
                                }
                                else if(perm_today_date == _day){
                                    console.print(text,Color::CYAN);
                                }
                                // if (_day == selectedDay || _day == selectedDay+1 || _day == selectedDay+2)
                                // {
                                //     //
                                //     //
                                //     // TODO: Change color
                                //     //
                                //     //
                                //     console.print(text, Color::RED);
                                // }
                                else
                                    console.print(text);
                            }
                            else
                                cout << "  ";

                            cout << "     ┃";
                            _day++;
                        }
                        else if (k == 3)
                        {
                            cout << "━━━━━━━━━━━";
                            if (j == 6)
                            {
                                if (i == noOfRows - 1)
                                {
                                    cout << "┛";
                                }
                                else
                                {
                                    cout << "┫";
                                }
                            }
                            else
                            {
                                if (i == noOfRows - 1)
                                {
                                    cout << "┻";
                                }
                                else
                                {
                                    cout << "╋";
                                }
                            }
                        }
                        else
                        {
                            cout << "           ┃";
                        }
                    }
                }

                cout << endl;
            }
        }
    }

    void setTodaysDate()
    {
        time_t theTime = time(NULL);
        struct tm *aTime = localtime(&theTime);

        int month = aTime->tm_mon + 1;    // Month is 0 - 11, add 1 to get a jan-dec 1-12 concept
        int year = aTime->tm_year + 1900; // Year is # years since 1900
        int day = aTime->tm_mday;
        perm_today_date = day;
        setDate(year, month, day);
    }

    void addDay(int amount)
    {
        int day = selectedDay, month = selectedMonth, year = selectedYear;

        day += amount;

        if (day > noOfDays)
        {
            month++;

            if (month > 12)
            {
                month = 1;
                year++;
            }

            day = 1;
        }

        setDate(year, month, day);
    }

    void addPeriodLen(int amount)
    {
        int day = selectedDay, month = selectedMonth, year = selectedYear;

        day += amount;
        int rem_days = 0;
        if (day > noOfDays)
        {
            rem_days = day-noOfDays;
            month++;

            if (month > 12)
            {
                month = 1;
                year++;
            }

            day = rem_days;
        }

        setDate(year, month, day);
    }

    void subDay(int amount)
    {
        int day = selectedDay, month = selectedMonth, year = selectedYear;

        day -= amount;

        if (day < 1)
        {
            month--;

            if (month < 1)
            {
                month = 12;
                year--;
            }

            day = noOfDaysInMonth(year, month);
        }

        setDate(year, month, day);
    }

    int ret_day() const{
        return selectedDay;
    }
    int ret_mon() const{
        return selectedMonth;
    }
    int ret_year() const{
        return selectedYear;
    }

};
