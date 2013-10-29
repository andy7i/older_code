//
// BST.cpp
//
//  Created by Andrew Jang
//      on: 7.17.2012
//

#ifndef BST_BST_cpp
#define BST_BST_cpp

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#include "BST.h"

using namespace std;


BST::BST ()
{
    root = NULL;
    itr = NULL;
    itrParent = NULL;
    head = NULL;
    itrLL = NULL;
}


void BST::insert (string word)
{
    if (root == NULL)
    {
        root = new Node;
        root->word = word;
        root->left = NULL;
        root->right = NULL;
        return;
    }

    if (BST::insertSearch(word, root))
    {
        return;
    }

    return;
}

bool BST::insertSearch (string word, Node* curr)
{
    if (word > curr->word)
    {
        if (curr->right == NULL)
        {
            itr = new Node;
            curr->right = itr;
            itr->word = word;
            itr->left = NULL;
            itr->right = NULL;
            return true;
        }

        return BST::insertSearch(word, curr->right);
    }

    if (word < curr->word)
    {
        if (curr->left == NULL)
        {
            itr = new Node;
            curr->left = itr;
            itr->word = word;
            itr->left = NULL;
            itr->right = NULL;
            return true;
        }

        return BST::insertSearch(word, curr->left);
    }

    if (word == curr->word)
    {
        return false;
    }

    return false;
}


int BST::size ()
{
    if (root == NULL)
    {
        return 0;
    }

    return BST::sizeRecursive(root);
}


int BST::sizeRecursive(Node* curr)
{
    if (curr == NULL)
    {
        return 0;
    }

    return 1 + BST::sizeRecursive (curr->left) + 
        BST::sizeRecursive (curr->right);
}


int BST::height ()
{
    if (root == NULL)
    {
        return 0;
    }

    return BST::heightRecursive (root);
}


int BST::heightRecursive (Node* curr)
{
    if (curr == NULL)
    {
        return 0;
    }

    return 1 + max (BST::heightRecursive (curr->left),
            BST::heightRecursive(curr->right) );
}


bool BST::find (string needle)
{
    if (root == NULL)
    {
        return false;
    }

    return BST::findRecursive (needle, root);
}

bool BST::findRecursive (string needle, Node* curr)
{
    if (needle > curr->word)
    {
        if (curr->right == NULL)
        {
            return false;
        }
        
        itrParent = curr;
        return BST::findRecursive(needle, curr->right);
    }

    if (needle < curr->word)
    {
        if (curr->left == NULL)
        {
            return false;
        }

        itrParent = curr;
        return BST::findRecursive(needle, curr->left);
    }

    if (needle == curr->word)
    {
        itr = curr;
        return true;
    }

    return false;
}


bool BST::deleteNode (string word)
{
    if (BST::find(word) )
    {
        Node* temp;
        Node* tempTreeHead;
        tempTreeHead = itr;

        if (itr->left == NULL && itr->right == NULL)
        {
            if (itr == root)
            {
                delete tempTreeHead;
                itr = NULL;
                root = NULL;
                return true;
            }
            else if (itrParent->left == tempTreeHead)
            {
                itrParent->left = NULL;
            }
            else itrParent->right = NULL;

            delete tempTreeHead;
            return true;
        }

        srand ( time(NULL) );   // initializes random number generator seed

        if ( ( ( rand() % 2 == 1 ) && ( itr->left != NULL ) )
                    || itr->right == NULL)
        {
            itr = itr->left;

            if (itr->right != NULL)
            {
                while ((itr->right)->right != NULL)
                {
                    itr = itr->right;
                }

                temp = itr->right;
                itr->right = temp->left;
                tempTreeHead->word = temp->word;
                delete temp;
            }

            else
            {
                tempTreeHead->left = itr->left;
                tempTreeHead->word = itr->word;
                temp = itr;
                delete temp;
            }

            return true;
        }

        else
        {
            itr = itr->right;

            if (itr->left != NULL)
            {
                while ((itr->left)->left != NULL)
                {
                    itr = itr->left;
                }

                temp = itr->left;
                itr->left = temp->right;
                tempTreeHead->word = temp->word;
                delete temp;
            }

            else
            {
                tempTreeHead->right = itr->right;
                tempTreeHead->word = itr->word;
                temp = itr;
                delete temp;
            }

            return true;
        }
    }

    else return false;
}


Node* BST::createLL()
{
    if (root != NULL)
    {
        head = NULL;
        itrLL = head;
        BST::createLLRecursive(root);
    }

    return head;
}


void BST::createLLRecursive(Node* curr)
{
    if (curr->left != NULL)
    {
        BST::createLLRecursive(curr->left);
    }

    if (itrLL == NULL)
    {
        itrLL = new Node;
        head = itrLL;
        itrLL->right = NULL;
        itrLL->left = NULL;
        itrLL->word = curr->word;
    }

    else
    {
        Node* temp = new Node;
        temp->right = NULL;
        temp->left = NULL;          // keeping the list singly linked, as
                                                            //  instructed
        temp->word = curr->word;
        itrLL->right = temp;
        itrLL = temp;
    }

    if (curr->right != NULL)
    {
        BST::createLLRecursive(curr->right);
    }

    return;
}


BST::~BST ()
{
    if (root != NULL)
    {
        BST::destructorRecurse(root);
    }

    root = NULL;
    itr = NULL;
    itrParent = NULL;
    head = NULL;
    itrLL = NULL;
}


void BST::destructorRecurse (Node* curr)
{
    Node* temp;
    temp = curr;

    if (curr->left != NULL)
    {
        BST::destructorRecurse (curr->left);
    }

    if (curr->right != NULL)
    {
        BST::destructorRecurse (curr->right);
    }

    delete temp;
}

#endif
