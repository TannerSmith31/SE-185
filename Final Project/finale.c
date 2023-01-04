//SE 185: Final Project Template//
/////////////////////////

/* 
Team xx (please insert your team number instead of xx)
Team member 1 "Tanner Smith" | "50%"
Team member 2 "Andrew Meder" | "109%"
Team member 3 "John Doe" | "0%"
Team member 4 "Garry Jangledorf" | "-10%"
*/

//Directory: cd /cygdrive/u/fall2022/se185/FINALE
//Compile: gcc -o finale finale.c
//Run: ./finale wordList.txt

////////////////////
#include<stdio.h>//
//add more here////
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>


//////////////////////
//Struct Definition//
////////////////////
typedef struct wordInfo{
  char word[20];     //Word
  int length;         //Length of word
  int startCol;       //Column location of first letter of word
  int row;            //Current Row
}wordInfo;

/////////////////////////////////////
//User Defined Functions Prototype//
//List prototypes here and define//
//them below the main function////
/////////////////////////////////
int getFileWordcount(char* file_name);
void trimws(char* str);
int read_words(char* WL[], char* file_name);
void initializeGameBoard(char gameBoard[][50], int rows, int columns);
void printGameBoard(char gameBoard[][50], int rows, int columns, int difficulty);
void addWord(char GB[][50], char word[20], wordInfo currWords[], int* currWordCnt);
void shiftDown(char GB[][50], wordInfo currWords[], int currWordCnt);
void removeWord(char GB[][50], wordInfo currWords[], char wordToRemove[], int* currWordCnt);
char* generateWord(char fileName[], int minLength);
int endGame(wordInfo currWords[], int currWordCnt);
int getCSeconds(struct timeval clock);
int getDifference(struct timeval clock1, struct timeval clock2);

int main(int argc, char* argv[]){
  //VARIABLES
  int NUMCOLS = 50;
  int NUMROWS = 20;
  char gameBoard[NUMROWS][NUMCOLS];   //variable for the gameboard
  char userCharInput;
  int userNumInput;
  char userStrInput[20];
  int fileWordcount;
  FILE* fPtr;
  int numWordsOnScreen = 0;
  int gameOver = 0;
  wordInfo wordsOnScreen[20];
  
  //Time variables
  struct timeval lastWrdTime;
  struct timeval curTime;
  struct timeval startTime;
  struct timeval endTime;
  int timeSinceLastWrd;
  int numWrdsToAdd;
  int timeLimit = 150;
  int TLCHANGE = 10;
  int TLFREQ = 600;
  int difficulty = 1;   //count how many times the times the time limit has been decreased
  
  /////////////
  //storing the name of the file given into a variable named fileName
  char fileName[30];
  strcpy(fileName, argv[1]);
  
  //counting how many words are in the file & creating a list of words
  fileWordcount = getFileWordcount(fileName);
  char* wordArray[fileWordcount]; //creating an array to store the number of words in the file
  read_words(wordArray, fileName); //putting words from the file into the array
  
  ////////////////////////////////////////////////BEGINNING OF PROGRAM
  printf("Hello, this is a typing game. You will need to type the words as they appear would you like to play or add a word?\n");
  printf("You currently have %d words that can be used. (p/w)\n", fileWordcount);
  scanf("%c", &userCharInput);
  if(userCharInput == 'p'){   //initialize game
    printf("What would you like your minimum word length to be?\n");
    scanf("%d", &userNumInput);
  } else if(userCharInput == 'w'){    //append word to file
    printf("What word would you like to add?\n");
    scanf("%s", userStrInput);
    fPtr = fopen(fileName, "a");
    fputs("\n", fPtr);
    fputs(userStrInput, fPtr);
    fclose(fPtr);
    fileWordcount++;  //adding 1 to the wordcount of the file
    printf("There are now %d words. Would you like to play or add another word? (p/w)\n", fileWordcount);
    while (userCharInput == 'w'){
      printf("What word would you like to add?\n");
      scanf("%s", userStrInput);
      fPtr = fopen(fileName, "a");
      fputs("\n", fPtr);
      fputs(userStrInput, fPtr);
      fclose(fPtr);
      fileWordcount++;
      printf("There are now %d words. Would you like to play or add another word? (p/w)\n", fileWordcount);
      scanf("%s", userStrInput);
    }
  }else{
    printf("Invalid input!");
    exit(0);
  }
  ////////////////////////////////////////////////////////////////BEGIN GAME
  initializeGameBoard(gameBoard, NUMROWS, NUMCOLS);
  gettimeofday(&startTime, NULL);
  srand(time(NULL));
  char* newWord = generateWord(fileName, userNumInput);
  addWord(gameBoard, newWord, wordsOnScreen, &numWordsOnScreen);
  printGameBoard(gameBoard, NUMROWS, NUMCOLS, difficulty);
  gettimeofday(&lastWrdTime, NULL);
  while(!gameOver){
    printf("Type here: ");
    scanf("%s", userStrInput);
    removeWord(gameBoard, wordsOnScreen, userStrInput, &numWordsOnScreen);
    gettimeofday(&curTime, NULL);   //get current time
    timeSinceLastWrd = getDifference(curTime, lastWrdTime);   //find out how much time has passed since we last added a word
    if (timeSinceLastWrd > timeLimit){  //if it has been long enough...
      for(int i = 0; i < (timeSinceLastWrd / timeLimit);i++){ //iterate through the loop X number of times so that you add the correct number of words given the ammount of time you spent since a last word was added
        shiftDown(gameBoard, wordsOnScreen, numWordsOnScreen);
        newWord = generateWord(fileName, userNumInput);
        addWord(gameBoard, newWord, wordsOnScreen, 
        &numWordsOnScreen);
      }
      gettimeofday(&lastWrdTime, NULL);  //now that you just added a word, set the time that you last added a word to the current time
      if (getDifference(curTime, startTime) > (difficulty*TLFREQ)){  //if it is time to decrease the ammount of time you have before a word gets addded, do it.
        if (!(timeLimit <= TLCHANGE)){
          timeLimit -= TLCHANGE;
          difficulty++;
        }
      }
    }
    printGameBoard(gameBoard, NUMROWS, NUMCOLS, difficulty);
    if(endGame(wordsOnScreen, numWordsOnScreen) == 1){
      shiftDown(gameBoard, wordsOnScreen, numWordsOnScreen);
      printGameBoard(gameBoard, NUMROWS, NUMCOLS, difficulty);
      gameOver = 1;
    }
  }
  ////////////////////////////////////////////////////////////////END GAME
  gettimeofday(&endTime, NULL);
  int totalGameTime = getDifference(endTime, startTime);
  printf("\n You made it %d seconds!", totalGameTime/100);
  return 0;
}

///////////////////////////////////////
//User Defined Functions' Definition//
/////////////////////////////////////

int getFileWordcount(char* file_name){
  char *p;
  char line[20];      //assuming that no word is over 19 characters long
  FILE* fp = fopen(file_name, "r");
  int numWordsInFile = 0;
  while (!feof(fp)) {
    p = fgets(line, 20, fp);    //assuming that no word is over 19 characters long
    if (p != NULL){
      numWordsInFile++;
    }
  }
  fclose(fp);
  return numWordsInFile;
}

//taken from lab 9
void trimws(char* str) {
  int length = strlen(str);
  int x;
  if (length == 0) return;
  x = length - 1;
  while (isspace(str[x]) && (x >= 0)) {
    str[x] = '\0';
    x -= 1;
  }
}

int read_words(char* WL[], char* file_name)  //WL is length 1000 becuase there are 1000 words in the text file we were given ("wordList.txt")
{
  int numread = 0;
  char line[20]; //assuming that no word is 
  over 15 characters long
  char *p;
  FILE* fp = fopen(file_name, "r");
  while (!feof(fp)) {
    p = fgets(line, 20, fp); //assuming that no word is over 15 
    characters long
    if (p != NULL) 
    {
      trimws(line);
      WL[numread] = (char *)malloc(strlen(line) + 1);
      strcpy(WL[numread], line);
      numread++;
    }
  }
  fclose(fp);
  return numread;
}

void initializeGameBoard(char gameBoard[][50], int rows, int columns){
  int i;
  int j;
  //FILLING GAMEBOARD
  for(i = 0; i < rows; i++){
    for(j = 0; j < columns; j++){
      if(i == 0 || i == 18 || i == 19){
        gameBoard[i][j] = '_';
      }
      else if(j == 0 || j == 49){
        gameBoard[i][j] = '|';
      }
      else{
        gameBoard[i][j] = ' ';
      }
    }
  }
}

void printGameBoard(char gameBoard[][50], int rows, int columns, int difficulty){
  int i;
  int j;
  //PRINTING GAMEBOARD
  for(i = 0; i < rows; i++){
    for(j = 0; j < columns; j++){
      printf("%c", gameBoard[i][j]);
    }
    printf("\n");
   }
   for (int i=0; i<difficulty;i++){
    printf("*");
  }
  printf("\n");
}

void addWord(char GB[][50], char word[], wordInfo currWords[], int* currWordCnt){
  int length = strlen(word);
  int startIndex = (rand() % (50 - length - 3)) + 1;    // -3 and +1 accounting for walls
  for(int i = 0; i < length; i++){
    GB[1][startIndex + i] = word[i];  //row starts at one because of gameboard upper boundary
  }
  strcpy(currWords[*currWordCnt].word, word);
  currWords[*currWordCnt].length = length;
  currWords[*currWordCnt].startCol = startIndex;
  currWords[*currWordCnt].row = 1;    //row starts at one because of gameboard upper boundary
  *(currWordCnt) += 1;
}

void shiftDown(char GB[][50], wordInfo currWords[], int currWordCnt){
  int i;
  int j;
  for(i = 0; i < currWordCnt; i++){
    for(j = 0; j < currWords[i].length; j++){
      GB[currWords[i].row + 1][currWords[i].startCol + j] = GB[currWords[i].row][currWords[i].startCol + j];
      GB[currWords[i].row][currWords[i].startCol + j] = ' ';
    }
    currWords[i].row++;
  }
}

void removeWord(char GB[][50], wordInfo currWords[], char wordToRemove[], int* currWordCnt){
  //Check if word exists in list
  for(int i = 0; i < *currWordCnt; i++){
    if(strcmp(currWords[i].word, wordToRemove) == 0){
      wordInfo temp = currWords[i];
      //Deleting word from game board
      for(int j = 0; j < temp.length; j++){
        GB[temp.row][temp.startCol + j] = ' ';
      }
      //Removing wordInfo from list of words on screen
      while(i < *currWordCnt - 1){
        currWords[i] = currWords[i + 1];
        i++;
      }
      //currWords[*currWordCnt - 1] = NULL;
      *(currWordCnt) -= 1;
      return;
    }
  }
  //Hit if word to remove is not on screen
  return;
}

char* generateWord(char fileName[], int minLength){
  FILE* fp;
  fp = fopen(fileName, "r");
  int wordCount = getFileWordcount(fileName);
  int randNum = rand() % wordCount;
  char* word = malloc(20 * sizeof(char)); 
  fscanf(fp, "%s", word);
  for(int i = 0; i < randNum; i++){
    fscanf(fp, "%s", word);
  }
  while (strlen(word) < minLength){
    fscanf(fp, "%s", word);
    if (feof(fp)){
      fseek(fp, 0, SEEK_SET);
    }
  }
  return word;
}

int endGame(wordInfo currWords[], int currWordCnt){
  int gameOver = 0;
  for(int i = 0; i < currWordCnt; i++){
    if(currWords[i].row == 18){
      gameOver = 1;
    }
  }
  return gameOver;
}

/**
 * returns clock time in centiseconds
 */
int getCSeconds(struct timeval clock){
  int sec = clock.tv_sec;
  int uSec = clock.tv_usec;
  int cSec = (uSec/10000) + ((sec%10000)*100); //1 centisecond is 10000 useconds and 1 second is 100 centiseconds
  return cSec;
}

/**
*returns the difference between 2 clock times (clock 1 - clock 2)
*/
int getDifference(struct timeval clock1, struct timeval clock2){
  return getCSeconds(clock1) - getCSeconds(clock2);
}
