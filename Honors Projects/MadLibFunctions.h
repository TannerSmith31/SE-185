///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
#ifndef MadLibFunctions_h
#define MadLibFunctions_h
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//FOR PART 2
#include <unistd.h> // for the getcwrd() function
#include <dirent.h>		//needed for directory stuff
#include <sys/stat.h> //needed for time



/**Structure to hold the game info*/
typedef struct madLib_struct {
	char fileName[20];		//stores the name of the file
	int commaIndices[20];	//where in the file the commas in the first line are (as well as the first index of the line and the end of the line)
	int storyStartIndex;	//the index of the file at which the story starts (the second line of code)
}madLibGame;

/////////////////////////
//FUNCTION DECLARATIONS//
/////////////////////////
/**function to initialize the Game structure by storing the file name and the parsed word list*/
void initializeGame(madLibGame* game, char filename[]);

/**Function that checks if a file exists. if it does, it opens the file. if it doesnt, it exits the program*/
FILE* fopenChecked(char fileName[], char mode[]);

/**Function that generates a random word from a textfile somewhere in the current directory (could be in a subfile)*/
void findWrdRec(char pathName[], char targetFileName[], char* returnWrd);

/**function that updates the given path name to instead point to whatever the dirent structure in the second parameter points to*/
void updatePathName(char pathName[], struct dirent* dent);

/**Function to revert a path name to whatever it was before you entered the directory**/
void revertPathName(char pathName[], struct dirent* dent);

//////////////////////////
///FUNCTION DEFINITIONS///
//////////////////////////

/**
 * function to initialize the Game structure by storing the file name, file pointer, and the parsed word list
 */
void initializeGame(madLibGame* game, char filename[]){
	FILE* fp = fopenChecked(filename, "r");

	//put file name into structure
	strcpy(game->fileName, filename);
	
	//put the list of comma indices into the structure
	int index = 0;
	game->commaIndices[0] = -1;	//gives the index of the start of the file to be where the first "comma" is
	int numIndices = 1;
	char ch = fgetc(fp);
	while (ch != '\n' && ch != EOF){	//iterates through the first line of code
		if (ch == ','){
			game->commaIndices[numIndices] = index;
			numIndices++;
		}
		ch = fgetc(fp);
		index++;
	}	//when this breaks, we should have a complete list of all the commas in the string
	game->commaIndices[numIndices] = index-1;	//adds the index of the end of the word list into the array list (-1 so you don't account for newline character or it would cause weird printing when taking input)
	
	//put the index of the start of the story into the text file
	game->storyStartIndex = index+1;//gets rid of the newLine character
	
	fclose(fp);	//good practice
}


/**
 * Function to open a file but exit the program if the file doesn't exist
 */
FILE* fopenChecked(char fileName[], char mode[])
{
    FILE* fp = fopen(fileName, mode);
	if (fp == NULL){
		printf("File Not Found");
		exit(0);
	}else{
		return fp;
	}
	//maybe add a warning if you are opening in write mode (it will delete the contents of the file if it already exists)
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////PART 2

/**
 *Function that generates a random word of the correct word type by checking though all files in a directory
 *unil it finds the text file that is labeled for the current word. You don't have to deal with it not being able to find the text file.
 */
void findWrdRec(char pathName[], char targetFileName[], char* returnWrd){
	//creating a pointer to access files in the directory
	DIR* dir;
	dir = opendir(pathName);
	struct dirent* dent;	//a thing that allows you to call functions on directory? dent->d_name gets the name of the file the pointer is currently on
	dent = readdir(dir);
	while(dent != NULL){	//iterates through all the stuff in the directory
		while(strcmp(dent->d_name,".") == 0 || strcmp(dent->d_name,"..") == 0){		//this loop ignores the '.' and '..' directories that always come first
			dent=readdir(dir);
			
		}
		if(dent->d_type == DT_DIR){	//if the current thing is a directory
				
			//UPDATE THE PATH NAME
			updatePathName(pathName, dent);	//updating the path name to store the directory path you are looking at
			findWrdRec(pathName, targetFileName, returnWrd);		//recursively call the function on the inner directory;
			revertPathName(pathName, dent);
		}else {	//it must be a file so check if the file has the correct name
			if (strcmp(dent->d_name, targetFileName) == 0){ //if names match
				updatePathName(pathName, dent);	//update the path name to hold the path to the correct file because you cant open the file by just the text file name because it isn't in the cwd
				FILE* fp = fopen(pathName, "r");
				srand(time(NULL));
				int randNum = rand() % 100;	//assume no file will be longer than 100 words for our case. you could make a word counter to get a count using fgets untill you hit end of file
				for (int i = 0; i <= randNum; i++){	//iterate through the words till you get to the random one
					if (feof(fp)){			//if you get to the end of the file, reset to the beginning
						fseek(fp, 0, SEEK_SET);
					}
					fscanf(fp, "%s\n", returnWrd);
				}
				revertPathName(pathName, dent);
				//return;
			}
		}
		dent = readdir(dir);
	}
	closedir(dir);
	return;
	
	
	//if the thing is a directory
		//go into directory
		//call findWrdRec on everything in the directory
	//else it must be a file so..
		//if it has the right name
			//open it and return a random word from it
		//else
			//do nothing
		
	//update dir pointer
}


/**
 *Function to update the given pathName and make it be a path to whatever is stored in dent.
 *NOTE: it overwrites the current path name
 */
void updatePathName(char pathName[], struct dirent* dent){
	strcat(pathName, "/"); strcat(pathName, dent->d_name);
}

/**
 *Function to revert the given pathName to what it was before you entered the current directory (i.e, it gets rid of the /DIRECTORYNAME)
 */
void revertPathName(char pathName[], struct dirent* dent){
	char tempString[PATH_MAX];
	for (int i = 0; i < strlen(pathName) - (strlen(dent->d_name)+1); i++){	//+1 to account for '/' character we also added
		tempString[i] = pathName[i];
	}
	printf(" ");
	strcpy(pathName, tempString);
}

#endif