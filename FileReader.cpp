//: FileReader.cpp
/*
Title:        FileReader.cpp
Description:  This source file implements a templated approach to reading and parsing data
				 for Characters, Items, and Locations from text files. It specializes generic
				 functions to handle attributes unique to each game object type.
Date:         December 17, 2024
Author:       Halie Favron
Student ID:   3673820
Version:      1.0
Copyright:    2024 Halie Favron
*/

/*
DOCUMENTATION

Program Purpose:
	- This file provides utilities to read data from external text files (e.g., Characters.txt,
	  Items.txt, Locations.txt) and populate corresponding game object vectors.
	- It leverages templates for shared parsing logic, while using specializations to handle
	  unique attributes for Characters, Items, and Locations.

Compile (assuming g++ is installed):
	g++ -o main Actions.cpp Alice.cpp Characters.cpp Control.cpp FileReader.cpp Game.cpp GameObject.cpp Items.cpp Locations.cpp main.cpp Utilities.cpp
Execution (assuming your terminal is Windows Command Prompt):
	main.exe

Compile Note:
	Ensure all files are being properly compiled or errors will occur
*/

#include "FileReader.h"
#include "Characters.h"
#include "Items.h"
#include "Locations.h"
#include "GameEnums.h"

/*******************************************************************************************************************************************************************************************
* Free Functions for Game Object Creation
*******************************************************************************************************************************************************************************************/

// Checks the label and store the data in the appropriate field
template <typename T>
void parseField(const std::string& label, const std::string value, T& t)
{
	// Check the label and store the data in the appropriate field
	if (label.empty() || value.empty()) // If either field is empty print error
	{
		std::cerr << "Invalid line format for label: \"" << label << "\" with value: \"" << value << "\"\n";
		return; // Skip lines with an invalid format  
	}

	// Handle generic attributes common to all GameObject types
	else if (label == "Name")
	{
		t.setName(value);
		return;
	}
	else if (label == "Long Description")
	{
		t.setLongDescription(value);
		return;
	}

	else if (label == "Short Description")
	{
		t.setShortDescription(value);
		return;
	}

	// Handle type-specific attributes using a specialized function for GameObject types Character, Location, and Item
	else
	{
		getSpecializedAttributes(label, value, t); // Source: https://www.geeksforgeeks.org/template-specialization-c/?utm_source=chatgpt.com
		return;
	}

	// If the label does not match any of the attributes, display an error
	std::cerr << "Unexpected label: \"" << label << "\"\n";
}

// Template Specialization Source: https://www.geeksforgeeks.org/template-specialization-c/?utm_source=chatgpt.com
// Populates the gameObjectSet vector with data from a file
// This template function supports creating sets for Character, Location, and Item types
template <typename T>
std::vector<T> getGameObjectSetFromFile(const std::string& fileName)
{
	std::vector<T> vectorObject;
	std::ifstream inputFile(fileName); // Open file containing game data

	checkFileError(inputFile, fileName); // Checks that the file was opened properly and terminates the program if it was not

	std::string line; // Store each line
	T tempGameObject; // Create a temporary GameObject object to store the data being read from the file

	while (std::getline(inputFile, line)) // Read line by line
	{
		std::stringstream lineStream(line); // Prepare current line for parsing
		std::string label, input; // label: store the data identifier, input: store the corresponding value

		std::getline(lineStream, label, ':'); // Parse the lineStream up to the colon char (':'), store in the label variable
		std::getline(lineStream, input); // Parse the lineStream up to the end of the line, store in the input variable

		// Check if the label denotes the end of the current object's data block
		if (label == "*****")
		{
			// Checks that the temporary object has a name, a short description, and a long description
			if (tempGameObject.getName() == "Undefined" || tempGameObject.getShortDescription() == "Undefined" || tempGameObject.getLongDescription() == "Undefined")
			{
				std::string errorMessage = "A game object was loaded with incomplete data, this is a terminal error, ending the game...\n";
				criticalError(errorMessage); // If a game object has incomplete data it will break the game, so the game must be ended
			}
			else
			{
				vectorObject.push_back(tempGameObject); // Add the tempGameObject object in the object vector
			}
			tempGameObject = T(); // Reset the temporary object for the next data block
		}
		
		else
		{
			parseField(label, input, tempGameObject); // Parses the current object's fields
		}
	}
	return vectorObject; // Returns the vector of game objects once the end of the file is reached
}

template <typename T>
void getSpecializedAttributes(const std::string& label, const std::string& value, T& t)
{
	// Default implementation does nothing for types other than Character, Item, and Location
}

// Specialization for Character attributes
template<>
void getSpecializedAttributes<Character>(const std::string& label, const std::string& value, Character& character)
{
	// Checks the label, when the label matches, add the value to the corresponding attribute
	if (label == "Friendship Score")
	{
		character.setFriendshipScore(std::stoi(value));
	}
	else if (label == "Hit Points")
	{
		character.setHitPoints(std::stoi(value));
	}
	else if (label == "Attack Damage")
	{
		character.setMaxAttackDamage(std::stoi(value));
	}
	else if (label == "Gifts")
	{
		std::stringstream inputStream(value);
		std::string itemName = "";
		
		// Reads the list of gifts and stores them in the giftItemValues attribute
		while (std::getline(inputStream, itemName, '-'))
		{
			Item gift;
			gift.setName(itemName);
			character.addToGiftItemValue(gift);
		}
		character.setGiftItemValues();
	}
}

// Specialization for Item attributes
template<>
void getSpecializedAttributes<Item>(const std::string& label, const std::string& value, Item& item)
{
	// Checks the label, when the label matches, add the value to the corresponding attribute
	if (label == "Item Type")
	{
		// Parse the item type and any attribute values that are specified
		std::stringstream inputStream(value);
		std::string type = "", attributes = ""; // variables to hold parsed values

		std::getline(inputStream, type, ':');
		std::getline(inputStream, attributes);

		// Set the default attributes to false
		item.setCanRespawn(false);

		// Changes default attributes depending on the item type

		if (type == "Key")
		{
			item.setItemType(Key);
		}
		else if (type == "Gift")
		{
			item.setItemType(Gift);
			item.setCanRespawn(true);
		}
		else if (type == "Treasure")
		{
			item.setItemType(Treasure);
		}
		else if (type == "Key Item")
		{
			item.setItemType(KeyItem);
		}
		else if (type == "Weapon")
		{
			item.setItemType(Weapon);
		}
		else
		{
			item.setItemType(NullItemType);
		}
	}
	// Checks the label, when the label matches, add the value to the corresponding attribute
	else if (label == "Points")
	{
		item.setPoints(std::stoi(value));
	}
}

// Specialization for Location attributes
template<>
void getSpecializedAttributes<Location>(const std::string& label, const std::string& value, Location& location)
{
	// Checks the label, when the label matches, add the value to the corresponding attribute
	if (label == "Hint")
	{
		location.setHint(value);
	}

	else if (label == "Exit")
	{
		int direction = NullDirection;
		int key = NullItem;
		bool isUnlocked = false;

		std::string directionString, exitName, description, unlocked, keyString;
		
		std::stringstream inputStream(value); // Prepare value for parsing
		
		// Parse all attributes for an Exit object
		std::getline(inputStream, directionString, '-');
		std::getline(inputStream, exitName, ':');
		std::getline(inputStream, description, '*');
		std::getline(inputStream, unlocked, '*');
		std::getline(inputStream, keyString);

		// Sets the direction of the Exit
		if (directionString == "N")
		{
			direction = North;
		}
		else if (directionString == "NE")
		{
			direction = NorthEast;
		}
		else if (directionString == "E")
		{
			direction = East;
		}
		else if (directionString == "SE")
		{
			direction = SouthEast;
		}
		else if (directionString == "S")
		{
			direction = South;
		}
		else if (directionString == "SW")
		{
			direction = SouthWest;
		}
		else if (directionString == "W")
		{
			direction = West;
		}
		else if (directionString == "NW")
		{
			direction = NorthWest;
		}
		else
		{
			direction = NullDirection;
		}

		// Checks if the Exit is unlocked
		if (unlocked == "unlocked")
		{
			isUnlocked = true;
		}

		// Checks if the Exit requires a key to unlock it
		if (keyString == "GardenKey")
		{
			key = GardenKey;
		}
		if (keyString == "CottageKey")
		{
			key = CottageKey;
		}
		if (keyString == "MushroomKey")
		{
			key = MushroomKey;
		}

		// Creates a Exit with the parsed attributes
		Exit exit(exitName, description, key, direction, isUnlocked);
		
		// Adds the Exit to the location
		location.setExit(exit);
	}
}


//Explicit instantiation for supported types 
//Source: https://en.cppreference.com/w/cpp/language/class_template
template std::vector<Character> getGameObjectSetFromFile<Character>(const std::string&);
template std::vector<Location> getGameObjectSetFromFile<Location>(const std::string&);
template std::vector<Item> getGameObjectSetFromFile<Item>(const std::string&);


