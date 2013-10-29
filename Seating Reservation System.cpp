/*
cts.cpp - a program to allocate seating arrangements and save a seating chart.

purpose: to make seating reservations and save them to a data structure so
	that it is easily accessible
input: takes in commands from user, and preferences for purchasing tickets
output: outputs map of the seating chart and a confirmation message when
	the user does an action.

	note: if the user's preference is "any" (no preference) then the
		program will attempt to find the optimal location for
		most overall revenue by minimalizing the amount of discounted
		tickets given out.

completed by: Andrew Jang
	on: 3-15-2012



*/



#include <iostream>
using namespace std;


const int ROWS = 14;
const int COLS = 20;
const int MAX_SEATS = 280;	// ROWS X COLS
const int HI_COL_START = 5;
const int HI_COL_END = 16;
const int HI_ROW_START = 1;
const int HI_ROW_END = 8;
const string EMPTY = "---";
const int HI_TICKET = 200;	//price
const int LO_TICKET = 150;
const double DISCOUNT = .90;
const double FULLPRICE = 1.00;
const int MIN_TICKETS = 1;
const int MAX_TICKETS = 12;
const string HI = "hi";
const string LO = "lo";
const string ANY = "any";

struct seating_struct		//main data struct
{
	string	custID_s;
	double	price;
	string	type_s;
	char	row;
	int	seat;
} ;

void initial (seating_struct [MAX_SEATS]);
bool check_ID (seating_struct seats1 [MAX_SEATS], string);
bool check_num (int, string);
void set_type (seating_struct seats1 [MAX_SEATS], int, int, int);
void set_seatrow (seating_struct seats1 [MAX_SEATS], int, int, int);
void print (seating_struct seats1 [MAX_SEATS]);
void cancel (seating_struct seats1 [MAX_SEATS], string);
void request (seating_struct seats1 [MAX_SEATS], string, string, int);
bool search (seating_struct seats1 [MAX_SEATS], string, string, int);
void add_seats (seating_struct seats1 [MAX_SEATS], int, string, int, double);
void fill_seats (seating_struct seats1 [MAX_SEATS], string, string, int);
void print_confirm (seating_struct seats1 [MAX_SEATS], string);
int  count_hilo (seating_struct seats1 [MAX_SEATS], string);

int main ()
{
	string 	action;
	string 	custID;
	int	num;
	string	type;

	seating_struct seats [MAX_SEATS] ;

	initial(seats);

	while (1)			//reads in action
	{
		cin >> action;

		if (action == "QU" )
		{
			break;
		}

		if ( action == "PR" )
		{
			print (seats);
			continue;
		}
	
		cin >> custID;

		if ( action == "CA" )
		{
			cancel (seats, custID);
			continue;
		}

		cin >> num;
		cin >> type;

		if ( action == "RQ" )
		{
				//checks to see if within bounds
				// if so, then allows the request
			if (check_ID (seats, custID) == true 
				&& check_num (num, custID) == true)
			{
				request (seats, custID, type, num);
			}
			continue;
		}
	}
}

// this function initializes the struct (there is only one) by setting names
// to "---" and prices charged to 0
void initial (seating_struct seats1 [MAX_SEATS])
{
	int i;
	int seatnum;
	int rownum;

	for (i=0; i < MAX_SEATS; i++)
	{
		seatnum = ( i % COLS + 1 );
		rownum = ( i / COLS ) ;
		seats1[i].custID_s = EMPTY;
		seats1[i].price = 0;
	
		set_type (seats1, seatnum, rownum, i);
		set_seatrow (seats1, seatnum, rownum, i) ;
	}

	return ;
}

// this function sets each seat to be either a low or high priced seat
// in the struct/array
void set_type (seating_struct seats1 [MAX_SEATS], int seatnum1, int rownum1, 
									int j)
{
	if ( rownum1 < HI_ROW_END )
	{
		if ( seatnum1 >= (HI_COL_START) &&
			seatnum1 <= HI_COL_END )
		{
			seats1[j].type_s = HI;
		}

		else seats1[j].type_s = LO;
	}

	else seats1[j].type_s = LO;

	return;
}

// this function gives each row a letter and assigns a seat number to each
// member of the struct/array
void set_seatrow (seating_struct seats1 [MAX_SEATS], int seatnum1, 
							int rownum1, int j)
{
	char letter;

	letter = 'A';
	seats1[j].row = ( letter + rownum1 );

	seats1[j].seat = seatnum1;

	return;
}

//this function prints out the seating chart and shows the total revenue
void print (seating_struct seats1 [MAX_SEATS])
{
	int i;

	double total_sales;
		
	for (i=0; i < MAX_SEATS; i++)
	{
		if (i == 0)
		{
		//	cout << "    " ;
		// taken out because won't fit, but kept here because
		// the piazza comment made it sound like it should look
		// like it does on the handout, where it looks indented.
		// However, with this indent it doesnt fit into 80 spaces.
		// This was kept in case this would be used for larger screens.
		}

		else if ( i % COLS == 0)
		{
			cout << endl;
		//	cout << "    ";
		// taken out /kept for the same reason.
		}

		else cout << " ";

		cout << seats1[i].custID_s;
		total_sales += seats1[i].price;

	}
	
	cout << endl;
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);		//set pointer to show 2 decimal
	cout.precision(2);				//places
	cout << "Revenue: " << total_sales << endl;

	return ;
}

// checks the number input to see if allowed and within bounds given in consts
// returns true  if acceptable and prints out error msg if not
bool check_num (int req_num, string custID1)
{
	if (req_num >= MIN_TICKETS && req_num <= MAX_TICKETS)
	{
		return true;
	}

	else 
	{
		cout << "    NO " << custID1 << " bad-number" << endl;
		return false;
	}
}

// checks ID to see if already has reservation
// returns true if accepted or prints error msg if not
bool check_ID (seating_struct seats1 [MAX_SEATS], string custID1)
{
	int i;

	for (i=0; i < MAX_SEATS; i++)
	{
		if (custID1 == seats1[i].custID_s )
		{
			cout << "    NO " << custID1 << " already-reserved" 
								<< endl;
			return false;
		}
	}

	return true;
}

// takes the requested info and channels it through to a search function
// if search returns false (nothing found), prints out an error msg
void request (seating_struct seats1 [MAX_SEATS], string custID1, string type1, 
								int num1)
{
	bool done;

	done = false;

	if ( type1 == HI )
	{
		done = search (seats1, custID1, type1, num1);
	}

	else if ( type1 == LO )
	{
		done = search (seats1, custID1, type1, num1);
	}
	
	// this is probably the most interesting section of the code
	// I made it so that the main priority was to minimize any discounts
	// by grouping members all together first. My first thought was to
	// have it default to filling up HI first, but that basically made
	// it so that there were too many LO seats left at the end.
	// By filling up the LO seats first until they have equal numbers
	// and then switching between the two, this arrangement usually gave
	// the best, or close to best results with the rand.dat data files.
	else if ( type1 == ANY )
	{
		string temp_type;

			//allows the LO seats to be filled more generously
			// to allow hi spenders their chance
		if ( (count_hilo (seats1, LO))  >  (count_hilo (seats1, HI)) )
		{
			temp_type = ANY + LO;
			done = search (seats1, custID1, temp_type, num1); 
			// almost same as request lo but doesn't run the
			// fill_seats function (searches for consecutive seats)
		}

		else
		{
			temp_type = ANY + HI;
			done = search (seats1, custID1, temp_type, num1); 
			//almost same as request hi but doesn't run the 
			// fill_seats func. (searches for consecutive seats)
		}
		if (done == false)
		{
			temp_type = ANY;
			done = search (seats1, custID1, temp_type, num1); 
			//allows searching for all seats to fill any empty
			// space if the other two functions don't have enough
			// space
		}
	}

	if (done == false)
	{
		cout << "    NO " << custID1 << " not-available" << endl;
	}

	return;
}

// searches for available consecutive seats. if found, uses a saving function.
// if nothing consecutive is found, but finds that there are enough total seats
// then it will run a seat-filling function.
// returns true if any seats can be reserved, false if not.
bool search (seating_struct seats2 [MAX_SEATS], string custID2, string type2,
								 int num2)
{
	int i;
	int count;	// # of consecutive available seats found
	int total;	// # total available seats found

	count = 0;
	total = 0;

	for (i=0; i < MAX_SEATS; i++)
	{
		if ( seats2[i].seat == 1 ) //each row starts at 0 consecutive
		{						//seats
			count = 0;
		}

		if ( ( seats2[i].type_s == type2 || type2 == ANY ) ||
			( type2 == ANY+HI && seats2[i].type_s == HI ) ||
			( type2 == ANY+LO && seats2[i].type_s == LO ) )
		{
			if (seats2[i].custID_s == EMPTY )
		
			{
				count++;
				total++;
			}
		}

		else count = 0;		// if nothing found, resets to 0
	
		if ( count == num2 )
		{
			add_seats (seats2, i, custID2, num2, FULLPRICE);
			print_confirm (seats2, custID2);
			return true;
		}	
	}

	if ( total >= num2 && 
		( type2 == HI || type2 == LO || type2 == ANY ) )
	{
		fill_seats (seats2, custID2, type2, num2);
		print_confirm (seats2, custID2);
		return true;
	}

	return false;
}

// fills in the struct info if enough seating spots are found from prev funcs
// uses info passed in from previous functions about what seats to reserve
// and how much to charge the customer (including discount) and saves it to
// the struct/array
// It can save one seat each time it is run or any number of consecutive seats
void add_seats (seating_struct seats4 [MAX_SEATS], int last, string custID4, 
							int num4, double disc)
{
	int i;
	int start;

	start = ( last - num4 + 1);

	for (i=start; i < (start + num4 ); i++)
	{
		seats4[i].custID_s = custID4;

		if (seats4[i].type_s == HI)		//how much to charge
		{
			seats4[i].price = (HI_TICKET * disc);
		}

		if (seats4[i].type_s == LO)
		{
			seats4[i].price = (LO_TICKET * disc);
		}
	}
}

//this is the function that finds the individual seats that are empty
// and sends them one at a time to the addseat function to be saved/reserved.
// a counter makes sure that it stops when all seats to be reserved are done.
void fill_seats (seating_struct seats3 [MAX_SEATS], string custID3, 
						string type3, int num3)
{
	int i;
	int counter;
	
	counter = num3;
	
	for (i=0; i < MAX_SEATS; i++)
	{
		if (seats3[i].custID_s == EMPTY )
		{
			if (seats3[i].type_s == type3)
			{
				add_seats (seats3, i, custID3, 1, DISCOUNT);
				counter--;
			}
	
			else if (type3 == ANY || type3 == ANY+LO 
						|| type3 == ANY+HI)
			{
				add_seats (seats3, i, custID3, 1, DISCOUNT);
				counter--;
			}

			if (counter == 0)
			{ 
				return;
			}
		}
	}
}

// this function checks the struct array and prints out the confirmation
// for the reservation. theoretically, this can also be used whenever required 
// since it conducts an immediate search for the name in question.
// it saves the seat number's position in the struct/array so that the
// total price can first be calculated before everything is printed out.
// this will cout the custID, total cost, number of tickets, and seat numbers.
void print_confirm (seating_struct seats4 [MAX_SEATS], string custID4)
{
	int i;
	int total_tickets;
	double total_cost;
	int hits[MAX_TICKETS];
	int count;

	total_tickets = 0;
	total_cost = 0;
	count = 0;

	for (i=0; i < MAX_TICKETS; i++)
	{
		hits[i] = 0;
	}

	for (i=0; i < MAX_SEATS; i++)
	{
		if (custID4 == seats4[i].custID_s)
		{
			total_tickets++;
			total_cost += seats4[i].price;
			hits[count] = i;
			count++;
		}
	}

	cout << "    OK " << custID4 << " " << total_cost << " " 
							<< total_tickets;

	for (i=0; i < count; i++)
	{
		cout << " " << seats4[hits[i]].row << seats4[i].seat;
	}

	cout << endl;

	return;
}

// counts the number of available seats of a certain type and returns the #
int count_hilo (seating_struct seats5 [MAX_SEATS], string hilo)
{
	int i;
	int count;

	count = 0;

	for (i=0; i < MAX_SEATS; i++)
	{
		if (seats5[i].type_s == hilo)
		{
			if (seats5[i].custID_s == EMPTY)
			{
				count++;
			}
		}
	}

	return count;
}

// finds and cancels any exiisting reservations. if none found, will give msg
// if any are found, it will reset them to the default initialization values
void cancel (seating_struct seats5 [MAX_SEATS], string custID5)
{
	bool found;
	int i;

	found = false;

	for (i=0; i < MAX_SEATS; i++)
	{
		if (custID5 == seats5[i].custID_s )
		{
			seats5[i].custID_s = EMPTY;
			seats5[i].price = 0;
			found = true;
		}
	}
	if ( found = true)
	{
		cout << "    OK " << custID5 << " cancelled" << endl;
	}
	
	else if ( found = false)
	{
		cout << "    NO " << custID5 << " no-reservation" << endl;
	}

	return;
}
