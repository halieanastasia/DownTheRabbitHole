//: Locations.cpp
/*
Title:        Locations.cpp
Description:  This source file implements the Location class,  which is derived from GameObject
			  to represent places in the game, as well as the Exit class,
			  which manages directional connections between locations.
Date:         December 15, 2024
Author:       Halie Favron
Student ID:   3673820
Version:      1.0
Copyright:    2024 Halie Favron
*/

/*
DOCUMENTATION

Program Purpose:
	- The Location class handles the data for each location in the game, including
	  its name, descriptions, and exits.
	- The Exit class specifies how a location connects to others, tracking whether
	  it is locked/unlocked, which direction it faces, and the key needed to unlock it.
	- This file also provides utility functions for searching exits within
	  location vectors.

Compile (assuming g++ is installed):
	g++ -o main Actions.cpp Alice.cpp Characters.cpp Control.cpp FileReader.cpp Game.cpp GameObject.cpp Items.cpp Locations.cpp main.cpp Utilities.cpp
Execution (assuming your terminal is Windows Command Prompt):
	main.exe

Compile Note:
	Ensure all files are being properly compiled or errors will occur

Notes:
	- Derived from GameObject class
*/

#include "Locations.h"
#include "GameEnums.h"

/*******************************************************************************************************************************************************************************************
* The Location Class
* Derived From Game Object
* Represents individual locations in the game
*******************************************************************************************************************************************************************************************/

// The Default Constructor for the Character class
Location::Location()
{
	// Most default values are read from the Locations.txt file
	hasBeenEntered = false;
}

// Equals operator overload
bool Location::operator==(Location location2)
{
	if (getName() == location2.getName())
	{
		return true;
	}

	return false;
}

// Not equals operator overload
bool Location::operator!=(Location location2)
{
	if (getName() != location2.getName())
	{
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Accessor and Mutator functions of the Locations class
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

std::vector<Exit> Location::getExits()
{
	return exits;
}

void Location::setExit(Exit& ex)
{
	exits.push_back(ex);
}

void Location::setHint(std::string h)
{
	hint = h;
}

std::string Location::getHint()
{
	return hint;
}

void Location::displayHint()
{
	std::cout << getHint() << "\n";
}

void Location::setHasBeenEntered(bool h)
{
	hasBeenEntered = h;
}

bool Location::getHasBeenEntered()
{
	return hasBeenEntered;
}

// Returns a reference to the exit object based the direction passed
Exit& Location::getExit(int direction)
{
	int index = searchVectorOfExits(exits, direction);

	if (index == -1)
	{
		throw std::out_of_range("There is no exit in the direction you specified"); // Handle invalid direction Source:https://en.cppreference.com/w/cpp/error/out_of_range
	}
	return  exits[index];
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Utility functions of the Locations class
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Prints the attributes of a Location object
void Location::print() 
{
	GameObject::print();
	
	int count = 1;

	for (Exit& exit : exits)
	{
		std::cout << "Exit " << count << ":\n\t";
		exit.print();
		count++;
	}

	std::cout << "\n";
}

// Prints the Location's Exits
void Location::displayLocationExits()
{
	for (Exit exit : exits)
	{
		std::string name = exit.getExitName();
		std::string description = exit.getExitDescription();

		std::cout << "To the *" << exit.directionToString()
			<< "* there is " << toLower(description)
			<< "\nIt looks like it might lead to a " << toLower(name) << "\n";
	}
}

/*******************************************************************************************************************************************************************************************
* The Exit Class
* Represents the exits belonging to the locations in the game
*******************************************************************************************************************************************************************************************/

// Default constructor
Exit::Exit() 
{ 
	exitName = ""; 
	description = ""; 
	key = NullItem;
	direction = NullDirection;
	isExitUnlocked = false;
}

// Parameterized constructor
Exit::Exit(std::string name, std::string descr, int k, int direc, bool l) 
{ 
	exitName = name; 
	description = descr; 
	key = k;
	direction = direc; 
	isExitUnlocked = l;
}


//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Accessor and Mutator functions of the Exit class
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Exit::setExitName(std::string n) 
{ 
	exitName = n; 
}

std::string Exit::getExitName()
{
	return exitName;
}

void Exit::setExitDescription(std::string d) 
{ 
	description = d;
}

std::string Exit::getExitDescription() 
{
	return description; 
}

void Exit::setKey(int k)
{
	key = k;
}

int Exit::getKey()
{
	return key;
}

void Exit::setDirection(int d)
{ 
	direction = d;
}

int Exit::getDirection()
{
	return direction; 
}

void Exit::setIsUnlocked(bool l) 
{ 
	isExitUnlocked = l;
}

bool Exit::isUnlocked() 
{
	return isExitUnlocked;
}


//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Utility functions of the Exit class
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Unlocks the isLocked attribute (changes the value to true)
void Exit::unlock() 
{
	isExitUnlocked = true;
}

// Gets a string representation of the Exit's direction
std::string Exit::directionToString()
{
	std::string directionString;

	if (direction == North)
	{
		directionString = "north";
	}
	else if (direction == NorthEast)
	{
		directionString = "north-east";
	}
	else if (direction == East)
	{
		directionString = "east";
	}
	else if (direction == SouthEast)
	{
		directionString = "south-east";
	}
	else if (direction == South)
	{
		directionString = "south";
	}
	else if (direction == SouthWest)
	{
		directionString = "south-west";
	}
	else if (direction == West)
	{
		directionString = "west";
	}
	else if (direction == NorthWest)
	{
		directionString = "north-west";
	}
	else
	{
		directionString = "Error";
	}
	return directionString;
}

// Print Exit object
void Exit::print()
{
	std::cout << "The exit to the *" << directionToString() << "* leads to a " << toLower(exitName) << std::endl;
}

/*******************************************************************************************************************************************************************************************
* Free Functions for Location Creation
*******************************************************************************************************************************************************************************************/
 
//Searches a Location vector for a specified exit, by its name
 //Returns the index of the location if it is found, if not returns -1
int findExitIndex(const std::vector<Location>& vector, Exit& exit)
{
	for (int i = 0; i < vector.size(); i++) // Iterates over vector
	{
		// Compares the name of the two objects
		if (exit.getExitName() == vector[i].getName())
		{
			return i; // If found return the index
		}
	}
	return -1; // Return -1 if object is not found
}

//Searches a Exit vector for a specified exit, by its direction
 //Returns the index of the Exit if it is found, if not returns -1
int searchVectorOfExits(std::vector<Exit>& exitVector, int exitDirection)
{
	for (int i = 0; i < exitVector.size(); i++) // Iterates over vector
	{
		// Compares the name of the two objects
		if (exitDirection == exitVector[i].getDirection())
		{
			return i; // If found return the index
		}
	}
	return -1; // Return -1 if object is not found
}





