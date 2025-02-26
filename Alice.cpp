//: Alice.cpp
/*
Title:        Alice.cpp
Description:  This source file implements the Alice class and the Inventory class.
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

Program Purpose:
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

#include "Alice.h"
#include "Items.h"
#include "Game.h"
#include "Actions.h"
#include "Characters.h"

#include <algorithm>

/*******************************************************************************************************************************************************************************************
* The Alice Class
* Stores treasure that have been added to the cottage location
* Stores the main players total score, treasure score, and friendship score
*******************************************************************************************************************************************************************************************/

// Default constructor
Alice::Alice()
{
    int startingAttackDamage = 20;
    int startingHP = 50;
    int startingTreasureScore = 0;

    setMaxAttackDamage(startingAttackDamage);
    setHitPoints(startingHP);
    setTreasureScore(startingTreasureScore);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Accessor and Mutator functions of the Alice class
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Alice::updateTotalScore()
{
   int score = treasureScore + friendshipScore;

   if (score > 2500) // It should not be possible to exceed 2500 but validation just in case
   {
       score = 2500;
   }
   totalScore = score;
}

int Alice::getTotalScore()
{
    return totalScore;
}

void Alice::setTreasureScore(int points)
{
    treasureScore = points;
}

int Alice::getTreasureScore()
{
    return treasureScore;
}

void Alice::setFriendshipScore(int points)
{
    friendshipScore = points;
}

int Alice::getFriendshipScore()
{
    return friendshipScore;
}

void Alice::setHitPoints(int hp)
{
    hitPoints = hp;
}

int Alice::getHitPoints()
{
    return hitPoints;
}

void Alice::setMaxAttackDamage(int a)
{
    maxAttackDamage = a;
}

int Alice::getMaxAttackDamage()
{
    return maxAttackDamage;
}

// Increases the players attack damage
void Alice::increaseAttackDamage(int increaseAmount)
{
    maxAttackDamage += increaseAmount; 
}

// Updates the players total friendship score
void Alice::updateFriendshipScore(std::vector<Character>& characters)
{
    friendshipScore = 0;

    for (Character& character : characters)
    {
        friendshipScore += character.getFriendshipScore();
    }
}

// Adds addition points to the existing treasure score
void Alice::addToTreasureScore(int pointsToAdd)
{
    treasureScore += pointsToAdd;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Utility functions of the Alice class
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Displays the players total score
void Alice::displayTotalScore()
{
    updateTotalScore();
    std::cout << "Total Friendship Score: " << friendshipScore << " \\ 400\n";
    std::cout << "Total Treasure Score: " << treasureScore << " \\ 2100\n";
    std::cout << "Final Score: " << getTotalScore() << " \\ 2500\n";
}


/*******************************************************************************************************************************************************************************************
* The Inventory Class
* Stores items that have been added to the inventory
* Implements functions to manage the item inventory
*******************************************************************************************************************************************************************************************/

//Default Constructor
Inventory::Inventory()
{
    inventory.clear(); // Clears the inventory vector
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Accessor and Mutator functions of the Inventory class
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

std::vector<Item> Inventory::getInventory()
{
    return inventory;
}


//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// inventory vector management functions of the Inventory class
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Adds an item to the inventory vector
void Inventory::addToInventory(Item& item)
{
    Item itemCopy = item;
    inventory.push_back(itemCopy);

    // Checks if the item should be respawned 
    if (item.getCanRespawn())
    {
        item.setRespawn(true); // Sets the respawn attribute to true
    }
    else
    {
        item.setRespawn(false); // Sets the respawn attribute to false
    }
}

// Removes an item from the inventory vector
void Inventory::removeFromInventory(Item item)
{
    if (isValidItem(item)) // Checks the item is in the inventory and it is not null item
    {
       // Finds and erases the specifed item
       inventory.erase(find(inventory.begin(), inventory.end(), item)); //https://www.geeksforgeeks.org/how-to-remove-an-element-from-vector-in-cpp/
    }
    else
    {
        std::cout << item.getName() << " is not an item in your inventory" << std::endl;
    }
}

// Searches the inventory vector for the specifed item
Item Inventory::searchInventory(Item& item)
{
    for (int index = 1; index < inventory.size(); index++)
    {
        if (item == inventory[index])
        {
            return inventory[index];
        }
    }
    return inventory[NullItem]; // The first element is NullItem
}

// Checks if the specifed item is in the inventory
bool Inventory::isInInventory(Item& item)
{
    for (int index = 1; index < inventory.size(); index++)
    {
        if (item == inventory[index])
        {
            return true;
        }
    }
    return false;
}

// Checks if an item is valid (in inventory and not null)
bool Inventory::isValidItem(Item& item)
{
    if (isInInventory(item) && item != inventory[NullItem])
    {
        return true;
    }

    return false;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Inventory sort functions of the Inventory class
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Compares items by item type
bool Inventory::compareByItemType(Item& a, Item& b)
{
    //Define how to sort items by type
    return a.getItemType() < b.getItemType();
}

// Sorts inventory vector by item type
void Inventory::sortByItemType() //Source https://www.geeksforgeeks.org/comparator-in-cpp/
{
    // Sort the inventory vector using the compareByItemType function
    std::sort(inventory.begin(), inventory.end(), compareByItemType);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Utility functions of the Inventory class
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Print the contents of the inventory 
void Inventory::displayInventory()
{
    // Sorts inventory by the item type
    sortByItemType();
    
    // Checks that the inventory is not empty
    if (inventory.size() != 1)
    {
        // Prints the contents of the inventory
        for (int index = 1; index < inventory.size(); index++)
        {
            std::cout << inventory[index].getName() << "\n";
            std::cout << "\tItem Type: " << inventory[index].itemTypeToString() << "\n";
            std::cout << "\tDescription: " << inventory[index].getLongDescription() << "\n";
        }
    }
    else
    {
        std::cout << "Inventory empty.\n";
    }
}