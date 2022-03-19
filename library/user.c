#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libraryStructures.h"
#include "user.h"
#include "utility.h"


////
// Code module for the library user
// They can look for available books,
// borrow and return books

// List the books that are available to borrow
// Input
// bookList - the array of Book structures
// numBooks - the number of books

void listAvailableBooks( Book *bookList, int numBooks ) {

  // TO DO :  
  int count=0;
  
  while (count!=numBooks){
      if (bookList[count].available == 1){
          printf("%i - %s - ", count, bookList[count].author);
          printf("%s\n", bookList[count].title);
      }
      
      count ++;
      }
  // print out available books with format "list number - author - title" on each line
  
  return;
}

// Borrow a book 
// Input
// theUser - user data structure
// bookList - the array of Book structures
// numBooks - the number of books
// maxBorrowed - max books we can borrow

void borrowBook( User *theUser, Book *bookList, int numBooks, int maxBorrowed ) {

  // TO DO :  
  // For any error message you should return to the menu

  // check that the user can borrow a book
  int count=0;

  if (theUser->numBorrowed >= maxBorrowed){
    printf("You have to return a book before you can borrow another\n");
    return;
  }
  int nextAvailableSpace, isInput;
  while (count<maxBorrowed){
      if (strcmp(theUser->borrowed[count]->author,"HELLO EVERYONE")==0){
          nextAvailableSpace=count;
          count = maxBorrowed;
      }
      else{
       count ++;   
      }
  }
  // request the choice of book 
//    printf("nextAvailableSpace -%i-, isInput -%i-", nextAvailableSpace, isInput);
  printf("Which book? (number):");
  isInput = optionChoice();
  if (isInput > numBooks || isInput < 0){
      printf("Error\nInvalid choice\n");
      return;
  }
  
  if (bookList[isInput].available != 1){
      printf("Book is not available\n");
      return;
  }
  // check that the choice is valid 
  // error messages
  
  bookList[isInput].available = 0;
 
  theUser->numBorrowed ++;
  strcpy(theUser->borrowed[nextAvailableSpace]->author, bookList[isInput].author);
  strcpy(theUser->borrowed[nextAvailableSpace]->title, bookList[isInput].title);
  theUser->borrowed[nextAvailableSpace]->available = 0;
  
  //borrow the book, update the data structures

  return; 
}

// List books I have borrowed 
// Input
// theUser - user data structure
// bookList - the array of Book structures
// maxBorrowed - max books we can borrow

void listMyBooks( User *theUser, Book *bookList, int maxBorrowed ) {

  // TO DO :  

  // list my books in format "number - author - title"
  int count=0;
  while (count<4){
      if (strcmp(theUser->borrowed[count]->author, "HELLO EVERYONE")){
      printf("%i - %s - %s \n", count, theUser->borrowed[count]->author, theUser->borrowed[count]->title);}
      
      count ++;
  }


  return;
}

// Return a book 
// Input
// theUser - user data structure
// bookList - the array of Book structures
// numBooks - the number of books
// maxBorrowed - max books we can borrow

void returnBook( User *theUser, Book *bookList, int numBooks, int maxBorrowed ) {

  // TO DO :  
  // For any error message you should return to the menu

  // check that we have borrowed books 
  // error messages
  if (theUser->numBorrowed==0){
    printf("Error\nYou have not borrowed any books\n");
    return;}

  // request the choice of book 
  // message
  int input;
  printf("Which book? (number):");
  input = optionChoice();

  // check the choice is valid
  if (input > numBooks || input < 0||strcmp(theUser->borrowed[input]->author,"HELLO EVERYONE")==0){
    printf("Error\nInvalid choice\n");
    return;
  }
  // error messages
  int count=0, stopFlag=0;
  while (stopFlag==0&&count<numBooks){
      if (strcmp(bookList[count].author, theUser->borrowed[input]->author)==0 && strcmp(bookList[count].title, theUser->borrowed[input]->title)==0){
          bookList[count].available=1;
          stopFlag=1;
      }
      count ++;
  }
  // return the book and update data structures 
  strcpy(theUser->borrowed[input]->author, "HELLO EVERYONE");
  strcpy(theUser->borrowed[input]->title, "HELLO EVERYONE");
  theUser->borrowed[input]->available=1;

  theUser->numBorrowed --;
  
  return;
}


// Menu system for library user

void userCLI( Library *theLibrary ) {
    int userLoggedIn = 1;
    int option;

    while( userLoggedIn ){
        printf("\n User options\n 1 List available books\n 2 Borrow book\n 3 Return book\n 4 Log out\n Choice:");
        option = optionChoice();

        if( option == 1 ) {
            printf("\nList available books:\n");
            listAvailableBooks( theLibrary->bookList, theLibrary->numBooks );
        }
        else if( option == 2 ) {
            printf("\nBorrow book from library:\n");
            listAvailableBooks( theLibrary->bookList, theLibrary->numBooks );
            borrowBook( &(theLibrary->theUser), theLibrary->bookList, theLibrary->numBooks, theLibrary->maxBorrowed );
        }
        else if( option == 3 ) {
            printf("\nReturn book from my list:\n");
            listMyBooks( &(theLibrary->theUser), theLibrary->bookList, theLibrary->maxBorrowed );
            returnBook( &(theLibrary->theUser), theLibrary->bookList, theLibrary->numBooks, theLibrary->maxBorrowed );
        }
        else if( option == 4 ) {
            userLoggedIn = 0;
            printf("\nLogging out\n");
        }
        else
            printf("\nUnknown option\n");
    }
    return;
}

