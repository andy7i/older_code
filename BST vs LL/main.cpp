//
// main.cpp
//
//  Created by Andrew Jang
//      on: 7.17.2012
//

#ifndef BST_main_cpp
#define BST_main_cpp

#include <iostream>
#include <fstream>
#include <cctype>
#include <sys/time.h>

#include "BST.h"
#include "LL.h"

using namespace std;

string makeLowercase (string changing);


int main()
{
    BST wordsBST;
    LL wordsLL;
    ifstream dataFile;

    string input;
    int userInput = 0;
    timeval start, end;
    bool didfindBST;
    bool didfindLL;
    double elapsedTime;

    dataFile.open ("randomized.txt");

    if (! dataFile.is_open() )
    {
        return 0;
    }

    while (dataFile >> input)
    {
        if (input == "")
        {
            break;
        }

        input = makeLowercase (input);

        wordsBST.insert(input);
//        wordsLL.insert(input);        // old way of adding (too slow)
    }

    dataFile.close();

    wordsLL.setHead( wordsBST.createLL() );     //newer, faster LL creation

    while (1)
    {
        cout << "-------------------------------------------------" << endl
            << "Please select from the following:" << endl
            << "1. Find the size of the BST" << endl
            << "2. Find the height of the BST" << endl
            << "3. Search for a particular word in the BST and LL" << endl
            << "4. Delete a Node from both the BST and LL" << endl
            << "5. Quit" << endl
            << "-------------------------------------------------" << endl;

        cin >> userInput;

        if (userInput == 1)
        {
            cout << "Size is: " << wordsBST.size() << endl;
        }
        else if (userInput == 2)
        {
            cout << "Height is: " << wordsBST.height() << endl;
        }
        else if (userInput == 3)
        {
            cout << "Please input a word to search for" << endl;
            cin >> input;
            input = makeLowercase (input);

            //start timer
            gettimeofday(&start, NULL);
            didfindLL = wordsLL.find(input);
            gettimeofday(&end, NULL);    //stop timer
            elapsedTime = (end.tv_sec - start.tv_sec) * 1000.0;
            elapsedTime += (end.tv_usec - start.tv_usec) / 1000.0;

            cout << "Time elapsed for LL: " <<
                        elapsedTime / 1000.0 << " seconds" << endl;
            

            //start timer
            gettimeofday(&start, NULL);
            didfindBST = wordsBST.find(input);
            gettimeofday(&end, NULL);    //stop timer
            elapsedTime = (end.tv_sec - start.tv_sec) * 1000.0;
            elapsedTime += (end.tv_usec - start.tv_usec) / 1000.0;

            cout << "Time elapsed for BST: " <<
                        elapsedTime / 1000.0 << " seconds" << endl;

            if (didfindBST && didfindLL )
            {
                cout << "Word exists in BST and LL." << endl;
            }
            else cout << "Word not found." << endl;
        }
        else if (userInput == 4)
        {
            cout << "Please input a word to delete" << endl;
            cin >> input;
            input = makeLowercase (input);

            if (wordsBST.deleteNode (input) && wordsLL.deleteNode (input) )
            {
                cout << "Word was deleted from BST and LL." << endl;
            }
            else cout << "Word not found." << endl;
        }
        else if (userInput == 5)
        {
            return 0;
        }
        else continue;
    }

    return 0;
}


string makeLowercase (string changing)
{
    for (int i = 0; changing[i] != '\0'; i++)
    {
        changing[i] = tolower(changing[i]);
    }
    return changing;
}


#endif
