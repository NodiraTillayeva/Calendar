#pragma warning(disable:4996)
#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include<ctime>
#include<stdio.h>
#include<ctype.h>
#include<conio.h>
#include <cstdlib>
#define line "------------------------------------------------------"
using namespace std;
//Global variables
int i, dates;
string a, currtime, number;
int Feb;

class Calendar
{
public:
	int day;
	string month_str; //Month is input with strings
	int month;
	int year;
	int days_in_one_month;
public:
	void setDay() //setting the date
	{

		cout << setw(35) << "Enter the day:	";
		cin >> day;
	}
	void setmonth()
	{
		cout << setw(35) << "Enter the month:	";
		cin >> month;
	}
	void setyear()
	{
		cout << setw(35) << "Enter the year:	";
		cin >> year;
	}
	void getDate() //Displaying the date
	{
		cout << "Day:	" << day << endl;
		cout << "Month:	" << month << endl;
		cout << "Year:	" << year << endl;
	}
	void month_to_num() //converts string values of monthes(Dec, Jan, Apr) to integers(12,1,4) for futher calculations
	{
		if (month == 1)
		{
			month_str = "Jan";
			days_in_one_month = 31;
		}
		if (month == 2)
		{
			month_str = "Feb";
			days_in_one_month = Feb;
		}
		if (month == 3)
		{
			month_str = "Mar";
			days_in_one_month = 31;
		}
		if (month == 4)
		{
			month_str = "Apr";
			days_in_one_month = 30;
		}
		if (month == 5)
		{
			month_str = "May";
			days_in_one_month = 31;
		}
		if (month == 6)
		{
			month_str = "Jun";
			days_in_one_month = 30;
		}
		if (month == 7)
		{
			month_str = "Jul";
			days_in_one_month = 31;
		}
		if (month == 8)
		{
			month_str = "Aug";
			days_in_one_month = 31;
		}
		if (month == 9)
		{
			month_str = "Sep";
			days_in_one_month = 30;
		}
		if (month == 10)
		{
			month_str = "Oct";
			days_in_one_month = 31;
		}
		if (month == 11)
		{
			month_str = "Nov";
			days_in_one_month = 30;
		}
		if (month == 12)
		{
			month_str = "Dec";
			days_in_one_month = 31;
		}
	}
	void integer_validation(int x)
	{
		while (!(cin >> x))
		{
			cout << "Enter valid year!" << endl;//expaining the error
			cin.clear();//clearing the previos input
			cin.ignore(123, '\n');//discarding previous enter
		}
	}
	void year_validation()
	{

		while (year <= 1980)
		{
			cout << "Enter valid year!" << endl;
			setyear();
			integer_validation(year);
			break;
		}
	}
	void month_validation()
	{
		while ((month <= 0) || (month > 12))
		{
			cout << "Enter valid month!";
			setmonth();
			integer_validation(month);
		}
	}
	void day_validation()
	{
		while (day <= 0 || (day > days_in_one_month))
		{
			cout << "Enter valid date ! ";
			cout << days_in_one_month;
			setDay();
			integer_validation(day);
		}
	}
};
class Calendar_Display : public Calendar//Inherits main values of calendar for special calculations to print two types of calendars
{
public:
	Calendar date;
	int day_in_week;
	int ymod, year_change, days_in_year;
	int n;
	int dayvnum[10], monthvnum[10], yearvnum[10];
	string monthch, daych, yearch;
public:
	void calendar_loop(int day_in_week, int Feb, int day, int monthp)//Special loop to print calendar dates depending on the leap year, in what day of the week year starts
	{
		int monthloopcheck;
		monthloopcheck = monthp;
		if (day_in_week == 0)
		{
			day_in_week = 7;
		}
		//ifstream inOne;//reading first file and summing its values
		string num;
		//inOne.open("one.txt"); 
		ifstream Notedates(number + "userdates.txt");
		for (int i = 0; i < 10; i++)
		{

			while (Notedates >> num)
			{
				size_t position;
				position = num.find("_");
				monthch = num.substr(position - 2, 2);
				daych = num.substr(position + 1, 2);
				position = num.find("_", position + 2);
				yearch = num.substr(position + 1, -2);
				dayvnum[i] = stoi(daych);
				monthvnum[i] = stoi(monthch);
				yearvnum[i] = stoi(yearch);
				break;
			}
		}
		Notedates.close();
		for (int i = 1; i < day_in_week; i++)
		{
			cout << "\t";
		}
		for (int i = 1; i <= Feb; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if ((i == dayvnum[j]) && (monthloopcheck == monthvnum[j]))
				{
					cout << '*';
				}
			}
			cout << i << "\t";
			if ((day_in_week + i) % 7 == 1)//when day comes to Sunday(7) new line starts
			{
				cout << endl;
			}
			if (i == (date.day - 1) && (date.month == monthloopcheck))
			{
				cout << '!';
			}
		}
		cout << endl;
	}
	void Calculations() //Algorithm to find leap years and the days of the week where Jan 1st is
	{
		while (date.year <= 0)
		{
			cout << "Enter valid year : ";
			cin >> date.year;
		}
		ymod = date.year % 100;
		if ((date.year % 4 == 0) || (date.year % 100 == 0) || (date.year % 400 == 0))
		{
			Feb = 29;
		}
		else
		{
			Feb = 28;
		}
		if ((date.year / 100) % 4 == 3)
		{
			year_change = 0;
		}
		if ((date.year / 100) % 4 == 0)
		{
			year_change = 6;
		}
		if ((date.year / 100) % 4 == 1)
		{
			year_change = 4;
		}
		if ((date.year / 100) % 4 == 2)
		{
			year_change = 2;
		}
		days_in_year = (1 + ((year_change + ymod + (ymod / 4)) % 7)) % 7;
		if (Feb == 29)
		{
			days_in_year = days_in_year;
		}
		if (Feb == 28)
		{
			days_in_year = days_in_year + 1;
		}
		if (days_in_year == 0 || days_in_year == 7)
		{
			day_in_week = 6;
		}
		if (days_in_year == 1)
		{
			day_in_week = 7;
		}
		if (days_in_year == 2)
		{
			day_in_week = 1;
		}
		if (days_in_year == 3)
		{
			day_in_week = 2;
		}
		if (days_in_year == 4)
		{
			day_in_week = 3;
		}
		if (days_in_year == 5)
		{
			day_in_week = 4;
		}
		if (days_in_year == 6)
		{
			day_in_week = 5;
		}
	}
	void Display_month_calendar()
	{
		date.setyear();
		date.year_validation();
		Calculations();
		date.setmonth();
		date.month_validation();
		date.month_to_num();
		date.setDay();
		date.day_validation();

		if (date.month == 1)
		{
			cout << line << endl << "January					" << date.year << endl << line << endl;
			cout << "M\tT\tW\tT\tF\tS\tS" << endl << line << endl;
			calendar_loop(day_in_week, 31, date.day, 1);
		}
		day_in_week = (day_in_week + 31) % 7;
		if (date.month == 2)
		{
			cout << line << endl << "February					" << date.year << endl << line << endl;
			cout << "M\tT\tW\tT\tF\tS\tS" << endl << line << endl;
			calendar_loop(day_in_week, Feb, date.day, 2);
		}
		day_in_week = (day_in_week + Feb) % 7;
		if (date.month == 3)
		{
			cout << line << endl << "March					" << date.year << endl << line << endl;
			cout << "M\tT\tW\tT\tF\tS\tS" << endl << line << endl;
			calendar_loop(day_in_week, 31, date.day, 3);
		}
		day_in_week = (day_in_week + 31) % 7;
		if (date.month == 4)
		{
			cout << line << endl << "April					" << date.year << endl << line << endl;
			cout << "M\tT\tW\tT\tF\tS\tS" << endl << line << endl;
			calendar_loop(day_in_week, 30, date.day, 4);
		}
		day_in_week = (day_in_week + 30) % 7;
		if (date.month == 5)
		{
			cout << line << endl << "May						" << date.year << endl << line << endl;
			cout << "M\tT\tW\tT\tF\tS\tS" << endl << line << endl;
			calendar_loop(day_in_week, 31, date.day, 5);
		}
		day_in_week = (day_in_week + 31) % 7;
		if (date.month == 6)
		{
			cout << line << endl << "June					" << date.year << endl << line << endl;
			cout << "M\tT\tW\tT\tF\tS\tS" << endl << line << endl;
			calendar_loop(day_in_week, 31, date.day, 6);
		}
		day_in_week = (day_in_week + 30) % 7;
		if (date.month == 7)
		{
			cout << line << endl << "July					" << date.year << endl << line << endl;
			cout << "M\tT\tW\tT\tF\tS\tS" << endl << line << endl;
			calendar_loop(day_in_week, 31, date.day, 7);
		}
		day_in_week = (day_in_week + 31) % 7;
		if (date.month == 8)
		{
			cout << line << endl << "August					" << date.year << endl << line << endl;
			cout << "M\tT\tW\tT\tF\tS\tS" << endl << line << endl;
			calendar_loop(day_in_week, 31, date.day, 8);
		}
		day_in_week = (day_in_week + 31) % 7;
		if (date.month == 9)
		{

			cout << line << endl << "September					" << date.year << endl << line << endl;
			cout << "M\tT\tW\tT\tF\tS\tS" << endl << line << endl;
			calendar_loop(day_in_week, 30, date.day, 9);
		}
		day_in_week = (day_in_week + 30) % 7;
		if (date.month == 10)
		{
			cout << line << endl << "October					" << date.year << endl << line << endl;
			cout << "M\tT\tW\tT\tF\tS\tS" << endl << line << endl;
			calendar_loop(day_in_week, 31, date.day, 10);
		}
		day_in_week = (day_in_week + 31) % 7;
		if (date.month == 11)
		{
			cout << line << endl << "November					" << date.year << endl << line << endl;
			cout << "M\tT\tW\tT\tF\tS\tS" << endl << line << endl;
			calendar_loop(day_in_week, 30, date.day, 11);
		}
		day_in_week = (day_in_week + 30) % 7;
		if (date.month == 12)
		{
			cout << line << endl << "December					" << date.year << endl << line << endl;
			cout << "M\tT\tW\tT\tF\tS\tS" << endl << line << endl;
			calendar_loop(day_in_week, 31, date.day, 12);
		}
	}
	void Display_year_calendar()
	{
		date.setyear();//User inputs day, month and year from keyboard
		//integer_validation(year);
		Calculations();//We calculate leap year and the day of the week when January 1st is
		//Print calendar for the whole year
		system("CLS");
		cout << line << endl << "January						" << date.year << endl << line << endl;
		cout << "M\tT\tW\tT\tF\tS\tS" << endl << line << endl;
		calendar_loop(day_in_week, 31, date.day, 1);//activating loop
		day_in_week = (day_in_week + 31) % 7;
		cout << line << endl << " February					" << date.year << endl << line << endl;
		cout << "M\tT\tW\tT\tF\tS\tS" << endl << line << endl;
		calendar_loop(day_in_week, Feb, date.day, 2);
		day_in_week = (day_in_week + Feb) % 7;
		cout << line << endl << " March						" << date.year << endl << line << endl;
		cout << "M\tT\tW\tT\tF\tS\tS" << endl << line << endl;
		calendar_loop(day_in_week, 31, date.day, 3);
		day_in_week = (day_in_week + 31) % 7;
		cout << line << endl << " April						" << date.year << endl << line << endl;
		cout << "M\tT\tW\tT\tF\tS\tS" << endl << line << endl;
		calendar_loop(day_in_week, 30, date.day, 4);
		day_in_week = (day_in_week + 30) % 7;
		cout << line << endl << " May						" << date.year << endl << line << endl;
		cout << "M\tT\tW\tT\tF\tS\tS" << endl << line << endl;
		calendar_loop(day_in_week, 31, date.day, 5);
		day_in_week = (day_in_week + 31) % 7;
		cout << line << endl << " June						" << date.year << endl << line << endl;
		cout << "M\tT\tW\tT\tF\tS\tS" << endl << line << endl;
		calendar_loop(day_in_week, 31, date.day, 6);
		day_in_week = (day_in_week + 30) % 7;
		cout << line << endl << " July						" << date.year << endl << line << endl;
		cout << "M\tT\tW\tT\tF\tS\tS" << endl << line << endl;
		calendar_loop(day_in_week, 31, date.day, 7);
		day_in_week = (day_in_week + 31) % 7;
		cout << line << endl << " August						" << date.year << endl << line << endl;
		cout << "M\tT\tW\tT\tF\tS\tS" << endl << line << endl;
		calendar_loop(day_in_week, 31, date.day, 8);
		day_in_week = (day_in_week + 31) % 7;
		cout << line << endl << " September					" << date.year << endl << line << endl;
		cout << "M\tT\tW\tT\tF\tS\tS" << endl << line << endl;
		calendar_loop(day_in_week, 30, date.day, 9);
		day_in_week = (day_in_week + 30) % 7;
		cout << line << endl << " October					" << date.year << endl << line << endl;
		cout << "M\tT\tW\tT\tF\tS\tS" << endl << line << endl;
		calendar_loop(day_in_week, 31, date.day, 10);
		day_in_week = (day_in_week + 31) % 7;
		cout << line << endl << " November					" << date.year << endl << line << endl;
		cout << "M\tT\tW\tT\tF\tS\tS" << endl << line << endl;
		calendar_loop(day_in_week, 30, date.day, 11);
		day_in_week = (day_in_week + 30) % 7;
		cout << line << endl << " December					" << date.year << endl << line << endl;
		cout << "M\tT\tW\tT\tF\tS\tS" << endl << line << endl;
		calendar_loop(day_in_week, 31, date.day, 12);
	}
};

//functions
int MainMenu();
void DiaryMenu();
void SubMainMenu();
void AddNote();
void AddNoteDate();
void AddNoteSubMenu();
void ReadNoteMenu();
void ReadNoteDate();
void DeleteMenu();
void DeleteNoteDate();
void Calendar_menu();
int Validation(int mode);
//registration function
void Registration()
{
	string rname, rpass, vpass, rnumber;
	char chrpass, chvpass;
	ifstream iftxt("i.txt");   // iftxt object created to read the value of i 
	iftxt >> ::i;			   // to know the number of existing users
	iftxt.close();
	system("cls");
	cout << "ENTER YOUR NAME >> ";
	cin >> rname;
	try {										// try catch is used to verify passwords entered by user
		cout << "ENTER YOUR PASSWORD >>";
		chrpass = _getch();
		while (chrpass != 13)
		{
			rpass.push_back(chrpass);
			cout << "*";
			chrpass = _getch();
		}
		cout << endl << "VERIFY YOUR PASSWORD >>";
		chvpass = _getch();
		while (chvpass != 13)
		{
			vpass.push_back(chvpass);
			cout << "*";
			chvpass = _getch();
		}
		if (rpass != vpass)
			throw rpass, vpass;
	}
	catch (string a)
	{
		cout << "PASSWORDS DO NOT MATCH, TRY AGAIN" << endl;
		system("pause");
		Registration();
	}
	cout << endl;
	rnumber = to_string(::i);
	ofstream user(rnumber + "user.txt");
	user << rname << " " << rpass << " " << rnumber << endl;
	user.close();
	::i++;									// increase the number of existing users after
	ofstream oftxt("i.txt");				// each successfull registration and rewrite i.txt with 
	oftxt << i;								// current number
	oftxt.close();
	MainMenu();
}
//Login function
void Login()
{
	string lname, lpass, lvname, lvpass, l, lnumber;
	char chlpass;
	system("cls");
	cout << endl << endl << endl << endl << line << endl << "                 L O G  I N  S C R E E N    " << endl << line << endl;
	cout << "Enter your name: ";
	cin >> lname;
	cout << line << endl;
	cout << "Enter your password: ";
	chlpass = _getch();
	while (chlpass != 13)
	{
		lpass.push_back(chlpass);
		cout << "*";
		chlpass = _getch();
	}
	cout << endl << line << endl;

	ifstream iftxt("i.txt");
	iftxt >> i;
	iftxt.close();

	for (int k = 0; k < ::i; k++) {					// loop to check among existing users

		l = to_string(k);
		ifstream login(l + "user.txt");

		login >> lvname >> lvpass >> lnumber;

		if (lvname == lname && lvpass == lpass)
		{
			number = lnumber;
			system("cls");
			cout << endl << endl << endl << endl << line << endl << "                 W E L C O M E, " << lname << endl << line << endl;
			SubMainMenu();
			break;
		}
		else if (lvname != lname && lvpass == lpass)
		{
			cout << "Wrong User name, try again" << endl;
			system("pause");
			break;
		}
		else if (lvname == lname && lvpass != lpass)
		{
			cout << "Wrong Password , try again" << endl;
			system("pause");
			break;
		}
		else if (k == ::i - 1)
		{
			cout << "There is no user with such Name and Password, try again" << endl;
			system("pause");
			break;
		}

	}
	MainMenu();
}
void AddNoteSubMenu()
{
	system("cls");
	cout << endl << endl << endl << endl << line << endl << "                 A D D  A  N O T E    " << endl << line << endl;
	cout << "		[1]ENTER DATE " << endl;
	cout << "		[2]CURRENT DATE" << endl;
	cout << "		[0]GO BACK" << endl << line << endl;

	switch (Validation(2))
	{
	case 1:
	{
		AddNoteDate();
		break;
	}
	case 2:
	{
		AddNote();
		break;
	}
	case 0:
	{
		DiaryMenu();
		break;
	}
	}
}
void AddNote()
{
	// getting the current time to use it in the names of files
	time_t timer;								//creating an object of type time_t
	char cutime[9];
	time(&timer);									//gets the current date and gives this value to timer
	strftime(cutime, 9, "%D", localtime(&timer));	//sets the cutime char array with the data of format %D(mm/dd/yy)

	for (int k = 2; k < 6; k = k + 3)					// puts _ instead of /
	{
		cutime[k] = '_';
	}

	if (currtime.length() == 0)
	{
		for (int m = 0; m < 8; m++)
		{
			::currtime = ::currtime + cutime[m];			//using concatination to convert char array to string
		}
	}
	system("cls");
	cout << endl << endl << endl << endl << line << endl << "                 A D D  A  N O T E    " << endl;
	cout << endl << "	Do not forget to press TAB when you finish" << endl << line << endl;
	ofstream Note(number + "user" + currtime + ".txt", ios::app);	// creating file like 0user04_29_20	in 	
	string unote;													// 	append mode 			
	getline(cin.ignore(), unote, '	');								//using cin.ignore() to get all the lines of text
	Note << unote << endl;
	Note.close();
	if (unote.length() != 0)
	{
		ifstream Notedates(number + "userdates.txt");
		string notedates;
		do
		{
			Notedates >> notedates;
			if (notedates != currtime)
			{
				ofstream ofNotedates(number + "userdates.txt", ios::app);
				ofNotedates << currtime << endl;
				ifstream Dates(number + "userdatesnumber.txt");
				Dates >> dates;
				dates++;
				ofstream ODates(number + "userdatesnumber.txt", ios::trunc);
				ODates << dates;
				break;
			}
			break;
		} while (Notedates >> notedates);

		DiaryMenu();


	}
}
void AddNoteDate()
{
	system("cls");
	cout << endl << endl << endl << endl << line << endl << "                 A D D  A  N O T E    " << endl << endl;
	cout << "		ENTER DATE (mm_dd_yy)" << endl << line << endl;
	cout << ">> ";

	string addnotedate;
	cin >> addnotedate;
	cout << line << endl << "	Do not forget to press TAB when you finish" << endl << line << endl;
	ofstream NoteDate(number + "user" + addnotedate + ".txt", ios::app);
	string notedate;
	getline(cin.ignore(), notedate, '	');
	NoteDate << notedate << endl;;
	NoteDate.close();

	if (notedate.length() != 0)
	{
		ifstream Notedates(number + "userdates.txt");
		string notedates;
		do
		{
			Notedates >> notedates;
			if (notedates != addnotedate)
			{
				ofstream ofNotedates(number + "userdates.txt", ios::app);
				ofNotedates << addnotedate << endl;
				ifstream Dates(number + "userdatesnumber.txt");
				Dates >> dates;
				dates++;
				ofstream ODates(number + "userdatesnumber.txt", ios::trunc);
				ODates << dates;
				break;
			}
			break;
		} while (Notedates >> notedates);


		DiaryMenu();

	}
}
void DiaryMenu()
{
	system("cls");
	cout << endl << endl << endl << endl << line << endl << "                 D I A R Y  M E N U    " << endl << line << endl;
	cout << setw(30) << "[1]ADD NOTES" << endl
		<< setw(31) << "[2]READ NOTES" << endl
		<< setw(33) << "[3]DELETE NOTES" << endl
		<< setw(28) << "[0]GO BACK" << endl << line << endl;

	switch (Validation(3))
	{
	case 1:
	{
		AddNoteSubMenu();
		break;
	}
	case 2:
	{
		ReadNoteMenu();
		break;
	}
	case 3:
	{
		DeleteMenu();
		break;
	}
	case 0:
	{
		SubMainMenu();
	}
	}
}
void ReadNoteMenu()
{
	system("cls");
	cout << endl << endl << endl << endl << line << endl << "                 R E A D   N O T E    " << endl << line << endl;
	cout << "		[1]ENTER DATE" << endl;
	cout << "		[0]GO BACK" << endl;

	switch (Validation(1))
	{
	case 1:
	{
		ReadNoteDate();
		break;
	}
	case 0:
	{
		DiaryMenu();
		break;
	}
	}
}

void ReadNoteDate()
{

	system("cls");
	cout << endl << endl << endl << endl << line << endl << "                 R E A D   N O T E    " << endl << line << endl;
	cout << "	Enter date in format mm_dd_yy" << endl;
	cout << "			";
	string rndate;
	cin >> rndate;
	cout << line << endl;
	ifstream RNDate(number + "user" + rndate + ".txt");
	string rnnote;
	system("cls");
	cout << endl << endl << endl << endl << line << endl << "		" << rndate << endl << line << endl;
	while (getline(RNDate, rnnote))
	{
		cout << rnnote << '\n';
	}
	system("pause");
	RNDate.close();

}

void DeleteMenu()
{
	system("cls");
	cout << endl << endl << endl << endl << line << endl << "            D E L E T E   N O T E    " << endl << line << endl;
	cout << "		[1]ENTER DATE" << endl;
	cout << "		[0]GO BACK" << endl;

	switch (Validation(1))
	{
	case 1:
	{
		DeleteNoteDate();
		break;
	}
	case 0:
	{
		DiaryMenu();
		break;
	}
	}
}
void DeleteNoteDate()
{
	system("cls");
	cout << endl << endl << endl << endl << line << endl << "            D E L E T E   N O T E    " << endl << line << endl;
	cout << "Enter date in format mm_dd_yy " << endl << ">>";
	string dnd, filename;
	cin >> dnd;
	filename = number + "user" + dnd + ".txt";
	int dnresult = remove(filename.c_str());
	if (dnresult == 0)
	{
		cout << "File has been successfully deleted" << endl;
		string oudates, savedates = "";
		bool q = true;
		ifstream odates(number + "userdates.txt");
		while (odates >> oudates)
		{
			if (oudates != dnd)
			{
				savedates.append(oudates);
			}
		}

		odates.close();
		ofstream ouserdate(number + "userdates.txt", ios::trunc);
		ouserdate << savedates;
		ouserdate.close();
		odates.open(number + "userdatesnumber.txt");
		string userdatesnumber;
		odates >> userdatesnumber;
		int iuserdatesnumber = stoi(userdatesnumber);
		iuserdatesnumber--;
		userdatesnumber = to_string(iuserdatesnumber);
		ouserdate.open(number + "userdatesnumber.txt");
		ouserdate << userdatesnumber;
		ouserdate.close();
	}
	else
	{
		cout << "File has not been found" << endl;
	}
}

void SubMainMenu()
{

	cout << setw(31) << "[1]DIARY" << endl
		<< setw(34) << "[2]CALENDAR" << endl
		<< setw(33) << "[0]GO BACK" << endl << line << endl;
	int smmch;       //sub main menu choice
	cin >> smmch;
	switch (smmch)
	{
	case 1:
	{
		DiaryMenu();
		break;
	}
	case 2:
	{
		Calendar_menu();
		break;
	}
	case 0:
	{
		MainMenu();
	}
	}
}
void Calendar_menu()
{
	Calendar_Display newcalendar;
	system("cls");
	cout << endl << endl << endl << endl << line << endl << "		      C A L E N D A R    " << endl << line << endl;
	cout << "			[1]YEAR" << endl;
	cout << "			[2]MONTH" << endl;
	cout << "			[0]GO BACK" << endl;

	cout << endl << line << endl;
	switch (Validation(2))
	{
	case 1:
		system("cls");
		cout << endl << endl << endl << endl << line << endl << "		      C A L E N D A R    " << endl << line << endl;
		newcalendar.Display_year_calendar();
		system("pause");
		break;
	case 2: 	system("cls");
		cout << endl << endl << endl << endl << line << endl << "		      C A L E N D A R    " << endl << line << endl;
		system("cls");
		newcalendar.Display_month_calendar();
		system("pause");
		break;
	case 0:
		SubMainMenu();
		break;
	}
}

// validation check which gets as a parameter variable int mode and if it is set to 1 it means there are only 3 options 
int Validation(int mode)
{
	string vch;
	int bool_chmm = 0;
	while (bool_chmm != 1)
	{
		cin >> vch;
		if (vch.length() == 1)
		{
			if (isdigit(vch[0]))
			{
				if ((vch[0] == '1' || vch[0] == '0') && mode == 1)
				{
					bool_chmm = 1;
				}
				else if ((vch[0] == '1' || vch[0] == '2' || vch[0] == '0') && mode == 2)
				{
					bool_chmm = 1;
				}
				else if ((vch[0] == '1' || vch[0] == '2' || vch[0] == '3' || vch[0] == '0') && mode == 3)
				{
					bool_chmm = 1;
				}
				else
				{
					cout << vch[0];
					cout << "Enter an appropriate number" << endl;
				}
			}
			else
			{
				cout << "Enter a number" << endl;
			}
		}
		else
		{
			cout << "Enter an appropriate value" << endl;
		}
	}
	return stoi(vch);
}

int MainMenu()
{
	system("cls");
	cout << endl << endl << endl << endl << line << endl << "                   M A I N  M E N U    " << endl << line << endl;
	cout << setw(34) << "[1] LOG IN" << endl;
	cout << setw(30) << "	[2] REGISTER" << endl;
	cout << setw(32) << "[0] QUIT" << endl;
	cout << line << endl;
	switch (Validation(2))
	{
	case 1:
	{
		Login();
		break;
	}
	case 2:
	{
		Registration();
		break;
	}
	case 0:
	{
		return 0;
		break;
	}
	}

}
int main()
{
	system("MODE CON COLS=55 LINES=3000");
	MainMenu();
	system("pause");
	return 0;
}

