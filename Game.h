//: Game.h
/*
Title:        Game.h
Description:  This header file declares the Game class, which runs the gameplay loop until the player ends the game or loses
				It is part of a text-adventure game inspired by "Alice’s Adventures in Wonderland" by Lewis Carroll.
				It handles loading game data (characters, items, locations), managing the player's current
				location, detecting user actions, and executing game events.
Date:         December 16, 2024
Author:       Halie Favron
Student ID:   3673820
Version:      1.0
Copyright:    2024 Halie Favron
*/

/*
DOCUMENTATION

Program Purpose:
	- The Game class manages critical logic for the adventure game, including:
	  1) Loading data and validating that objects are present (Characters, Locations, Items).
	  2) Running the main game loop, prompting user input, and responding to actions.
	  3) Tracking the player's current location, inventory, and overall progress.
	  4) Handling combat, items, exploration, and movement through exits.

Compile (assuming g++ is installed):
	g++ -o main Actions.cpp Alice.cpp Characters.cpp Control.cpp FileReader.cpp Game.cpp GameObject.cpp Items.cpp Locations.cpp main.cpp Utilities.cpp
Execution (assuming your terminal is Windows Command Prompt):
	main.exe

Compile Note:
	Ensure all files are being properly compiled or errors will occur
*/

#pragma once
#include "Characters.h"
#include "Items.h"
#include "Locations.h"
#include "Actions.h"
#include "Alice.h"
#include "Control.h"

#include <vector> 
#include <array>

class Game
{
private:
	const int WIN_SCORE = 2500;
	
	// Player instance keeps track of player stats and scores
	Alice alice;

	// Stores all possible input actions
	Actions actions;

	// Control object to control the user input
	Control c;

	// Stores the parsed current action: [Keyword, Verb, Character, Location, Item, Direction]
	std::array<int, 6> currentAction;

	// Stores the characters at the current location
	std::vector<Character*> charactersAtLocation;

	// Stores the items at the current location
	std::vector<Item*> itemsAtLocation;

	// Vectors to store all possible game objects
	std::vector<Character> characters;
	std::vector<Location> locations;
	std::vector<Item> items;

	// Stores the current location
	Location* currentLocation;

	// Stores the items that have been collected
	Inventory playerInventory;
	Inventory treasureInventory;

	// Checks if the Pool of Tears has been filled
	bool poolIsFull;

	// End of game condition
	bool endGame;
	bool win;

public:
	// Default Constructor
	Game();

	// Game Builder Functions
	void loadGame();
	void checkObjectsLoaded();

	// Gameplay Loop
	void gameplay();

	// Location functions 
	void meadow(); // The location where the player starts
	void enterRabbitHole();
	void enterLongHallway();
	void enterCottage();
	void enterHaresLawn();
	void enterMushroomForest();
	void enterPoolOfTears();
	void enterIsleOfSorrow();
	void enterGarden();
	void enterCastle();

	// Location Builder Functions
	void loadCurrentLocation();
	void loadLocationObjects(std::vector<Character*> charactersAtLocation, std::vector<Item*> itemsAtLocation);
	void clearLocationObjects();

	// Current Location Item Management Functions
	void setItemsAtLocation(std::vector<Item*> i);
	void removeItemFromRoom(Item& item);
	bool isItemAtLocation(Item& item);

	// Current Location Character Management Functions
	void setCharactersAtLocation(std::vector<Character*> c);
	void removeCharacterFromRoom(Character& character);
	bool isCharacterInRoom(Character& character);

	// Random Function
	int getRandomInt(int min, int max);

	// Random Item Function
	std::vector<Item*> getRandomItems(int numItems, ItemType type);

	// Random Character Function
	std::vector<Character*> getRandomCharacters(int numCharacters);

	// Common Action Check Functions
	bool commonActionChecks();
	bool checkInvalidAction();

	// Player Related Action Check Functions
	bool checkDisplayInventory();
	bool checkDisplayStats();
	bool checkHelp(); 
	bool checkEndGame(); 
	bool checkPlayerWin();

	// Item Related Action Check Functions
	int checkPickUpItem();
	bool checkStoreTreasure();
	int checkUseItem();
	bool checkExamineItem();

	// Character Related Action Check Functions
	bool checkGiveGift();
	int checkTalkToCharacter();
	int checkFight();

	// Location Related Action Check Functions
	bool checkEnter();
	bool checkExplore();
	bool checkUnlockExit();
	bool checkHint();

	// Item Event Functions
	void pickUpItem(Item& item);
	void storeTreasure(Item& item);
	void examineItem(Item& item);

	// Character Event Functions
	void giveGift(Item item, Character& character);
	bool talkToCharacter(int character);
	bool fight(Character& character);

	// Location Event Functions
	bool enterExit(int direction);
	void unlockExit(Exit& exit);
	void exploreLocation();
	bool croquetOutcome();

	// Current Action Functions
	void setCurrentAction(std::array<int, 6> a); // Used for initializing currentAction and for debugging/ hard coding a path for testing
	void setCurrentAction();
	std::array<int, 6> getCurrentAction();
	void resetCurrentAction();

	// Current Location Functions
	void setCurrentLocation(Location* location);
	Location getCurrentLocation();
	std::string getCurrentLocationDescription();

	// Display Functions
	void displayFinalStats();
	void displayInputInstructions(); 
	void displayInventory();
	void displayStats();

	// Test if the current action element matches the value passed
	bool matches(Keywords keyword);
	bool matches(Verbs verb);
	bool matches(Characters character);
	bool matches(Locations location);
	bool matches(Items item);
	bool matches(Directions direction);
};