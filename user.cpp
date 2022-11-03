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
#include<vector>
// #include "./login.cpp"
using namespace std;
class detail{
    private:
    string s_date;
    int cycleLen;
    int periodLen;
    int year;
    int month;
    int day;
    Console console;
    public:

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
    void date_separate(string date){
        vector<int> v;
        // Get the string to be taken
        // as input in stringstream
        stringstream ss(date);
        // Parse the string
        for (int i; ss >> i;) {
            v.push_back(i);
            if (ss.peek() == '/')
                ss.ignore();
        }
        year = v[0];
        month = v[1];
        day = v[2];
    }
    void getDetails(int userId){
        MYSQL *conn;
        MYSQL_ROW row;
	    MYSQL_RES* res;
        conn = mysql_init(0);
        conn = mysql_real_connect(conn ,"localhost" ,"root", "root", "codered" ,0,NULL,0);
        if(conn)
            cout<<"connected"<<endl;
        else cout<<"not connected"<<endl;
        int qstate =0;
        stringstream ss;
        // ss<<"INSERT INTO user(username,password,periodLen,cycleLen,start_date) VALUES('"<<username<<"','"<<password<<"')";
        ss<<"select periodLen,cycleLen,start_date from users where id ='"<<userId<<"'";
        // cout<<userId<<endl;
        string query =  ss.str();
        const char* q= query.c_str();
        qstate = mysql_query(conn,q);
         if(!qstate)
        {
            res = mysql_store_result(conn);
            while(row = mysql_fetch_row(res))
                {
                // cout<<row[0]<<" "<<row[1]<<" "<<row[2]<<endl;
                periodLen = stoi(row[0]);
                cycleLen = stoi(row[1]);
                s_date = row[2];
                }
        }
        date_separate(s_date);
    }
    void showUserCal(int userId){
        getDetails(userId);
            // cout<<year<<" "<<month<<" "<<day;
        Calender calender;
        calender.setTodaysDate();
        calender.setCycleLen(cycleLen);
        calender.setDate(year,month,day);
        while (true)
        {
            console.print("Press any key to exit! Right arrow key to move the Calendar!", Color::MAGENTA);
            cout << endl;
            bool arrowKeysPressed = getch() == 224;
            if (arrowKeysPressed)
            {
                int key = getch();
                if(key == 77){
                    calender.addPeriodLen(periodLen);
                }
                else
                break;
            }
            else

                break;
        }
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

    void updateDetails(int userId)
    {
    getDetails(userId);
    system("cls");
    cout<<"*****YOUR PREVIOUS DETAILS ARE*****"<<endl;
    cout<<"Period Length->"<<periodLen<<endl;
    cout<<"Cycle Length->"<<cycleLen<<endl;
    cout<<"Start date->"<<s_date<<endl;
    MYSQL *conn;
    MYSQL_RES* res;
    MYSQL_ROW row;
	conn = mysql_init(0);
	conn = mysql_real_connect(conn ,"localhost" ,"root", "root", "codered" ,0,NULL,0);

	// string cyclelen,periodlen, startdate;
    cout<<endl<<"Enter y to update your existing details"<<endl;
    char ch;
    cin>>ch;
	stringstream a,ss;
	a<<"SELECT * from users where id =" <<userId;
	string b = a.str();
	const char* query = b.c_str();
	if(!(mysql_query(conn,query)) && ch == 'y')
    {
       res=mysql_store_result(conn);
       row=mysql_fetch_row(res);//returns address of id
       if(row!=0)
       {
           cout<<"\n\n Enter Period Length->";
           cin.ignore();
           cin>>periodLen;
           cout<<"\n\n Enter Cycle Length->";
           cin>>cycleLen;
        //    cout<<"\n\n Enter Start date->";
        //    cin>>s_date;
        string s_date = cal(cycleLen);
           ss<<"UPDATE users SET periodLen='"<< periodLen << "', cycleLen='"<<cycleLen<<"', start_date='"<< s_date<<"' WHERE id ="<<userId;
            b=ss.str();
            query=b.c_str();
            mysql_query(conn,query);
            cout<<"* Record Updated Successfully *";
        }
         else
        {
            cout<<"\n\n*** USER ID NOT FOUND  ";
        }
    }
    else
    {

        cout<<"\n\n * Thank You! *";
    }
    getch();

    }


    void addSymptoms(int userId){
    system("cls");
    cout<<"What symptoms do you have?"<<endl<<"Type 1 for yes and 0 for no"<<endl;
    string sym_1, sym_2, sym_3, sym_4, sym_5;

    sym_1 = "Headache";
    sym_2 = "Abdominal pain";
    sym_3 = "Back ache";
    sym_4 = "Sleep apenea";
    sym_5= "Acne";
    int r1=0,r2=0,r3=0,r4=0,r5=0;
    int in=0;
    cout<<sym_1<<"?"<<endl;
    cin>>in;
    if(in == 1){
        r1 = 1;
    }

    cout<<sym_2<<"?"<<endl;
    cin>>in;
    if(in == 1){
        r2 = 1;
    }

    cout<<sym_3<<"?"<<endl;
    cin>>in;
    if(in == 1){
        r3 = 1;
    }

    cout<<sym_4<<"?"<<endl;
    cin>>in;
    if(in == 1){
        r4 = 1;
    }

    cout<<sym_5<<"?"<<endl;
    cin>>in;
    if(in == 1){
        r5 = 1;
    }

    // update existing record if not create new one;
    MYSQL *conn;
    MYSQL_RES* res;
    MYSQL_ROW row;
	conn = mysql_init(0);
	conn = mysql_real_connect(conn ,"localhost" ,"root", "root", "codered" ,0,NULL,0);
    stringstream a,si,su;
	a<<"select sym_1,sym_2 from symptoms where user_id ='"<<userId<<"'";
	string b = a.str();
	const char* query = b.c_str();
    int qstate = mysql_query(conn,query);
    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);
    if(!row){
        // we need to use insert query here.
        cout<<"Going to insert"<<endl;
        si<<"INSERT INTO symptoms(user_id,sym_1,sym_2,sym_3,sym_4,sym_5) VALUES('"<<userId<<"','"<<r1<<"','"<<r2<<"','"<<r3<<"','"<<r4<<"','"<<r5<<"')";
        string query =  si.str();
        const char* q= query.c_str();
        qstate = mysql_query(conn,q);
        if(qstate==0)
            cout<<"* Symptoms Inserted Succesfully ... *"<<endl;
    }
    else{
        // we need to update query here.
        cout<<"Going to update"<<endl;
        su<<"UPDATE symptoms SET sym_1='"<< r1 << "', sym_2='"<<r2<<"', sym_3='"<< r3<< "', sym_4='"<<r4<< "', sym_5='"<<r5<<"' WHERE user_id ="<<userId;
        b=su.str();
        query=b.c_str();
        qstate = mysql_query(conn,query);
        if(qstate==0)
            cout<<"* Symptoms Updated Succesfully ... *"<<endl;
    }

    }

    void viewSymptoms(int userId,string user){
        system("cls");
        cout<<userId<<endl;
        cout<<"Hi "<<user<<"!"<<endl;
        cout<<"You have following symptoms now :(Active symptoms are marked as (\xfb)) "<<endl;
        MYSQL *conn;
        MYSQL_RES* res;
        MYSQL_ROW row;
        stringstream ss;
        conn = mysql_init(0);
	    conn = mysql_real_connect(conn ,"localhost" ,"root", "root", "codered" ,0,NULL,0);
        int qstate = 0;
        ss<<"select sym_1,sym_2,sym_3,sym_4,sym_5 from symptoms where user_id ='"<<userId<<"'";
        string query =  ss.str();
        const char* q= query.c_str();
        qstate = mysql_query(conn,q);
        res = mysql_store_result(conn);
        row = mysql_fetch_row(res);
        // sym_1 = "Headache";
        // sym_2 = "Abdominal pain";
        // sym_3 = "Back ache";
        // sym_4 = "Sleep apenea";
        // sym_5= "Acne";
        if(row){
            (stoi(row[0])==1)?
                cout<<"Headache\t\t(\xfb)\n":cout<<"Headache\t\t(x)\n";
            (stoi(row[1])==1)?
                cout<<"Abdominal pain\t\t(\xfb)\n":cout<<"Abdominal pain\t\t(x)\n";
            (stoi(row[2])==1)?
                cout<<"Back ache\t\t(\xfb)\n":cout<<"Back ache\t\t(x)\n";
            (stoi(row[3])==1)?
                cout<<"Sleep apenea\t\t(\xfb)\n":cout<<"Sleep apenea\t\t(x)\n";
            (stoi(row[4])==1)?
                cout<<"Acne\t\t\t(\xfb)\n":cout<<"Acne\t\t\t(x)\n";
            // cout<<row[0]<<row[1]<<row[2]<<row[3]<<row[4]<<endl;
        }
        else{
            cout<<"*** Add the symptoms first ! ***"<<endl;
        }
        cout<<"\n\nPress any key to exit.";
        getch();
    }
};