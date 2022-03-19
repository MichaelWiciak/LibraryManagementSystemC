#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libraryStructures.h"
#include "library.h"
#include "user.h"
#include "librarian.h"
#include "utility.h"

////
// Code module for main library menu and file management
// Reads the book and initialises the problem data

// Initialise library data
// Input: 
// bookfile - name of book file
// theLibrary - library data structure

void initLibrary( char *bookFile, Library *theLibrary ) {

  theLibrary->maxBooks = 12;
  theLibrary->maxBorrowed = 4;

  // TO DO :
  // dynamically allocate the bookList array for storing books
  Book *bookList = (Book *)calloc(12, sizeof(Book));
  
  FILE *books;
   if ((books = fopen(bookFile, "r")))
    {
     theLibrary->numBooks = readBooks(books, bookList);
     theLibrary->bookList = bookList;
     fclose(books);}
    else {
        printf("Error\nBook file does not exist: %s\n",bookFile);
        exit(1);
    }
  // check the book file exists 
  // use the error message and exit the program if it does not
  theLibrary->bookList = bookList;
  // open it if it exists

  // use the readBooks function to read in the file and add the book records into the bookList array

  // close the file
  // Initialise the User data  Book *borrowed[4];
  
  User *theUser = (User *)malloc(sizeof(User));
  theUser->numBorrowed = 0;
  
char emptyString[40]="HELLO EVERYONE";
  int count=0;
  
while (count<4){
theUser->borrowed[count]= (Book *)malloc(sizeof(Book));
strcpy(theUser->borrowed[count]->author, emptyString);
strcpy(theUser->borrowed[count]->title, emptyString);
  count ++;
  }
  
  theLibrary->theUser= *theUser;
  
  return;
}

// Read in book file and create the books data structure
// the book file is in a fixed format:
// * book author
// * book title
// * blank line
// Input:
//   books - file pointer to text input file
//   bookList - alocated array for storing Book structures
// Output:
//   numBooks - number of books read

int readBooks( FILE *books, Book *bookList ) {

  int numBooks = 0;
  char line[999];
  int count = 0;
  int lineMeaning=0;
    while(fgets(line,40, books)) {
        
        if (lineMeaning==0){
            lineMeaning=1;
            line[strlen(line)-1] = '\0';
            line[strlen(line)-1] = '\0';
            if (line[0] != '\0'){
            strcpy(bookList[numBooks].author, line);
            }
        }
        else if (lineMeaning==1){
            lineMeaning=2;
            line[strlen(line)-1] = '\0';
            if (line[0] != '\0'){
            strcpy(bookList[numBooks].title, line);
            numBooks ++;
            }
        }
        else if (lineMeaning==2){
            lineMeaning=0;
        } 
        
        count ++;}
        
    count = 0;

    while (count <= numBooks){
        bookList[count].available = 1;
        count ++;
    }
    
        
  // read from the book file pointer
 
  // assign values to a Book structure in the bookList array for each complete record
        
  // read data until the file ends
  return numBooks;
}

// Free any allocated library data
// Input: 
// theLibrary - library data structure

void exitLibrary( Library *theLibrary ) {

  // TO DO:

  // free the allocated lists
   int count=0;
  free(theLibrary->bookList);
  while (count<4){
    free(theLibrary->theUser.borrowed[count]);
  count++;
  }


  return;
}

// Library menu system

void libraryCLI( char *bookFile ) {
    int libraryOpen = 1;
    int option;

    // create the library structure
    Library *theLibrary = (Library *)malloc( sizeof(Library) );

    initLibrary( bookFile, theLibrary );
   
    while( libraryOpen ){
        printf("\n Main menu options\n 1 User login\n 2 Librarian login\n 3 Exit system\n Choice:");
        option = optionChoice();

        if( option == 1 ) {
            printf("\nUser login\n");
            userCLI( theLibrary );
        }
        else if( option == 2 ) {
            printf("\nLibrarian login\n");
            librarianCLI( theLibrary );
        }
        else if( option == 3 ) {
            libraryOpen = 0;
            printf("\nClosing\n");
        }
        else
            printf("\nUnknown option\n");
    }

    exitLibrary( theLibrary );

    // free the library structure
    free( theLibrary );

    return;
}

