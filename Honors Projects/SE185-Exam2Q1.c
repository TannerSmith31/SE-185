#include <stdio.h>		//This library is needed for printf() and scanf() functions to work
#include <string.h>		//This library is needed for string stuff
#include <stdlib.h>		//This library is needed for malloc(), realloc(), free()

/**
 *POINTER BASICS: malloc(), realloc(), free(), iterating through string w/ pointer
 *
 *Write a program that asks the user for a username for their primary email
 * and then, using pointers, creates an email address for the user by appending "@iastate.edu". 
 * Then, use memory reallocation to create a secondary email from a second
 * username input by the user.
 */

void main(void){
	char username[20];
	char emailTag[13] = "@iastate.edu"; //13 to account for null character
	char* userEmailPtr;	//* makes it a pointer variable
	int usernameLength;
	
	//Get primary input from user
	printf("Enter a username for primary email: ");
	scanf("%s", username);
	usernameLength = strlen(username);
	
	//use Malloc to assign usernameptr to userEmailPtr which holds just enough to add "@iastate.edu" to the end
	userEmailPtr = (char*)malloc((usernameLength + 13)* sizeof(char)); //the +13 has to do with making just enough space for the "@iastate.edu" and null character '\0'
	for (int i = 0; i< usernameLength; i++){
		*(userEmailPtr + i) = username[i];
	}
	for (int j = 0; j < 13; j++){
		*(userEmailPtr + usernameLength + j) = emailTag[j];
	}

	printf("Your primary email is %s", userEmailPtr);	//no need for '*' so it prints out entire string
	
	//Get secondary input from user
	printf("\n\nPlease enter a second username to create a secondary email: ");
	scanf("%s", username);
	usernameLength = strlen(username);
	
	//use reallocate
	userEmailPtr = (char*)realloc(userEmailPtr, (usernameLength +13) * sizeof(char)); //the +13 has to do with making just enough space for the "@iastate.edu" and null character '\0'
	
	for (int i = 0; i< usernameLength; i++){
		*(userEmailPtr + i) = username[i];
	}
	for (int j = 0; j < 13; j++){
		*(userEmailPtr + usernameLength + j) = emailTag[j];
	}
	printf("Your secondary email is %s", userEmailPtr);	//no need for '*' so it prints out entire string
	
	free(userEmailPtr); //memory in the userEmailPtr is removed.
	
}