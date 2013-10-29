/*

    AirplaneLine.h


    created by:
        Andrew Jang
    on:
        6.26.2012

*/

#ifndef AIRPLANELINE_H
#define AIRPLANELINE_H

#include <iostream>
#include "Airplane.h"

using namespace std;


// class invariant: has airplaneInfo

class Node
{
public:

    // Description: creates new airplane and passes in information
    // Precondition: info is passed in
    // Postcondition: new airplane is created
    Node (string a, string b, string c, string d, int e) 
    {
        airplaneInfo = new Airplane (a, b, c, d, e);
        next = NULL;
    }

    Airplane* airplaneInfo;
    Node* next;
};



//class invariant: will make sure length is not longer than maxLength, keeps
//track of root and plane and passenger counts

class AirplaneLine
{
private:
    Node* root;
    Node* itr;
    Node* tail;
    Node* newNode;

    int maxLength;  // maxlength of queue "n"
    int passengerCount;
    int planeCount;

public:
    // Description: Initializes the AirplaneLine's linked list and other data
    // Precondition: maxlength must be passed in
    // Postcondition: pointers and counters are initialized and maxlength is set
    AirplaneLine(int);

    // Description: deconstructor
    // Precondition: class is being closed
    // Postcondition: data is deallocated
    ~AirplaneLine();

    // Description: adds new node to end of the queue
    // Precondition: data passed in
    // Postcondition: node is created and added to end of queue
    void enqueue(string, string, string, string, int);

    // Description: finds end of queue and sets tail to it
    // Precondition: is run / queue exists
    // Postcondition: sets tail to tail of queue
    void setTail();

    // Description: checks if full
    // Precondition: maxlength established
    // Postcondition: returns true/false
    bool isFull();

    // Description: checks if empty
    // Precondition: is run / queue exists
    // Postcondition: returns true if head == NULL
    bool isEmpty();

    // Description: adds passengerNum from head node to count
    // Precondition: a node must exist
    // Postcondition: passenger # added to count
    void addPassengerCount();

    // Description: counts planes added to list
    // Precondition: node is added
    // Postcondition: plane counter is increased
    void addPlaneCount();

    // Description: returns passengerCount
    // Precondition: passengerCount exists
    // Postcondition: returns passengerCount
    int getPassengerCount();

    // Description: returns PlaneCount
    // Precondition: planeCount exists
    // Postcondition: returns planeCount
    int getPlaneCount();

    // Description: removes the head node from queue
    // Precondition: node must exist, no other node being added to queue
    // Postcondition: head node removed, head repointed
    void dequeue();

    // Description: removes the head node from queue and adds another in
    // Precondition: the Node* pointer of node being added must be passed in
    // Postcondition: head node removed, node added to end
    void dequeue(Node*);

    // Description: dequeues a head node to add to another queue
    // Precondition: node exists
    // Postcondition: pointer to the node is returned
    Node* dequeueHead();

    // Description: counts length of the queue
    // Precondition: queue exists
    // Postcondition: length of queue returned
    int countLength();

    // Description: reads out all planes in queue
    // Precondition: queue exists
    // Postcondition: couts airplaneinfo of planes in queue
    void readOut();
};

#endif
