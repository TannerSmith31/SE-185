#include <stdio.h>		//This library is needed for printf() and scanf() functions to work
#include <string.h>		//This library is needed for string stuff
#include <stdlib.h>		//This library is needed for Exit() and rand() to work

/**
 *Structures
 *
 *Create a program that uses a structure to simulate a piggy bank
 *the structure will include variables for all 4 type of coins (pennies, nickels, dimes, quarters) as well as the total ammount in dollars
 *User will first input an initial dollar amount (in cents) and a piggyBank structure will be created with taht much money with the least nubmer of coins.
 *User will input letter for each of the coins ('P' = penny, 'N' = nickel, 'D' = dime, 'Q' = quarter) until they
 *choose to "break" the piggy bank by entering 'S', at which point the total & number of coins in the piggy bank will be printed out.
 */
 
 //structure to act as our piggybank
 typedef struct PiggyBank_struct{
		int pennies;
		int nickels;
		int dimes;
		int quarters;
		double total;
		
	}PiggyBank;
	
	
//function to initialize a piggy bank with a given intial balance
PiggyBank initPiggy(int initBal);

//function to add coins to the piggy bank
void addCoins(char coin, PiggyBank* p);


void main(void){
	
	//instance variables
	PiggyBank p;				//creates a piggyBank structure (this has spots to hold all the internal variables
	char userInput;				//variable to store user input
	int initialBalance;			//variable to store initial balance
	

	printf("Enter an initital balance (as a integer for cents): ");
	scanf("%d", &initialBalance);
	
	//construct a piggyBank with the correct initial balance
	p = initPiggy(initialBalance);
	
	printf("\n\nAdd coins to your piggy bank.\nP = penny, N = nickel, D = dime, Q = quarter\n");
	printf("Type 'S' to smash!\n");
	printf("Insert Coin: ");
	scanf(" %c", &userInput);
	while(userInput != 'S'){
		addCoins(userInput, &p);
		printf("Insert Coin: ");
		scanf(" %c", &userInput);
	}
	printf("\nYou saved %d Pennies, %d Nickels, %d Dimes, and %d Quarters.\nyour net worth is $%.2lf!\n", p.pennies, p.nickels, p.dimes, p.quarters, p.total);
 }
 
//pass the piggyBank as a pointer so that you can edit the variables inside. if it was passed as an object, it wouldn't update using p.pennies += 1;
 void addCoins(char coin, PiggyBank* p){
	switch(coin){
		case 'P':
			p->pennies += 1;
			p->total += 0.01;
			break;
		case 'N':
			p->nickels += 1;
			p->total += 0.05;
			break;
		case 'D':
			p->dimes += 1;
			p->total += 0.10;
			break;
		case 'Q':
			p->quarters += 1;
			p->total += 0.25;
			break;
		default:
			printf("Not a valid coin!\n");
			break;
	 }
 }

//The point of this function is to show that functions can return structures
 PiggyBank initPiggy(int initBal){
	PiggyBank newPig;
	int remainder;
	
	newPig.total = initBal/100.0;
	
	newPig.quarters = initBal/25;
	remainder = initBal %25;
	
	newPig.dimes = remainder/10;
	remainder = remainder % 10;
	
	newPig.nickels = remainder/5;
	
	newPig.pennies = remainder % 5;
	return newPig;
 }