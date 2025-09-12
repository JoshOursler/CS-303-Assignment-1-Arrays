#pragma once

#include <iostream>		// required for input and output
#include <fstream>		// required for file stream classes
#include <string>		// required for string class
#include <limits>		// required for numeric limits
#include <stdexcept>	// required for exception handling
#include <cstddef>		// required for size_t

namespace HW1 {

	template<typename item_type>
	class arrays {
	private:
		// Declare array attribbutes
		// Declare the initial size of the array
		static const size_t initialSize = 10;
		// Declare the current maximum size of the array
		size_t currentMaxSize = initialSize;
		// Declare the current number of items in the array
		size_t numItems = 0;
		// Declare the array to contain the data
		item_type* data;

		// Configure cin to throw exceptions on input failure
		inline void configure_cin_exceptions() {
			std::cin.exceptions(std::ios_base::failbit);
		}

	public:
		// Member functions
		// Create an empty array with the template item_type
		arrays<item_type>() : currentMaxSize(initialSize), data(new item_type[initialSize]), numItems(0) {};

		// Change a value at a given index in the array
		item_type& operator[](const size_t index) {
			// Check if the index is valid
			if (index >= numItems) {
				throw std::out_of_range("Index out of bounds");
			}
			return data[index];
		}

		// Reference to an item in the array at a given index
		const item_type& operator[](const size_t index) const {
			// Check if the index is valid
			if (index >= numItems) {
				throw std::out_of_range("Index out of bounds");
			}
			return data[index];
		}

		// Create space in the array to add more items
		void create_space(const size_t newSize) {
			// Ensure the new space is double the old space
			if (newSize > currentMaxSize) {
				if (newSize > 2 * currentMaxSize) {
					currentMaxSize = newSize;
				} else {
					// Double the capacity of the array
					currentMaxSize *= 2;
				}
			}

			// Create a new array with the new size
			item_type* newData = new item_type[currentMaxSize];

			// Copy the contents of the old array to the new array
			for (size_t i = 0; i < numItems; i++) {
				newData[i] = data[i];
			}

			// Delete the old array
			delete[] data;

			// Put the new array in place of the old array
			data = newData;
		}

		// Add a number to the end of an array
		void addValue(const item_type value) {
			// Check if there is enough space in the array
			if (numItems == currentMaxSize) {
				// Allocate size for the new items
				create_space(2 * currentMaxSize);
			}

			// Add the new number to the end of the array
			data[numItems] = value;
			numItems++; // Increment the number of items in the array
		}

		// Check the the array for a value and return its index
		size_t checkValue(const item_type value) {
			// Declare a variable to hold the index of the number
			size_t index = numItems;

			// Loop through the array to find the value
			for (size_t i = 0; i < numItems; i++) {
				if (data[i] == value) {
					index = i;	// Return the index of the number if found
				}
			}
			
			// Check if item was found
			if (index == numItems) {
				throw std::out_of_range("Value not found in array");
			}
			return index; // Return the index of the value
		}

		// Modify a value in the array to a new value with user inputs
		void user_modifyValue() {
			// Declare a variable to hold the old value
			item_type oldValue;
			// Declare a variable to hold the new value
			item_type newValue;
			// Declare a variable to hold the index of the old value
			size_t index;

			configure_cin_exceptions(); // Configure cin to throw exceptions on input failure

			// Try catch block to ensure user input is valid for old value
			while (true) {
				try {
					// Get user input for value to modify
					std::cout << "\nEnter the item you wish to modify: ";
					std::cin >> oldValue;

					// If input is valid, break out of loop
					break;
				}
				catch (std::ios_base::failure& e) {
					// return error if input is invalid
					std::cerr << "Error: Invalid input. Please enter a valid item." << std::endl;

					// Clear the user input
					std::cin.clear();

					// Discard invalid user input
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
			}
			
			// Try and Catch block to find the index of the old value
			try {
				index = checkValue(oldValue);
			}
			catch (std::out_of_range& e) {
				// Return error if value is not found
				std::cerr << "Error: " << e.what() << std::endl;
				index = numItems; // Set index to an invalid value
			}

			// Try catch block to ensure user input is valid for new value
			while (true) {
				try {
					// Get user input for value to modify
					std::cout << "\nEnter the new value for item you wish to modify: ";
					std::cin >> newValue;

					// If input is valid, break out of loop
					break;
				}
				catch (std::ios_base::failure& e) {
					// return error if input is invalid
					std::cerr << "Error: Invalid input. Please enter a valid item." << std::endl;

					// Clear the user input
					std::cin.clear();

					// Discard invalid user input
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
			}

			// Modify the number at the given index to the new number
			data[index] = newValue;

			// Confirm the change to the user
			std::cout << "\nItem " << oldValue << " has been changed to " << newValue << "." << std::endl;
		}

		// Remove a value at a given index from the array
		void removeValue(const size_t index) {
			// Check if the index is valid
			if (index >= numItems) {
				throw std::out_of_range("Index out of bounds");
			}
			// Shift all numbers after the index to the left
			for (size_t i = index; i < numItems - 1; i++) {
				data[i] = data[i + 1];
			}
			// Reduce the number of items in the array
			numItems--;
		}

		// Prints the array to the console
		void printArray() {
			for (size_t i = 0; i < numItems; i++) {
				std::cout << data[i] << " ";
			}
		}

		// Allows user to input values at the end of the array
		void user_addValue() {
			// Declare a variable to hold the new value
			item_type newValue;

			configure_cin_exceptions(); // Configure cin to throw exceptions on input failure

			// Try catch block to ensure user input is valid for new value
			while (true) {
				try {
					// Get user input for value to modify
					std::cout << "\nEnter the value for item you wish to add: ";
					std::cin >> newValue;

					// If input is valid, break out of loop
					break;
				}
				catch (std::ios_base::failure& e) {
					// return error if input is invalid
					std::cerr << "Error: Invalid input. Please enter a valid item." << std::endl;

					// Clear the user input
					std::cin.clear();

					// Discard invalid user input
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
			}

			// Add the new value to the end of the array
			addValue(newValue);
		}

		// Read data from file into array
		void readDataFromFile(const std::string filename) {
			// Open the file
			std::ifstream inputFile;
			inputFile.open(filename.c_str());

			// Declare variable to hold values from read file
			item_type tempValue;

			if (inputFile.is_open()) {	// read data if file is open
				while (inputFile >> tempValue) { // add values to the end of the array until end of file
					addValue(tempValue);
				}
				inputFile.close();	// close file
			}
			else {
				std::cerr << "Error: Could not open file " << filename << std::endl;	// return error if file cannot be opened
			}
		}
	};
};