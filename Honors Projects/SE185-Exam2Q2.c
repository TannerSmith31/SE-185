#include <stdio.h>		//This library is needed for printf() and scanf() functions to work
#include <string.h>		//This library is needed for string stuff
#include <stdlib.h>		//This library is needed for Exit() and rand() to work

/**
 *POINTERS & FUNCTIONS
 *
 *Create a cash piggy bank program that stores coins.
 *The number of coins in the piggy bank is stored in an array of the form [pennies, nickels, dimes, quarters]. 
 *The total ammount of money in the piggy bank is stored in a variable "total". 
 *User will input letter for each of the coins ('P' = penny, 'N' = nickel, 'D' = dime, 'Q' = quarter) until they
 *choose to "break" the piggy bank by entering 'S', at which point the total & number of coins in the piggy bank will be printed out.
 */
 
 //
 void addCoins(char coin, int coinArr[], double* total);

void main(void){
	double total = 0;
	int coins[4] = {0, 0, 0, 0};
	char userInput;
	
	printf("Add coins to your piggy bank.\nP = penny, N = nickel, D = dime, Q = quarter\n");
	printf("Type 'S' to smash!\n");
	printf("Insert Coin: ");
	scanf(" %c", &userInput);
	while(userInput != 'S'){
		addCoins(userInput, coins, &total);
		printf("Insert Coin: ");
		scanf(" %c", &userInput);
	}
	printf("\nYou saved %d Pennies, %d Nickels, %d Dimes, and %d Quarters.\nyour net worth is $%.2lf!\n", coins[0], coins[1], coins[2], coins[3], total);
 }
 
 
 
 void addCoins(char coin, int coinArr[], double* total){
	switch(coin){
		case 'P':
			coinArr[0] += 1;
			*total += 0.01;
			break;
		case 'N':
			coinArr[1] += 1;
			*total += 0.05;
			break;
		case 'D':
			coinArr[2] += 1;
			*total += 0.10;
			break;
		case 'Q':
			coinArr[3] += 1;
			*total += 0.25;
			break;
		case 'S':
			//nothing to do here but break the switch statement. Will break loop once switch statement is broken
			break;
		default:
			printf("Not a valid coin!\n");
			break;
	 }

 }