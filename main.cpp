//: main.cpp
/*
Title:        main.cpp
Description:  This program is the main entry point to a text-adventure style game based on Alice's Adventures in Wonderland by Lewis Carrol (1865)
Date:         December 15, 2024
Author:       Halie Favron
Student ID:   3673820
Version:      1.0
Copyright:    2024 Halie Favron
*/

/*
DOCUMENTATION

Program Purpose:
	- The program initializes the "Game" object and starts gameplay.

Compile (assuming g++ is installed):
	g++ -o main Actions.cpp Alice.cpp Characters.cpp Control.cpp FileReader.cpp Game.cpp GameObject.cpp Items.cpp Locations.cpp main.cpp Utilities.cpp
Execution (assuming your terminal is Windows Command Prompt):
	main.exe

Compile Note:
	Ensure all files are being properly compiled or errors will occur

Notes:
	- All source code must be compiled in order for the game to run
		Actions.cpp 
		Alice.cpp 
		Characters.cpp 
		Control.cpp 
		FileReader.cpp 
		Game.cpp 
		GameObject.cpp
		Items.cpp 
		Locations.cpp
		main.cpp 
		Utilities.cpp
*/

/*
TEST PLAN

*******************************************************************************************************************************************************************************************
* Normal Cases
*******************************************************************************************************************************************************************************************

Normal Case 1 (Game Initialization and Start):
	[The game correctly initializes and starts at the meadow]
	[No input needed]

	>You wake up in a meadow filled with wildflowers and tall grass.
	>You look around for your sister but she is nowhere to be found.
	>Just when you begin to wake up, a white rabbit runs by muttering about the time...

Normal Case 2 (Valid Pick Up Action)
	> pick up marmalade jar
	You found a broken jar of marmalade

Normal Case 3 (Valid Treasure Action):
	> store daisy-crown
	The treasure has been placed in the cottage

Normal Case 4 (Valid Use Item Action):
	> eat the eat-me cake
	You start to grow and cry, your tears begin to trickle towards the crack in the south wall
	
	> drink drink-me bottle
	You shrink back down to size, maybe you can fit through the crack in the wall now

Normal Case 5 (Valid Gifting Action)
	> give the milk to the Cheshire cat
	You give The Cheshire Cat the Milk

Normal Case 6 (Valid Talk):
	> talk to the Cheshire cat
	You start talking to The Cheshire Cat...

	> talk to the white rabbit
	We're all mad here. I'm mad. You're mad..
	Please pass the sugar.

Normal Case 7 (Valid Fight):
	> fight Cheshire cat
	The fight begins...

Normal Case 8 (Valid Enter Actions):
	> follow rabbit
	You follow the rabbit, until you see a rabbit hole...

	> go east
	You are in a long hallway with a door on each wall...

Normal Case 9 (Valid Explore Actions):
	> explore
	You are in the bottom of a deep dark rabbit hole...

Normal Case 10 (Valid Unlock Actions):
	> unlock north door
	You unlock the northern exit

Normal Case 11 (Capitalization is insignificant):
	> Go NoRtH
	You are in a little clearing in-front of a large modge-podge of colourful rooms

Normal Case 12 (Display Inventory):
	> inventory
	Daisy Crown
			Item Type: Treasure
			Description: A daisy crown made by your sister and placed upon your head while you were sleeping

Normal Case 13 (Help):
	> help
	This game works by reading your input.

Normal Case 14 (End Game):
	> end game
	Are you sure you want to end the game? (Yes/No)
	...
	> no
	Returning to the game

	> end game
	Are you sure you want to end the game? (Yes/No)
	...
	> yes
	Ending the game...
	Final stats...

Normal Case 15 (Hint):
	> hint
	You really should try to make some friends

Normal Case 16 (Valid Examine Item):
	[Player examines an item in their inventory]
	> examine daisy-chain
		Item: Daisy Crown
		Item Type: Treasure
		Description: A daisy crown made by your sister and placed upon your head while you were sleeping
	
	[Player stores an item in the cottage then examines it]
	> store daisy-chain
	The treasure has been placed in the cottage
	Treasure Inventory:
	Daisy Crown
			Item Type: Treasure
			Description: A daisy crown made by your sister and placed upon your head while you were sleeping

	What do you want to do next?
	> examine daisy-chain
	Item: Daisy Crown
	Item Type: Treasure
	Description: A daisy crown made by your sister and placed upon your head while you were sleeping
	
*******************************************************************************************************************************************************************************************
* Bad Data Cases
*******************************************************************************************************************************************************************************************

Bad Data Case 1 (Invalid Input Command):
	[The game handles invalid input without crashing]
	> asdf
	Please try rephrasing your input

Bad Data Case 2 (Invalid Pick Up Actions)
	[The game prevents invalid pick up actions]

	[The game requires the player to specify the item to pick up]
	> pick up
	You must specify an item to pick up

	[The game requires the item to be in the current location]
	> pick up milk
	There is no Milk in this location, try picking up something else

Bad Data Case 3 (Invalid Treasure Actions):
	[The game prevents invalid store treasure actions]

	[The game only lets players store items of item type Treasure]
	> place milk
	milk is not considered a treasure, you can only place treasure in the cottage

	[The game requires the player to specify the item to store]
	place
	You must specify what you would like to place in the cottage

	[The player cannot store Treasure while outside the Cottage]
	> place daisy crown
	Treasure cannot be placed here, you must return to your cottage

Bad Data Case 4 (Invalid Use Item Actions):
	[The game prevents invalid item actions]

	[Players cannot use items that are not in their inventory]
	> use pocket watch
	Pocket Watch is not in your inventory

	[The game requires the player to specify which item to use]
	> use
	You must specify what item you would like to use.

Bad Data Case 5 (Invalid Gifting Actions)
	[The game prevents incomplete or incorrect gift attempts]

	[The game requires the player to specify which character to give gift to]
	> give milk
	You must specify who you would like to give a gift to.

	[The game requires the player to specify which item to gift]
	> give cat
	You must specify the item you would like to give.

	[The game requires the character to be in the current location]
	> give cat milk
	The Cheshire Cat is not in the location

	[The game requires the item to be gifted, be in the players inventory]
	> give rabbit milk
	Milk is not in your inventory

Bad Data Case 6 (Talking to Non-Present Characters):
	[In order to talk to a character the characters must be in the current location]
	> talk to rabbit
	White Rabbit is not in the location

Bad Data Case 7 (Fighting a Non-Present Characters):
	[In order to fight a character the characters must be in the current location]
	> fight rabbit
	You can't fight a character that is not in the location

Bad Data Case 8 (Invalid Enter Actions):
	[The game prevents invalid movement actions]
	> go up
	You need to specify a direction
	> go north
	There is no exit in the direction you specified

	[The game only remembers the most current action word]
	> go south talk to rabbit
	"I am very late", the rabbit exclaims.

	[Players can not enter locked doors]
	> go south
	You are unable to go this way right now
	You need to unlock it with the Garden key

Bad Data Case 9 (Invalid Explore Actions):
	[The game prevents users from exploring locations other than the current location]
	> explore garden
	You can only explore areas where you are currently located

Bad Data Case 10 (Invalid Unlock Actions):
	[The game prevents invalid movement actions]

	[The player must specify which direction to unlock]
	> unlock garden door
	You must specify the direction

	[The key must be in the players inventory]
	> unlock south
	You need the Mushroom Forest Key to unlock this exit 

Bad Data Case 11 (A file is missing or not loaded correctly):
	[The game fails to initialize and exits the game]

	[Locations.txt file is miss spelled or missing]
	The Location.txt file could not be opened, ending the game...

	[the Locations.txt is found but no characters and present]
	No locations have been loaded from the game files, ending the game...

	[A game object (Character, Item, Location) is missing critical data]
	Invalid line format for label: "Name" with value: ""
	A game object was loaded with incomplete data, this is a terminal error, ending the game...

Bad Data Case 11 (Invalid Examine Item):
	[The player attempts to examine an item that is not in their inventory or in the current location]

Win Input Sequence (Fastest win scenario)
	**See external file: "SpeedRunOutput.txt"**
Normal Input Sequence (Normal win scenario)
	**See external file: "NormalPlaythroughTest.txt"**
	Includes the command window log of a normal wiining playtrough, with some invalid inputs to demonstrate robust input validation
*/

#include "Game.h"

int main()
{
	// Instantiates a Game object
	Game game;

	// Starts the game
	game.gameplay();
}