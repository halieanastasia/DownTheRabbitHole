//: Locations.h
/*
Title:        Locations.h
Description:  This header file declares the Location class,  which is derived from GameObject
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

#pragma once
#include "GameObject.h"

/*******************************************************************************************************************************************************************************************
* The Location Class
* Derived From Game Object
* Represents individual locations in the game
*******************************************************************************************************************************************************************************************/

// Forward declaration
class Exit;

class Location : public GameObject
{
private:
	// Attributes
	std::vector<Exit> exits;

	std::string hint;
	bool hasBeenEntered;

public:
	// Constructors
	Location();

	// Operator overload functions
	bool operator == (Location location2);
	bool operator != (Location location2);

	// Accessor and mutator functions
	std::vector<Exit> getExits(); // Returns the exit vector
	Exit& getExit(int direction); // Returns a reference to the exit object based the direction passed
	void setExit(Exit& ex); // Adds a Exit object to the exits vector

	void setHint(std::string h);
	std::string getHint();
	void displayHint();

	void setHasBeenEntered(bool h);
	bool getHasBeenEntered();

	// Prints the attributes of a Location object
	void print();
	void displayLocationExits();
};

/*******************************************************************************************************************************************************************************************
* The Exit Class
* Used to represent the entrances and exits of a Location
*******************************************************************************************************************************************************************************************/

class Exit
{
private:
	// Attributes
	std::string exitName;
	std::string description;
	int key;
	int direction;
	bool isExitUnlocked;

public:
	// Constructors
	Exit();
	Exit(std::string name, std::string descr, int k, int direc, bool l);

	// Accessor and Mutator functions
	void setExitName(std::string n);
	std::string getExitName();

	void setExitDescription(std::string d);
	std::string getExitDescription();

	void setKey(int d);
	int getKey();

	void setDirection(int d);
	int getDirection();

	void setIsUnlocked(bool l);
	bool isUnlocked();

	// Unlocks the isLocked attribute (changes the value to true)
	void unlock();

	// Gets a string representation of the exit's direction
	std::string directionToString();

	// Print Exit object
	void print();
};

/*******************************************************************************************************************************************************************************************
* Free Functions for Location Creation
*******************************************************************************************************************************************************************************************/

//Searches a Location vector for a specified exit, by its name
int findExitIndex(const std::vector<Location>& vector, Exit& exit);

//Searches a Exit vector for a specified exit, by its direction
int searchVectorOfExits(std::vector<Exit>& exitVector, int exitDirection);