/*

Contact.h
Contact

Created by Andrew Jang on 6.3.2012

*/

#ifndef CONTACT_H
#define CONTACT_H
#include  <iostream>

using namespace std;

// class invariant: will always have firstname and lastname
class Contact
{
private:
	string firstname;
	string lastname;
	string phonenumber;
	string email;

public:
	// Description: initializes new Contact node
	// Precondition: a node must exist
	// Postcondition: node is initialized
	Contact();
	
	// Description: sets first name
	// Precondition: have first name info
	// Postcondition: first name is set
	void setFirstname (string firstn);

    // Description: sets last name
	// Precondition: have last name info
	// Postcondition: last name is set
    void setLastname (string lastn);

    // Description: sets phonenumber
	// Precondition: have phonenumber info 
	// Postcondition: phonenumber is set
    void setPhonenumber(string phn);

    // Description: sets email
	// Precondition: have email info
	// Postcondition: email is set
    void setEmail(string eml);

    // Description: gets first name
	// Postcondition: returns first name
    string getFirstname();

    // Description: gets last name
	// Postcondition: returns last name
    string getLastname();

    // Description: gets phonenumber
	// Postcondition: returns phone number
    string getPhonenumber();

    // Description: gets email
	// Postcondition: returns email
    string getEmail();

	// Description: deletes used memory
	// Precondition: there is data to delete
	// Postcondition: used memory is cleared
	~Contact();
};

#endif
