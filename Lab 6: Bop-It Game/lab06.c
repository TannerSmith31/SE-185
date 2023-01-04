/*----------------------------------------------------------------------------
-		                    SE 185: Lab 06 - Bop-It!	    	             -
-	Name: Tanner Smith														 -
- 	Section: 7																 -
-	NetID:	trs3103														     -
-	Date: 10/13/22															 -
-----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
-								Includes									 -
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*----------------------------------------------------------------------------
-	                            Prototypes                                   -
-----------------------------------------------------------------------------*/
int randButton();
int currentButton(int triangle, int circle, int x_button, int square);

/*----------------------------------------------------------------------------
-	                            Notes                                        -
-----------------------------------------------------------------------------*/
// Compile with gcc lab06.c -o lab06
// Run with ./ds4rd.exe -d 054c:05c4 -D DS4_BT -t -b | ./lab06

/*----------------------------------------------------------------------------
-								Implementation								 -
-----------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
	int triangle, circle, x_button, square;
	int correctButton;
	int currButton= 0;
	double currentTime;
	int gameOver = 0;
	int quit = 0;
	int numCorrect = 0;
	srand(time(NULL)); /* This will ensure a random game each time. */
	
	
	printf("Press Triangle to start. Press X to quit\n\n");
	fflush(stdout);
	while(!gameOver){
		scanf("%lf, %d, %d, %d, %d", &currentTime, &triangle, &circle, &x_button, &square);
		currButton = currentButton(triangle, circle, x_button, square);
		
		
		if (triangle){ //start game
			int timeLimit = 2500;	//initializing a time limit
			double startTime = currentTime;
			int roundResult = 0;	//tells how the round ended (0 = ran out of time, 1 = pressed wrong button, 2 = pressed correct button)
			while(!gameOver){
				correctButton = randButton();
				printf("\nYou have %d milliseconds to respond!\n\n\n", timeLimit);
				startTime = currentTime;
				fflush(stdout);
				roundResult = 0;	//reseting round result
				
				//RESET BUTTON
				while (currButton != 0){
					scanf("%lf, %d, %d, %d, %d", &currentTime, &triangle, &circle, &x_button, &square);
					currButton = currentButton(triangle, circle, x_button, square);
				}
				
				while(currentTime - startTime <= timeLimit){
					scanf("%lf, %d, %d, %d, %d", &currentTime, &triangle, &circle, &x_button, &square);
					currButton = currentButton(triangle, circle, x_button, square);
					if (currButton == correctButton){
						timeLimit-= 100;
						roundResult = 2;
						numCorrect++;
						break;
					}
					if (currButton != correctButton && currButton != 0){
						roundResult = 1;
						break;
					}
				}
				
				if (roundResult == 0){
					printf("\nYou ran out of time");
					fflush(stdout);
					gameOver = 1;
				}
				else if (roundResult == 1){
					printf("\nWrong Button");
					fflush(stdout);
					gameOver = 1;
				}
			}
		
		}else if (x_button){
			gameOver = 1;
		}
		
	}
	printf("\nYou made it through %d rounds!", numCorrect);
    return 0;
}

/* Put your functions here, and be sure to put prototypes above. */
int randButton(){
	int randomNum = rand() % 4 + 1;
	if (randomNum == 1){
		printf("\nTRIANGLE!");
		fflush(stdout);
		return 1;
		
	}else if (randomNum == 2){
		printf("\nCIRCLE!");
		fflush(stdout);
		return 2;
		
	}else if (randomNum == 3){
		printf("\nX!!");
		fflush(stdout);
		return 3;
	
	}else{
		printf("\nSQUARE!");
		fflush(stdout);
		return 4;
	}
}

int currentButton(int triangle, int circle, int x_button, int square){
	double currentTime;
	
	while (1){
		if (triangle){
			return 1;
		}else if (circle){
			return 2;
		}else if (x_button){
			return 3;
		}else if (square){
			return 4;
		}else {
			return 0;
		}
	}

}
