/*

AddressBook.h
Created by Andrew Jang
	on: 6.9.2012

*/
#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H
#include  <iostream>
#include "Contact.h"

using namespace std;

// (struct) invariant: Node* next and Node* prev point to something or NULL
struct Node
{
    Contact cntct;
	Node *next;
	Node *prev;
};

// class invariant: will always keep track of head and tail; data deleted
                                                            //  after use
class AddressBook
{
private:
	Node *head;
	Node *tail;
	Node *current;
	Node *newNode;
public: 
    // Description: Initializes Node pointers
    // Precondition: Nodes pointers must exist
    // Postcondition: Pointers are initialized to NULL
	AddressBook();


    // Description: creates new contact Node
    // Precondition: Node struct must exist and there must be available memory
                    // and appropriate contact info
    // Postcondition: new contact is created with contact info set
	void newcontact(string firstn, string lastn, string eml, string phonen);


    // Description: creates new contact Node
    // Precondition: Node struct must exist and there must be available memory
                    // and appropriate contact info
    // Postcondition: new contact is created with contact info set
	void newcontact(string firstn, string lastn);
    

    // Description: creates new contact Node
    // Precondition: Node struct must exist and there must be available memory
                    // and appropriate contact info
    // Postcondition: new contact is created with contact info set
    void newcontactphone(string firstn, string lastn, string phonen);
    

    // Description: creates new contact Node
    // Precondition: Node struct must exist and there must be available memory
                    // and appropriate contact info
    // Postcondition: new contact is created with contact info set
    void newcontactemail(string firstn, string lastn, string eml);
    

    // Description: finds where to place the newly created Node alphabetically
    // Precondition: a new node must have been created
    // Postcondition: current is pointing to the spot where the Node can be 
                                                                    //placed
	void placeNode();
    

    // Description: does the magic of inserting a node while maintaining the
                    // node structure by linking the nodes appropriately
    // Precondition: current is pointing to a node
    // Postcondition: the node is inserted into the location pointed to by
                                                                //current
	void insertNode();
    

    // Description: finds where to place the node when there are duplicate
                  // last names. It searches for first names alphabetically
    // Precondition: there is another node with same lastname
    // Postcondition: places the node in the right spot
	void placeNodewithsamelastname();
    

    // Description: sets up the process of removing a contact
    // Precondition: needs input on what firstname and lastname to search for
    // Postcondition: any instances with the given input are deleted
	bool remove(string firstn, string lastn);
    

    // Description: finds the first instance of a node with a given lastname
    // Precondition: needs input (last name)
    // Postcondition: if found, sets current to point to first instance
	bool locatelastname(string lastn);
    

    // Description: deletes node and maintains linked list integrity
    // Precondition: needs location (from *current)
    // Postcondition: node is deleted and other nodes are connected
	void removeNode();
    

    // Description: searches for a last name and prints all instances of it
    // Precondition: needs input
    // Postcondition: prints all instances found
	bool search(string lastn);
    

    // Description: prints linked list in alphabetical order
    // Precondition: the head must point to something (even just NULL)
    // Postcondition: any data is all printed out
	bool print();
    

    // Description: prints linked list in reverse alphabetical order
    // Precondition: the tail must point to something
    // Postcondition: any data is all printed out
	bool printReverse();
    

    // Description: deconstructor
    // Precondition: data was allocated
    // Postcondition: data is deallocated
	~AddressBook();
};


#endif
