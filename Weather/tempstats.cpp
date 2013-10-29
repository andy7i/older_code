#include <iostream>
using namespace std;

// tempstats.cpp
//   purpose: analyze a list of daily temperatures 
//     input: a list of daily temperatures as integers
//    output: some statistics about the temperature list
//
//    output: 
//	      highest: 67
//            lowest: 41
//            average: 52.3
//            days above: xxx
//            days below: xxx
//
//    completed by: Andrew Jang
//              on: 2-22-12
//

const int	MAX_TEMPS = 1000;

int	read_in(int[]);
double	get_avg(int[], int);
int	get_max(int[], int);
int	get_min(int[], int);
int	get_num_above(int[], int, double);
int	get_num_below(int[], int, double);
void	report(int, int, double, int, int);

int main()
{
	int	temps[MAX_TEMPS];
	int	num_temps;
	int	highest, lowest;
	double	avg;
	int	days_above;
	int	days_below;
	
	num_temps = read_in(temps);		// read in the data
	avg       = get_avg(temps, num_temps);
	highest   = get_max(temps, num_temps);
	lowest    = get_min(temps, num_temps);
	days_above=get_num_above(temps, num_temps, avg);	//# days above avg
	days_below=get_num_below(temps, num_temps, avg);	//# days below avg

	report(highest, lowest, avg, days_above, days_below);	// printing out
	return 0;
}
//
// read_in -- read in the temperatures from cin, store in array
//        data consists of one integer representing the number of temps
//        then that many ints
//   returns: the number of temperatures read in
//   affects: modifies the array by storing data
//      note: if number of temps exceeds MAX_TEMPS, then complain and exit(1)
//
int read_in(int list[MAX_TEMPS])
{
	int	num;
	int 	i;

	cin >> num;
	for (i=0; i<num; i++)
	{
		cin >>  list[i];
	}
	
	
	return num;
}
//
// get_avg -- compute the average of all the temps in the array
//    args: list[] the data
//          num    the number of temps in the array
//    rets: the average
//    note: if num is 0, then print a message and exit(1)
//
double get_avg(int list[MAX_TEMPS], int num)
{
	double	avg ;
	int	total ;
	int	i;

	total = 0 ;
	
	if ( num == 0 )
	{
		cout << "There is no data" << endl;
		
		exit(1);
	}

	else for (i=0; i<num; i++)
	{
		(total = total + list[i] ) ;
	}	

	avg = total / num ;

	return avg;



}

//
// get_max -- returns the maximum value in a list of num ints
//
int get_max(int list[MAX_TEMPS], int num)
{
	int	i;
	int	max;

	max = list[0];

	for (i=0; i<num; i++)
	{
		if (list[i] > max)
		{
			max = list[i];
		}
	}

	return max ;


}

//
// get_min -- returns the minimum value in a list of num ints
//
int get_min(int list[MAX_TEMPS], int num)
{

	int	i;
	int	min;

	min = list[0];

	for (i=0; i<num; i++)
	{
		if (list[i] < min)
		{
			min = list[i];
		}
	}

	return min ;



}

// 
// get_num_above -- returns the number of elements in an array
//                  that are above a given value
//
int	get_num_above(int list[], int num, double val)
{

	int	i;
	int	count;

	count = 0;

	for (i=0; i<num; i++)
	{
		if (list[i] > val)
		{
			count++ ;
		}
	}

	return count ;

}

// 
// get_num_below -- returns the number of elements in an array
//                  that are below a given value
//
int	get_num_below(int list[], int num, double val)
{

	int	i;
	int	count;

	count = 0;

	for (i=0; i<num; i++)
	{
		if (list[i] < val)
		{
			count++ ;
		}
	}

	return count;

}

//
// report -- displays the results in the required format
//    args: max, min, average, number above, number below
//    rets: nothing, just prints things

void	report (int highest1, int lowest1, double avg1, int days_above1, int days_below1)
{


				//junk
//	int	highest1
//	int	lowest1
//	double	avg1
//	int	days_above1
//	int	days_below1


	cout << "highest: " << highest1 << endl;
	cout << "lowest: " << lowest1 << endl;
	cout << "average: " << avg1 << endl;
	cout << "days above: " << days_above1 << endl;
	cout << "days below: " << days_below1 << endl;

	//return 0;

}
