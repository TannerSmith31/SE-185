/*----------------------------------------------------------------------------
-          SE 185: Midterm Project                   -
- List the names of all team members, their roles, and their participation
    1- Student 1 - Andrew Meder 
      Role: Quiz Creator, program creater, and debugger
      Participation: 50%
    2- Student 2 - Tanner Smith
      Role: Quiz Creator, program creater, and debugger
      Participation: 50%
NOTE: we worked together on the project and kinda just talked through it together
-----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
                                Includes 
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*----------------------------------------------------------------------------
-                             Functions Prototypes                         -
-----------------------------------------------------------------------------*/
int quiz1(); //returns score
int quiz2();
int quiz3();

/*----------------------------------------------------------------------------
-                                 Notes                                    -
-----------------------------------------------------------------------------*/
// Compile with gcc midtermProject.c -o proj

/*----------------------------------------------------------------------------
                            - Implementation-
-----------------------------------------------------------------------------*/
int main()
{
  int luckyNum;
  int randomNum;
  int curScore;
  int totalScore = 0;
  int overallScore = 0;
  int quizCount = 0;
  int overallQuizCount = 0;
  char playerChoice;
  double average;
  double overallAverage;
  //Ask player to play
  printf("Welcome! here is a list of possible quizes\n Quiz 1\n Quiz 2\n Quiz 3\n");
  printf("Do you want to take a quiz (y/n)? ");
  scanf("%c", &playerChoice);
  while(playerChoice != 'n' && playerChoice != 'N'){
    //Ask user to enter a number and use this number as a seed for a random
    printf("\nEnter a lucky number between 1 and 9: ");
    scanf("%d", &luckyNum);
    srand(luckyNum - 6);
    randomNum = rand() % 3;
    //determine which quiz to use
    switch(randomNum){
      case 0:
        curScore = 0;
        while (curScore != 15){
          curScore = quiz1();
          if (curScore < 15){
            printf("\nQUIZ FAILED: Try Again until you get 100%%\n\n");
          }
          totalScore += curScore;
          quizCount++;
        }
        break;
      case 1:
        curScore = 0;
        while (curScore != 15){
          curScore = quiz2();
          if (curScore < 15){
            printf("\nQUIZ FAILED: Try Again until you get 100%%\n\n");
          }
          totalScore += curScore;
          quizCount++;
        }
        break;
      case 2:
        curScore = 0;
        while (curScore != 15){
          curScore = quiz3();
          if (curScore < 15){
            printf("\nQUIZ FAILED: Try Again until you get 100%%\n\n");
          }
          totalScore += curScore;
          quizCount++;
        }
        break;
      default:
        printf("ERROR");
        break;
    }
    average = ((double)totalScore / (double)(quizCount * 15)) * 100;
    printf("Average Score: %.3lf%%\n\n", average);
    overallScore += totalScore;
    overallQuizCount += quizCount;
    printf("Do you want to take another quiz (y/n)? ");
    scanf(" %c", &playerChoice);
    totalScore = 0;
    quizCount = 0;
  }
  //Extra credit
  if (overallQuizCount == 0){
    printf("\nOverall Average Score: N/A (You haven't taken any quizes yet)");
  }else{
    overallAverage = ((double)overallScore / (double)(overallQuizCount * 15))*100;
    printf("\nOverall Average Score: %.3lf%%", overallAverage);
  }
  return 0;
}
        
/* Put your functions here, and be sure to put prototypes above. */

int quiz1(){
  char answer1;
  char answer2 ;
  char answer3[15];
  int score = 0;
  
  //Question 1
  printf("(T/F) The format specifier for integer is \"%%d\": ");
  scanf(" %c", &answer1);
  if (answer1 == 'T' || answer1 == 't'){
    printf("CORRECT\n");
    score += 5;
  } else {
    printf("INCORRECT\n");
  }
  printf("\n");
  
  //Question 2
  printf("Multiple Choice: What is the Answer to the following equation: 3 + 5 %% 2 * 2?\n");
  printf("A. 0\n");
  printf("B. 1\n");
  printf("C. 5\n");
  printf("D. 4\n");
  printf("Enter answer here: ");
  scanf(" %c", &answer2);
  if (answer2 == 'c' || answer2 == 'C'){
    printf("CORRECT\n");
    score += 5;
  } else {
    printf("INCORRECT\n");
  }
  printf("\n");
  
  //Question 3
  printf("Fill in the Blank: the _______ function takes input from a user and stores it in a variable\n");
  printf("Enter answer (<15 characters): ");
  scanf("%s", answer3);
  if (strcmp(answer3, "scanf()") == 0){
    printf("CORRECT\n");
    score += 5;
  } else {
    printf("INCORRECT\n");
  }
  printf("\n");
  return score;
}


int quiz2(){
  char answer1;
  char answer2;
  char answer3[15];
  int score = 0;
  
  //Question 1
  printf("(T/F) srand(5) creates a random number between 0 and 5: ");
  scanf(" %c", &answer1);
  if (answer1 == 'F' || answer1 == 'f'){
    printf("CORRECT\n");
    score += 5;
  } else {
    printf("INCORRECT\n");
  }
  printf("\n");
  
  //Question 2
  printf("Multiple Choice: How would you generate a random number from 2 to 7?\n");
  printf("A. rand(2,7)\n");
  printf("B. rand() %% 5 + 2\n");
  printf("C. rand() %% 7 + 2\n");
  printf("D. srand(7)\n");
  printf("Enter answer here: ");
  scanf(" %c", &answer2);
  if (answer2 == 'b' || answer2 == 'B'){
    printf("CORRECT\n");
    score += 5;
  } else {
    printf("INCORRECT\n");
  }
  printf("\n");
  
  //Question 3
  printf("Fill in the Blank: the __________ is the powerhouse of the cell\n");
  printf("Enter answer (<15 characters): ");
  scanf(" %s", answer3);
  if (strcmp(answer3, "mitochondria") == 0){
    printf("CORRECT\n");
    score += 5;
  } else {
    printf("INCORRECT\n");
  }
  return score;
}


int quiz3(){
  char answer1;
  char answer2;
  char answer3[15];
  int score = 0;
  //Question 1
  printf("(T/F) A dodecahedron has 12 sides: ");
  scanf(" %c", &answer1);
  if (answer1 == 'T' || answer1 == 't'){
    printf("CORRECT\n");
    score += 5;
  } else {
    printf("INCORRECT\n");
  }
  printf("\n");
  
  //Question 2
  printf("Multiple Choice: How many bells are in the campanile?\n");
  printf("A. 25\n");
  printf("B. 60\n");
  printf("C. 30\n");
  printf("D. 50\n");
  printf("Enter answer here: ");
  scanf(" %c", &answer2);
  if (answer2 == 'd' || answer2 == 'D'){
    printf("CORRECT\n");
    score += 5;
  } else {
    printf("INCORRECT\n");
  }
  printf("\n");
  
  //Question 3
  printf("Fill in the Blank: _______ is the name of the ISU mascot\n");
  printf("Enter answer (<15 characters): ");
  scanf(" %s", answer3);
  if (strcmp(answer3, "cy") == 0 || strcmp(answer3, "Cy") == 0){
    printf("CORRECT\n");
    score += 5;
  } else {
    printf("INCORRECT\n");
  }
  return score;
}
