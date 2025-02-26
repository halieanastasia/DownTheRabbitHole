#pragma once
//: GameEnums.h
/*
Title:        GameEnums.h
Description:  This file contains the global Enums for managing all the actions an input throughout the game as well as used in specific functions
Date:         January 10, 2025
Author:       Halie Favron
Student ID:   3673820
Version:      1.0
Copyright:    2025 Halie Favron
*/

/*
DOCUMENTATION

Program Purpose:
	- Global Enums for managing all the actions an input throughout the game as well as used in specific functions

Compile (assuming g++ is installed):
	g++ -o main Actions.cpp Alice.cpp Characters.cpp Control.cpp FileReader.cpp Game.cpp GameObject.cpp Items.cpp Locations.cpp main.cpp Utilities.cpp
Execution (assuming your terminal is Windows Command Prompt):
	main.exe

Compile Note:
	Ensure all files are being properly compiled or errors will occur

Notes:
	- GameEnums.h does not have an accompanying cpp file
*/

/*******************************************************************************************************************************************************************************************
* Global Enums for managing all the actions an input throughout the game, as well as used in specific functions
* Enum Action Index for accessing the elements of the currentAction array
* Enums used for categorizing the action maps: Keywords, Verbs, Characters, and Directions
* Enums for accessing the elements of the Character, Location, and Item vectors
* Enum to manage Item Types
*******************************************************************************************************************************************************************************************/

// Enum for accessing the elements of the currentAction array 
enum ActionIndex { K = 0, V, C, L, I, D };

// Enums used for categorizing the action maps
enum Keywords { NullKeyword = -1, Yes, No, Help, End, PlayerInventory, Hint, Stats };
enum Verbs { NullVerb = -1, Enter, PickUp, Follow, Use, Unlock, Give, Talk, Explore, Examine, Attack, PlaceTreasure };
enum Directions { NullDirection = -1, North, NorthEast, East, SouthEast, South, SouthWest, West, NorthWest };

// Enums for accessing the elements of the Character, Location, and Item vectors
enum Characters { NullCharacter = 0, CheshireCat, Queen, MadHatter, MarchHare, WhiteRabbit, Caterpillar, Duchess, Soldier, Gryphon, MockTurtle};
enum Locations { NullLocation = 0, Meadow, RabbitHole, LongHallway, Cottage, MushroomForest, HaresLawn, PoolOfTears, IsleOfSorrow, Garden, Castle };
enum Items { NullItem = 0, GardenKey, CottageKey, MushroomKey, Milk, Butter, FauxSoup, PocketWatch, KidGloves, PaintedRose, Tart, Spectacles, DaisyChain, LookingGlass, MusicBox, Fan, Hookah, Hedgehog, GuineaPig, Teapot, CourtierDiamond, KingsCrown, HattersHat, DrinkMeBottle, EatMeCake, MarmaladeJar, AncientSword };

// Enum to manage Item Types
enum ItemType { NullItemType = -1, Key, Gift, Treasure, KeyItem, Weapon };
