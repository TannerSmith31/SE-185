#include <math.h>		//This library is needed to use the pow() function, as well as to use the M_PI constant variable
#include <stdio.h>		//This library is needed to use the printf() and scanf() functions

/* Write a program that takes 2 coordinates of the form (x,y) from the user
 * and outputs the area of a circle whose diameter is the distance between
 * the 2 points. Also ask the user for a 3rd point and print out whether that
 * point is inside the circle.
 */
 
 //PROTOTYPES. If you forget to add these here, you will get a compile error. user defined functions have to have prototypes declared before Main.
 double calcRadius(double userPoints[3][2]);			//returns the radius of the circle given the 2 user points
 double calcArea(double radius);						//returns the Area of the circle given the radius
 double* circleMidpoint(double userPoints[3][2]);		//returns the coordinates of the midpoint of the circle. Needs the "*" because C functions CANNOT return arrays. Only pointers to arrays.
 int isInCircle(double midpoint[2], double radius, double otherPoint[2]);	//returns true if "otherPoint" is on or within the circle. Else, if "otherPoint" is outside the circle, returns false.
 
void main(void){
	
	double userPoints[3][2]; 	//2D Array to hold the 3 points given by the user
	double radius;				//variable to store the radius of the circle.
	double area;				//varible to store the area of the circle
	double midpoint[2];			//coords of the midpoint of the circle
	
	printf("Enter the X and Y values of point 1 seperated by a space: "); 
	scanf("%lf %lf", &userPoints[0][0], &userPoints[0][1]);				//assigns X1 and Y1. %lf specifier is for DOUBLE varaibles (aka "ong float")
	printf("Enter the X and Y values of point 2 seperated by a space: "); 
	scanf("%lf %lf", &userPoints[1][0], &userPoints[1][1]);				//assigns X2 and Y2
	
	//CALCULATING MIDPOINT AND RADIUS
	radius = calcRadius(userPoints);
	for (int i=0; i<2; i++){ 					//I have to go through each element of midpoint individualy and add them because functions are unnable to return multiple variables
		midpoint[i] = circleMidpoint(userPoints)[i];
	}
	
	//CALCULATING & DISPLAYING AREA
	area = calcArea(radius);
	printf("The Area of your circle is %.3lf units\n", area);	//the ".3" in "%.3lf" rounds what gets printed to the screen to 3 decimal places
	
	//TAKING 3RD POINT FROM USER
	printf("Enter the X and Y values of a 3rd point seperated by a space: ");	
	scanf("%lf %lf", &userPoints[2][0], &userPoints[2][1]);			//stores X3 and Y3
	
	//PRINTING WHERE THE 3RD POINT IS IN RELATION TO THE CIRCLE
	if (isInCircle(midpoint, radius, userPoints[2])){				//if isInCircle returns 1 (true) then we tell the user it is in or on the circle
		printf("Point 3 is ON/INSIDE the circle");
	}else{
		printf("Point 3 is OUTSIDE the circle");
	}
}



double calcRadius(double points[3][2]){
	double distance = sqrt( pow(points[0][0] - points[1][0], 2) + pow(points[0][1] - points[1][1], 2) ); //Using the distance formula to compute distance between 2 points
	return distance / 2;	//because distance is a double, this will do double division
}

double calcArea(double radius){
	return M_PI * pow(radius, 2);		//formula for the area of a circle is PI * (radius)^2
}

int isInCircle(double midpoint[2], double radius, double otherPoint[2]){
	double distance = sqrt( pow(midpoint[0] - otherPoint[0], 2) + pow(midpoint[1] - otherPoint[1], 2) );	//distance from midpoint to 3rd point
	if (distance <= radius){
		return 1;	//returning "true" when point is inside or on the circle MAKE NOT OF WHY I DIDN'T HAVE A SEPERATE BRANCH FOR ON THE CIRCLE (use "==" on double type is frowned upon)
	}else{
		return 0;	//returning "false" otherwise
	}
}

double* circleMidpoint(double points[3][2]){
	static double midPoint[2];							//This has to be declared as static so that it can be used in the return statement.
	midPoint[0] = (points[0][0] + points[1][0])/2.0;	//finding the x value of the midpoint using the equation (X1 + X2)/2
	midPoint[1] = (points[0][1] + points[1][1])/2.0;	//finding the y value of the midpoint using the equation (Y1 + Y2)/2
	return midPoint;									//returns the midpoint as a 2D array that is of the form [xVal, yVal]
}