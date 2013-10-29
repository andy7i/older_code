//
//  BST.h
//
//  Created by Ming Chow
//

#ifndef BST_BST_h
#define BST_BST_h

#include <iostream>

using namespace std;

struct Node {
    string word;
    Node *left;
    Node *right;
};

class BST
{

// Class invariants: number of nodes > 0; the data value of each node in the tree is...
//   ...greater than any data value in its left subtree and...
//   ...less than any data value in its right subtree.

public:
    BST();

    // Description: inserts a word into the tree
    // Precondition: word does not exist in the binary search tree
    // Postcondition: word is added to binary search tree
    void insert(string word);

    // Description: finds the location to insert the word with a recursive func
    // Precondition: a node must exist
    // Postcondition: word is added to binary search tree in proper location
    bool insertSearch(string word, Node* curr);
    
    // Description: returns the number of the nodes in the tree (i.e., words)
    // Postcondition: returns 0 or the number of nodes in the tree
    int size();

    // Description: helps returns the number of the nodes in the tree (i.e., words)
    // Precondition: a node must exist
    // Postcondition: returns 0 or the number of nodes in the tree
    int sizeRecursive(Node* curr);

    // Description: computes the maximum height of the tree
    // Postcondition: returns 0 if empty tree, else the maximum height of tree
    int height();

    // Description: helps compute the maximum height of the tree
    // Precondition: node must exist
    // Postcondition: returns 0 if empty tree, else the maximum height of tree
    int heightRecursive(Node* curr);

    // Description: searches for a given word in the tree, *** case insensitive ***
    // Postcondition: returns true if key in found in tree, otherwise false
    bool find (string needle);

    // Description: help search for a given word in the tree recursively
    // Precondition: node must exist
    // Postcondition: returns true if key in found in tree, otherwise false
    bool findRecursive (string needle, Node* curr);

    // Description: deletes a word from the tree, *** case insensitive ***
    // Postcondition: returns true if word is deleted, otherwise false
    bool deleteNode (string word);

    // Description: creates a LL using the words in the BST
    // Precondition: nodes must exist in BST
    // Postcondition: sorted LL is created
    Node* createLL ();

    // Description: "helper" function for createLL() - recursively
                    // alphabetically traverses BST and adds to LL
    // Precondition: nodes must exist in BST
    // Postcondition: nodes added to LL
    void createLLRecursive(Node* curr);

    // Description: recursive destructor function for BST
    // Precondition: destructor is called
    // Postcondition: nodes in BST erased
    void destructorRecurse(Node* curr);

    ~BST();
    
private:
    Node *root;
    Node *itr;
    Node* itrParent;    // for using the parent node of itr
    Node* head;         // head ptr of LL
    Node* itrLL;         // itr for LL
};

#endif
