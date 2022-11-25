#include <iostream>
#include<winsock.h>
#include<windows.h>
#include<sstream>
#include<ctime>
#include<string>
#include<mysql.h>
#include<cstring>
#include<conio.h>
#include<cstring>
#include<map>
#include<fstream>
#include<string>
#include "./user.cpp"
// #include "./Console.cpp"

void blog(int);
using namespace std;
class user;
int users =0;
int count_attempt=0;
int curr_user=0;
int user_no=0;
string loggedin_user="";
int loggedin_userId=0;

class user
{

private:
string username;
string password;
string cycleLen;
string periodLen;
Console console;
public:

    void showtime()
{
	time_t now = time(0);
	char *dt = ctime(&now);
	cout<<dt;
	cout<<endl<<endl;
}
void logs()
{

     string text;

    int n;

    cout<<"1. PCOS"<<endl;
    cout<<"2. Endometriosis"<<endl;
    cout<<"3. Firbroids"<<endl;
    cout<<"4. Gynecologists"<<endl;
    cout<<"5. Period Poverty"<<endl;
    cout<<"0. Exit"<<endl<<endl;

    cin>>n;
    //system("cls");

    blog(n);
}
void blog(int n)
{


    if(n==1)
    {
        char ch;
        ifstream in;
        in.open("PCOS.txt", ios::in);
        if (in.fail())
    {
        cout << "Error opening file" << endl;
        cout << "Exiting ...." << endl;
        exit(1);
    }
       cout << "content of the file" << endl;
    while (in.get(ch))
    {
        cout << ch;
    }
    in.close();



    }


      else if(n==2)
    {
        char ch;
        ifstream in;
        in.open("Endometriosis.txt", ios::in);
        if (in.fail())
    {
        cout << "Error opening file" << endl;
        cout << "Exiting ...." << endl;
        exit(1);
    }
       cout << "content of the file" << endl;
    while (in.get(ch))
    {
        cout << ch;
    }
    in.close();



    }

     else if(n==3)
    {
        char ch;
        ifstream in;
        in.open("Fibroids.txt", ios::in);
        if (in.fail())
    {
        cout << "Error opening file" << endl;
        cout << "Exiting ...." << endl;
        exit(1);
    }
       cout << "content of the file" << endl;
    while (in.get(ch))
    {
        cout << ch;
    }
    in.close();



    }

      else if(n==4)
    {
        char ch;
        ifstream in;
        in.open("Gynocologists.txt", ios::in);
        if (in.fail())
    {
        cout << "Error opening file" << endl;
        cout << "Exiting ...." << endl;
        exit(1);
    }
       cout << "content of the file" << endl;
    while (in.get(ch))
    {
        cout << ch;
    }
    in.close();



    }

     else if(n==5)
    {
        char ch;
        ifstream in;
        in.open("periodpoverty.txt", ios::in);
        if (in.fail())
    {
        cout << "Error opening file" << endl;
        cout << "Exiting ...." << endl;
        exit(1);
    }
       cout << "content of the file" << endl;
    while (in.get(ch))
    {
        cout << ch;
    }
    in.close();



    }
  else if(n==0)
    {
        return;

    }
    else
        return;

}
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
string cal(int len){
    Calender calender;
            calender.setTodaysDate();
            calender.setCycleLen(len);
            calender.setTodaysDate();
            while (true)
            {
                cout << "Press arrows to move date and other keys to set the start date of period!" << endl;

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
            cout << "Date: " << calender.ret_year() << "/" << calender.ret_mon() << "/" << calender.ret_day() << endl;
            string str_date = to_string(calender.ret_year()) +"/"+to_string(calender.ret_mon())+"/"+to_string(calender.ret_day());
            getch();
            return str_date;
}
void adduser()
{
	MYSQL *conn;
	conn = mysql_init(0);
        conn = mysql_real_connect(conn ,"192.168.137.1" ,"admin", "admin", "codered" ,3307,NULL,0);
	if(conn)
        cout<<"connected"<<endl;
    else cout<<"not connected"<<endl;

	cout<<"Username:";
	cin>>username;
	cout<<"Password:";
	cin>>password;
    cout<<"Period Length (Default is 28 days):";
    cin>>periodLen;
    cout<<"Cycle Length:";
    cin>>cycleLen;
    int len = stoi(cycleLen);
    string str_date = cal(len);
	int qstate =0;
	stringstream ss;
	// ss<<"INSERT INTO user(username,password,periodLen,cycleLen,start_date) VALUES('"<<username<<"','"<<password<<"')";
	ss<<"INSERT INTO users(username,password,periodLen,cycleLen,start_date) VALUES('"<<username<<"','"<<password<<"','"<<periodLen<<"','"<<cycleLen<<"','"<<str_date<<"')";
	string query =  ss.str();
        const char* q= query.c_str();
        qstate = mysql_query(conn,q);
        if(qstate==0)
            cout<<"Record Inserted Succesfully ... "<<endl;
        else cout<<"Failed"<<endl;

	users++;
}
void no_users()
{
	cout<<"The users are:  "<<endl;
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);
        conn = mysql_real_connect(conn ,"192.168.137.1" ,"admin", "admin", "codered" ,3307,NULL,0);
	if(conn)
    {
        int qstate = mysql_query(conn,"SELECT username FROM users");
    //    bool flag=false;
        if(!qstate)
        {
            res = mysql_store_result(conn);
            int i=1;
            while(row = mysql_fetch_row(res))
                {
                    cout<<i<<"."<<row[0]<<endl;
                    i++;
                }
        }
    }
}
void menu2(){
    if(loggedin_userId!=0){
        cout << "Hi"<< " ";
        console.print(loggedin_user,Color::MAGENTA);
        cout<<"!"<<endl;
        int x;
        detail d1;
        int choice = 0;
        do
        {
            cout << endl;
            console.print("Choose from the Following:",Color::GRAY);
            cout << endl;
            console.print("1. Show User Calendar",Color::LIGHTBLUE);
            cout << endl;
            console.print("2. Settings",Color::LIGHTBLUE);
            cout << endl;
            console.print("3. Add Symptoms",Color::LIGHTBLUE);
            cout << endl;
            console.print("4. Your Symptoms",Color::LIGHTBLUE);
            cout << endl;
            console.print("5. View Logs", Color :: LIGHTBLUE);
            cout<<endl;
            console.print("6. LogOut",Color::RED);
            cout << endl;
            cin >> x;
            string no2;
            switch (x)
            {
            case 1:
                d1.showUserCal(loggedin_userId);
                break;
            case 2:
                d1.updateDetails(loggedin_userId);
                break;
            case 3:
                d1.addSymptoms(loggedin_userId);
                break;
            case 4:
                d1.viewSymptoms(loggedin_userId,loggedin_user);
                break;
            case 5:
                logs();

                break;

            case 6:
                logout();
                choice = 1;
                break;
            case 0:
                choice = 1;
            }
        } while (choice == 0);
    }
}
void login()
{
	if(curr_user==1)
	{
	cout<<"Already logged in";
	return;
	}
	if(count_attempt==2)
	{
		cout<<endl<<endl;
		cout<<"No more attempts";
		exit(0);
	}
	cout<<"Enter Credentials for Login (ID Password)"<<endl;
	string user_name;
	string pass_word;
    Console console;
	cout<<"Username:";
	cin>>user_name;
	cout<<"Password:";
	cin>>pass_word;
	cin.ignore();
	system("cls");

	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);
        conn = mysql_real_connect(conn ,"192.168.137.1" ,"admin", "admin", "codered" ,3307,NULL,0);
	if(conn)
    {
        int qstate = mysql_query(conn,"SELECT id,username,password FROM users");
        bool flag=false;
        if(!qstate)
        {
            res = mysql_store_result(conn);
            while(row = mysql_fetch_row(res))
                {
                if(row[1]==user_name && row[2]==pass_word)
                {
                        console.print("Login Successful", Color::GREEN);
                        cout<<endl;
                        // Like the session storage
                        loggedin_userId = stoi(row[0]);
                        loggedin_user = row[1];
                        curr_user=1;
                        flag=true;
                        menu2();
                        break;
                }
                }
                if(!flag)
                {
                    console.print("Try Again!", Color::RED);
                    count_attempt++;
                    cin.ignore();
                    system("cls");
                    login();
                }


        }
        else
        {
            cout<<"No Accounts Registered";
        }
    }
}
	void logout()
	{
		curr_user=0;
        loggedin_user ="";
        loggedin_userId=0;
	}
};
