//: Utilities.cpp
/*
Title:        Utilities.cpp
Description:  This source file provides various utility functions used throughout
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


#include "Utilities.h"
#include <algorithm>


// Checks for critical errors and terminates the program if an error condition is met
void criticalError(std::string errorMessage, bool errorCondition)
{
	if (errorCondition)
	{
		std::cerr << errorMessage << std::endl;
		exit(EXIT_FAILURE);  // Source: https://www.geeksforgeeks.org/exit-codes-in-c-c-with-examples/
	}
}

// Overloads the critical error function and terminates the program
void criticalError(std::string errorMessage)
{
	std::cerr << errorMessage << std::endl;
	exit(EXIT_FAILURE);  // Source: https://www.geeksforgeeks.org/exit-codes-in-c-c-with-examples/
}

// Checks that the file was opened properly and terminates the program if it was not
void checkFileError(std::ifstream& inputFile, const std::string& fileName)
{
	if (!inputFile)
	{
		std::string errorMessage = "The " + fileName + " file could not be opened, ending the game...";
		criticalError(errorMessage);
	}
}

// Transforms a string to lowercase 
std::string toLower(std::string str)
{
	std::transform(str.begin(), str.end(), str.begin(), ::tolower); // Source: https://www.geeksforgeeks.org/how-to-convert-std-string-to-lower-case-in-cpp/
	return str;
}

// Converts a string to a Boolean value
bool stringToBool(std::string str)
{
	std::string strLower = toLower(str); // Converts str to lowercase
	
	// Checks if string represents true
	if (strLower == "true" || strLower == "t" || strLower == "yes" || strLower == "y")
	{
		return true;
	}
	// Otherwise it represents false
	else
	{
		return false;
	}
}

