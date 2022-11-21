#include "./DEFINES.hpp"

using namespace std;

class Console
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    UINT oldcp = GetConsoleOutputCP();

public:
    Console()
    {
        SetConsoleOutputCP(CP_UTF8); // support utf8
        GetConsoleScreenBufferInfo(hConsole, &csbi);
    }

    ~Console()
    {
        SetConsoleOutputCP(oldcp);
    }

    void print(string text, Color color = Color::DEFAULT)
    {
        if (color == Color::DEFAULT)
        {
            cout << text;
        }
        else
        {
            SetConsoleTextAttribute(hConsole, int(color));
            cout << text;
            SetConsoleTextAttribute(hConsole, csbi.wAttributes);
        }
    }

    void clear()
    {
        // cout << "\033[2J\033[1;1H";
        // cout << string(100, '\n');

        system("cls");

        // COORD coordScreen = {0, 0};
        // SetConsoleCursorPosition(hConsole, coordScreen);
    }
};
