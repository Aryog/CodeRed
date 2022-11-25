/*#include "./DEFINES.hpp"
#include "./Calender.cpp"

bool handleCalenderInput(int key, Calender &calender)
{
    switch (key)
    {
    case 72: // move up
        calender.subDay(7);
        return true;
    case 80: // move down
        calender.addDay(7);
        return true;
    case 75: // move left
        calender.subDay(1);
        return true;
    case 77: // move right
        calender.addDay(1);
        return true;
    }

    return false; // key is not handled
}

int main(void)
{

    Calender calender;
    calender.setTodaysDate();

    while (true)
    {
        cout << "Press arrows to move date and other keys to set current" << endl;
        bool arrowKeysPressed = getch() == 224;
        if (arrowKeysPressed)
        {
            int key = getch();

            if (!handleCalenderInput(key, calender)) // break from loop if anything other than arroow key pressed
                break;
        }
        else
            break;
    }
    // Have to put below date to the database;
    cout<<"Date: "<<calender.ret_year()<<"/"<<calender.ret_mon()<<"/"<<calender.ret_day()<<endl;
    cout<<"This is the end of the program."<<endl;
    getch();
    return 0;
}

*/

//////
#include "./DEFINES.hpp"
#include "./Calender.cpp"
#include "./login.cpp"
using namespace std;
bool handleCalenderInput(int key, Calender &calender)
{
    switch (key)
    {
    case 72: // move up
        calender.subDay(7);
        return true;
    case 80: // move down
        calender.addDay(7);
        return true;
    case 75: // move left
        calender.subDay(1);
        return true;
    case 77: // move right
        calender.addDay(1);
        return true;
    }

    return false; // key is not handled
}

int main(void)
{
    user u;
    u.showtime();
    Console console;
    cout << " \t \t \t \t \t  " ;console.print("Period Tracking System",Color::LIGHTGREEN);cout<< endl
         << endl
         << endl
         << endl;
    user u1;
    int x;
    int choice = 0;

    do
    {
        cout << endl;
        console.print("Choose from the Following:",Color::GRAY);
        cout <<endl;
        console.print("1. Login",Color::LIGHTBLUE);
        cout<<endl;
        console.print("2. Add User",Color::LIGHTBLUE);
        cout<<endl;
        console.print("0. Exit",Color::RED);
        cout<<endl;
        cin >> x;
        string no2;
        switch (x)
        {
        case 1:
            u1.login();
            break;
        case 2:
            u1.adduser();
            u1.login();
            break;
        // case 5:
        // {  b1.print_user();
        // if(loggedin_userId>0){
        //     cout << "Hi "
        //          << " " << loggedin_user;
        //     Calender calender;
        //     calender.setTodaysDate();

        //     while (true)
        //     {
        //         cout << "Press arrows to move date" << endl;

        //         bool arrowKeysPressed = getch() == 224;
        //         if (arrowKeysPressed)
        //         {
        //             int key = getch();

        //             if (!handleCalenderInput(key, calender)) // break from loop if anything other than arroow key pressed
        //                 break;
        //         }
        //         else

        //             break;
        //     }
        //     // Have to put below date to the database;
        //     cout << "Date: " << calender.ret_year() << "/" << calender.ret_mon() << "/" << calender.ret_day() << endl;
        //     cout << "This is the end of the program." << endl;
        //     getch();
        // }
        // else
        //     cout<<"Login to see User Credentials."<<endl;
        // }
        // break;
        case 0:
            choice = 1;
        }
    } while (choice == 0);

    return 0;
}
