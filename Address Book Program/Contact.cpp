/*

Contact.cpp
Contact

Created by Andrew Jang on 6/3/2012


*/

#ifndef CONTACT_CPP
#define CONTACT_CPP

#include <iostream>
#include "Contact.h"
#include "AddressBook.h"

using namespace std;

Contact::Contact()
{
    AddressBook adrsbook;
    firstname = "";
    lastname = "";
    email = "";
    phonenumber = "";
}

void Contact::setFirstname (string firstn)
{
	firstname = firstn;
}

void Contact::setLastname (string lastn)
{
	lastname = lastn;
}

void Contact::setPhonenumber(string phn)
{
	phonenumber = phn;
}

void Contact::setEmail(string eml)
{
	email = eml;
}

string Contact::getFirstname()
{
	return firstname;
}

string Contact::getLastname()
{
	return lastname;
}

string Contact::getPhonenumber()
{
	return phonenumber;
}

string Contact::getEmail()
{
	return email;
}

Contact::~Contact()
{	
}

#endif
