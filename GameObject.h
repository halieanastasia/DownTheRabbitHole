//: GameObject.h
/*
Title:        GameObject.h
Description:  This header file declares the GameObject class, which serves as a base class
				for Characters, Locations, and Items in the game. It stores
				fundamental properties such as name, short description, and long description.
Date:         December 15, 2024
Author:       Halie Favron
Student ID:   3673820
Version:      1.0
Copyright:    2024 Halie Favron
*/

/*
DOCUMENTATION

Program Purpose:
	- The GameObject class provides common fields and methods to all in-game objects
	  (Characters, Locations, and Items). It centralizes handling of names and descriptions.

Compile (assuming g++ is installed):
	g++ -o main Actions.cpp Alice.cpp Characters.cpp Control.cpp FileReader.cpp Game.cpp GameObject.cpp Items.cpp Locations.cpp main.cpp Utilities.cpp
Execution (assuming your terminal is Windows Command Prompt):
	main.exe

Compile Note:
	Ensure all files are being properly compiled or errors will occur

Notes:
	- Base class for Character, Location, and Item classes.
*/

#pragma once
#include "Utilities.h"

#include <string>
#include <vector>
#include <sstream>

/*******************************************************************************************************************************************************************************************
* The GameObjects Class
* Represents individual GameObjects in the game
*******************************************************************************************************************************************************************************************/

class GameObject
{
private:
	// Attributes common to all GameObjects
	std::string name;
	std::string shortDescription;
	std::string longDescription;

public:
	// Constructor
	GameObject();

	// Accessor and Mutator functions
	void setName(std::string n);
	std::string getName() const;

	void setShortDescription(std::string d);
	std::string getShortDescription();

	void setLongDescription(std::string rD);
	std::string getLongDescription();

	// Prints the attributes of a GameObject, each derived class will have its own implementation
	void print();
};
