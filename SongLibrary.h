/*
Name: Grace Lee
Class: CPSC 122, Spring 2023
Date: March 26, 2023
Programming Assignment: PA6
Description: We arrange our music library based attributes such as song title, song artist, song genre, and rating. We will write a program for managing a music library using classes
*/
#ifndef SONG_LIBRARY_H
#define SONG_LIBRARY_H

#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>
#include "Song.h"

using namespace std;

class SongLibrary {
	private:
		Song * head;
		string sortAttribute; // NEW: keep track of what attribute the library is currently ordered by
	public:
		SongLibrary();
		SongLibrary(const SongLibrary&); // NEW: copy constructor
		~SongLibrary();
		Song * getHead() const; // UPDATED: name
		void setHead(Song *); // UPDATED: name
		string getSortAttribute() const; // NEW: getter for sortAttribute
		void setSortAttribute(string); // NEW: setter for sortAttribute
		
		void performLoad(string);
		void performSave(string);
		void performSort(); // UPDATED: no parameter for sort attribute, using Song's sortAttribute member variable
		Song * performSearch(string, string, bool *, int *); // UPDATED: parameter list and return type
		void performInsertSongInOrder(Song *); // NEW: replaces addSong()
		void performRemoveSong(Song *); // UPDATED: parameter list
		void performEditSong(Song *, string, string); // UPDATED: parameter list

        //helper func
        void loadLibrary(); //1
        void saveLibrary(); //2
        void displayLibrary(); //3
        void sortLibrary(); //4
        void searchLibrary(); //5
        void insertASongToLibrary(); //6
        void removeSongFromLibrary(); //7
        void editSongInLibrary();//8

};

#endif
