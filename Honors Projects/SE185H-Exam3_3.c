///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
*You have just obtained a degree in Software engineering and decide to become a conductor of a railway.
*create a program that uses a linked list to model a train where each of the train cars is a node.
*First the program will ask the user how many train cars will be entered
*Second it will ask the user for a train car weight as many times as there are train cars
*Next it prints out the original train configuration
*Then it sorts the cars so that the heaviest cars are at the front of the train
*Finally it prints of the train car weights in order after sorting
*
*NOTE: the head of your linked list will be a trainCar called "engine"
*/

/*node structure*/
struct trainCar{
	int weight;
	struct trainCar* next;	//this is the thing storing the next node
};					//note how if this wern't here you would have to type "struct" before you make nodes

void printTrain(struct trainCar* engine, int numCars);
void ChooChoo(struct trainCar* engine, int numCars);

void main(){
	//initialize the engine
	struct trainCar* engine = (struct trainCar*)malloc(sizeof(struct trainCar));
	engine->weight = -1;
	engine->next = NULL;
	
	int numCars;
	int carWeight;
	//asking for user input
	printf("Enter number of train cars: ");
	scanf("%d", &numCars);
	
	struct trainCar* curCar = engine;
	for (int i = 0; i < numCars; i++){
		printf("Enter a train car weight: ");
		scanf("%d", &carWeight);
		curCar->next = (struct trainCar*)malloc(sizeof(struct trainCar));	
		curCar->next->weight = carWeight;			//assigning the next car's weight
		curCar->next->next = NULL;					//assigning the next car of the next car to null
		curCar = curCar->next;						//shifting to the next car
	}
	
	//print the linked list Train unsorted
	printf("\nUNSORTED: ");
	printTrain(engine, numCars);
	ChooChoo(engine, numCars);
	
	//use count to do insertion sort
	struct trainCar* successorCar;
	struct trainCar* currentCar;
	struct trainCar* previousCar;
	for (int i=0;i<numCars;i++){
		previousCar = engine;				//making engine the "previous car" (need previous car for swapping
		currentCar = engine->next;			//starting at the first car in the row
		successorCar = currentCar->next;	//make a successor car to compare with current
		while (successorCar != NULL){							//while we still have nodes
			if (successorCar->weight > currentCar->weight){				//if the next nodes age is greater than the current nodes age
				//SWAP CARS
				currentCar->next = successorCar->next;
				successorCar->next = currentCar;
				previousCar->next = successorCar;
				
				//update positions correctly due to swapping
				previousCar = previousCar->next;
				successorCar = currentCar->next;
			}else{
				//update place in list so you don't get caught in infinite loop
				previousCar = previousCar->next;		//previous->next is the old "successor"
				currentCar = currentCar->next;			//currentCar->next is the car AFTER the old "successor"
				successorCar = successorCar->next;		//successorCar->next is the old "current"
			}
		}
	}
	
	//print the sorted linked list Train
	printf("\nSORTED: ");
	printTrain(engine, numCars);
	ChooChoo(engine, numCars);
} 


void printTrain(struct trainCar* engine, int numCars){
	struct trainCar* currentCar = engine->next; //MAYBE MAKE JUST ENGINE
	while (currentCar != NULL){
		printf("%d ", currentCar->weight);
		//update your place in the list
		currentCar = currentCar->next;	//if you don't do this you get caught in an infinite while loop
	}
}


//               .  * 
//             *     _
//            !_____| |  _____   _____
//           ( ENGINE |-| 313 |-| 404 |
//          /--O----O-' 'o---o' 'o---o'
void ChooChoo(struct trainCar* engine, int numCars){
	struct trainCar* curCar = engine->next;
	printf("\n\n");
	printf("     .  *\n");
	printf("   *     _\n");
	printf("  !_____| |");
	for (int i = 0; i<numCars; i++){
			  printf("  _____ ");
	}
	printf("\n");
	 printf(" ( ENGINE |");
	for (int i=0; i<numCars;i++){
		       printf("-| %3d |", curCar->weight);
			   curCar = curCar->next;
	}
	printf("\n");
	printf("/--O----O-'");
	for (int i=0; i<numCars;i++){
			   printf(" 'o---o'");
	}
	printf("\n");
}

//start curNode at head
//start counter at 0
//while curnode is not null
	//add 1 to counter
	//curnode = curnode.next
	

//start prevNode as head
//start currNode as head.next
//for i;i<counter;i++s

	//while (currNode != null){
		//if curNode is less than previous
			//swap
		//put the curNode into previous node
		//put curNode.next into curNode