/*
Name: Grace Lee
Class: CPSC 122, Spring 2023
Date: March 26, 2023
Programming Assignment: PA6
Description: We arrange our music library based attributes such as song title, song artist, song genre, and rating. We will write a program for managing a music library using classes
*/
#include "PA6.h"


void displayMenu() {
	cout << endl << "Welcome to the CPSC 122 Music Manager!!" << endl;
	cout << "Please choose from the following options: " << endl;
	cout << "1) Load library" << endl;
	cout << "2) Store library" << endl;
	cout << "3) Display library" << endl;
	cout << "4) Sort library" << endl;
	cout << "5) Search library" << endl;
	cout << "6) Insert song in order" << endl;
	cout << "7) Remove song" << endl;
	cout << "8) Edit song" << endl;
	cout << "9) Exit" << endl;
}

int getValidChoice() {
	int choice = -1;
	string temp;
	do {
		cout << "Choice: ";
		cin >> choice;
		if (choice < FIRST_OPTION || choice > LAST_OPTION) {
			cout << "That is not a valid option. Please try again." << endl;
		}
	} while (choice < FIRST_OPTION || choice > LAST_OPTION);
	getline(cin, temp); // flush the newline outta the buffer
	return choice;
}

void executeUserChoice(int choice, SongLibrary& lib) 
{
	switch (choice) {
		case 1:
			// TODO: call a member function, something like lib.loadLibrary();
            lib.loadLibrary();
			break;
		case 2:
			// TODO: call a member function, something like lib.saveLibrary();
            lib.saveLibrary(); 
			break;
		case 3: 
			// TODO: call a member function, something like lib.displayLibrary();
            lib.displayLibrary(); 
			break;
		case 4:
			// TODO: call a member function, something like  
            lib.sortLibrary();
			break;
		case 5:
			// TODO: call a member function, something like  
            lib.searchLibrary();
			break;
		case 6:
			// TODO: call a member function, something like
            lib.insertASongToLibrary();
			break;
		case 7:
			// TODO: call a member function, something like 
            lib.removeSongFromLibrary();
			break;
		case 8:
			// TODO: call a member function, something like 
            lib.editSongInLibrary();
			break;
		default:
			cout << "Unrecognized menu choice" << endl;
			break;
	}
}

void runMusicManager() {
	SongLibrary lib;
	
	int choice = -1;
	do {
		displayMenu();
		choice = getValidChoice();
		if (choice != QUIT_OPTION) {
			executeUserChoice(choice, lib);
		}
	} while (choice != QUIT_OPTION);
	cout << "Thanks for you using the CPSC 122 Music Manager!!" << endl;
}
