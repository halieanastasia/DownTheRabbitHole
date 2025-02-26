//: Alice.h
/*
Title:        Alice.h
Description:  This header file declares two classes:
				1) Alice: Represents the main player character in the game, tracking total score, treasure score, friendship score, health, and attack damage.
				2) Inventory: Manages a collection of game items, allowing for additions, removals, searches, and sorting by item type.
Date:         January 10, 2025
Author:       Halie Favron
Student ID:   3673820
Version:      1.0
Copyright:    2025 Halie Favron
*/

/*
DOCUMENTATION

File Purpose:
	- This file is part of a larger text-adventure game. 
	- The 'Alice' class encapsulates all attributes and behaviours needed for the player, including scoring, health, and attack mechanics. 
	- The 'Inventory' class holds game items, with methods for adding, removing, sorting, and verifying items.

Compile (assuming g++ is installed):
	g++ -o main Actions.cpp Alice.cpp Characters.cpp Control.cpp FileReader.cpp Game.cpp GameObject.cpp Items.cpp Locations.cpp main.cpp Utilities.cpp
Execution (assuming your terminal is Windows Command Prompt):
	main.exe

Compile Note:
	Ensure all files are being properly compiled or errors will occur
*/

#pragma once
#include "Actions.h"

#include <iostream>
#include <vector>

/*******************************************************************************************************************************************************************************************
* The Alice Class
* Stores treasure that has been added to the cottage location
* Stores the main players total score, treasure score, and friendship score
*******************************************************************************************************************************************************************************************/

// Forward declarations
class Item;
class Character;

class Alice
{
private:
	// Attributes 
	int totalScore;
	int treasureScore;
	int friendshipScore;
	int hitPoints;
	int maxAttackDamage;

public:
	// Default constructor
	Alice();
	
	// Accessor and mutator functions
	void updateTotalScore();
	int getTotalScore();

	void setTreasureScore(int points);
	int getTreasureScore();

	void setFriendshipScore(int points);
	int getFriendshipScore();

	void setHitPoints(int hp);
	int getHitPoints();

	void setMaxAttackDamage(int a);
	int getMaxAttackDamage();
	
	// Increases the players attack damage
	void increaseAttackDamage(int increaseAmount);

	// Displays the players total score
	void displayTotalScore();
	
	// Updates the players total friendship score
	void updateFriendshipScore(std::vector<Character>& characters);
	
	// Adds addition points to the existing treasure score
	void addToTreasureScore(int pointsToAdd);
};


/*******************************************************************************************************************************************************************************************
* The Inventory Class
* Stores items that have been added to the inventory
* Implements functions to manage the item inventory
*******************************************************************************************************************************************************************************************/

class Inventory
{
private:
	// Attributes 
	std::vector<Item> inventory;

public:
	// Constructor
	Inventory(); // Clears the inventory vector

	// Accessor and Mutator functions
	std::vector<Item> getInventory();

	// Adds an item to the inventory vector
	void addToInventory(Item& item);

	// Removes an item from the inventory vector
	void removeFromInventory(Item item);

	// Searches the inventory vector for the specifed item
	Item searchInventory(Item& item);

	// Checks if the specifed item is in the inventory
	bool isInInventory(Item& item);

	// Checks if an item is valid (in inventory and not null)
	bool isValidItem(Item& item);

	// Compares items by item type
	static bool compareByItemType(Item& a, Item& b);

	// Sorts inventory vector by item type
	void sortByItemType();

	// Print the contents of the inventory 
	void displayInventory(); 
};
