//: Utilities.h
/*
Title:        Utilities.h
Description:  This header file declares/ implements various utility functions used throughout
				the game, including error handling, file checking, and
				string manipulation.
Date:         December 17, 2024
Author:       Halie Favron
Student ID:   3673820
Version:      1.0
Copyright:    2024 Halie Favron
*/

/*
DOCUMENTATION

Program Purpose:
	- Contains helper functions used by multiple files in the project

Compile (assuming g++ is installed):
	g++ -o main Actions.cpp Alice.cpp Characters.cpp Control.cpp FileReader.cpp Game.cpp GameObject.cpp Items.cpp Locations.cpp main.cpp Utilities.cpp
Execution (assuming your terminal is Windows Command Prompt):
	main.exe

Compile Note:
	Ensure all files are being properly compiled or errors will occur
*/

#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <cctype>
#include <sstream>
#include <string>
#include <fstream>

/*******************************************************************************************************************************************************************************************
* Free Utility Functions
*******************************************************************************************************************************************************************************************/

// Searches a vector for a specified object, by its name
// Returns the index of the vector if found, if not returns -1
template <typename T>
int searchVectorOfGameObject(const std::vector<T>& vector, const T& obj)
{
	for (int i = 0; i < vector.size(); i++) // Iterates over vector
	{
		// Compares the name of the two objects
		if (obj.getName() == vector[i].getName())
		{
			return i; // If found return the index
		}
	}
	return -1; // Return -1 if object is not found
}

// Searches a vector of pointers for a specified object, by its name
// Returns the index of the vector if found, if not returns -1
template <typename T>
int searchVectorOfGameObject(const std::vector<T*>& vector, const T& obj)
{
	for (int i = 0; i < vector.size(); i++) // Iterates over vector
	{
		// Compares the name of the two objects
		if (obj.getName() == vector[i]->getName())
		{
			return i; // If found return the index
		}
	}
	return -1; // Return -1 if object is not found
}

// Checks for critical errors and terminates the program if an error condition is met
void criticalError(std::string errorMessage, bool errorCondition);

// Overloads the critical error function and terminates the program
void criticalError(std::string errorMessage);

// Checks that the file was opened properly and terminates the program if it was not
void checkFileError(std::ifstream& inputFile, const std::string& fileName);

// Transforms a string to lowercase 
std::string toLower(std::string str);

// Converts a string to a Boolean value
bool stringToBool(std::string str);
