/*
Name: Grace Lee
Class: CPSC 122, Spring 2023
Date: March 26, 2023
Programming Assignment: PA6
Description: We arrange our music library based attributes such as song title, song artist, song genre, and rating. We will write a program for managing a music library using classes
*/
#ifndef PA6_H
#define PA6_H

#include <iostream>
#include <fstream>
#include "Song.h"
#include "SongLibrary.h"

using namespace std;

const int QUIT_OPTION = 9;
const int FIRST_OPTION = 1;
const int LAST_OPTION = 9;

void displayMenu();
int getValidChoice();
void executeUserChoice(int, SongLibrary&);
void runMusicManager();

#endif
