/*-----------------------------------------------------------------------------
-					  		SE 185 Lab 08
-             Developed for 185-Rursch by T.Tran and K.Wang
-	Name: Tanner Smith
-   Section: 7
-	NetID:trs3103
-	Date: 10/30/22
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
-								Includes
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#include <ncurses/ncurses.h>
#include <unistd.h>
#include <stdlib.h>


/*-----------------------------------------------------------------------------
-								Defines
-----------------------------------------------------------------------------*/
/* Mathmatical constants */
#define PI 3.14159
#define MAXPOINTS 10000
/* 	Screen geometry
    Use ROWS and COLUMNS for the screen height and width (set by system)
    MAXIMUMS */
#define COLUMNS 100
#define ROWS 80

/* 	Character definitions taken from the ASCII table */
#define AVATAR 'A'
#define WALL '*'
#define EMPTY_SPACE ' '

/*	Number of samples taken to form an moving average for the gyroscope data
    Feel free to tweak this. */
#define NUM_SAMPLES 10


/*-----------------------------------------------------------------------------
-								Static Data
-----------------------------------------------------------------------------*/
/* 2D character array which the maze is mapped into */
// to compile:  gcc -o lab8_2 lab8_2.c -lncurses
// to run: ./ds4rd-real.exe -d 054c:05c4 -D DS4_USB -t -g | ./lab8_2 5
char MAZE[COLUMNS][ROWS];

 
/*-----------------------------------------------------------------------------
-								Prototypes
-----------------------------------------------------------------------------*/
/*	POST: Generates a random maze structure into MAZE[][]
    You will want to use the rand() function and maybe use the output %100.
    You will have to use the argument to the command line to determine how
    difficult the maze is (how many maze characters are on the screen). */
void generate_maze(int difficulty);

/*	PRE: MAZE[][] has been initialized by generate_maze()
    POST: Draws the maze to the screen */
void draw_maze(void);

/*	PRE: 0 < x < COLUMNS, 0 < y < ROWS, 0 < use < 255
    POST: Draws character use to the screen and position x,y */
void draw_character(int x, int y, char use);

/*	PRE: -1.0 < mag < 1.0
    POST: Returns tilt magnitude scaled to -1.0 -> 1.0
    You may want to reuse the roll function written in previous labs. */
double calc_roll(double mag);

/* 	Updates the buffer with the new_item and returns the computed
    moving average of the updated buffer */
double m_avg(double buffer[], int avg_size, double new_item);


/*-----------------------------------------------------------------------------
-								Implementation
-----------------------------------------------------------------------------*/
/*	Main - Run with ./ds4rd.exe -t -g -b (piped into STDIN) */
//REMOVE B
void main(int argc, char* argv[])
{
	int time;
	int difficulty;
	double gx, gy, gz;
	double gx_avg;
	double x[MAXPOINTS];
	int loc_x = 50;
	int loc_y = 0;
	int win = 1;
	

  if (argc != 2 )
  {
      printw("You must enter the difficulty level on the command line.");
      refresh();
      return;
  }
  else
  {
    /* 	Setup screen for Ncurses
        The initscr functionis used to setup the Ncurses environment
        The refreash function needs to be called to refresh the outputs
        to the screen */
    initscr();
    refresh();

    /* WEEK 2 Generate the Maze */
	sscanf(argv[1], "%d", &difficulty );
	generate_maze(difficulty);
	
    /* Read gyroscope data and fill the buffer before continuing */
	draw_maze();
	draw_character(loc_x, loc_y, AVATAR);
	
	scanf("%d, %lf, %lf, %lf", &time, &gx, &gy, &gz);
	int timer1 = time;
	int timer2 = time;
	
    /* Event loop */
    do
    {
		if (time > timer2 + 30){	//ENTERS EVERY 50ms (horizontal movement)
			timer2 = time;
			
			if (gx_avg < 0 && loc_x >0 && MAZE[loc_x -1][loc_y] != 1){
				draw_character(loc_x, loc_y, EMPTY_SPACE);
				loc_x -= 1;
				draw_character(loc_x, loc_y, AVATAR);
			}
			else if (gx_avg > 0 && loc_x < 99 && MAZE[loc_x + 1][loc_y] != 1){
				draw_character(loc_x, loc_y, EMPTY_SPACE);
				loc_x += 1;
				draw_character(loc_x, loc_y, AVATAR);
			}
		}
		
		if (time > timer1 + 200){	//ENTERS EVERY 500ms (vertical movement)
			timer1 = time;
		
			if (MAZE[loc_x][loc_y + 1] != 1){
				draw_character(loc_x, loc_y, EMPTY_SPACE);
				loc_y++;
				draw_character(loc_x, loc_y, AVATAR);
			}
			
			//check for doomage
			if (MAZE[loc_x][loc_y + 1] == 1){
				int doomedLeft = 0;
				int doomedRight = 0;
				
				//count blocks low right
				int numRight = 0;
				int i = 1;
				while(MAZE[loc_x + i][loc_y + 1] == 1){
					numRight++;
					i++;
					if (loc_x + i == COLUMNS + 1){
						break;
					}
				}
				
				//count blocks low left
				int numLeft = 0;
				i = 1;
				while(MAZE[loc_x - i][loc_y + 1] == 1){
					numLeft++;
					i--;
					if (loc_x - i == -1){
						break;
					}
				}
				
				//count blocks even right
				for(i=1; i <= numRight + 1; i++){
					if(MAZE[loc_x + i][loc_y] == 1 || (loc_x + i) == COLUMNS){
						doomedRight = 1;
					}
				}
				
				//blocks even left
				
				for(i=1; i <= numLeft + 1; i++){
					if(MAZE[loc_x - i][loc_y] == 1 || (loc_x - i) == 0){
						doomedLeft = 1;
					}
				}
				
				if (doomedRight == 1 && doomedLeft == 1 ){
					win = 2; //means you are doomed
				}
			}
			
			
		}
		gx_avg = calc_roll(m_avg(x, 2, gx));
		scanf("%d, %lf, %lf, %lf", &time, &gx, &gy, &gz);
			
		if ((loc_x == 0 || MAZE[loc_x - 1][loc_y] == 1) && (loc_x == 99 || MAZE[loc_x + 1][loc_y] == 1) && MAZE[loc_x][loc_y + 1] == 1){
			win = 0;
			break;
		}
		if (win == 2){
			break;
		}
     
    } while(loc_y <= 80); // Change this to end game at right time

    /* Print the win message */


    /* This function is used to cleanup the Ncurses environment.
    Without it, the characters printed to the screen will persist
    even after the progam terminates */
    endwin();

  }
	if (win == 1){
		printf("YOU WIN!\n");
	} else if (win == 0){
		printf("YOU SUCK!\n");
	} else if (win == 2){
		printf("You were doomed");
	}
}

double m_avg(double buffer[], int avg_size, double new_item)
{
	double sum = 0.0;
	int i;
	int j;
    for(i = 0; i < avg_size - 1; i++ ){
		buffer[i] = buffer[i+1];
	}
	buffer[avg_size - 1] = new_item;
	
	for(j = 0; j < avg_size; j++ ){
		sum += buffer[j];
	}
	
	return sum / avg_size;
}


/* 	PRE: 0 < x < COLUMNS, 0 < y < ROWS, 0 < use < 255
    POST: Draws character use to the screen and position x,y
    THIS CODE FUNCTIONS FOR PLACING THE AVATAR AS PROVIDED.
    DO NOT NEED TO CHANGE THIS FUNCTION. */
void draw_character(int x, int y, char use)
{
    mvaddch(y,x,use);
    refresh();
}

double calc_roll(double mag){
	if(mag < -.2){
		return 1;
	}
	else if(mag > .2){
		return -1;
	}
	else{
		return 0;
	}
	
}
void draw_maze(void){
	for(int i=0; i<COLUMNS; i++){
		for(int j=0; j<ROWS; j++){
			if (MAZE[i][j] == 1){
				draw_character(i,j,WALL);
			}
		}
	}
}
	
void generate_maze(int difficulty){
	for(int i=0; i<COLUMNS; i++){
		for(int j=0; j<ROWS; j++){
			int randomNum = rand() % 100;
			if(randomNum < difficulty){
				MAZE[i][j] = 1;	//1 = wall, 0 = space
			}
		}
	}
}
