/*
Name: Grace Lee
Class: CPSC 122, Spring 2023
Date: March 26, 2023
Programming Assignment: PA6
Description: We arrange our music library based attributes such as song title, song artist, song genre, and rating. We will write a program for managing a music library using classes
*/
#include "SongLibrary.h"
/*************************************************************
 * Function: SongLibrary::SongLibrary()
 * Date Created: 4/1/23                 	        
 * Date Last Modified: 4/1/23                     
 * Description: This function sets numSongs to 0 and songs to NULL         	
 * Input parameters: none         	   
 *************************************************************/
SongLibrary::SongLibrary() 
{
	//initialize to empty list
	head = NULL; 
	// default sort attribute is title
    sortAttribute = "title";
}
/*************************************************************
 * Function: SongLibrary::SongLibrary(const SongLibrary& other)
 * Date Created: 4/1/23                 	        
 * Date Last Modified: 4/1/23                     
 * Description: This function copies the other        	
 * Input parameters: none         	   
 *************************************************************/
SongLibrary::SongLibrary(const SongLibrary& other) 
{
    head = NULL; 
    sortAttribute = other.sortAttribute;

    Song * currSong = other.head;
    while(currSong != NULL)
    {
        Song * newSong = new Song(*currSong); 
        performInsertSongInOrder(newSong);
        currSong = currSong->getNext();
    }
}
/*************************************************************
 * Function:SongLibrary::~SongLibrary()
 * Date Created: 3/29/23                 	        
 * Date Last Modified: 4/1/23                      
 * Description: This function call the destructor       	
 * Input parameters: none         	   
 *************************************************************/
SongLibrary::~SongLibrary() 
{
    Song * current = head;
    Song * next;
    while(current != NULL)
    {
        next = current->getNext();
        delete current;
        current = next;
    }
    head = NULL;
    
}
/*************************************************************
 * Function: Song * SongLibrary::getHead() const 
 * Date Created: 4/29/23                 	        
 * Date Last Modified: 4/1/23                      
 * Description: This function gets head
 * Input parameters: none
 * Returns: void
 *************************************************************/
Song * SongLibrary::getHead() const 
{
	return head;
}
/*************************************************************
 * Function: void SongLibrary::setHead(Song * newHead) 
 * Date Created: 4/29/23                 	        
 * Date Last Modified: 4/1/23                      
 * Description: This function sets head
 * Input parameters: none
 * Returns: void
 *************************************************************/
void SongLibrary::setHead(Song * newHead) 
{
	if(head != NULL) 
    {
        Song * current = head;
        while (current != NULL) 
        {
            Song * temp = current;
            current = current->getNext();
            delete temp;
        }
	}
	head = newHead;
}
/*************************************************************
 * Function: void SongLibrary::setHead(Song * newHead) 
 * Date Created: 3/29/23                 	        
 * Date Last Modified: 4/1/23                      
 * Description: This function sets head
 * Input parameters: none
 * Returns: void
 *************************************************************/
string SongLibrary::getSortAttribute() const 
{
	return sortAttribute;
}
/*************************************************************
 * Function: void SongLibrary::setSortAttribute(string newSortAttribute)
 * Date Created: 3/29/23                 	        
 * Date Last Modified: 4/1/23                      
 * Description: This function sets the sort attribute value
 * Input parameters: string newSortAttribute
 * Returns: void
 *************************************************************/
void SongLibrary::setSortAttribute(string newSortAttribute)
{
	sortAttribute = newSortAttribute;
}
/*************************************************************
 * Function: void SongLibrary::performLoad(string filename) 
 * Date Created: 3/29/23                 	        
 * Date Last Modified: 4/2/23                      
 * Description: This function loads the library by reading in with a given file
 * Input parameters: string filename
 * Returns: void
 *************************************************************/
void SongLibrary::performLoad(string filename) 
{
    string sTitle, sArtist, sGenre, temp;
    int sRating;
    ifstream inFile;
    Song * newSong = NULL;
    

    setHead(NULL);
    inFile.open(filename);
    if (inFile.fail())
    {
        // cout << "Failed to open the file" << endl;
        // exit(-1);
        string parentPath = "../" + filename;
        inFile.open(parentPath);
        if (!inFile.is_open()) {
            cerr << "Error: Could not open file: " << filename << endl;
            cerr << "Tried locations:" << endl;
            cerr << "  - Current directory: " << filename << endl;
            cerr << "  - Parent directory: " << parentPath << endl;
            exit(-1);
        }
    }

    while (!inFile.eof())
    {
        getline(inFile, sTitle);
        if (sTitle == "")
        {
            break;
        }
        getline(inFile, sArtist);
        getline(inFile, sGenre);
        inFile >> sRating;
        getline(inFile, temp); //newline
        getline(inFile, temp); //whitespace

        newSong = new Song(sTitle, sArtist, sGenre, sRating);
        performInsertSongInOrder(newSong);
    }
   
    inFile.close();
    cout << "Library has been loaded!" << endl;
}
/*************************************************************
 * function: void SongLibrary::saveLibrary()
 * Date Created: 3/29/23                 	        
 * Date Last Modified: 4/1/23                      
 * Description: This function saves the songs that were loaded into an output file
 * Input parameters: string filename 
 *************************************************************/
void SongLibrary::performSave(string filename) 
{
    ofstream file;
    
    file.open(filename);
    if(file.fail())
    {
        cout << "Failed to open file" << endl;
        exit(-1);
    }
    Song * current = head; //start current at head
    while(current != NULL) //NULL means end of linked list
    {
        file << current->getTitle() << endl;
        file << current->getArtist() << endl;
        file << current->getGenre() << endl;
        file << current->getRating() << endl;
        file << endl;
        current = current->getNext(); //current is now assigned next
    }
    
    file.close();
    cout << "Library has been saved to " << filename << "!" << endl;
    delete current;
}
/*************************************************************
 * function: void SongLibrary::performSort() 
 * Date Created: 3/26/23                 	        
 * Date Last Modified: 4/4/23                      
 * Description: This functions sorts the songs by the users desidres attribute
 * Input parameters: string attribute
 *************************************************************/
void SongLibrary::performSort() 
{
    Song * currSong = head;
    Song * prevSong = NULL;
    bool sorted = false;
    
    while(!sorted)
    {
        sorted = true;
        while(currSong != NULL && currSong->getNext() != NULL) //if the currSong!=NULL and the next!= NULL
        {
            if(currSong->getStringAttributeValue(sortAttribute) > currSong->getNext()->getStringAttributeValue(sortAttribute))//if the currSong attribute is > than the currSong's next, its not sorted
            {
                sorted = false;
                Song * nextSong = currSong->getNext(); //nextSong gets next
                Song * nextNextSong = nextSong->getNext(); //nextnextSong is now the nextSong's next
                if(prevSong == NULL)
                {
                    head = nextSong;
                }
                else
                {
                    prevSong->setNext(nextSong);
                }

                nextSong->setNext(currSong);
                currSong->setNext(nextNextSong);

                prevSong = nextSong;
            }
            else
            {
                prevSong = currSong;
                currSong = currSong->getNext();
            }
        }
    }
}
/*************************************************************
 * function: Song * SongLibrary::performSearch(string searchAttribute, string searchAttributeValue, bool * found, int * index) 
 * Date Created: 3/25/23                 	        
 * Date Last Modified: 4/4//23                      
 * Description: This functions sorts the songs by the users desidres attribute
 * Input parameters: string searchAttribute, string searchAttributeValue, bool * found, int * index
 *************************************************************/
Song * SongLibrary::performSearch(string searchAttribute, string searchAttributeValue, bool * found, int * index) 
{
	int count = 0;
    Song * current = head; //curr starts at head

    while (current != NULL) 
    {
        if(current->getStringAttributeValue(searchAttribute) == searchAttributeValue)
        {
            *found = true;
            *index = count;
            return current;
        }
        current = current->getNext();
        count += 1;
    }
    *found = false; //if song was not found
    return NULL; 
}
/*************************************************************
 * function: void SongLibrary::performInsertSongInOrder(Song * songToInsert) 
 * Date Created: 3/25/23                 	        
 * Date Last Modified: 4/4//23                      
 * Description: This function inserts the song in order
 * Input parameters: Song * songToInsert
 *************************************************************/
void SongLibrary::performInsertSongInOrder(Song * songToInsert) 
{
    if(head == NULL)
    {
        head = songToInsert;
        
    }
    else
    {
        Song * currSong = head;
        Song * prevSong = NULL;

        while(currSong != NULL && currSong->getStringAttributeValue(sortAttribute) < songToInsert->getStringAttributeValue(sortAttribute))
        {
            prevSong = currSong;
            currSong = currSong->getNext(); //use get next because next is not defined in SongLibrary.h
        }
        if(prevSong == NULL)
        {
            songToInsert->setNext(head);
            head = songToInsert;
        }
        else
        {
            songToInsert->setNext(currSong);
            prevSong->setNext(songToInsert);
        }
    }
}
/*************************************************************
 * function: void SongLibrary::performRemoveSong(Song * songToRemove)
 * Date Created: 3/28/23                 	        
 * Date Last Modified: 4/3/23                      
 * Description: This functions removes a song depending on the users desired attributes
 * Input parameters: Song * songToRemove
 *************************************************************/
void SongLibrary::performRemoveSong(Song * songToRemove) 
{
    Song * current = head;
    Song * previous = nullptr;
    
    while (current != nullptr && current != songToRemove) 
    {
        previous = current;
        current = current->getNext();
    }

    if (current != nullptr && current == songToRemove) 
    {
        if (current == head) 
        {
            head = current->getNext();
        }
        else 
        {
            previous->setNext(current->getNext());
        }

        delete current;
        cout << "Song removed successfully." << endl;
    }
    else 
    {
        cout << "Song not found in library." << endl;
    }
}
/*************************************************************
 * function: void SongLibrary::performEditSong(Song * songToEdit, string attribute, string newAttributeValue)	        
 * Date created: 3/28/23      x      
 * Date Modified: 3/28/23  
 * Description: This functions edits a song depending on the users desires input
 * Input parameters: int indexToEdit, string attribute, string newAttributeValue)
 *************************************************************/
void SongLibrary::performEditSong(Song * songToEdit, string attribute, string newAttributeValue) 
{	
    //if the song is found, edit the specified attribute
    if (attribute == "title") 
    {
        songToEdit->setTitle(newAttributeValue);
        cout << "song to edit title" << songToEdit->getTitle() << endl;
    }
    else if (attribute == "artist") 
    {
        songToEdit->setArtist(newAttributeValue);
    }
    else if (attribute == "genre") 
    {
        songToEdit->setGenre(newAttributeValue);
    }
    else if (attribute == "rating") 
    {
        int newRating = stoi(newAttributeValue);
        if (newRating < 0) 
        {
            newRating = 0;
            songToEdit->setRating(newRating);
        }
        if(newRating > 5)
        {
            newRating = 5;
            songToEdit->setRating(newRating);
        }
        songToEdit->setRating(newRating);
    }
    else {
        cout << "Invalid attribute name." << endl;
        return;
    }
    cout << "Song edited successfully." << endl;
       
}
/*************************************************************
 * function: void SongLibrary:: loadLibrary()
 * Date Created: 4/2/23                 	        
 * Date Last Modified: 4/2/23                      
 * Description: This functions is a helper function for load
 * Input parameters: none
 *************************************************************/
void SongLibrary:: loadLibrary()
{
    string fileLoadName;
    cout << "Enter the name of the file to load to" << endl;
    cin >> fileLoadName;
    performLoad(fileLoadName);
}
/*************************************************************
 * function: void SongLibrary::displayLibrary()
 * Date Created: 4/2/23                 	        
 * Date Last Modified: 4/2/23                      
 * Description: This functions is a helper function for load
 * Input parameters: none
 *************************************************************/
void SongLibrary::displayLibrary()
{
    Song * currentSong = head;

    while(currentSong != NULL)
    {
        cout << "Title: " << currentSong->getTitle() << endl;
        cout << "Arist: " << currentSong->getArtist() << endl;
        cout << "Genre: " << currentSong->getGenre() << endl;
        cout << "Rating: " << currentSong->getRating() << endl;
        cout << endl;
        currentSong = currentSong->getNext(); //moves the current song to the next
    }
}
/*************************************************************
 * function: void SongLibrary::saveLibrary()
 * Date Created: 4/3/23                 	        
 * Date Last Modified: 4/3/23                      
 * Description: This functions is a helper function for save library
 * Input parameters: none
 *************************************************************/
void SongLibrary::saveLibrary()
{
    string fileSaveName;
    cout << "Enter the name of the file to save to" << endl;
    cin >> fileSaveName;
    performSave(fileSaveName);
}
/*************************************************************
 * function: void SongLibrary::searchLibrary()
 * Date Created: 4/3/23                 	        
 * Date Last Modified: 4/3/23                      
 * Description: This functions is a helper function that searches the library
 * Input parameters: none
 *************************************************************/
void SongLibrary::searchLibrary()
{
    string searchAttribute, searchAttributeValue;
    bool found = false;
    int index;
    Song * returnedSong;

    cout << "What song do you want to search for? Please type in an attribute (title, artist, genre, rating)" << endl;
    getline(cin, searchAttribute);
    cout << "What song " << searchAttribute << " do you want to search for?" << endl;
    getline(cin, searchAttributeValue);
    returnedSong = performSearch(searchAttribute, searchAttributeValue, &found, &index);
    if (found)
    {
        cout << "\nFound Song #" << index << endl;
        cout << "Title: " << returnedSong->getTitle() << endl;
        cout << "Artist: " << returnedSong->getArtist() << endl;
        cout << "Genre: " << returnedSong->getGenre() << endl;
        cout << "Rating: " << returnedSong->getRating() << endl;
    }
    else
    {
        cout << "Song was not found. " << endl;
    }
}
/*************************************************************
 * function: void SongLibrary::addSongToLibrary()
 * Date Created: 4/3/23                 	        
 * Date Last Modified: 4/3/23                      
 * Description: This functions is a helper function that addssong 
 * Input parameters: none
 *************************************************************/
void SongLibrary::insertASongToLibrary()
{
    string ntitle, nartist, ngenre;
    int nrating;
    Song * songAdd = new Song();
    
    cout << "Please enter name of the song" << endl;
    getline(cin, ntitle);
    cout << "Please enter an artist" << endl;
    getline(cin, nartist);
    cout << "Please enter a genre" << endl;
    getline(cin, ngenre);
    cout << "Please enter a rating" << endl;
    cin >> nrating;
    cin.ignore();
    songAdd->setTitle(ntitle);
    songAdd->setArtist(nartist);
    songAdd->setGenre(ngenre);
    songAdd->setRating(nrating);
    performInsertSongInOrder(songAdd);

    cout << "Song was added!" << endl;
    
    /*delete songAdd;
    songAdd = NULL;*/
}
/*************************************************************
 * function: void SongLibrary::removeSongFromLibrary()
 * Date Created: 4/3/23                 	        
 * Date Last Modified: 4/3/23                      
 * Description: This functions is a helper function that removes songs 
 * Input parameters: none
 *************************************************************/
void SongLibrary::removeSongFromLibrary()
{
    string searchAttribute, searchAttributeValue;
    bool found;
    int index;
    Song * songNew;
    cout << "Please enter an attribute to search for a song to remove (title, artist, genre, rating)" << endl;
    getline(cin, searchAttribute);
    cout << "Please enter the " << searchAttribute << " to find and remove the song" << endl; 
    getline(cin, searchAttributeValue);
    
    songNew = performSearch(searchAttribute, searchAttributeValue, &found, &index);
    if(found == true)
    {
        performRemoveSong(songNew);
    }
}
/*************************************************************
 * function: void SongLibrary::sortLibrary()
 * Date Created: 3/29/23                 	        
 * Date Last Modified: 3/30/23                      
 * Description: This functions is a helper function that sorts library
 * Input parameters: none
 *************************************************************/
void SongLibrary::sortLibrary()
{
    string getAttribute;
    cout << "What song attribute would you like to sort by? (title, artist, genre, rating)" << endl;
    cin >> getAttribute;
    setSortAttribute(getAttribute);
    performSort();
    cout << "Song was sorted by " << getAttribute << "!" << endl;
}

/*************************************************************
 * function: void editSongInLibrary()
 * Date Created: 4/3/23                 	        
 * Date Last Modified: 4/3/23                      
 * Description: This functions is a helper function that edits songs library
 * Input parameters: none
 *************************************************************/
void SongLibrary::editSongInLibrary()
{ 
    string attribute, attributeValue;
    bool found = false;
    int index = 0;
    Song* returnedSong;

    cout << "Please enter an attribute to update (title, artist, genre, rating)" << endl;
    getline(cin, attribute);
    cout << "Please enter the " << attribute << " you want to update" << endl;
    getline(cin, attributeValue);

    returnedSong = performSearch(attribute, attributeValue, &found, &index);
   
    if(found == true)
    {
        cout << "Title: " << returnedSong->getTitle() << endl;
        cout << "Artist: " << returnedSong->getArtist() << endl;
        cout << "Genre: " << returnedSong->getGenre() << endl;
        cout << "Rating: " << returnedSong->getRating() << endl;

        cout << "Enter new attribute value" << endl;
        getline (cin, attributeValue);
        cout << "att value: "<<  attributeValue << endl;

        performEditSong(returnedSong, attribute, attributeValue);
    }
    else 
    {
        cout << "Song was not found to edit. " << endl;
    }

    
}

   
