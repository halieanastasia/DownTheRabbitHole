//: Characters.h
/*
Title:        Characters.h
Description:  This header file declares the Character class, which is derived from GameObject 
				and represent different characters in the text-adventure game. Each character
				maintains friendship score, hit points, attack damage, and a vector of items
				indicating their gift preferences.
Date:         December 15, 2025
Author:       Halie Favron
Student ID:   3673820
Version:      1.0
Copyright:    2024 Halie Favron
*/

/*
DOCUMENTATION

File Purpose:
	- This file is part of a larger text-adventure game.
	- The 'Character' class inherits from 'GameObject' and includes data and methods
	  for managing a character's friendship level, health, attack power, and gift item preferences.
	- It also allows characters to receive gifts, adjust friendship points, and determine if they
	  are considered a friend to the player.

Compile (assuming g++ is installed):
	g++ -o main Actions.cpp Alice.cpp Characters.cpp Control.cpp FileReader.cpp Game.cpp GameObject.cpp Items.cpp Locations.cpp main.cpp Utilities.cpp
Execution (assuming your terminal is Windows Command Prompt):
	main.exe

Compile Note:
	Ensure all files are being properly compiled or errors will occur
*/

#pragma once
#include "GameObject.h"

// Forward declarations
class Item;
class Alice;

class Character : public GameObject
{
private:
	// Attributes
	int friendshipScore;
	int hitPoints;
	int maxAttackDamage;

	//Considering adding a feature where each player has different likes/ dislikes see notebook for implementation
	std::vector<Item> giftItemValue; // Stores items from least liked to most liked 

public:
	int FRIEND = 0;
	int MAX_GIFT_VALUE = 40;
	int GIFT_VALUE_DECREASE = 10;

	int	LOWEST_FRIENDSHIP = -40;
	int HIGHEST_FRIENDSHIP = 40;
	
	// Constructors
	Character();

	// Equals operator overload
	bool operator == (Character character2);

	// Accessor and Mutator functions

	void setFriendshipScore(int points);
	int getFriendshipScore();

	void setHitPoints(int hp);
	int getHitPoints();

	void setMaxAttackDamage(int a);
	int getMaxAttackDamage();

	// Adds an item to the giftItemValue vector
	void addToGiftItemValue(Item item);

	// Returns the giftValue of the item at the specified index 
	int getGiftItemValue(Item gift);

	// Gets the most liked gift of a character
	std::string getMostLikedGift();

	// Sets the giftValue's of items specific to the characters giftItemValue vector
	// The giftItem vector stores items from least liked to most liked 
	void setGiftItemValues();

	// Adds gift points to friendshipPoints
	void receiveGift(Item gift);

	// Checks if the character is considered a friend
	bool isCharacterFriend();

	// Prints the attributes of a Character object
	void print();
};