//: Control.h
/*
Title:        Control.h
Description:  This header file declares the Control class, which manages user interactions
				and input parsing for the text-adventure game. It reads user commands, checks
				them against the defined actions, and interprets them accordingly.
Date:         February 5, 2025
Author:       Halie Favron
Student ID:   3673820
Version:      1.0
Copyright:    2025 Halie Favron
*/

/*
DOCUMENTATION

File Purpose:
	- The Control class manages the user interface for input collection and parsing.
	- It converts raw user input into recognizable game commands by mapping input tokens
		to keywords, verbs, characters, locations, items, and directions

Compile (assuming g++ is installed):
	g++ -o main Actions.cpp Alice.cpp Characters.cpp Control.cpp FileReader.cpp Game.cpp GameObject.cpp Items.cpp Locations.cpp main.cpp Utilities.cpp
Execution (assuming your terminal is Windows Command Prompt):
	main.exe

Compile Note:
	Ensure all files are being properly compiled or errors will occur
*/

/*******************************************************************************************************************************************************************************************
* The Control Class
* Manages the input user interface
*******************************************************************************************************************************************************************************************/
#pragma once
#include "Actions.h"

class Control //Control class change before submitting 
{
private:
	// Attributes
	Actions action;

public:
	// Constructor
	Control() { };

	// Accessor and mutator functions
	void setAction(Actions a);
	Actions getAction();

	// Input processing functions
	std::string getInputFromUser();
	std::array<int, 6> parseUserInput();

	// Displays all potential actions to the user
	void displayPotentialActions(); 
};