#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "MadLibFunctions.h"

/**
*Update our MadLib game to allow the computer to randomly generate a madLib.
*Assume that the words to be input will be stored in text files titled with the word descriptors in the first line of the code
*The files may be in seperate folders, so use a recursive function to search through all the files in the Current Working Directory
* and any sub directory.
*/


void main(){
	//instance Variables
	char curFilename[20];
	FILE* storyReader;
	FILE* gameOutput;
	madLibGame curGame;
	char userInput[20];
	
	
	//ask user to enter a text file to play the game
	printf("Enter a MadLib text File of the correct format: ");
	scanf("%s", curFilename);
	
	//Ask player how they want to play the game//////////////////////////////////////////////////////
	int gameMode;
	printf("How would you like to play? [0]User Generated, [1]Computer Generated:");
	scanf("%d", &gameMode);
	if (gameMode > 1 || gameMode < 0){
		printf("INVALID GAMEMODE");
		exit(0);
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////
	
	
	//Initialize madLibGame structure to hold the right info
	initializeGame(&curGame, curFilename);
 
 
	//Open a new file to write the story in and a file to read the story from
	storyReader = fopenChecked(curFilename, "r");
	gameOutput = fopenChecked("FilledMadLib.txt", "w");
	
	//set the storyReader to the begining of the story and read through, asking for user input when needed
	fseek(storyReader, curGame.storyStartIndex, SEEK_SET);
	char ch = fgetc(storyReader);
	int curStoryIndex = curGame.storyStartIndex;
	int usrInputCnt = 0;
	char wrdDescription[15];
	
	while (ch != EOF){
		if (ch == '*'){
			fseek(storyReader, curGame.commaIndices[usrInputCnt]+1,SEEK_SET);
			fgets(wrdDescription, curGame.commaIndices[usrInputCnt+1] - curGame.commaIndices[usrInputCnt], storyReader);
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if (gameMode == 0){
				printf("Please enter a(n) %s: ", wrdDescription);
				scanf("%s", userInput);
			
			} else if (gameMode == 1){
				//get Cwd to pass into the method first
				char cwd[PATH_MAX];
				getcwd(cwd, sizeof(cwd));
				//get the text file name
				char txtFileName[25];		//stores the name of the text file that will be searched for
				strcpy(txtFileName, wrdDescription);
				for (int i = 0; i<strlen(wrdDescription); i++){	//iterates through all characters of the word description and replaces ' ' with '_'
					if (wrdDescription[i] == ' '){
						txtFileName[i] = '_';
					}
				}
				strcat(txtFileName, ".txt");	//have to add this on so it searches for a text file
				findWrdRec(cwd, txtFileName, userInput);	//store the resulting word in userInput because thats how it works
				
			}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			fseek(storyReader, ++curStoryIndex, SEEK_SET);
			fputs(userInput, gameOutput);
			usrInputCnt++;
		}else{
			fputc(ch, gameOutput);
			curStoryIndex++;
		}
		ch = fgetc(storyReader);	
	}
	
	fclose(storyReader);
	fclose(gameOutput);
	
	
	//Append "THE END"
	gameOutput = fopenChecked("FilledMadLib.txt", "a");
	fputs(" THE END.", gameOutput);
	fclose(gameOutput);
	
	//print out the story to the console
	printf("\n\n");
	gameOutput = fopenChecked("FilledMadLib.txt", "r");
	ch = fgetc(gameOutput);
	while (ch != EOF){
		printf("%c", ch);
		ch = fgetc(gameOutput);
	}
}