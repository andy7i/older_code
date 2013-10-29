#include <iostream>

/* 
	chkdate.cpp -- is a program that checks whether a date is valid or not
	usage: ./chkdate
	input: MM DD YYYY
	output: "Y" or "N" depending on whether the date is valid or not
	note: user is not prompted, and output has no explanation

	created by: Andrew Jang
	creation date: 2-14-2012
*/

using namespace std;

const int MAX_YEAR = 9999;	//end range of years
const int MIN_YEAR = 1;		//start range of years
const int MAX_MON = 12;		// end range of months
const int MIN_MON = 1;		// start range of months
const int MIN_DAY = 1;		//start range of days
const int MAX_DAY = 31; 	// end range of days possible
const int CENT = 100;		//century rule for non-leap years
const int LCENT = 400;		// 400 year rule for leap years
const int LEAP = 4;		// 4 year rule for leap years
const int LDAYFEB = 29;		// days in Feb in leap year
const int DAYFEB = 28;		// days in Feb normally
const int FEB = 2;		// numeric representation of month

bool isLeap(int);		// function to check if year is leap
int month,day,year;		// introducing values

int main ()
{

	int monthDays[MAX_MON] = { 31, 28, 31, 30, 31, 30, 
				31, 31, 30, 31, 30, 31 };
				// setting number of days for the month

	cin >> month >> day >> year;	//read in Month, Day, Year

	if ( ((year > MAX_YEAR) || (year < MIN_YEAR))
		|| ((month < MIN_MON) || (month > MAX_MON))
		|| ((day < MIN_DAY) || (day > MAX_DAY)) )
				// quick and dirty check to see if ranges
					//make overall sense so it doesn't
					//have to do the later, longer processes
					//unnecessarily
	{
		cout << "N" << endl;	//signals "not valid"
	}

	else				//if quick check is okay, moves on
	{
		if (month == FEB)	//if Feb, runs leap year program
		{
			if ( isLeap(year) == true)	// checks if leapyear
			{
				if (LDAYFEB >= day)
				{
					cout << "Y" << endl;	//signals "valid"
				}

				else cout << "N" << endl;
			}

			else
			{
				if (DAYFEB >= day)
				{
					cout << "Y" << endl;
				}

				else cout << "N" << endl;
			}

		}

		else if ( monthDays[month-1] >= day )	//checks day with day limit
		{
			cout << "Y" << endl;  
		}

		else cout << "N" << endl;



	}
}

bool isLeap(int)			//checks if year is leap year
{
	if (year % LCENT == 0)		// 400 leapyear rule
	{
		return true;
	}

	else if (year % CENT == 0)	// 100 non leapyear rule
	{
		return false;
	}

	else if (year % LEAP == 0)	// 4 leapyear rule
	{
		return true;
	}

	else return false;


}
