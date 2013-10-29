//
// LL.cpp
//
//  Created by Andrew Jang
//      on: 7.17.2012
//

#ifndef BST_LL_cpp
#define BST_LL_cpp

#include <iostream>
#include "LL.h"

using namespace std;

LL::LL()
{
    head = NULL;
    tail = NULL;
    itr = NULL;
}

/*
void LL::insert (string word)
{
    Node* temp;

    if (head == NULL)
    {
        temp = new Node;
        temp->word = word;
        temp->left = NULL;
        temp->right = NULL;
        head = temp;
        tail = temp;
        return;
    }

    if (word < head->word)
    {
        temp = new Node;
        temp->word = word;
        temp->left = NULL;
        temp->right = head;
        head->left = temp;
        head = temp;
        return;
    }

    itr = head;
    
    while (word > itr->word)
    {
        if (itr->right == NULL)
        {
            temp = new Node;
            temp->word = word;
            temp->left = itr;
            temp->right = NULL;
            itr->right = temp;
            tail = temp;
            return;
        }

        itr = itr->right;
    }

    if (word == itr->word)
    {
        return;
    }

    temp = new Node;
    temp->word = word;
    temp->right = itr;
    temp->left = itr->left;
    (itr->left)->right = temp;
    itr->left = temp;
    return;
}
*/

bool LL::find (string needle)
{
    itr = head;

    while (itr != NULL)
    {
        if (itr->word == needle)
        {
            return true;
        }

        else 
        {
            itrPrev = itr;
            itr = itr->right;
        }
    }

    return false;
}


bool LL::deleteNode (string word)
{
    if ( LL::find(word) )
    {
        Node* temp;
        temp = itr;

        if (itr == head)
        {
            if (head == tail)
            {
                delete temp;
                head = NULL;
                tail = NULL;
                itr = NULL;
                return true;
            }

            itr = itr->right;

            delete temp;
            head = itr;
//            itr->left = NULL;

            if (itr->right == NULL)
            {
                tail = itr;
            }

            return true;
        }

        if (itr == tail)
        {
            itr = itrPrev;
            delete temp;
            tail = itr;
            itr->right = NULL;

            return true;
        }

        itrPrev->right = temp->right;
//        (temp->right)->left = itr->left;      //not needed for SLL
        delete temp;
        return true;
    }

    return false;
}

void LL::queue(string word)
{
    if (head == NULL)
    {
        itr = new Node;
        itr->word = word;
        itr->left = NULL;
        itr->right = NULL;
        head = itr;
        tail = itr;
        return;
    }

    itr = new Node;
    itr->word = word;
//    itr->left = tail;
    itr->left = NULL;
    itr->right = NULL;
    tail->right = itr;
    tail = itr;
    return;
}


void LL::setHead(Node* newHead)
{
    head = newHead;

    itr = head;
    while (itr->right != NULL)
    {
        itr = itr->right;
    }
    tail = itr;
}


LL::~LL()
{
    itr = head;
    while (itr != NULL)
    {
        Node* temp = itr;
        itr = itr->right;
        delete temp;
    }

    head = NULL;
    tail = NULL;
}


#endif
