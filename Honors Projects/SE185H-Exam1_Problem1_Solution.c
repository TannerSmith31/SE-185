#include <stdio.h>	//This library is needed to use the printf() and scanf() functions

/*Program to get a list of up to 10 integers from the user.
 *Stops taking input early if the user enters a 0.
 *First prints off those numbers in the order they were entered
 *Then it sorts the numbers in acending order and prints them again
 */
void main(void){
	int numberList[10];					//integer array variable of length 10 to store the numbers that the user inputs.
	int curNum; 						//variable to store curent user input integer
	int numElements = 0;				//index variable for storing numbers into numberList
	printf("Enter up to 10 integers to sort. To quit early, enter 0.\n");
	while (numElements < 10){			//won't enter if the user has entered more than 10 integers
		printf("Enter a number: ");
		scanf("%d", &curNum);			//%d format specifier for INTEGERS. dont forget the "&".
		if (curNum == 0)
			break;						//breaks out of the while loop once a zero is entered and the break statment is hit
		numberList[numElements] = curNum;
		numElements++;					//DO NOT FORGET THIS! If you forget to increment your counter variable, it will cause this loop to execute infinitely
	}
	
	//PRINT NUMBERS IN ORDER THEY WERE INPUT
	int index;
	printf("Entered Numbers: ");
	for (index = 0; index < numElements; index++){		//Loops through the array list of user numbers from element 0 up to element 9 (length - 1)
		printf("%d ", numberList[index]);				//each iteration of the for loop it will print out the value in the given index (index 0 up to index 9)
	}
	printf("\n");
	
	//SORT NUMBERS
	int i;				//loop index variable for the outer loop
	int j;				//loop index variable for the inner loop
	int temp; 			//variable to store array values when swapping
	int minValIndex;	//variable to store the minimum value for each pass of i
	for(i = 0; i < numElements - 1; i++){
		minValIndex = i;	//Assigns minValIndex with index i (begining of the loop)
		for(j = i + 1; j<numElements; j++){
			if(numberList[j] < numberList[minValIndex]){	//checking to see if the number at the index "j" is less than the element at index "minValIndex"
				minValIndex = j;							//If it is, changes the minValIndex to index j
			}
		}
		//The following 3 lines are how you correctly "swap" values
		temp = numberList[i];
		numberList[i] = numberList[minValIndex];
		numberList[minValIndex] = temp;
	}
	
	//PRINT SORTED NUMBERS
	printf("Numbers Sorted: ");
	for (index = 0; index < numElements; index++){
		printf("%d ", numberList[index]);
	}
}