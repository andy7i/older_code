#include <iostream>
using namespace std;

// heatwave.cpp
//	purpose: to list the temperatures of each heatwave 
//				(3+ days with temps over 90)
//	input: a list of daily temperatures as integers
//	output: temperatures of the days that were part of a heatwave
//
//	completed by: Andrew Jang
//		on: 2-23-12
//

const	int	MAX_TEMPS = 1000;
const	int	HEAT_TEMP = 90;		// upper limit of heat waves

int	read_in(int[]);
void	scan_temps(int[], int);
int	print_temps(int[], int, int);


int main()
{
	int	temps[MAX_TEMPS];
	int	num_temps;
	

	num_temps = read_in(temps);	// read in the data
	scan_temps(temps, num_temps);

	return 0;

}

// read_in -- read in the temperatures from cin, store in array
//        data consists of one integer representing the number of temps
//        then that many ints
//   returns: the number of temperatures read in
//   affects: modifies the array by storing data
//      note: if number of temps exceeds MAX_TEMPS, then complain and exit(1)
//
int read_in(int list[MAX_TEMPS])
{
 
        int     num;
        int     i;

        cin >> num;

        for (i=0; i<num; i++)
        {
                cin >>  list[i];
        }
 
 
        return num;
}

//
// scan_temps - reads the temps to find heat waves
// 	function: to find 3 consecutive numbers that are over 90'F
//	return: does not return any value, but runs another function if 3 consecutive dates are over 90'F
//
//

void scan_temps(int list[MAX_TEMPS], int num)
{
	int	i;


	for (i=0; i<(num-2); i++)
	{
		if ( ( list[i] >= HEAT_TEMP)  && ( list[i+1] >= HEAT_TEMP) && ( list[i+2] >= HEAT_TEMP) )
		{
			i = print_temps(list, i, num);
		}

		else ;
	}
}

// print_temps - reads each temp and prints out each temp that is over 90' until it reaches one that is below 90
//	function: prints all consecutive temps over 90'
//

int print_temps(int list[MAX_TEMPS], int cur, int tot)
{
	int i;

	cout << "Started on " << cur << ":";

	for (i=cur; i<tot; i++) 
	{
		if (list[i] >= 90)
		{
			cout << " " << list[i];
		}
		
		else
		{
			cout << endl;
			return (i);
		}

	}


	return i;

}



