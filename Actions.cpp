//: Actions.cpp
/*
Title:        Actions.cpp
Description:  This source file implements the Actions class, which reads and processes
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

#include "Actions.h"
#include "Utilities.h"
#include "Game.h"

#include <fstream>

/*******************************************************************************************************************************************************************************************
* The Actions Class
* Stores all the possible actions a user can input
*******************************************************************************************************************************************************************************************/

// Constructor
Actions::Actions(std::string actionFileName)
{
	readFileToMap(actionFileName);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Functions for parsing the Actions.txt file and populating the maps
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Reads a file and processes its contents line by line
void Actions::readFileToMap(std::string actionFileName)
{
	// Opens the file containing actions using the provided filename
	std::ifstream inputFile(actionFileName);

	// Check if the file was opened successfully, terminates the program if it was not
	checkFileError(inputFile, actionFileName);

	std::string category, line;

	// Reads the file line by line
	while (std::getline(inputFile, line))
	{
		// Skip empty lines or lines containing "*****", which separate categories in the file		
		if (line.empty() || line == "*****") 
		{
			continue;
		}
		
		// When a category header is encountered, update the category variable
		if (line == "Keywords:" || line == "Verbs:" || line == "Characters:" || line == "Locations:" || line == "Items:" || line == "Directions:")
		{
			category = line;
		}

		// Otherwise, process the line based on the current category
		else
		{
			processLine(category, line);
		}
	}
}

// Processes each line from the action file, splitting it into labels and tokens
void Actions::processLine(const std::string& category, const std::string& line)
{
	std::stringstream lineStream(line);
	std::string label, token;

	// Extracts the label from the line stream, using a colon (:) as a delimeter
	std::getline(lineStream, label, ':');

	// Extracts tokens from the line stream, splitting by spaces (' ')
	while (std::getline(lineStream, token, ' '))
	{
		// Processes each token based on the category and label
		processCategory(category, label, token);
	}
}

// Processes the categories from the action file
// Adds elements to the corresponding action map based on the category
void Actions::processCategory(const std::string& category, const std::string& label, const std::string& token)
{
	// Based on the category, process the label and token and add to the correct map
	if (category == "Keywords:") 
	{
		addToKeywordMap(stringToKeywordEnum(label), token); 			
	}
	else if (category == "Verbs:")
	{
		addToVerbMap(stringToVerbEnum(label), token);
	}
	else if (category == "Characters:")
	{
		addToCharacterMap(stringToCharacterEnum(label), token);
	}
	else if (category == "Locations:")
	{
		addToLocationMap(stringToLocationEnum(label), token);
	}
	else if (category == "Items:")
	{
		addToItemMap(stringToItemEnum(label), token);
	}
	else if (category == "Directions:")
	{
		addToDirectionMap(stringToDirectionEnum(label), token);
	}
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Functions for adding values to action maps
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Actions::addToKeywordMap(Keywords keyword, std::string value)
{
	keywordMap[value] = keyword;
}

void Actions::addToVerbMap(Verbs verb, std::string value)
{
	verbMap[value] = verb;
}

void Actions::addToCharacterMap(Characters character, std::string value)
{
	characterMap[value] = character;
}

void Actions::addToLocationMap(Locations location, std::string value)
{
	locationMap[value] = location;
}

void Actions::addToItemMap(Items item, std::string value)
{
	itemMap[value] = item;
}

void Actions::addToDirectionMap(Directions direction, std::string value)
{
	directionMap[value] = direction;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Functions for returning action maps
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
std::map<std::string, Keywords> Actions::getKeywordMap()
{
	return keywordMap;
}

std::map<std::string, Verbs> Actions::getVerbMap()
{
	return verbMap;
}

std::map<std::string, Characters> Actions::getCharacterMap()
{
	return characterMap;
}

std::map<std::string, Locations> Actions::getLocationsMap()
{
	return locationMap;
}

std::map<std::string, Items> Actions::getItemsMap()
{
	return itemMap;
}

std::map<std::string, Directions> Actions::getDirectionMap()
{
	return directionMap;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Functions for converting strings to enums
// Converts strings to the corresponding enum values
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Keywords Actions::stringToKeywordEnum(const std::string label)
{
	// Matches the string label to a specific Keyword enum value
	if (label == "Yes")
	{
		return Yes;
	}
	else if (label == "No")
	{
		return No;
	}
	else if (label == "Help")
	{
		return Help;
	}
	else if (label == "End")
	{
		return End;
	}
	else if (label == "Inventory")
	{
		return PlayerInventory;
	}
	else if (label == "Hint")
	{
		return Hint;
	}
	else if (label == "Stats")
	{
		return Stats;
	}
	else
	{
		return NullKeyword; // Returns a default value equal to -1 when no match is found
	}
}

Verbs Actions::stringToVerbEnum(const std::string label)
{
	// Matches the string label to a specific Verb enum value
	if (label == "Enter")
	{
		return Enter;
	}
	else if (label == "Pick Up")
	{
		return PickUp;
	}
	else if (label == "Use")
	{
		return Use;
	}
	else if (label == "Unlock")
	{
		return Unlock;
	}
	else if (label == "Gift")
	{
		return Give;
	}
	else if (label == "Follow")
	{
		return Follow;
	}
	else if (label == "Talk")
	{
		return Talk;
	}
	else if (label == "Explore")
	{
		return Explore;
	}
	else if (label == "Examine")
	{
		return Examine;
	}
	else if (label == "Attack")
	{
		return Attack;
	}
	else if (label == "Place Treasure")
	{
		return PlaceTreasure;
	}
	else
	{
		return NullVerb; // Returns a default value equal to -1 when no match is found
	}
}

Characters Actions::stringToCharacterEnum(const std::string label)
{
	// Matches the string label to a specific Characters enum value
	if (label == "Cheshire Cat")
	{
		return CheshireCat;
	}
	else if (label == "The Queen")
	{
		return Queen;
	}
	else if (label == "The Mad Hatter")
	{
		return MadHatter;
	}
	else if (label == "The March Hare")
	{
		return MarchHare;
	}
	else if (label == "The White Rabbit")
	{
		return WhiteRabbit;
	}
	else if (label == "The Caterpillar")
	{
		return Caterpillar;
	}
	else if (label == "The Duchess")
	{
		return Duchess;
	}
	else if (label == "The Soldier")
	{
		return Soldier;
	}
	else if (label == "The Gryphon")
	{
		return Gryphon;
	}
	else if (label == "The Mock Turtle")
	{
		return MockTurtle;
	}
	else
	{
		return NullCharacter; // Returns a default value equal to 0 when no match is found
	}
}

Locations Actions::stringToLocationEnum(const std::string label)
{
	// Matches the string label to a specific Locations enum value
	if (label == "Cottage")
	{
		return Cottage;
	}
	else if (label == "Meadow")
	{
		return Meadow;
	}
	else if (label == "Rabbit Hole")
	{
		return RabbitHole;
	}
	else if (label == "Long Hallway")
	{
		return LongHallway;
	}
	else if (label == "Cottage")
	{
		return Cottage;
	}
	else if (label == "Hare's Lawn")
	{
		return HaresLawn;
	}
	else if (label == "Pool of Tears")
	{
		return PoolOfTears;
	}
	else if (label == "Isle of Sorrow")
	{
		return IsleOfSorrow;
	}
	else if (label == "Garden")
	{
		return Garden;
	}
	else if (label == "Castle")
	{
		return Castle;
	}
	else
	{
		return NullLocation; // Returns a default value equal to 0 when no match is found
	}
}

Items Actions::stringToItemEnum(const std::string label)
{
	// Matches the string label to a specific Items enum value
	// Keys
	if (label == "Garden Key")
	{
			return GardenKey;
	}
	else if (label == "Cottage Key")
	{
			return CottageKey;
	}
	else if (label == "Mushroom Key")
	{
			return MushroomKey;
	}
	
	// Gifts
	else if (label == "Milk")
	{
		return Milk;
	}
	else if (label == "Butter")
	{
		return Butter;
	}
	else if (label == "Faux Turtle Soup")
	{
		return FauxSoup;
	}
	else if (label == "Pocket Watch")
	{
		return PocketWatch;
	}
	else if (label == "Kid Gloves")
	{
		return KidGloves;
	}
	else if (label == "Painted Rose")
	{
		return PaintedRose;
	}
	else if (label == "Tart")
	{
		return Tart;
	}
	else if (label == "Spectacles")
	{
		return Spectacles;
	}

	// Treasure
	else if (label == "Daisy Chain")
	{
		return DaisyChain;
	}
	else if (label == "Looking Glass")
	{
		return LookingGlass;
	}
	else if (label == "Music Box")
	{
		return MusicBox;
	}
	else if (label == "Fan")
	{
		return Fan;
	}
	else if (label == "Hookah")
	{
		return Hookah;
	}
	else if (label == "Hedgehog")
	{
		return Hedgehog;
	}
	else if (label == "Guinea Pig")
	{
		return GuineaPig;
	}
	else if (label == "Teapot")
	{
		return Teapot;
	}
	else if (label == "Courtier Diamond")
	{
		return CourtierDiamond;
	}
	else if (label == "King's Crown")
	{
		return KingsCrown;
	}
	else if (label == "Hatter's Hat")
	{
		return HattersHat;
	}

	// Key Items
	else if (label == "Drink Me Bottle")
	{
		return DrinkMeBottle;
	}
	else if (label == "Eat Me Cake")
	{
		return EatMeCake;
	}

	// Weapons
	else if (label == "Marmalade Jar")
	{
		return MarmaladeJar;
	}
	else if (label == "Ancient Sword")
	{
		return AncientSword;
	}

	// Null Item
	else
	{
		return NullItem; // Returns a default value equal to 0 when no match is found
	}
}

Directions Actions::stringToDirectionEnum(const std::string label)
{
	// Matches the string label to a specific Direction enum value
	if (label == "North")
	{
		return North;
	}
	else if (label == "North East")
	{
		return NorthEast;
	}
	else if (label == "East")
	{
		return East;
	}
	else if (label == "South East")
	{
		return SouthEast;
	}
	else if (label == "South")
	{
		return South;
	}
	else if (label == "South West")
	{
		return SouthWest;
	}
	else if (label == "West")
	{
		return West;
	}
	else if (label == "North West")
	{
		return NorthWest;
	}
	else
	{
		return NullDirection; // Returns a default value equal to -1 when no match is found
	}
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Utility Functions
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Prints the contents of the action maps
void Actions::print()
{
	std::cout << "Keywords:\n";
	for (auto k : keywordMap)
	{
		std::cout << "\t" << k.first << '\n';
	}

	std::cout << "Verbs:\n";
	for (auto v : verbMap)
	{
		std::cout << "\t" << v.first << '\n';
	}

	std::cout << "Characters:\n";
	for (auto n : characterMap)
	{
		std::cout << "\t" << n.first << '\n';
	}

	std::cout << "Directions:\n";
	for (auto a : directionMap)
	{
		std::cout << "\t" << a.first << '\n';
	}
}

