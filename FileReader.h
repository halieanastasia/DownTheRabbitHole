//: FileReader.h
/*
Title:        FileReader.h
Description:  This source file declares free functions that provide a templated approach to reading and parsing data
				 for Characters, Items, and Locations from text files. It specializes generic
				 functions to handle attributes unique to each game object type.
Date:         December 17, 2024
Author:       Halie Favron
Student ID:   3673820
Version:      1.0
Copyright:    2024 Halie Favron
*/

/*
DOCUMENTATION

Program Purpose:
	- This file provides utilities to read data from external text files (e.g., Characters.txt,
	  Items.txt, Locations.txt) and populate corresponding game object vectors.
	- It leverages templates for shared parsing logic, while using specializations to handle
	  unique attributes for Characters, Items, and Locations.

Compile (assuming g++ is installed):
	g++ -o main Actions.cpp Alice.cpp Characters.cpp Control.cpp FileReader.cpp Game.cpp GameObject.cpp Items.cpp Locations.cpp main.cpp Utilities.cpp
Execution (assuming your terminal is Windows Command Prompt):
	main.exe

Compile Note:
	Ensure all files are being properly compiled or errors will occur
*/

#pragma once
#include <string>
#include <vector>

/*******************************************************************************************************************************************************************************************
* Free Functions for Game Object Creation
*******************************************************************************************************************************************************************************************/

// Forward declarations
class Character;
class Location;
class Item;

// Default Specialization
template <typename T>
void getSpecializedAttributes(const std::string& label, const std::string& value, T& t);

// Specialization for Character
template<>
void getSpecializedAttributes<Character>(const std::string& label, const std::string& value, Character& t);

// Specialization for Location
template<>
void getSpecializedAttributes<Location>(const std::string& label, const std::string& value, Location& location);

// Specialization for Item
template<>
void getSpecializedAttributes<Item>(const std::string& label, const std::string& value, Item& item);


// Checks the label and store the data in the appropriate field
template <typename T>
void parseField(const std::string& label, const std::string value, T& t);

// Populates the gameObjectSet vector with data from a file
template <typename T>
std::vector<T> getGameObjectSetFromFile(const std::string& filename);

