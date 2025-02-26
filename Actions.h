//: Actions.h
/*
Title:        Actions.h
Description: This header file declares the Actions class, which reads and processes
				the Actions from a text file. It populates a collection of maps for keywords, verbs,
				characters, locations, items, and directions based on the file's contents.
Date:         December 20, 2024
Author:       Halie Favron
Student ID:   3673820
Version:      1.0
Copyright:    2024 Halie Favron
*/

/*
DOCUMENTATION

Program Purpose:
	- The Actions class is responsible for parsing an external file ("Actions.txt")
	  to build and store various game-related enumerations in maps. These maps help
	  translate user-input text into internal enum values, enabling more efficient game logic.

Compile (assuming g++ is installed):
	g++ -o main Actions.cpp Alice.cpp Characters.cpp Control.cpp FileReader.cpp Game.cpp GameObject.cpp Items.cpp Locations.cpp main.cpp Utilities.cpp
Execution (assuming your terminal is Windows Command Prompt):
	main.exe

Compile Note:
	Ensure all files are being properly compiled or errors will occur
*/

#pragma once
#include "GameEnums.h"

#include <array>
#include <map>
#include <string>


/*******************************************************************************************************************************************************************************************
* The ActionSet Class
* Stores all the possible actions a user can input in maps for easy look ups
* Gets the actions from a file
*******************************************************************************************************************************************************************************************/

// Forward declaration
class Game;
class Actions
{
private:	
	// Maps for storing string-to-enum mappings for actions | Source: https://www.geeksforgeeks.org/map-associative-containers-the-c-standard-template-library-stl/
	std::map <std::string, Keywords> keywordMap;
	std::map <std::string, Verbs> verbMap;
	std::map <std::string, Characters> characterMap;
	std::map <std::string, Locations> locationMap;
	std::map <std::string, Items> itemMap;
	std::map <std::string, Directions> directionMap;
	
public:
	// Constructors
	Actions() {};
	Actions(std::string actionFileName);

	// Core functions for parsing the actions file and populating the maps
	void readFileToMap(std::string actionFileName);
	void processLine(const std::string& category, const std::string& line);
	void processCategory(const std::string& category, const std::string& label, const std::string& token);

	
	// Functions for adding values to action maps
	void addToKeywordMap(Keywords keyword, std::string value);
	void addToVerbMap(Verbs verb, std::string value);
	void addToCharacterMap(Characters character, std::string value);
	void addToLocationMap(Locations location, std::string value);
	void addToItemMap(Items item, std::string value);
	void addToDirectionMap(Directions direction, std::string value);

	// Functions for returning action maps
	std::map<std::string, Keywords> getKeywordMap();
	std::map <std::string, Verbs> getVerbMap();
	std::map <std::string, Characters> getCharacterMap();
	std::map <std::string, Locations> getLocationsMap();
	std::map <std::string, Items> getItemsMap();
	std::map <std::string, Directions> getDirectionMap();


	// Functions for converting strings to enums
	Keywords stringToKeywordEnum(const std::string label);
	Verbs stringToVerbEnum(const std::string label);
	Characters stringToCharacterEnum(const std::string label);
	Locations stringToLocationEnum(const std::string label);
	Items stringToItemEnum(const std::string label);
	Directions stringToDirectionEnum(const std::string label);

	// Prints the contents of the action maps
	void print();
};

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Free Functions to Help The Actions Class
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Searches a template map for the specified token. 
// If the token is found, updates the reference variable "action" with the corresponding value from the map and returns true. 
// Returns false if the token is not found.
template <typename T>
bool searchMap(std::map<std::string, T> map, std::string token, int& action)
{
	auto m = map.find(token); // Source: https://www.geeksforgeeks.org/map-find-function-in-c-stl/
	if (m != map.end())
	{
		// Updates the variable to store the enum value of m
		action = m->second; // Source: https://cplusplus.com/reference/map/map/find/
		return true;
	}
	return false;
}