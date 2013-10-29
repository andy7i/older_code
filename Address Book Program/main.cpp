/*
   main.cpp
   created by Andrew Jang
        on 6.3.2012
*/

#ifndef MAIN_CPP
#define MAIN_CPP

#include <iostream>
#include <cctype>
#include "Contact.h"
#include "AddressBook.h"

using namespace std;


int main ()
{
	int selection;
	string data;
    string firstn;
    string lastn;
    string eml;
    string phonen;

    Contact cntct;
    AddressBook adrsbook;
	
	while (1)
	{

		
		cout << "Please make a selection from the following:" << endl
			<< "1 - Create new contact" << endl
			<< "2 - Remove a contact" << endl
			<< "3 - Search address book" << endl
			<< "4 - Print address book" << endl
			<< "5 - Print address book in reverse order" << endl
			<< "6 - Quit" << endl;

		cin >> selection;
		
		
		if (selection == 1)
		{
            eml = "";
            phonen = "";

			
			cout << "Please enter first name." << endl;
			cin >> firstn;
						
            cout << "Please enter last name." << endl;
			cin >> lastn;
						
			cout << "Would you like to add a phone number?" << endl
				<< "1 - Yes" << endl
				<< "2 - No" << endl;
			cin >> selection;
			
			if (selection == 1)
			{
				cout << "Enter phone number here:" << endl;
				cin >> phonen;
			}
			
			cout << "Would you like to add an email?" << endl
				<< "1 - Yes" << endl
				<< "2 - No" << endl;
			cin >> selection;
			
			if (selection == 1)
			{
				cout << "Enter email here:" << endl;
				cin >> eml;
			}

            for (int i = 0; firstn[i] != '\0'; i++)
            {
                firstn[i] = tolower(firstn[i]);
            }
            firstn[0] = toupper(firstn[0]);

            for (int j = 0; lastn[j] != '\0'; j++)
            {
                lastn[j] = toupper(lastn[j]);
            }

            if (eml != "" && phonen != "")
            {
                adrsbook.newcontact(firstn, lastn, eml, phonen);
            }

            else if (phonen!= "")
            {
                adrsbook.newcontactphone(firstn, lastn, phonen);
            }

            else if (eml != "")
            {
                adrsbook.newcontactemail(firstn, lastn, eml);
            }

            else adrsbook.newcontact(firstn, lastn);


		}

		else if (selection == 2)
		{
			string fn;
			string ln;
			cout << "Please enter the first name of the contact you would like to delete" << endl;
			cin >> fn;
			cout << "Please enter the last name of the contact you would like to delete" << endl;
			cin >> ln;

            for (int i = 0; fn[i] != '\0'; i++)
            {
                fn[i] = tolower(fn[i]);
            }
            fn[0] = toupper(fn[0]);

            for (int j = 0; ln[j] != '\0'; j++)
            {
                ln[j] = toupper(ln[j]);
            }
			
			if (adrsbook.remove(fn, ln) == false)
			{
				cout << "Contact not found" << endl;
			}
		}
		
		else if (selection == 3)
		{
			cout << "Please enter the last name of the contact you are searching for." << endl;
			cin >> data;
			
            for (int j = 0; data[j] != '\0'; j++)
            {
                data[j] = toupper(data[j]);
            }

			if (adrsbook.search(data) == false)
			{
				cout << "Contact not found" << endl;
			}
		}
		
		else if (selection == 4)
		{
			if (adrsbook.print() == false)
			{
				cout << "No contacts." << endl;
			}
		}
		
		else if (selection == 5)
		{
			if (adrsbook.printReverse() == false)
			{
				cout << "No contacts." << endl;
			}
		}
		
		else if (selection == 6)
		{
			cout << "Goodbye." << endl;
			break;
		}
    }

    return 0;
}
		
		
#endif
