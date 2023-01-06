#include <stdio.h>		//This library is needed for printf() and scanf() functions to work
#include <string.h>		//This library is needed for string stuff
#include <stdlib.h>		//This library is needed for Exit() and rand() to work
#include <time.h>		//This library is needed for the time function to work

/* Write a program to create a username from a user-entered letter (A-E) and
 * number (0-100) and creates a username of the form [WORD]_[NUMBER].
 * RULES:
 *
 * If the letter is 'A', WORD is "Alpha"
 * If the letter is 'B', WORD is "Bravo"
 * If the letter is 'C', WORD is "Charlie"
 * If the letter is 'D', WORD is "Delta"
 * If the letter is 'E', WORD is "Echo"
 * 
 * If the number is between 25 and 50, NUMBER is a random number 0-2
 * Otherwise, if the number is between 50 and 75, NUMBER is a random number 3-5
 * Otherwise, if the number is NOT divisible by 10, NUMBER is random number 6-8
 * If none of the above hold true, NUMBER is 9
 */

void main(void){
	char userLetter;			//variable to store what letter the user enters
	int userNum;				//variable to store the nubmer the user enters
	int randomNum;				//variable to store the random number to be added to the username
	char userNameWord[9];		//variable to store the username
	
	printf("Enter a letter A to E: ");
	scanf("%c", &userLetter);		//%c format specifier because we are getting a CHARACTER from the user. DONT FORGET THE "&".
	
	//CALCULATE USER NAME
	//We use a switch statement here because there are a few specific values that the user is allowed to enter.
	switch(userLetter){
		case 'A':
		case 'a':
			strcpy(userNameWord,"Alpha_");	//you have to use strcpy(str,str) due to it being a string. "=" would not work.
			break;							//remember the break statements. Without them the next branch will execute
			
		case 'B':
		case 'b':
			strcpy(userNameWord,"Bravo_");
			break;
			
		case 'C':
		case 'c':
			strcpy(userNameWord,"Charlie_");
			break;
			
		case 'D':
		case 'd':
			strcpy(userNameWord,"Delta_");
			break;
		
		case 'E':
		case 'e':
			strcpy(userNameWord,"Echo_");
			break;
		
		default:
			printf("Invalid Letter Entry\n");
			exit(0);
	}
	
	//GET NUMBER FROM USER
	printf("Enter an integer 0-100: ");
	scanf("%d", &userNum);				//%d format specifier because we are getting an INTEGER from the user. Don't forget the "&"
	
	//CREATE A RANDOM NUMBER BASED ON USER INTEGER
	srand(time(NULL));
	
	//We use "if" and "else if" conditional statment here because we are checking for a range of values (rather than a few distinct values).
	if (userNum < 0 || userNum > 100){
		printf("Invalid Entry: number must be between 0 and 100\n");
		exit(0);						//this function terminates the program once this line is hit.
		
	} else if (userNum > 25 && userNum < 50){	
		randomNum = rand() % 3;				//enters this branch if number is between 25 and 50 (exclusive)
		
	} else if (userNum > 50 && userNum < 75){
		randomNum = rand() %3 + 3;			//enters this branch if number is between 50 and 75 (exclusive)
	
	} else if (userNum%10 != 0){
		randomNum = rand() %3 + 6;
		
	} else {
		randomNum = 9;
	}

	printf("%s%d", userNameWord, randomNum);	//%s format specifier for STRINGS becuase userNameWord is a string. %d format specifier for IINTEGER because randomNum is an integer.
}