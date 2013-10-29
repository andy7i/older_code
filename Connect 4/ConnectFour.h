/*
    ConnectFour.h - a program that acts as player AI for the game connect 4
 
Purpose: reads in connect4 playing board info and makes an intelligent move.
        It will try to (in order):
            win,
            block the oppoment's win,
            set up for a win, or
            place a move randomly (but in a location that will not allow the
                                                            opponent to win.
        It will also output 0 if the board is full and will randomly place a
        move if all available options lead the opponent to win.

Input: Reads in the player color and the current playing board for connect four.

Output: outputs one move (a number).

completed by: Andrew Jang
    on: 4-23-2012

*/


#include <iostream>
using namespace std;

const int ROWS = 6;
const int COLS = 7;
const char PLAYER1 = 'R';
const char PLAYER2 = 'Y';
const char EMPTY = '.';
const int FULL = -1;                //when a column is full
const int WIN = 4;
const int SENTINEL = -2;            // when 0 potential win solutions exist

class ConnectFour
{
	public:
		ConnectFour();              //constructor
		void move();

	private:


		char m_playerColor;
		char m_opponentColor;
		char m_board [ROWS][COLS];
		int m_temp_row;             //used to save the current col/row so that
		int m_temp_col;             // it is easy to use between diff functions
		int m_nextMove;         //saves the location of the next move

		void place ();
		int findrow (int);      //finds empty row

		bool findfour (char);               //finds 4-in-a-row
		bool checkwin (char);               //checks for wins
		bool checkspotforwin (char);        //checks one location for a win

		bool check_diagonalbottomL (char);  //these 4 will check individual
		bool check_diagonaltopL (char);     //ways of winning
		bool check_horizontal (char);
		bool check_vertical (char);

		bool lookaheadone ();           //fortune-telling / finding best move
		bool randomDefense ();
		bool randomMove ();
        int findemptycol();             //randomly checks for an empty column
        int findmax(int[COLS]);         //finds the largest win-producing move
};
