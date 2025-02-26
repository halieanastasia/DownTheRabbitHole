//: Character.cpp
/*
Title:        Character.cpp
Description:  This source file implements the Character class,  which is derived from GameObject 
				and represent individual characters in the text-adventure game.
				It handles friendship scoring, hit points, attack damage, and gift mechanics.
Date:         December 15, 2024
Author:       Halie Favron
Student ID:   3673820
Version:      1.0
Copyright:    2024 Halie Favron
*/

/*
DOCUMENTATION

Program Purpose:
	- This file manages the logic for non-player characters (NPCs) in a
	  text-adventure game, including how they respond to gifts and how
	  their friendship score or hostility is determined.

Compile (assuming g++ is installed):
	g++ -o main Actions.cpp Alice.cpp Characters.cpp Control.cpp FileReader.cpp Game.cpp GameObject.cpp Items.cpp Locations.cpp main.cpp Utilities.cpp
Execution (assuming your terminal is Windows Command Prompt):
	main.exe

Compile Note:
	Ensure all files are being properly compiled or errors will occur

Notes:
	- Derived from GameObject class
*/

#include "Characters.h"
#include "Items.h"

#include <iostream>

/*******************************************************************************************************************************************************************************************
* The Character Class
* Derived From Game Object
* Represents individual characters in the game
*******************************************************************************************************************************************************************************************/

// The Default Constructor for the Character class
Character::Character()
{
	friendshipScore = 0;
	hitPoints = 0;
	maxAttackDamage = 0;

}

// Equals operator overload
bool Character::operator==(Character character2)
{
	if (getName() == character2.getName())
	{
		return true;
	}
	
	return false;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Accessor and Mutator functions of the Character class
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Character::setFriendshipScore(int points)
{
	// Validate that the friendshipScore is within the limits (-120 to 120)
	if (points < LOWEST_FRIENDSHIP || points > HIGHEST_FRIENDSHIP)
	{
		if (points < LOWEST_FRIENDSHIP)
		{
			points = LOWEST_FRIENDSHIP;
		}
		else if (points > HIGHEST_FRIENDSHIP)
		{
			points = HIGHEST_FRIENDSHIP;
		}
	}
	friendshipScore = points;
}

int Character::getFriendshipScore()
{
	return friendshipScore;
}

void Character::setHitPoints(int hp)
{
	hitPoints = hp;
}

int Character::getHitPoints()
{
	return hitPoints;
}

void Character::setMaxAttackDamage(int a)
{
	maxAttackDamage = a;
}

int Character::getMaxAttackDamage()
{
	return maxAttackDamage;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Gift mechanic functions of the Character class
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


// Checks if the character is considered a friend
bool Character::isCharacterFriend()
{
	// restructure to decide when friendship points reach a certain integer for the character to become an enemy
	if (friendshipScore >= FRIEND)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Adds an item to the giftItemValue vector
void Character::addToGiftItemValue(Item item)
{
	giftItemValue.push_back(item);
}

// Returns the giftValue of the item at the specified index 
int Character::getGiftItemValue(Item gift)
{
	int index = searchVectorOfGameObject(giftItemValue, gift);
	
	if (index != -1)
	{
		return giftItemValue[index].getGiftValue(); // Returns the giftValue of the item at the specified index 
	}
	else
	{
		return -1;
	}
}

// Gets the most liked gift of a character
std::string Character::getMostLikedGift()
{
	return giftItemValue[0].getName();
}

// Sets the giftValue's of items specific to the characters giftItemValue vector
// The giftItem vector stores items from least liked to most liked 
void Character::setGiftItemValues()
{
	// Figure out how much points should start at and how much it should be decremented 
	int points = MAX_GIFT_VALUE;
	for (Item& item : giftItemValue) // giftItemValue stores items from least liked to most liked 
	{
		if (points != 0) // Skip points being equal to 0 
		{
			item.setGiftValue(points);
			points -= GIFT_VALUE_DECREASE; // Subtract GIFT_VALUE_DECREASE (10) from points so that items that are liked are worth more friendshipPoints than items that are less liked 
		}
		else // Skip directly to -10
		{
			points -= GIFT_VALUE_DECREASE;
			item.setGiftValue(points);
			points -= GIFT_VALUE_DECREASE; 
		}
	}
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Utility functions of the Character class
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Adds gift points to friendshipPoints
void Character::receiveGift(Item gift)
{
	int giftPoints = 0;
	int index = 0;

	std::string reaction;
	
	index = searchVectorOfGameObject(giftItemValue, gift);
	
	// Adds the gift points to the character's friendship score
	if (index != -1)
	{
		giftPoints = giftItemValue[index].getGiftValue();
		
		// Sets the characters reaction based on the gift value of the individual character
		if (giftPoints == MAX_GIFT_VALUE)
		{
			reaction = "Thank You! I love this!";
		}
		else if (giftPoints < MAX_GIFT_VALUE && giftPoints > 0)
		{
			reaction = "Thank You! I like this!";
		}
		else if (giftPoints > -40 && giftPoints < 0)
		{
			reaction = "I don't like this.";
		}
		else if (giftPoints == -40)
		{
			reaction = "I HATE this!";
		}

		// Updates the character's friendship score
		int newScore = friendshipScore + giftPoints;
		setFriendshipScore(newScore);
		std::cout << reaction << "\n";
	}
	// This statement should be impossible to reach but added just in case
	else
	{
		std::cout << "This gift does not seem to make a difference what-so ever to your friendship\n";
	}
}

// Prints the attributes of a Character object
void Character::print()
{
	GameObject::print();
	std::cout << "HP: " << hitPoints << "\n";
	std::cout << "Max Attack Damage: " << maxAttackDamage << "\n";
	std::cout << "Friendship Score: " << friendshipScore << "\n";
}

