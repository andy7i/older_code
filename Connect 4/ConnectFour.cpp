#include <iostream>
#include "ConnectFour.h"
//
// constructor
// purpose: sets up player color, reads in board, and sets up random number
//                                                                  generator
// output: none
//
ConnectFour::ConnectFour()
{
	char Mycolor;

	cin >> Mycolor;

	if (Mycolor == PLAYER1)
	{
		m_playerColor = PLAYER1;
		m_opponentColor = PLAYER2;
	}

	else
	{
		m_playerColor = PLAYER2;
		m_opponentColor = PLAYER1;
	}

    srand( (unsigned)time(NULL) );      //seeds random number generator

	for (int i = ROWS-1; i >= 0; i--)
	{
		for (int j = 0; j < COLS; j++)
		{
			cin >> m_board [i] [j];
		}
	}
}


//
// purpose: this function sets up the logic order for what strategy to use
// arguments: none
// returns: nothing
// outputs: nothing
// note: it calls each strategy, then if the strategy works (returns true)
//      then it will call the place function. No further work is done.
//
void ConnectFour::move()
{
    if (findemptycol () == FULL)        //this will check if the board is full
    {
        m_nextMove = FULL;
        place ();
    }

    else if (findfour(m_playerColor) == true)       //player win
	{
		place();
	}

	else if (findfour(m_opponentColor) == true)     // opp win
	{
		place();
	}

	else if (lookaheadone () == true)
	{
		place();
	}

    else if (randomDefense () == true)
	{
		place();
	}

	else if	(randomMove() == true)
    {
		place();
	}
}


//
// purpose: checks every location to see if a win is possible to achieve
//          and calls on the checkwin function to check it
// arguments: color - based on the color specified previously in the main func.
//          also uses m_temp_col/m_temp_row to pass into the checkwin function
// returns: true or false, based on if a win is possible or not
// output: none
//
bool ConnectFour::findfour(char color)
{
	for (int j = 0; j < COLS; j++)
	{
		m_temp_col = j;
		m_temp_row = findrow (m_temp_col);

		if (m_temp_row == FULL)
		{
			continue;
		}

		m_board [m_temp_row][m_temp_col] = color;

		if (checkwin (color) == true)
		{ 
			m_nextMove = j;
			m_board [m_temp_row][m_temp_col] = EMPTY;
			return true;
		}

		m_board [m_temp_row][m_temp_col] = EMPTY;
	}

	return false;
}


//
// purpose: calls 4 win-checking functions for the current location being looke
//          at.
// arguments: uses the color being checked for and passes it along
// returns true if any of the functions find a win
// output: none
//
bool ConnectFour::checkwin (char color)
{
	if ( (check_diagonalbottomL (color) == true) 
        || (check_diagonaltopL (color) == true) 
	    || (check_horizontal (color) == true) 
        || (check_vertical (color) == true) )
	{
		return true;
	}

	else return false;
}


//
// purpose: finds the first empty location in a column
// arguments: uses the m_board and a column number being passed in
// returns the value of the row that is empty, if empty returns a sentinel
//          (FULL)
// 
int ConnectFour::findrow (int col)
{
	for (int i = 0; i < ROWS; i++)
	{
		if (m_board[i][col] == EMPTY)
		{
			return i;
		}
	}

	return FULL;
}

//
// purpose: to output the location of the move
// arguments: uses the m_nextMove which is specified by other functions
// output: the next move
// returns: nothing
//
void ConnectFour::place()
{
	cout << m_nextMove+1 << endl;
}


//
// purpose: to get magical bonus points. also to set up the best potential
//          game-winning move. uses 3 nested for loops to check a player's move,
//          the opponent's move, and then another player's move.
// arguments: uses the m_board and passes along relevant color info and the
//          locations being checked into the win-checking functions it calls
// returns true if there are any potential game-winning moves (in 2 moves)
//
bool ConnectFour::lookaheadone ()
{
    int winlocations[COLS];         // an array to store locations where wins
                                    // were possible from
    for (int i = 0; i < COLS; i++)
    {                                  // initializing
            winlocations [i] = 0;
    }

	for (int a = 0; a < COLS; a++)      //first for loop to check player moves
	{
		int testcol1;
		int testrow1;

		testcol1 = a;
		testrow1 = findrow(testcol1);

		if (testrow1 == FULL)
		{
			continue;
		}

		m_board[testrow1][testcol1] = m_playerColor;    // temporarily sets
                                                        // the move on the board
		m_temp_col = testcol1;
		m_temp_row = findrow(m_temp_col);

		if (checkspotforwin (m_opponentColor) == true)  //makes sure the opp
		{                                               // can't win from that
			m_board[testrow1][testcol1] = EMPTY;        // move
			continue;
		}

		for (int b = 0; b < COLS; b++)          // second for loop for opp move
		{                                       // (very similar to first loop)
			int testcol2;
			int testrow2;

			testcol2 = b;
			testrow2 = findrow(testcol2);

			if (testrow2 == FULL)
			{
				continue;
			}

			m_board[testrow2][testcol2] = m_opponentColor;

            for (int c = 0; c < COLS; c++)  //third for loop for players second
            {                               // move
                m_temp_col = c;
	    		m_temp_row = findrow(m_temp_col);

		    	if (checkspotforwin (m_playerColor) == true)
		    	{
                    winlocations[testcol1]++;  //records each win scenario
		    	}                               // (saves the location of the
            }                                   // first move)

			m_board[testrow2][testcol2] = EMPTY; //deletes the temp move
		}

		m_board[testrow1][testcol1] = EMPTY;        //deletes the temp move
	}

    m_nextMove = findmax(winlocations);         //finds the location that offers
                                                // the most # of possible win
    if (m_nextMove == SENTINEL)                 // scenarios.
    {
        return false;                           //this is in case no wins are
    }                                           // possible.

    else return true;
}


//
// purpose: checks a particular point for a win
// arguments: uses the color (passed in) and the temp row/col info
// returns true if a win is possible in that spot
// output: nothing
//
bool ConnectFour::checkspotforwin(char color)
{
	if (m_temp_row == FULL)
	{
		return false;
	}

	m_board [m_temp_row][m_temp_col] = color;

	if (checkwin (color) == true)
	{ 
		m_board [m_temp_row][m_temp_col] = EMPTY;
		return true;
	}

	m_board [m_temp_row][m_temp_col] = EMPTY;
	return false;
}


//
// purpose: finds the location offering the max # of wins
// arguments: the array of win locations
// returns: the location of the column with the max # of wins
// output: nothing
//
int ConnectFour::findmax(int winlocations[COLS])
{
    int max = 0;
    int col = 0;

    for (int i = 0; i < COLS; i++)
    {
        if (winlocations[i] > max)
        {
            max = winlocations[i];
            col = i;
        }
    }

    if (max == 0)
    {
        return SENTINEL;
    }

    else return col;
}


//
// purpose: places in random location, checks to make sure opp doesnt win
// returns: true if move possible
// output: nothing:
//
bool ConnectFour::randomDefense ()
{
    int colstried = 0;
    bool nums[COLS];
    int temprow;

    for (int j = 0; j < COLS; j++)
    {
        nums[j] = 0;
    }

    while (colstried != COLS)
	{
		m_temp_col = rand() % 7;
		temprow = findrow (m_temp_col);

		if (nums[m_temp_col] == 0)
		{
			colstried++;
			nums[m_temp_col]++;
		}

        if (temprow == FULL)
        {
            continue;
        }

		m_board[temprow][m_temp_col] = m_playerColor;

        m_temp_row = findrow (m_temp_col);

		if (checkspotforwin (m_opponentColor) == false)
		{
			m_nextMove = m_temp_col;
			return true;
		}

        m_board[temprow][m_temp_col] = EMPTY;
	}
    
    return false;
}

//
// purpose: places in random location
// arguments: none
// returns: true if possible
//
bool ConnectFour::randomMove()
{
    m_nextMove = findemptycol();
    return true;
}


//
// purpose: finds the location of a random empty column.
// returns: # of the empty col
//
int ConnectFour::findemptycol()
{
    int colstried = 0;
    bool nums[COLS];

    for (int j = 0; j < COLS; j++)
    {
        nums[j] = 0;
    }

    while (colstried != COLS)
    {
        int x = rand() % 7;

        if (nums[x] == 1)
        {
            continue;
        }

        for (int i = 0; i < ROWS; i++)
        {
            if (m_board[i][x] == EMPTY)
            {
                return x;
            }
        }

        nums[x] = 1;
        colstried++;
    }
    return FULL;

}


//
// purpose: checks for a diagonal (bottom left to top right) win
// arguments: color is passed in
// return true if possible
//
bool ConnectFour::check_diagonalbottomL (char color)
{
	int count = 0;

	int testcol = m_temp_col;
	int testrow = m_temp_row;

	while( (testcol >= 0 && testcol < COLS) && (testrow >= 0 && testrow < ROWS) )
	{
		if (m_board [testrow][testcol] == color)
		{
			count++;
		}

        else break;

		testrow++;
		testcol--;
	}

	testcol = m_temp_col+1;
	testrow = m_temp_row-1;

	while ( (testcol >= 0 && testcol < COLS) && (testrow >= 0 && testrow < ROWS) )
	{
		if (m_board [testrow][testcol] == color)
		{
			count++;
		}
        
         else break;

		testrow--;
		testcol++;
	}

	if (count >= WIN)
	{
		m_nextMove = m_temp_col;
		return true;
	}

	else return false;
}


//
// purpose: checks for a diagonal (top left to bottom right) win
// arguments: color is passed in
// return true if possible
//
bool ConnectFour::check_diagonaltopL (char color)
{
	int count = 0;

	int testcol = m_temp_col;
	int testrow = m_temp_row;

	while ( (testcol >= 0 && testcol < COLS) && (testrow >= 0 && testrow < ROWS) )
	{
		if (m_board [testrow][testcol] == color)
		{
			count++;
		}

		else break;

		testrow++;
		testcol++;
	}

	testcol = m_temp_col-1;
	testrow = m_temp_row-1;

	while ( (testcol >= 0 && testcol < COLS) && (testrow >= 0 && testrow < ROWS) )
	{
		if (m_board [testrow][testcol] == color)
		{
			count++;
		}

		else break;

		testrow--;
		testcol--;
	}


	if (count >= WIN)
	{
		m_nextMove = m_temp_col;
		return true;
	}

	else return false;
}


//
// purpose: checks for a horizontal win
// arguments: color is passed in
// return true if possible
//
bool ConnectFour::check_horizontal(char color)
{
	int count = 0;
	int testcol = m_temp_col;
	int testrow = m_temp_row;

	while (testcol >= 0 && testcol < COLS)
	{
		if (m_board [testrow][testcol] == color)
		{
			count++;
		}

		else break;

		testcol--;
	}

	testcol = m_temp_col + 1;

	while (testcol >= 0 && testcol < COLS)
	{
		if (m_board [testrow][testcol] == color)
		{
			count++;
		}

		else break;

		testcol++;
	}

	if (count >= WIN)
	{
		m_nextMove = m_temp_col;
		return true;
	}

	else return false;
}


//
// purpose: checks for a vertical win
// arguments: color is passed in
// return true if possible
//
bool ConnectFour::check_vertical(char color)
{
	int count = 0;
	int testcol = m_temp_col;
	int testrow = m_temp_row;

	while (testrow >= 0 && testrow < ROWS)
	{
		if (m_board [testrow][testcol] == color)
		{
			count++;
		}

		else break;

		testrow--;
	}

	testrow = m_temp_row + 1;

	while (testrow >= 0 && testrow < ROWS)
	{
		if (m_board [testrow][testcol] == color)
		{
			count++;
		}

		else break;

		testrow++;
	}

	if (count >= WIN)
	{
		m_nextMove = m_temp_col;
		return true;
	}

	else return false;
}
