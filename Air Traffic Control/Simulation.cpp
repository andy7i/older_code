/*

   Simulation.cpp


   created by:
        Andrew Jang
    on:
        6.26.2012

*/

#ifndef SIMULATION_CPP
#define SIMULATION_CPP

#include <iostream>
#include <fstream>
#include "Airplane.h"
#include "AirplaneLine.h"

using namespace std;

const string ARRIVE = "A";
const string DEPART = "D";
const string ADDPLANE = "!";
const string MYAIRPORT = "BOS";
const int INFINITYSENTINEL = -1;


int main(int argc, char* argv[])
{
    int maxLength;
    string command;
    string flightNum;
    string origin;
    string destination;
    string airline;
    string passengerNum;
    int passengerNumInt;


    if (argc !=2)
    {
        cout << "You must enter an input. Please enter a single positive integer."
            << endl;
        return 0;
    }

    maxLength = atoi(argv[1]);

    if (maxLength <= 0)
    {
        cout << "Input was invalid. Please enter a single positive integer."
            << endl;
        return 0;
    }

    AirplaneLine arriving (maxLength);
    AirplaneLine departing (maxLength);
    AirplaneLine waitingtoarrive (INFINITYSENTINEL);
    AirplaneLine waitingtodepart (INFINITYSENTINEL);

    ifstream infile;
    infile.open("./activity.log");

    if (infile.is_open() )
    {
        while (infile >> command )
        {
            if (command == ARRIVE)
            {
                if ( !arriving.isEmpty() )
                {
                    if ( waitingtoarrive.isEmpty() )
                    {
                        arriving.dequeue();
                    }

                    else
                    {
                        arriving.dequeue( waitingtoarrive.dequeueHead () );
                    }
                }
            }

            else if (command == DEPART)
            {
                if ( !departing.isEmpty() )
                {
                    if ( waitingtodepart.isEmpty() )
                    {
                        departing.dequeue();
                    }

                    else departing.dequeue( waitingtodepart.dequeueHead() );
                }
            }

            else if (command == ADDPLANE)
            {
                infile >> flightNum;
                infile >> origin;
                infile >> destination;
                infile >> airline;
                infile >> passengerNum;
                passengerNumInt = atoi (passengerNum.c_str() );

                if (origin == MYAIRPORT)
                {
                    
                    if ( !departing.isFull() )
                    {
                        departing.enqueue(flightNum, origin, destination,
                                            airline, passengerNumInt);
                    }

                    else
                    {
                        waitingtodepart.enqueue(flightNum, origin, destination,
                                            airline, passengerNumInt);
                    }
                }
                
                else
                {
                    if ( !arriving.isFull() )
                    {
                        arriving.enqueue(flightNum, origin, destination,
                                            airline, passengerNumInt);
                    }

                    else
                    {
                        waitingtoarrive.enqueue(flightNum, origin, destination,
                                            airline, passengerNumInt);

                    }
                }
            }

        }

        infile.close();

        //outputing info
        cout << "Total number of passengers flown out of the airport: "
            << departing.getPassengerCount() << endl;
        cout << "Total number of passengers that arrived: "
            << arriving.getPassengerCount() << endl;
        cout << "Total number of planes that had to circle in the air: "
            << waitingtoarrive.getPlaneCount() << endl;
        cout << "Total number of planes that had to be delayed for takeoff: "
            << waitingtodepart.getPlaneCount() << endl;
        cout << "The planes that are still waiting to depart:" << endl;

        //LIST AIRPLANES...
        departing.readOut();

        cout << "The planes that are still waiting to land:" << endl;

        arriving.readOut();
    }

    else cout << "Unable to open file. Exiting." << endl;

    return 0;
}


#endif
