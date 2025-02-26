//: Items.cpp
/*
Title:        Items.cpp
Description:  This source file implements the Item class, which is derived from GameObject
				and represents individual items in the game.
Date:			December 15, 2024
Author:       Halie Favron
Student ID:   3673820
Version:      1.0
Copyright:    2024 Halie Favron
*/

/*
DOCUMENTATION

Program Purpose:
	- The Item class manages in-game objects the player can pick up, use, or store,
	  including keys, gifts, treasure, and miscellaneous objects.

Compile (assuming g++ is installed):
	g++ -o main Actions.cpp Alice.cpp Characters.cpp Control.cpp FileReader.cpp Game.cpp GameObject.cpp Items.cpp Locations.cpp main.cpp Utilities.cpp
Execution (assuming your terminal is Windows Command Prompt):
	main.exe

Compile Note:
	Ensure all files are being properly compiled or errors will occur

Notes:
	- Derived from GameObject class
*/

#include "Items.h"
#include "Locations.h"
#include "Characters.h"
#include "Alice.h"

#include <iostream>

/*******************************************************************************************************************************************************************************************
* The Item Class
* Derived From Game Object
* Represents individual items in the game
*******************************************************************************************************************************************************************************************/

// The Default Constructor for the Item class
Item::Item()
{
	setItemType(NullItem);
	setCanRespawn(false);
	
	respawn = true;
	setPoints(0);
	setGiftValue(0);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Accessor and Mutator functions of the Item class
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool Item::operator==(Item item2)
{
	if (getName() == item2.getName())
	{
		return true;
	}

	return false;
}

bool Item::operator!=(Item item2)
{
	if (getName() != item2.getName())
	{
		return true;
	}

	return false;
}

void Item::setItemType(int t)
{
	itemType = t;
}

int Item::getItemType()
{
	return itemType;
}

void Item::setCanRespawn(bool r)
{
	canRespawn = r;
}

bool Item::getCanRespawn()
{
	return canRespawn;
}

void Item::setRespawn(bool r)
{
	respawn = r;
}

bool Item::getRespawn()
{
	return respawn;
}

void Item::setGiftValue(int v)
{
	giftValue = v;
}

int Item::getGiftValue()
{
	return giftValue;
}

void Item::setPoints(int p)
{
	points = p;
}

int Item::getPoints()
{
	return points;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Utility functions of the Item class
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Displays the attributes of a Item object
void Item::displayItem()
{
	std::cout << "Item: " << getName() << "\n";
	std::cout << "Item Type: " << itemTypeToString() << "\n";
	std::cout << "Description: " << getLongDescription() << "\n";
}

// Gets a string representation of the item type
std::string Item::itemTypeToString()
{
	switch (itemType)
	{
	case Key:
		return "Key";
		break;
	
	case Gift:
		return "Gift";
		break;

	case Treasure:
		return "Treasure";
		break;

	case KeyItem:
		return "Key Item";
		break;

	case Weapon:
		return "Weapon";
		break;

	default: 
		return "Null";
	}
}
