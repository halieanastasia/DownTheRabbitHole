//: GameObject.cpp
/*
Title:        GameObject.cpp
Description:  This source file implements the GameObject class, which serves as a base class
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


#include "GameObject.h"

#include <iostream>

// Forward declarations
class Character;
class Location;
class Item;


/*******************************************************************************************************************************************************************************************
* The GameObjects Class
* Represents individual GameObjects in the game
*******************************************************************************************************************************************************************************************/

// The Default Constructor for the Character class
GameObject::GameObject()
{
	// Set the GameObject to default values
	setName("Undefined");
	setShortDescription("Undefined");
	setLongDescription("Undefined");
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Accessor and Mutator functions of the GameObject class
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void GameObject::setName(std::string n)
{
	name = n;
}

std::string GameObject::getName() const
{
	return name;
}

void GameObject::setShortDescription(std::string d)
{
	shortDescription = d;
}

std::string GameObject::getShortDescription()
{
	return shortDescription;
}

void GameObject::setLongDescription(std::string rD)
{
	longDescription = rD;
}

std::string GameObject::getLongDescription()
{
	return longDescription;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Utility functions of the Locations class
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Prints the attributes of a GameObject, each derived class will have its own implementation
void  GameObject::print()
{
	std::cout << "Name: " << name
		<< "\nShort Description: " << shortDescription
		<< "\nLong Description: " << longDescription;
}
