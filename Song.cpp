/*
Name: Grace Lee
Class: CPSC 122, Spring 2023
Date: March 26, 2023
Programming Assignment: PA6
Description: We arrange our music library based attributes such as song title, song artist, song genre, and rating. We will write a program for managing a music library using classes
*/
#include "Song.h"
/*************************************************************
 * function: string convertToLowercase(string s)
 * Date Created: 3/27/23                 	        
 * Date Last Modified: 4/4/23                      
 * Description: This functions converts the given string into a lower case
 * Input parameters: string s
 *************************************************************/
string convertToLowercase(string s) 
{
    string store;
    char newC;

    for (char c : s)
    {
        newC = tolower(c);
        store += newC;
    }
    s = store;
    return s;
}
/*************************************************************
 * function: Song::Song()
 * Date Created: 3/26/23                 	        
 * Date Last Modified: 4/1/23                      
 * Description: This functions is the DVC
 * Input parameters: none
 *************************************************************/
Song::Song() 
{
    title = "";
    artist = "";
    genre = "";
    rating = 1;
	next = NULL;
}
/*************************************************************
 * function: Song::Song(string titleParam, string artistParam, string genreParam, int ratingParam)
 * Date Created: 3/27/23                 	        
 * Date Last Modified: 3/27/23                      
 * Description: This functions sets a Song given the input
 * Input parameters: (string titleParam, string artistParam, string genreParam, int ratingParam)
*************************************************************/
Song::Song(string titleParam, string artistParam, string genreParam, int ratingParam) 
{
    title = titleParam;
    artist = artistParam;
    genre = genreParam;
    rating = ratingParam;
	next = NULL;
}
/*************************************************************
 * function: Song::Song(const Song& other) 
 * Date Created: 3/26/23                 	        
 * Date Last Modified: 3/26/23                      
 * Description: This function is the copy constructor. 
 * Input parameters: const Song& other
 *************************************************************/
Song::Song(const Song& other) 
{
    title = other.title;
    artist = other.artist;
    genre = other.genre;
    rating = other.rating;
	next = NULL;
}
/*************************************************************
 * function: string Song::getTitle() 
 * Date Created: 3/26/23                 	        
 * Date Last Modified: 3/26/23                      
 * Description: This functions gets the title
 * Input parameters: none
 *************************************************************/
string Song::getTitle() 
{
	return title;
}
/*************************************************************
 * function: void Song::setTitle(string newTitle) 
 * Date Created: 3/26/23                 	        
 * Date Last Modified: 3/26/23                      
 * Description: This functions sets a title to a new one
 * Input parameters: (string newTitle)
 *************************************************************/
void Song::setTitle(string newTitle) 
{
	title = convertToLowercase(newTitle);
}
/*************************************************************
 * function: string Song::getArtist() 
 * Date Created: 3/26/23                 	        
 * Date Last Modified: 3/26/23                      
 * Description: This functions cgets the artist
 * Input parameters: none
 *************************************************************/
string Song::getArtist() 
{
	return artist;
}
/*************************************************************
 * function: void Song::setArtist(string newArtist)
 * Date Created: 3/26/23                 	        
 * Date Last Modified: 3/26/23                      
 * Description: This functions sets the artist
 * Input parameters: (string newArtist)
 *************************************************************/
void Song::setArtist(string newArtist) 
{
	artist = convertToLowercase(newArtist);
}
/*************************************************************
 * function: string Song::getGenre()
 * Date Created: 3/23/23                 	        
 * Date Last Modified: 3/23/23                      
 * Description: This functions gest the genre
 * Input parameters: none
 *************************************************************/
string Song::getGenre() 
{
	return genre;
}
/*************************************************************
 * function: void Song::setGenre(string newGenre)
 * Date Created: 3/23/23                 	        
 * Date Last Modified: 3/23/23                      
 * Description: This functions gets the genre
 * Input parameters: string newGenre)
 *************************************************************/
void Song::setGenre(string newGenre) 
{
	genre = convertToLowercase(newGenre);
}

/*************************************************************
 * function: int Song::getRating()
 * Date Created: 3/23/23                 	        
 * Date Last Modified: 3/23/23                      
 * Description: This functions gest the rating
 * Input parameters: none
 *************************************************************/
int Song::getRating() 
{
	return rating;
}
/*************************************************************
 * function: void Song::setRating(int newRating)
 * Date Created: 3/23/23                 	        
 * Date Last Modified: 3/23/23                      
 * Description: This functions sets the correct rating
 * Input parameters: int newRating
 *************************************************************/
void Song::setRating(int newRating) {
	if (newRating < MIN_RATING || newRating > MAX_RATING) {
		cout << "Rating must be in [" << MIN_RATING << ", " << MAX_RATING << "]" << endl;
	}
	if (newRating < MIN_RATING) {
		rating = MIN_RATING;
	}
	else if (newRating > MAX_RATING) {
		rating = MAX_RATING;
	}
	else {
		rating = newRating;
	}
}
/*************************************************************
 * function: Song * Song::getNext() 
 * Date Created: 3/23/23                 	        
 * Date Last Modified: 3/23/23                      
 * Description: This functions gets next
 * Input parameters: none
 *************************************************************/
Song * Song::getNext() 
{
	return next;
}
/*************************************************************
 * function: void Song::setNext(Song * newNext) 
 * Date Created: 3/23/23                 	        
 * Date Last Modified: 3/23/23                      
 * Description: This functions gets next
 * Input parameters: Song * newNext
 *************************************************************/
void Song::setNext(Song * newNext) 
{
	next = newNext;
}
/*************************************************************
 * function: string Song::getStringAttributeValue(string attribute)
 * Date Created: 3/23/23                 	        
 * Date Last Modified: 3/23/23                      
 * Description: This functions converts the given string into a lower case
 * Input parameters: sting attribute
 *************************************************************/
string Song::getStringAttributeValue(string attribute) 
{
    if (attribute == "title")
    {
        attribute = getTitle();
        return attribute;
    }
    if (attribute == "artist")
    {
        attribute = getArtist();
        return attribute;
    }
    if (attribute == "genre")
    {
        attribute = getGenre();
        return attribute;
    }
    if (attribute == "rating")
    {
        attribute = to_string(getRating());
        return attribute;
    }
    else
    {
        attribute = "";
        return attribute;
    }
    return attribute;
}
/*************************************************************
 * function: void Song::displaySong() 
 * Date Created: 3/23/23                 	        
 * Date Last Modified: 3/23/23                      
 * Description: This functions displays the song
 * Input parameters: sting attribute
 *************************************************************/
void Song::displaySong() 
{
    Song * currentSong = this; //starts at the current song
    while(currentSong != NULL)
    {
        cout << "Song title: " << currentSong->getTitle() << endl;
        cout << "Song artist: " << currentSong->getArtist() << endl;
        cout << "Song genre: " << currentSong->getGenre() << endl;
        cout << "Song rating: " << currentSong->getRating() << endl;
        currentSong = currentSong->getNext();
    }
}

