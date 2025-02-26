//: Items.h
/*
Title:        Items.h
Description:  This header file declares the Item class, which is derived from GameObject
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

#pragma once
#include "GameObject.h"

// Forward declarations
class Location;
class Exit;
class Character;
class Inventory;

class Item : public GameObject
{
private:
	// Attributes
	int itemType;
	int points;
	int giftValue;

	bool canRespawn;
	bool respawn;
	
	

public:
	// Constructor
	Item();

	bool operator == (Item item2);
	bool operator != (Item item2);

	// Accessor and Mutator functions
	void setItemType(int t);
	int getItemType();

	void setCanRespawn(bool r);
	bool getCanRespawn();

	void setRespawn(bool r);
	bool getRespawn();

	void setGiftValue(int v);
	int getGiftValue();

	void setPoints(int p);
	int getPoints();

	// Displays the attributes of a Item object
	void displayItem();
	
	// Gets a string representation of the item type
	std::string itemTypeToString();
};




