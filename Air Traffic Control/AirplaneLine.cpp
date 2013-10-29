/*

    AirplaneLine.cpp


    created by:
        Andrew Jang
    on:
        6.26.2012

*/

#ifndef AIRPLANELINE_CPP
#define AIRPLANELINE_CPP

#include <iostream>
#include "AirplaneLine.h"
#include "Airplane.h"

using namespace std;


const int INFINITYSENTINEL = -1;


AirplaneLine::AirplaneLine(int max)
{
    root = NULL;
    tail = NULL;
    itr = NULL;
    newNode = NULL;

    maxLength = max;
    
    passengerCount = 0;
    planeCount = 0;
}


AirplaneLine::~AirplaneLine()
{
    while (root != NULL)
    {
        Node* tempDelete;
        tempDelete = root;
        root = tempDelete->next;

        delete tempDelete->airplaneInfo;
        delete tempDelete;
    }
}


void AirplaneLine::enqueue(string flightNum, string origin, 
                string destination, string airline, int numPassengers)
{
    newNode = new Node (flightNum, origin, destination, airline, 
                                                        numPassengers);

    if (AirplaneLine::isEmpty() )
    {
        root = newNode;
    }

    else
    {
        AirplaneLine::setTail();
        tail->next = newNode;
    }

    AirplaneLine::addPlaneCount();
}

void AirplaneLine::setTail()
{
    itr = root;

    if ( !AirplaneLine::isEmpty() )
    {
        while (itr->next != NULL)
        {
            itr = itr->next;
        }
    }

    tail = itr;
}


bool AirplaneLine::isFull()
{
    if (isEmpty() )
    {
        return false;
    }

    if (maxLength == INFINITYSENTINEL)
    {
        return false;
    }

    if (maxLength == AirplaneLine::countLength() )
    {
        return true;
    }

    return false; 
}


bool AirplaneLine::isEmpty()
{
    if (root == NULL)
    {
        return true;
    }

    else return false;
}

void AirplaneLine::addPassengerCount()
{
    itr = root;
    passengerCount = passengerCount + itr->airplaneInfo->getNumPassengers();
}


void AirplaneLine::addPlaneCount()
{
    planeCount++;
}


int AirplaneLine::getPassengerCount()
{
    return passengerCount;
}


int AirplaneLine::getPlaneCount()
{
    return planeCount;
}


void AirplaneLine::dequeue()
{
    AirplaneLine::addPassengerCount();
    Node* temp = root;
    root = temp->next;

    delete temp->airplaneInfo;
    delete temp;
}


void AirplaneLine::dequeue(Node* movingNode)
{
    AirplaneLine::dequeue();

    if (AirplaneLine::isEmpty() )
    {
        root = movingNode;
        return;
    }
   
    AirplaneLine::setTail();
    tail->next = movingNode;
}


Node* AirplaneLine::dequeueHead()
{
    itr = root;
    root = itr->next;
    itr->next = NULL;
    return itr;
}


int AirplaneLine::countLength()
{
    if (isEmpty() )
    {
        return 0;
    }

    int count = 1;

    itr = root;

    while (itr->next != NULL)
    {
        itr = itr->next;
        count ++;
    }

    return count;
}

void AirplaneLine::readOut()
{
    itr = root;

    while (itr != NULL)
    {
        cout << "Flight Number => " << itr->airplaneInfo->getFlightNum() << endl;
        cout << "Origin => " << itr->airplaneInfo->getOrigin() << endl;
        cout << "Destination => " << itr->airplaneInfo->getDestination() << endl;
        cout << "Description => " << itr->airplaneInfo->getDescription() << endl;
        cout << "Number of Passengers => " <<
                                itr->airplaneInfo->getNumPassengers() << endl;
        itr = itr->next;
    }
}

#endif
