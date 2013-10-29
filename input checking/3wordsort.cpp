#include <iostream>

/* 
      3wordsort.cpp -- program to print out three words in alpha order
     usage: ./3wordsort
     input: three words
    output: the three words in alphabetical order, separated by spaces
      note: no prompt for user, no explanation on output
    
    modified by: Andrew Jang
    modified on: 2-14-12
 */

using namespace std;

void printInOrder(string, string, string);	// tell compiler about this

int main()
{
	string	w1,w2,w3;		// input values
	
	cin >> w1 >> w2 >> w3;		// read in three values
	printInOrder(w1,w2,w3);		// function does not return anything
	return 0;
}

//
// printInOrder() prints out the three words in alpha order
//		  with spaces between them, no return value
//
void printInOrder(string x, string y, string z)	
{
	if ( ( x <= y) && ( x <= z) ) {
		if ( y < z) {
		cout << x << ' ' << y << ' ' << z << endl;
		}
		else cout << x << ' ' << z << ' ' << y << endl;
	}

        if ( ( y <= x) && ( y <= z) ) {
                if ( x < z) {
                cout << y << ' ' << x << ' ' << z << endl;
                }
                else cout << y << ' ' << z << ' ' << x << endl;
        }
        if ( ( z <= y) && ( z <= x) ) {
                if ( y < x) {
                cout << z << ' ' << y << ' ' << x << endl;
                }
                else cout << z << ' ' << x << ' ' << y << endl;
        }

	// your code here
	// your function does NOT use return
	// Instead, it sends values to cout
}
