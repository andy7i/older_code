//
// LL.h
//
//  Created by Andrew Jang
//      on: 7.17.2012
//

#ifndef BST_LL_h
#define BST_LL_h

#include <iostream>
#include "BST.h"


using namespace std;

// class invariants: All nodes must be connected

class LL
{
public:
    LL();

    // Description: alphabetically inserts a word into the LL
    // Postcondition: word inserted alphabetically
//    void insert (string word);        //not used // not optimized for SLL
    
    // Description: finds a word in the LL
    // Postcondition: returns true if found
    bool find (string needle);

    // Description: deletes node 
    // Postcondition: list integrity is preserved
    bool deleteNode (string word);

    // Description: add node to the end of the list
    // Postcondition: node added at end of list and tail reassigned
    void queue (string word);

    // Description: sets head to a passed-in Node*
    // Postcondition: LL runs from passed-in info
    void setHead (Node* newHead);

    ~LL();
private:
    Node* head;     //to keep track of the linked list
    Node* tail;     //adding for functionality sake && also in order to reuse
                                                        // the Node struct
    Node* itr;      // iterator
    Node* itrPrev;  // node previous to itr
};


#endif
