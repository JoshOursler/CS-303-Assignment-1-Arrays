// CS 303 Assignemt 1 Arrays.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "arrays.h"		// include the arrays class header file

int main() {
	HW1::arrays<int> intArray;			// Create an integer array object

	intArray.readDataFromFile("A1input.txt"); // Read data from file into the array
	
	intArray.printArray();				// Print the array to the console

	intArray[0] = 42;
	int tempNum = intArray[0]; // Change the first item in the array to 42 and store it in a variable

	std::cout << "\nThe first item in the array is now: " << tempNum << std::endl; // Print the new first item in the array

	intArray.user_addValue(); // Allow the user to add a value to the end of the array

	intArray.printArray(); // Print the array to the console
	
	intArray.user_modifyValue(); // Allow the user to modify a value in the array

	intArray.printArray(); // Print the array to the console
	
	intArray.removeValue(0); // Remove the first item in the array

	std::cout << std::endl;

	intArray.printArray(); // Print the array to the console
	
	return 0;

}