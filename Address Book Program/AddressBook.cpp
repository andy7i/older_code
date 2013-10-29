/*

AddressBook.cpp
Created by Andrew Jang
	on: 6.9.2012

*/

#ifndef ADDRESSBOOK_CPP
#define ADDRESSBOOK_CPP
#include <iostream>
#include <string>
#include "AddressBook.h"
#include "Contact.h"

using namespace std;

//Contact cntct;

AddressBook::AddressBook()
{
	head = NULL;
	tail = NULL;
	current = NULL;
	newNode = NULL;
}


void AddressBook::newcontact(string firstn, string lastn)
{
	newNode = new Node;
    newNode->prev = NULL;
    newNode->next = NULL;
    newNode->cntct.setFirstname(firstn);
    newNode->cntct.setLastname(lastn);
    AddressBook::placeNode();
}


void AddressBook::newcontact(string firstn, string lastn, string eml, 
                                                             string phonen)
{
	newNode = new Node;
    newNode->prev = NULL;
    newNode->next = NULL;
    newNode->cntct.setFirstname(firstn);
    newNode->cntct.setLastname(lastn);
    newNode->cntct.setPhonenumber(phonen);
    newNode->cntct.setEmail(eml);
    AddressBook::placeNode();
}

void AddressBook::newcontactphone(string firstn, string lastn, string phonen)
{
	newNode = new Node;
    newNode->prev = NULL;
    newNode->next = NULL;
    newNode->cntct.setFirstname(firstn);
    newNode->cntct.setLastname(lastn);
    newNode->cntct.setPhonenumber(phonen);
    AddressBook::placeNode();
}

void AddressBook::newcontactemail(string firstn, string lastn, string eml)
{
	newNode = new Node;
    newNode->prev = NULL;
    newNode->next = NULL;
    newNode->cntct.setFirstname(firstn);
    newNode->cntct.setLastname(lastn);
    newNode->cntct.setEmail(eml);
    AddressBook::placeNode();
}

void AddressBook::placeNode()
{
	if (head == NULL)
	{
		head = newNode;
		tail = newNode;
	}
	
	else
	{
		current = head;
		
		while (1)
		{
			if (current == NULL)
			{
				tail->next = newNode;
				newNode->prev = tail;
				tail = newNode;
                break;
			}

			else if 
            ((newNode->cntct.getLastname()).compare(current->cntct.getLastname(                                                                      )) > 0)
			{
				current = current->next;	//continues traversing list
			}
			else if
            ((newNode->cntct.getLastname()).compare(current->cntct.getLastname(                                                                      )) < 0)
			{
				//if current node comes alphabetically after, then places 
                                                    //before current node
				AddressBook::insertNode();
				break;
			}
			else if
            ((newNode->cntct.getLastname()).compare(current->cntct.getLastname(                                                                     )) == 0)
			{
				//find order of first names
				placeNodewithsamelastname();
				break;
			}
		}
    }
	
}

void AddressBook::insertNode()
{
	if (current == head)
	{
		current->prev = newNode;
		newNode->next = current;
		head = newNode;
	}
	
    else
    {
    	Node *tempPreviousnode;

		tempPreviousnode = current->prev;
		tempPreviousnode->next = newNode;
		newNode->prev = tempPreviousnode;
		current->prev = newNode;
		newNode->next = current;
	}
}

void AddressBook::placeNodewithsamelastname()
{
	while (1)
	{
		if (current == NULL)
		{
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
            break;
		}

		else if 
        ((newNode->cntct.getLastname()).compare(current->cntct.getLastname()) 
                                                                       != 0)
		{
			AddressBook::insertNode();
            break;
		}

		else if 
        ((newNode->cntct.getFirstname()).compare(current->cntct.getFirstname())                                                                         > 0)
		{
			current = current->next;	//continues traversing list
		}
		else if 
        ((newNode->cntct.getFirstname()).compare(current->cntct.getFirstname())                                                                          < 0)
		{
			//if current node comes alphabetically after, then places before 
                                                           //current node
			AddressBook::insertNode();
			break;
		}
        else if
        ((newNode->cntct.getFirstname()).compare(current->cntct.getFirstname())                                                                         == 0)
        {
            AddressBook::insertNode();
            break;
        }
	}
}

bool AddressBook::remove(string firstn, string lastn)
{
	bool removed = false;
	
	if (AddressBook::locatelastname(lastn) == true)
	{
		while (current->cntct.getLastname() == lastn)
		{
			if (current->cntct.getFirstname() == firstn)
			{
				AddressBook::removeNode();
				cout << "Contact deleted." << endl;
				removed = true;
                if (current == NULL)
                {
                    return removed;
                }
			}
			
			else if ((current->cntct.getFirstname()).compare(firstn) > 0)
			{
				break;
			}
			
			else if (current->cntct.getFirstname().compare(firstn) < 0)
			{
				current = current->next;
			}
			
			if (current == NULL)
			{
				break;
			}
		}
	}
	return removed;
}

bool AddressBook::locatelastname(string lastn)
{
	if (head == NULL)
	{
		return false;
	}
	
	current = head;
	
	while (current != NULL)
	{
		if (current->cntct.getLastname() == lastn)
		{
			return true;
		}
		else current = current->next;
	}
	
	return false;
}

void AddressBook::removeNode()
{
	Node *tempPrev;
	Node *tempNext;
    Node *temp;


	if (head == tail)
	{
        delete current;
		head = NULL;
		tail = NULL;
        current = NULL;
	}
	
	else if (current == head)
	{
		current = current->next;
		temp = head;
        delete temp;
		head = current;
		current->prev = NULL;
	}
	
	else if (current == tail)
	{
		current = current->prev;
		temp = tail;
        delete temp;
		tail = current;
		current->next = NULL;
	}
	
	else
	{

		tempPrev = current->prev;
		tempNext = current->next;
		tempPrev->next = tempNext;
		tempNext->prev = tempPrev;
		delete current;
		current = tempNext;
	}
}

bool AddressBook::search(string lastn)
{
	if (AddressBook::locatelastname(lastn) == true)
	{
		while (current->cntct.getLastname() == lastn)
		{
			cout << current->cntct.getLastname() << ", " <<
                current->cntct.getFirstname() << endl
				<< current->cntct.getEmail() << endl
				<< current->cntct.getPhonenumber() << endl << endl;
			
			current = current->next;
			
			if (current == NULL)
			{
				break;
			}
		}
		
		return true;
	}
	
	else return false;
}

bool AddressBook::print()
{
	if (head == NULL)
	{
		return false;
	}

	current = head;
	
	while (current !=NULL)
	{
		cout << current->cntct.getLastname() << ", " 
            << current->cntct.getFirstname() << endl
		<< current->cntct.getEmail() << endl
		<< current->cntct.getPhonenumber() << endl << endl;
	
		current = current->next;
	}
	return true;
}

bool AddressBook::printReverse()
{
	if (tail == NULL)
	{
		return false;
	}

	current = tail;
	
	while (current !=NULL)
	{
		cout << current->cntct.getLastname() << ", " 
            << current->cntct.getFirstname() << endl
		<< current->cntct.getEmail() << endl
		<< current->cntct.getPhonenumber() << endl << endl;
	
		current = current->prev;
	}
	return true;
}

AddressBook::~AddressBook()
{
	if (head == NULL)
	{
	return;
	}
	
	Node *tempNext;
    Node *temp;
	temp = head;
	
	while (tempNext !=NULL)
	{
		tempNext = temp->next;
		delete temp;
		temp = tempNext;
	}
    head = NULL;
    temp = NULL;
    tail = NULL;
    newNode = NULL;

    cout << "Used memory has been cleared" << endl;
}


#endif
