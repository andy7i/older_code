#include <iostream>
using namespace std;

//tempfreq.cpp
//	purpose: analyze a list of daily temperatures for frequency of temp
//	input: a list of daily temperatures as integers
//	output: frequency of temperatures from 55-99 all listed
//
//	completed by: Andrew Jang
//		on 2-23-12

const	int	MAX_TEMPS = 1000;
const	int	TEMP_MAX = 99;		//upper limit of temps interested in
const	int	TEMP_MIN = 55;		//lower limit of temps interested in

int	read_in(int[]);
void	count_temp(int[], int, int[]);
void	report(int[]);

int main()
{
	int	temps[MAX_TEMPS];
	int	tempcount[MAX_TEMPS];
	int	num_temps;

	num_temps = read_in(temps);	//read  in the data

	count_temp(temps, num_temps, tempcount);

	report(tempcount);
	
	return 0;
}


// read_in -- read in the temperatures from cin, store in array
// data consists of one integer representing the number of temps
// returns: the number of temps read in
// affects: stores temperature data into array
// note: if # of attempts is greater than MAX_TEMPS then exits

int read_in (int list[MAX_TEMPS])
{
	int	num;
	int	i;

	num = 0;

	cin >> num;

	for (i=0; i<num; i++)
	{
		cin >> list[i];
	}

	return num;
}

// count_temp -- analyzes the data to store counters for each temp reported
// returns: nothing (void)
// affects: counts the temperature frequencies into the tempcount1 array

void count_temp ( int list[MAX_TEMPS], int num1, int tempcount1[MAX_TEMPS])
{

	int	i;
	int	cur;

	for (i=TEMP_MIN; i<=TEMP_MAX; i++)		// cleaning closets
	{
		tempcount1[i] = 0;
	}
	
	for (i=0; i<num1; i++)		// counting for each temp
	{
		cur = list[i];
		tempcount1[cur]++ ;
	}
	
	return;
}


// reports - prints out everything from from start of range to end
// output: prints frequency of each temp in a range
// affects: nothing

void report ( int tempcount2[MAX_TEMPS] )
{

	int	i;

	for (i=TEMP_MIN; i<=TEMP_MAX; i++)
	{
		cout << i << ": " << tempcount2[i] << endl;
	}

	return;
}
