//: Control.cpp
/*
Title:        Control.cpp
Description:  This source file implements the Control class, which manages user interactions
				and input parsing for the text-adventure game. It reads user commands, checks
				them against the defined actions, and interprets them accordingly.
Date:         February 5, 2025
Author:       Halie Favron
Student ID:   3673820
Version:      1.0
Copyright:    2024 Halie Favron
*/

/*
DOCUMENTATION

Program Purpose:
	- The Control class manages the user interface for input collection and parsing.
	- It converts raw user input into recognizable game commands by mapping input tokens
		to keywords, verbs, characters, locations, items, and directions.

Compile (assuming g++ is installed):
	g++ -o main Actions.cpp Alice.cpp Characters.cpp Control.cpp FileReader.cpp Game.cpp GameObject.cpp Items.cpp Locations.cpp main.cpp Utilities.cpp
Execution (assuming your terminal is Windows Command Prompt):
	main.exe

Compile Note:
	Ensure all files are being properly compiled or errors will occur
*/

#include "Control.h"
#include "Utilities.h"

/*******************************************************************************************************************************************************************************************
* The Control Class
* Manages the input user interface
*******************************************************************************************************************************************************************************************/

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Accessor and Mutator functions of the Control class
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Control::setAction(Actions a)
{
	action = a;
}

Actions Control::getAction()
{
	return action;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Input processing functions
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Retrieves the user's input
std::string Control::getInputFromUser()
{
	// Stores the input retrieved from the user
	std::string input;

	// Shows the user where to enter their input
	std::cout << "> ";

	// Get a line from a user
	std::getline(std::cin, input);

	// Returns the input retrieved from the user
	return input;
}

// Parses the user's input to identify and categorize tokens into Keyword, Verb, Character, and Direction
// Returns an array of integers representing the corresponding enum values for each category, based on the last token found
std::array<int, 6> Control::parseUserInput()
{
	int k = NullKeyword;
	int v = NullVerb;
	int c = NullCharacter;
	int l = NullLocation;
	int i = NullItem;
	int d = NullDirection;

	int invalidInputAttempts = 0;

	// Retrieves the input from the user
	std::string input = getInputFromUser();

	// Repeatedly prompts the user until a non-empty input line is provided
	while (input.empty())
	{
		// After multiple empty inputs, provides instructions to the user and resets the invalid input counter
		if (invalidInputAttempts >= 1)
		{
			std::cout << "Line was empty, please re-enter input\n";
			std::cout << "\tType Q or Quit to end game\n";
			std::cout << "\tType H or Help for input instructions\n";
			input = getInputFromUser();
			invalidInputAttempts = 0;
		}
		// Prompts the user again after the first empty input
		else
		{
			std::cout << "Line was empty, please re-enter input\n";
			input = getInputFromUser();
			invalidInputAttempts++;
		}
	}

	std::stringstream inputStream(toLower(input));
	std::string token;

	// Extracts tokens from the input stream, splitting by spaces (' ')
	while (std::getline(inputStream, token, ' '))
	{
		if (token.empty()) continue;

		// Checks if the token matches any keyword, verb, noun, or direction in the action maps
		if (searchMap(action.getKeywordMap(), token, k)) continue;
		if (searchMap(action.getVerbMap(), token, v)) continue;
		if (searchMap(action.getCharacterMap(), token, c)) continue;
		if (searchMap(action.getLocationsMap(), token, l)) continue;
		if (searchMap(action.getItemsMap(), token, i)) continue;
		if (searchMap(action.getDirectionMap(), token, d)) continue;
	}

	// Returns an array of integers representing the enum values for each category
	return { k, v, c, l, i , d };
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Display Functions
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Displays all potential actions to the user
void Control::displayPotentialActions()
{
	std::cout << "PotentialActions:\n";
	action.print();
}