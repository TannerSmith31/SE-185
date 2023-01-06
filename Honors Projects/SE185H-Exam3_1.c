///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "MadLibFunctions.h"

/**
*Write a program that simulates a game of MadLib wherin the player enters the name of a text file that contains a base story of proper format.
*The text file must have the following structure: 
*	The first line is a list of word types that the user will have to enter (seperated by commas)
*	The rest of the file will be the short story with '*' characters where user input will go.
*The program will scan through the story, copying it to a seperate output file, and whenever it finds a '*' it will
*ask the user to enter a certain type of word (following the list in the first line).
*The completed madLibGame will be put into a different file. it should NOT overwrite the origional template!
*
*	max words to be input by user is 20 (so is the max lenght of said words). 
*	The most characters to be used to describe a word is 20. Most characters in first line of file is 80.
*/


void main(){
	char curFilename[20];
	FILE* storyReader;
	FILE* gameOutput;
	madLibGame curGame;   //stores the name of the file, comma indexes, and start of the file
	char userInput[20];
	//ask user to enter a text file to play the game
	printf("Enter a MadLib text File of the correct format: ");
	scanf("%s", curFilename);
	
	//Initialize madLibGame structure to hold the right info
	initializeGame(&curGame, curFilename);
 
	//Open a new file to write the story in and a file to read the story from
	storyReader = fopenChecked(curFilename,"r");
	gameOutput = fopenChecked("FilledMadLib.txt", "w");
	
	//set the storyReader to the begining of the story
	fseek(storyReader, curGame.storyStartIndex, SEEK_SET);	//SEEK_SET sets the origin (reference point) at the begining of the file
	char ch = fgetc(storyReader);
	int curStoryIndex = curGame.storyStartIndex;	//start your current story cursor at the start of the story
	int usrInputCnt = 0;
	char wrdDescription[15];
	
	while (ch != EOF){
		if (ch == '*'){	//if you hit an asterickt, its time to take user input
			fseek(storyReader, curGame.commaIndices[usrInputCnt]+1, SEEK_SET);
			fgets(wrdDescription, curGame.commaIndices[usrInputCnt+1] - curGame.commaIndices[usrInputCnt], storyReader);
			printf("Please enter a(n) %s: ", wrdDescription);
			scanf("%s", userInput);
			fseek(storyReader, ++curStoryIndex, SEEK_SET);	//move the storyReader back to where it was (plus one using PRE INCREMENT so '*' isn't reread)
			fputs(userInput, gameOutput);	//put the word into the output file
			usrInputCnt++;
		} else {
			fputc(ch, gameOutput);	//else you just print to the output file whatever character you read from the story
			curStoryIndex++;
		}
		ch = fgetc(storyReader);
	}
	//close the two fileReaders
	fclose(storyReader);
	fclose(gameOutput);
	
	//TEST THE FILE AS IS UP TO THIS POINT (with the code to print to console) THEN DO THE APPEND THING
	//Open the output file in append mode to add "THE END"
	gameOutput = fopenChecked("FilledMadLib.txt", "a");
	fputs(" THE END.", gameOutput);
	fclose(gameOutput);
	
	//print out the story to the console?
	printf("\n\n");
	gameOutput = fopenChecked("FilledMadLib.txt", "r");
	ch = fgetc(gameOutput);
	while (ch != EOF){
		printf("%c", ch);
		ch = fgetc(gameOutput);
	}
}




/*
void main(){
	//instance Variables
	
	
	//ask user to enter a text file to play the game
	printf("Enter a MadLib text File of the correct format: ");
	scanf("%s", curFilename);
	
	//Initialize madLibGame structure to hold the right info
 
 
	//Open a new file to write the story in and a file to read the story from
	
	
	//set the storyReader to the begining of the story and read through, asking for user input when needed
	
	
	//Append "THE END"
	
	//print out the story to the console?
}
*/

/*
void initializeGame(madLibGame* game, char filename[]){
	//put file name into structure
	
	//put the list of comma indices into the structure
	
	//put the index of the start of the story into the text file
}
*/

