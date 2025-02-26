//: Game.cpp
/*
Title:        Game.cpp
Description:  This source file implements the Game class, which runs the gameplay loop until the player ends the game or loses
				It is part of a text-adventure game inspired by "Alice’s Adventures in Wonderland" by Lewis Carroll.
				It handles loading game data (characters, items, locations), managing the player's current
				location, detecting player actions, and executing game events.
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
	  2) Running the main game loop, prompting player input, and responding to actions.
	  3) Tracking the player's current location, inventory, and overall progress.
	  4) Handling combat, items, exploration, and movement through exits.

Compile (assuming g++ is installed):
	g++ -o main Actions.cpp Alice.cpp Characters.cpp Control.cpp FileReader.cpp Game.cpp GameObject.cpp Items.cpp Locations.cpp main.cpp Utilities.cpp
Execution (assuming your terminal is Windows Command Prompt):
	main.exe

Compile Note:
	Ensure all files are being properly compiled or errors will occur
*/

#include "Game.h"
#include "FileReader.h"
#include "alice.h"
#include "GameEnums.h"

#include <chrono>
#include <thread>
#include <random>
#include <algorithm>

/*******************************************************************************************************************************************************************************************
* The Game Class
* Implements the gameplay and assisting functions
*******************************************************************************************************************************************************************************************/

// Default Constructor
Game::Game() 
{
	// Initializes the attributes of the Game class 
	loadGame();
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Game Builder Functions
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Initializes the attributes of the Game class 
void Game::loadGame()
{
	// Player instance keeps track of player stats and scores
	Alice alice;
	
	// Reads all possible input actions from file
	const std::string actionFileName = "Actions.txt";
	Actions actions(actionFileName);

	// Sets the action attribute of the games instance of the control class 
	c.setAction(actions);

	// Sets the current action to null
	setCurrentAction({ Keywords::NullKeyword, Verbs::NullVerb, Characters::NullCharacter, Directions::NullDirection });
	
	// Clears the characters at the current location
	charactersAtLocation.clear();

	// Clears the items at the current location
	itemsAtLocation.clear();

	// Populates the characters vector with data from the "Characters.txt" file
	const std::string characterFile = "Characters.txt";
	characters = getGameObjectSetFromFile<Character>(characterFile);

	// Populates the locations vector with data from the "Locations.txt" file
	const std::string locationFile = "Locations.txt";
	locations = getGameObjectSetFromFile<Location>(locationFile);

	// Populates the items vector with data from the "Items.txt" file
	const std::string itemFile = "Items.txt";
	items = getGameObjectSetFromFile<Item>(itemFile);

	// Checks that all game objects were loaded correctly
	checkObjectsLoaded();

	// Sets the current location to The Meadow (Starting location)
	setCurrentLocation(&locations[Meadow]);

	// Adds NullItem to both inventories
	playerInventory.addToInventory(items[NullItem]);
	treasureInventory.addToInventory(items[NullItem]);

	// Initializes the pool is full condition to false
	poolIsFull = false;

	// Initializes the end game conditions to false
	endGame = false;
	win = false;
}

// Checks that all game objects were loaded correctly
void Game::checkObjectsLoaded()
{
	try
	{
		Character test = characters.at(NullCharacter); // Source: https://cplusplus.com/forum/beginner/170060/
	}
	catch (const std::out_of_range& e)
	{
		std::string errorMessage = "No characters have been loaded from the game files, ending the game...";
		criticalError(errorMessage); 
	}
	try
	{
		Location test = locations.at(NullLocation);
	}
	catch (const std::out_of_range& e)
	{
		std::string errorMessage = "No locations have been loaded from the game files, ending the game...";
		criticalError(errorMessage); 
	}
	try
	{
		Item test = items.at(NullItem);
	}
	catch (const std::out_of_range& e)
	{
		std::string errorMessage = "No items have been loaded from the game files, ending the game...";
		criticalError(errorMessage);
	}
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Gameplay Loop
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Starts the gameplay loop until the player ends the game / loses/ or wins
void Game::gameplay()
{
	// Start game
	std::cout << "Welcome to a text adventure game based on Alice's Adventures in Wonderland by Lewis Carroll (1865)\n";
	std::cout << "\tType H or Help for instructions\n";
	std::cout << "\tType Q or Quit to end game\n\n";
	std::this_thread::sleep_for(std::chrono::seconds(3));

	std::cout << "Starting game...\n\n";
	std::this_thread::sleep_for(std::chrono::seconds(1));

	// Loops until the player ends/ loses/ or wins
	while(!endGame)
	{
		// Loads the current location of the player
		loadCurrentLocation(); 
	}
	
	// Checks if the player has won
	if (win)
	{
		std::cout << "\nYou have befriended every character and collected and stored every treasure.\n";
		std::cout << "You have also managed to survive all of the trials of wonderland.\n\n";

		std::cout << "You wake up feeling well rested with your head in your sisters lap, as she braids daisy into your hair.\n";
		std::cout << "You feel a great sense of accomplishment.\n";
	}

	// Displays the players final stats at the end of the game
	displayFinalStats();
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Location Functions
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// The Meadow Location Function
void Game::meadow()
{
	// Checks if the player has entered this location previously
	if (!locations[Meadow].getHasBeenEntered())
	{
		// Carroll p.1-2
		std::cout << "You've just woken up from a long nap in a meadow filled with wildflowers and tall grass."
			<< "\n You look around for your sister but she is no where to be found."
			<< "\n You notice that while you slept she has placed a daisy crown upon your head."
			<< "\n Just when you begin to wake up a white rabbit runs by muttering about the time."
			<< "\n How odd, you think, how does he keep track of the time, surely without thumbs he can't hold a pocket watch properly."
			<< std::endl;
		playerInventory.addToInventory(items[DaisyChain]);
		removeItemFromRoom(items[DaisyChain]);
		locations[Meadow].setHasBeenEntered(true);
	}

	// Loop continues while player is in the Meadow Location or until they end the game
	while (currentLocation == &locations[Meadow] && !endGame)
	{
		// Gets input/ actions from the player
		setCurrentAction();

		if ((matches(Follow) && matches(WhiteRabbit)) || (matches(Enter) && matches(South)))
		{
			// Chronos time to delay print statements
			std::cout << "You follow the rabbit, until you see a rabbit hole.\n";
			std::cout << "You peek over the edge to see if you can see the rabbit\n";
			std::this_thread::sleep_for(std::chrono::seconds(1));							
			std::cout << "Your foot slips and you tumble into the rabbit hole\n";
			std::this_thread::sleep_for(std::chrono::seconds(1));
			std::cout << "You start to fall\n";
			std::this_thread::sleep_for(std::chrono::seconds(1));
			std::cout << "Down\n";
			std::this_thread::sleep_for(std::chrono::seconds(1));
			std::cout << "Down\n";
			std::this_thread::sleep_for(std::chrono::seconds(1));
			std::cout << "Down\n";
			std::this_thread::sleep_for(std::chrono::seconds(1));
			std::cout << "You wonder if you will keep falling forever\n";
			std::this_thread::sleep_for(std::chrono::seconds(1));
			std::cout << "You see a jar of marmalade\n";
			std::this_thread::sleep_for(std::chrono::seconds(1));
			std::cout << "You think about how dangerous it is to leave a glass jar lying about...";
			std::this_thread::sleep_for(std::chrono::seconds(2));
			std::cout << "or is it falling about\n";
			std::this_thread::sleep_for(std::chrono::seconds(2));
			std::cout << "Down\n";
			std::this_thread::sleep_for(std::chrono::seconds(1));
			std::cout << "Down\n";
			std::this_thread::sleep_for(std::chrono::seconds(1));
			std::cout << "Down\n";
			std::this_thread::sleep_for(std::chrono::seconds(1));
			std::cout << "Finally you land in what appears to be a giant cupcake, you are sticky but uninjured.\n";

			currentLocation = &locations[RabbitHole];
		}

		else if (checkTalkToCharacter() == WhiteRabbit)
		{
			if (talkToCharacter(WhiteRabbit))
			{
				std::cout << "\"I am very late\", the rabbit exclaims.\n"; // Carroll p.2
			}
		}

		// There are no items that can be used in this location
		else if (checkUseItem() != NullItem)
		{
			std::cout << "You cannot use that item right now.\n";
		}

		// Action checks that sometimes require customization (included for proper player feedback)
		else if (checkPickUpItem());
		else if (checkFight());
		else if (checkGiveGift());

		// Action checks that are common in each location and require no customization
		else if (commonActionChecks());
	}
}

// The Rabbit Hole Location Function
void Game::enterRabbitHole()
{
	// Checks if the player has entered this location previously
	if (!locations[RabbitHole].getHasBeenEntered()) 
	{
		std::cout << "Maybe you should try exploring the area.\n";
		locations[RabbitHole].setHasBeenEntered(true);
	}
	
	// Loop continues while player is in the Rabbit Hole Location or until they end the game
	while (currentLocation == &locations[RabbitHole] && !endGame)
	{
		// Gets input/ actions from the player
		setCurrentAction();

		if (checkPickUpItem() == MarmaladeJar)
		{
			alice.increaseAttackDamage(10);
			std::cout << "Your max attack damage has increased to " << alice.getMaxAttackDamage() << ".\n";
		}

		// Checks if the player wants to use an item but it can't be used in this location
		else if (checkUseItem() != NullItem)
		{
			std::cout << "You cannot use that item right now\n";
		}
		
		// Action checks that sometimes require customization (included for proper player feedback)
		else if (checkTalkToCharacter());
		else if (checkFight());
		else if (checkGiveGift());

		// Action checks that are common in each location and require no customization
		else if (commonActionChecks());
	}
}

// The Long Hallway Location Function
void Game::enterLongHallway()
{
	// Checks if the player has entered this location previously
	if (!locations[LongHallway].getHasBeenEntered())
	{
		// Tells the player the goal of the game
		std::cout << "On that long fall down the rabbit-hole you've had a minute to process the fact that you may never be able to go home.\n"
			<< "It might be a good idea to try and make some friends.\n" // Goal #1: Make Friends, not enemies
			<< "Maybe if you're luck you will find some treasure.\n";  // Goal #2: Collect treasures and bring them to the cottage/ saferoom
		
		locations[LongHallway].setHasBeenEntered(true);
	}

	// Loop continues while player is in the Long Hallway Location or until they end the game
	while (currentLocation == &locations[LongHallway] && !endGame)
	{
		// Gets input/ actions from the player
		setCurrentAction();

		// Item pick-up target
		int pickUpTarget = checkPickUpItem();

		// Checks if the player tries to talk to the Cheshire Cat
		if (checkTalkToCharacter() == CheshireCat)
		{
			if (talkToCharacter(CheshireCat))
			{
				std::cout << "\"I sure am thirsty\", the cat purrs.\n";
			}
		}

		// Checks if the player tries to give a gift to a character
		else if (checkGiveGift())
		{
			// Checks if the player gives the Cheshire Cat the milk and that they have not yet received the CottageKey
			if ((matches(CheshireCat) && matches(Milk)) && isItemAtLocation(items[CottageKey]))
			{
				std::cout << "It looks like you have befriended the Cheshire Cat.\n";
				std::cout << "They give you a Cottage Key.\n";
				std::cout << "It looks like might unlock the northern exit.\n";
				playerInventory.addToInventory(items[CottageKey]);
				removeItemFromRoom(items[CottageKey]);
			}
		}

		// Checks if the player picks up the carton of milk 
		else if (pickUpTarget == Milk)
		{
			std::cout << "You wonder how anyone would milk a cat, you probably shouldn't drink this.\n";
		}

		// Checks if the player picks up the fan
		else if (pickUpTarget == Fan)
		{
			std::cout << "All you need now is somewhere to keep your treasures safe.\n";
		}

		// Checks if the player tries to fight the Cheshire Cat and wins
		else if (checkFight() == CheshireCat)
		{
			// Checks that the player has already received the CottageKey from the Cheshire Cat
			if (!isItemAtLocation(items[CottageKey])) // If they have the game continues as normal
			{
				std::cout << "Good thing you already obtained the Garden Key from the Cheshire Cat, or you would be in serious trouble.\n";
			}
			else // If they have not, the player dies and the game ends
			{
				std::cout << "Unfortunately you never find your way out and eventually starve to death.\n";
				std::cout << "You have plenty of time to think about how you should have tried to befriend the Cheshire Cat instead.\n";
				endGame = true;
			}
		}

		// There are no items that can be used in this location
		else if (checkUseItem() != NullItem)
		{
			std::cout << "You cannot use that item right now\n";
		}

		// Action checks that are common in each location and require no customization
		else if (commonActionChecks());
	}
}

// The Cottage Location Function: Safe Room
void Game::enterCottage()
{
	// Checks if the player has entered this location previously
	if (!locations[Cottage].getHasBeenEntered())
	{
		std::cout << "You decide to move in\n";
		std::cout << "Maybe you should check your inventory to see if you have collected any treasures you should store here. They will be safe here.\n";
		locations[Cottage].setHasBeenEntered(true);
	}
	
	// Loop continues while player is in the Cottage Location or until they end the game
	while (currentLocation == &locations[Cottage] && !endGame)
	{
		// Gets input/ actions from the player
		setCurrentAction();
		
		// There are no items that can be used in this location
		if (checkUseItem() != NullItem)
		{
			std::cout << "You cannot use that item right now\n";
		}

		// Action checks that sometimes require customization (included for proper player feedback)
		else if (checkPickUpItem());
		else if (checkTalkToCharacter());
		else if (checkFight());
		else if (checkGiveGift());

		// Action checks that are common in each location and require no customization
		else if (commonActionChecks());
	}
}

// The March Hare's Lawn Location Function
void Game::enterHaresLawn()
{
	// Checks if the player has entered this location previously
	if (!locations[HaresLawn].getHasBeenEntered())
	{
		std::cout << "Maybe you should join the tea party, perhaps someone has some useful information.\n";
		locations[HaresLawn].setHasBeenEntered(true);

		locations[LongHallway].getExit(NorthEast).unlock(); // Unlock the exit in the Long Hallway location that leads to the Hare's Lawn
	}
	
	int talkCount = 0; // Used to cycle through a list of character dialogue 

	// Loop continues while player is in the Hare's lawn Location or until they end the game
	while (currentLocation == &locations[HaresLawn] && !endGame)
	{
		// Gets input/ actions from the player
		setCurrentAction();
		int talkTarget = checkTalkToCharacter();

		// Checks if the player tries to talk to a character
		if (talkTarget != NullCharacter) // Checks that the player is trying to talk to a character currently in the location
		{
			// Each time the player talks to a character at the Hare's lawn a cycle of character dialogue is printed
			switch (talkCount)
			{
			case 0:
				if (talkToCharacter(talkTarget))
				{
					std::cout << "\"We're all mad here. I'm mad. You're mad...\"\n"; // Source: Carroll p.76
					std::cout << "Please pass the sugar.\n";
					talkCount++;
				}
				break;

			case 1:
				if (talkToCharacter(talkTarget))
				{
					std::cout << "\"We are all a little mad sometimes...\"\n";
					std::cout << "They take a bow, you are very confused.\n";

					// The second time the player speaks to a character at the Hare's lawn they receive a key
					if (isItemAtLocation(items[MushroomKey])) // Checks if the player has the Mushroom Key yet
					{
						std::cout << "You notice that when they bowed a mushroom shaped key fell out of who knows where\n";
						std::cout << "They don't seem inclined to pick it up so you do.\n";
						std::cout << "It looks like it unlocks the south exit.\n";
						playerInventory.addToInventory(items[MushroomKey]);
						removeItemFromRoom(items[MushroomKey]);
					}
					talkCount++;
				}
				break;

			case 2:
				if (talkToCharacter(talkTarget))
				{
					std::cout << "\"This tea is delicious.\"\n";
					talkCount++;
				}
				break;

			case 3:
				if (talkToCharacter(talkTarget))
				{
					// Source: Carroll p.94
					std::cout << "You start to say \"I don't think\", but you are abruptly cut off.\n";
					std::cout << "\"Well then, you shouldn't speak!\" " << characters[talkTarget].getName() << " exclaims.\n";
					std::cout << "Bewildered, you had only been trying to say that they shouldn't put the dormouse in the teapot.\n";
					talkCount++;
				}
				break;

			case 4:
				if (talkToCharacter(talkTarget))
				{
					std::cout << "A little bird tells me you just moved in down the path.\n";
					talkCount = 0; // Reset talk count
					break;
				}
			}
		}

		// There are no items that can be used in this location
		else if (checkUseItem() != NullItem)
		{
			std::cout << "You cannot use that item right now\n";
		}

		// Action checks that sometimes require customization (included for proper player feedback)
		else if (checkPickUpItem());
		else if (checkGiveGift());
		else if (checkFight());

		// Action checks that are common in each location and require no customization
		else if (commonActionChecks());
	}
}

// The Mushroom Forest Location Function
void Game::enterMushroomForest()
{
	// Manages the east exit of the Mushroom Forest, which leads to the Pool of Tears
	Exit & poolExit = currentLocation->getExit(East);
	
	// Checks if the player has entered this location previously
	if (!locations[MushroomForest].getHasBeenEntered())
	{
		std::cout << "Sitting upon a tall mushroom is the biggest blue and purple caterpillar you have ever seen.\n"
			<< "They are smoking a hookah crafted from deep indigo glass embellished with gold. The violet smoke billowing from it is shaped like ghostly butterflies.\n"
			<< "A mischievous disembodied smile, is grinning at you.\n";
		locations[MushroomForest].setHasBeenEntered(true);
	}
	
	// Loop continues while player is in the Mushroom Forest Location or until they end the game
	while (currentLocation == &locations[MushroomForest] && !endGame)
	{
		// Gets input/ actions from the player
		setCurrentAction();

		// Target use item
		int targetItem = checkUseItem();
		int targetTalk = checkTalkToCharacter();

		// Checks if the player tries to talk to the Caterpillar
		if (targetTalk == Caterpillar) 
		{
			if (talkToCharacter(Caterpillar))
			{
				// Source: Carroll p. 50
				std::cout << "The caterpillar squints at you through a cloud of purple ghostly butterflies.\n";
				std::cout << "You are not sure if he can actually see you.\n\n";
				std::cout << "\"Who are you?\" demanded the Caterpillar.\n";
				std::cout << "\"I hardly know,\" said Alice, \"because I'm not myself.\"\n";
				std::cout << "\"You must be yourself!\" retorted the Caterpillar, quite argumentatively.\n";

				std::cout << "\nYou have never met such a contrarian caterpillar.\n"
					<< "You quickly end the conversation.\n";
			}
		}

		// Checks if the player tries to talk to the Cheshire Cat
		else if (targetTalk == CheshireCat)
		{
			if (talkToCharacter(CheshireCat))
			{
				// Source: Carroll p.75
				std::cout << "The Cheshire Cat materializes peering down at you from the bough of a tall mushroom tree.\n"
					<< "You decide to ask the cat for directions.\n"
					<< "\"Well it depends where you would like to go, but I would like to go swimming.\"\n"
					<< "\"But you're a cat\"...\n"
					<< "\"And you're a little girl\", replies the cat.\n"
					<< "You are very confused.\n";
			}
		}

		// Checks if the player picks up an item
		else if (checkPickUpItem());

		// Checks if the player uses the cake
		else if (targetItem == EatMeCake)
		{
			std::cout << "You start to grow. Tears begin to trickle down your cheeks and towards the crack in the east wall.\n"
				<< "The more you grow the more you cry.\n"
				<< "You peer through the crack and see a vast pool of your tears.\n"
				<< "You see an isle far off in the distance, but now you are much too large to fit through the crack.\n\n";
			poolIsFull = true;
			playerInventory.removeFromInventory(items[EatMeCake]);

			std::cout << "The Cheshire cat materializes beside you, giving you quite a fright\n"
				<< "\"I'm off for a swim\", he purrs\n";
			std::cout << "Before they swim off they give you a Garden Key.\n";
			std::cout << "It looks like might unlock the south-west exit.\n";
			playerInventory.addToInventory(items[GardenKey]);
			removeItemFromRoom(items[GardenKey]);
		}

		// Checks if the player uses the bottle
		else if (targetItem == DrinkMeBottle)
		{
			// Forces the player to wait until the Pool of Tears is full before using the bottle
			if (poolIsFull)
			{
				std::cout << "You shrink back down to size, maybe you can fit through the crack in the wall now\n";
				poolExit.setIsUnlocked(true);
				playerInventory.removeFromInventory(items[DrinkMeBottle]);
			}
			else if (searchVectorOfGameObject(charactersAtLocation, characters[Caterpillar]) != -1) // Checks the Caterpillar is still in the location
			{
				std::cout << "The Caterpillar tells you not to drink from that bottle quite yet\n";
				std::cout << "Maybe you should try the cake first\n";
			}
			else
			{
				std::cout << "You decide to wait to drink that\n";
				std::cout << "Maybe you should try the cake first\n";
			}
		}

		// Checks if the player tries to use other items
		else if (targetItem != NullItem)
		{
			std::cout << "You can't use that item here\n";
		}

		// Action checks that sometimes require customization (included for proper player feedback)
		else if (checkFight());
		else if (checkGiveGift());

		// Action checks that are common in each location and require no customization
		else if (commonActionChecks());
	}
}

// The Pool of Tears Location Function
void Game::enterPoolOfTears()
{
	// Checks if the player has entered this location previously
	if (!locations[PoolOfTears].getHasBeenEntered())
	{
		std::string lookingGlassDescription = items[LookingGlass].getLongDescription();
		
		std::cout << "You see " << toLower(lookingGlassDescription)
			<< "\nIt is bobbling along in the salty waves.\n"
			<< "You hear a faint odd melody, it almost sounds like *Twinkle Twinkle Little Star*, but the lyrics are definitely *Twinkle Twinkle Little Bat.\n\n";

		locations[PoolOfTears].setHasBeenEntered(true);
	}
	// Checks if the sword is not in inventory 
	if (!playerInventory.isInInventory(items[AncientSword]))
	{
		std::cout << "A glint of silver catches your eye from the south.\n";
	}

	// Loop continues while player is in the Long Hallway Location or until they end the game
	while (currentLocation == &locations[PoolOfTears] && !endGame)
	{
		setCurrentAction();


		// Checks if the player picks up the music box
		if (checkPickUpItem() == MusicBox)
		{
			std::cout << "You are spellbound by the beauty of this little music box.\n";
		}
		// There are no items that can be used in this location
		else if (checkUseItem() != NullItem)
		{
			std::cout << "You cannot use that item right now\n";
		}

		// Action checks that sometimes require customization (included for proper player feedback)
		else if (checkTalkToCharacter());
		else if (checkFight());
		else if (checkGiveGift());

		// Action checks that are common in each location and require no customization
		else if (commonActionChecks());
	}
}

// The Isle of Sorrow Location Function
// Dialogue inspired by Carroll p. 118-138
void Game::enterIsleOfSorrow()
{
	// Characters and items at location { &characters[MockTurtle], &characters[Gryphon] }, { &items[FauxSoup], &items[AncientSword] }
	// Checks if the player has entered this location previously
	if (!locations[IsleOfSorrow].getHasBeenEntered())
	{
		std::cout << "You come across a sleepy Gryphon, lounging on the beach, next to a turtle with his flipper flung dramatically across his eyes.\n";
		locations[IsleOfSorrow].setHasBeenEntered(true);
		locations[Garden].getExit(East).unlock(); // Unlock the exit in the Garden location that leads to the Isle of Sorrow
	}

	// Loop continues while player is in the Long Hallway Location or until they end the game
	while (currentLocation == &locations[IsleOfSorrow] && !endGame)
	{
		setCurrentAction();
		int talkTarget = checkTalkToCharacter();
		
		if (talkTarget == MockTurtle) 
		{
			if (talkToCharacter(MockTurtle))
			{
				std::cout << "The Mock Turtle sighs deeply and begins to tell his sorrowful tale.\n";
				std::cout << "You see, he was once a turtle as real as real can be.\n";
			}
		}

		else if (talkTarget == Gryphon) 
		{
			if (talkToCharacter(Gryphon))
			{
				std::cout << "The sleepy Gryphon laughs, \"the nose, knows, no curiosity.\"\n";
			}
		}


		if (checkPickUpItem() == AncientSword)
		{
			alice.increaseAttackDamage(10);
			std::cout << "Your max attack damage has increased to " << alice.getMaxAttackDamage() << ".\n";
		}

		// There are no items that can be used in this location
		else if (checkUseItem() != NullItem)
		{
			std::cout << "You cannot use that item right now\n";
		}

		// Action checks that sometimes require customization (included for proper player feedback)
		else if (checkFight());
		else if (checkGiveGift());

		// Action checks that are common in each location and require no customization
		else if (commonActionChecks());
	}
}

// The Garden Location Function
void Game::enterGarden()
{
	// Characters and items at location { &characters[Queen], &characters[Soldier], &characters[WhiteRabbit] }, { &items[PaintedRose], &items[Hedgehog], &items[CourtierDiamond], &items[KingsCrown] }
	// Checks if the player has entered this location previously
	if (!locations[Garden].getHasBeenEntered())
	{
		// Source: Carroll p.97
		std::cout << "A group of card gardeners, are anxiously painting white roses red.";
		std::cout << "The White Rabbit scurries frantically southward, muttering about being very-very late for the trial.\n\n";
		
		// Source: Carroll p.98
		std::cout << "You watch as a royal procession passes by, first the courtiers dripping in diamonds\n";
		std::cout << "After them come the royal children, skipping along in pairs, adorned with hearts.\n";
		std::cout << "Then the guests, mostly Kings and Queens.\n";
		std::cout << "Following them, the soldier of Hearts carries the King's crown on a crimson velvet cushion.\n";
		std::cout << "At last, the Queen of hearts comes into view.\n";

		std::cout << "When everyone has arrived you realize they are setting up to play the strangest game of croquet you have ever encountered\n";
		std::cout << "They are using hedgehogs as the balls and pink flamingos as the clubs\n";
		locations[Garden].setHasBeenEntered(true);
	}

	// Loop continues while player is in the Long Hallway Location or until they end the game
	while (currentLocation == &locations[Garden] && !endGame)
	{
		setCurrentAction();

		int talkTarget = checkTalkToCharacter();

		// Checks if the player tries to talk to the Queen
		if (talkTarget == Queen)
		{
			// Source: Carroll p.101
			std::cout << "She is screaming \"OFF WITH THEIR HEADS\" over every minor inconvenience, when you speak her gaze turns on you.\n";
			std::cout << "\"You must join the croquet game\", she shouts.\n";
			std::cout << "You try to refuse but it does no good.\n\n";

			// Random croquet event
			bool outcome = croquetOutcome();
			int friendScore = characters[Queen].getFriendshipScore();
			if (outcome && friendScore >= 50)
			{
				std::cout << "You try to throw the game, but your hedgehog and flamingo are very competitive.\n";
				std::cout << "The better you do, the angrier the Queen gets.\n\n";
				std::cout << "When the game ends you are the clear winner.\n";
				std::cout << "The Queen seems angry, but atleast she isn't ordering your execution, maybe all the gifts have made her sweet.\n";
				
				// Players loses 25 friendship points with the Queen
				friendScore -= 25;
				characters[Queen].setFriendshipScore(friendScore);
				
				// Update player's scores
				alice.updateFriendshipScore(characters);
				alice.updateTotalScore();
			}
			else if (outcome)
			{
				std::cout << "You try to throw the game, but your hedgehog and flamingo are very competitive.\n";
				std::cout << "The better you do, the angrier the Queen gets.\n\n";
				std::cout << "When the game ends you are the clear winner.\n";
				std::cout << "The queen shouts \"OFF WITH HER HEAD\" and the card soldier advances on you.\n";
				fight(characters[Soldier]);
			}
			else
			{
				std::cout << "You lose the game, but the queen seems very competitive, so it is probably for the best.\n";
			}
		}

		// Checks if the player tries to talk to the Soldier
		else if (talkTarget == Soldier)
		{
			if (talkToCharacter(Soldier))
			{
				std::cout << "\"The kings crown is worth more than both our heads.\"\n";
			}
		}

		// Checks if the player tries to talk to the Soldier
		else if (talkTarget == Duchess)
		{
			if (talkToCharacter(Duchess))
			{
				std::cout << "\"I am famished and craving something sweet.\"\n";
			}
		}

		// Checks if the player tries to talk to the White Rabbit
		else if (talkTarget == WhiteRabbit)
		{
			if (talkToCharacter(WhiteRabbit))
			{
				std::cout << "The white rabbit looks around anxiously and says, \"If this goes on much longer, we will all be late to the trial.\"\n";
			}
		}

		// There are no items that can be used in this location
		else if (checkUseItem() != NullItem)
		{
			std::cout << "You cannot use that item right now\n";
		}

		// Action checks that sometimes require customization (included for proper player feedback)
		else if (checkPickUpItem());
		else if (checkFight());
		else if (checkGiveGift());

		// Action checks that are common in each location and require no customization
		else if (commonActionChecks());

		// Prints a warning message for the player if their input is invalid
		else
		{
			std::cout << "Please try rephrasing your input\n";
		}
	}
}

// The Castle Location Function
void Game::enterCastle() // (Court of justice)
{
	// Characters and items at location { &characters[Queen], &characters[Duchess] }, { &items[Spectacles], &items[GuineaPig],  &items[HattersHat] }
	// Checks if the player has entered this location previously
	if (!locations[Castle].getHasBeenEntered())
	{
		std::cout << "You step into the grand courtroom of the Castle of Hearts, where a trial is about to commence.\n";
		std::cout << "The Queen sits upon her throne, while a jury of creatures scribble nonsense notes.\n";
		std::cout << "The Duchess stands accused of stealing the King's Crown.\n";
		std::cout << "The White Rabbit, is acting as the herald.\n";
		locations[Castle].setHasBeenEntered(true);
	}

	// Kill player if they enter the castle with the kings crown
	if (playerInventory.isInInventory(items[KingsCrown]))
	{
		std::cout << "Thief! screams the queen, soldiers rush in around you with swords drawn\n"
			<< "Off with their head!\n";
		endGame = true;
	}

	// Loop continues while player is in the Long Hallway Location or until they end the game
	while (currentLocation == &locations[Castle] && !endGame)
	{
		setCurrentAction();
		
		int talkTarget = checkTalkToCharacter();
		// Checks if the player talks to the Queen of Hearts
		if (talkTarget == Queen)
		{
			if (talkToCharacter(Queen))
			{
				std::cout << "The Queen of Hearts yells, \"Sentence first verdict afterwards!\"\n"; // Carroll p.158
			}
		}

		// Checks if the player talks to the White Rabbit
		else if (talkTarget == WhiteRabbit)
		{
			if (talkToCharacter(MockTurtle))
			{
				std::cout << "The White Rabbit adjusts his spectacles and clears his throat. \"Silence in the court!\"\n";
			}
		}

		// Checks if the player talks to the White Rabbit
		else if (talkTarget == Duchess)
		{
			if (treasureInventory.isInInventory(items[KingsCrown]))
			{
				std::cout << "Admit to the Duchess that you stole the King's Crown?(Yes/No)\n";
				setCurrentAction();
				if (matches(Yes))
				{
					std::cout << "Honesty is usually the best policy, but unfortunately the Queen does not seem in a forgiving mood as she screams \"OFF WITH THEIR HEAD\"\n";
					std::cout << "The last thing you see is the soldiers swarming you before your vision goes dark.\n";
					endGame = true;
				}
				else
				{
					std::cout << "This decision weighs heavily on your conscience.\n";
					std::cout << "Maybe there is another way to save the Duchess.\n";
				}
			}
		} 

		// Checks if the player gives the queen a tart
		else if (checkGiveGift())
		{
			if (matches(Tart) && matches(Queen) && matches(Give))
			{
				std::cout << "The Queen seems so enraptured with the tart that she seems to have forgotten all about the Duchess.\n";
				std::cout << "The Queen leaves to go demand her cook learn this tart recipe.\n";
				std::cout << "Everyone else decides to leave while they have the chance.\n";

				removeCharacterFromRoom(characters[Queen]);
				removeCharacterFromRoom(characters[WhiteRabbit]);
				removeCharacterFromRoom(characters[Duchess]);
			}
		}

		// There are no items that can be used in this location
		if (checkUseItem() != NullItem)
		{
			std::cout << "You cannot use that item right now\n";
		}

		// Action checks that sometimes require customization (included for proper player feedback)
		else if (checkPickUpItem());
		else if (checkFight());

		// Action checks that are common in each location and require no customization
		else if (commonActionChecks());
	}
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Location Builder Functions
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Builds the current location
// Displays the description of the current location
// Checks the current location then adds the appropriate game objects and calls the location function
void Game::loadCurrentLocation()
{
	//Resets the vector of current actions
	resetCurrentAction();

	// Displays the current location description
	std::cout << "You are in " << getCurrentLocationDescription() << "\n";

	// Checks the current location and loads game objects for that location
	// then calls the location function
	if (*currentLocation == locations[Meadow])
	{
		// Loads the location with a vector of Character pointers and a vector of Item pointers
		loadLocationObjects({&characters[WhiteRabbit]}, {&items[DaisyChain]});
		
		// Calls the meadow location function
		meadow();
	}
	else if (*currentLocation == locations[RabbitHole])
	{
		// Loads the location with a vector of Character pointers and a vector of Item pointers
		{
			{
				loadLocationObjects({ /*No Characters*/ }, { &items[MarmaladeJar], &items[PocketWatch] });
			}
		}
		
		// Calls the rabbit hole location function
		enterRabbitHole();
	}
	else if (*currentLocation == locations[LongHallway])
	{
		loadLocationObjects({ &characters[CheshireCat] }, { &items[Milk], &items[KidGloves], &items[Fan], &items[CottageKey]});

		// Calls the long hallway location function
		enterLongHallway();
	}
	else if (*currentLocation == locations[Cottage])
	{
		loadLocationObjects({ /*No Characters*/ }, {  /*No Items*/ }); 

		// Calls the cottage location function
		enterCottage();
	}
	else if (*currentLocation == locations[HaresLawn])
	{
		// Creates a vector of random characters
		std::vector<Character*> teaPartyCharacters = getRandomCharacters(3);
		
		// Checks if the March Hare is present, if not adds them
		if (searchVectorOfGameObject(teaPartyCharacters, characters[MarchHare]) == -1)
		{
			teaPartyCharacters.push_back(&characters[MarchHare]);
		}
		
		// Checks if the Mad Hatter is present, if not adds them
		if (searchVectorOfGameObject(teaPartyCharacters, characters[MadHatter]) == -1) 
		{
			teaPartyCharacters.push_back(&characters[MadHatter]);
		}

		// Stores the items at the tea party in a vector
		std::vector<Item*> teaPartyItems;
		teaPartyItems.push_back(&items[Teapot]);
		teaPartyItems.push_back(&items[Tart]);
		teaPartyItems.push_back(&items[Butter]);
		teaPartyItems.push_back(&items[PaintedRose]);
		teaPartyItems.push_back(&items[MushroomKey]);
		
		// Stores a random gift item
		Item* item = getRandomItems(1, Gift)[0]; 

		// Checks if the random gift is present, if not adds it
		if (searchVectorOfGameObject(teaPartyItems, *item) == -1) 
		{
			teaPartyItems.push_back(item);
		}

		// Loads the location with a vector of Character pointers and a vector of Item pointers
		loadLocationObjects({ teaPartyCharacters }, { teaPartyItems });

		// Calls the hares lawn location function
		enterHaresLawn();
	}
	else if (*currentLocation == locations[MushroomForest])
	{
		// Loads the location with a vector of Character pointers and a vector of Item pointers
		loadLocationObjects({ &characters[Caterpillar], &characters[CheshireCat] }, { &items[GardenKey], &items[Hookah], &items[DrinkMeBottle], &items[EatMeCake] });

		// Calls the mushroom forest location function
		enterMushroomForest();
	}
	else if (*currentLocation == locations[PoolOfTears])
	{
		loadLocationObjects({ /*No Characters*/ }, { &items[LookingGlass], &items[MusicBox] });

		// Calls the pool of tears location function
		enterPoolOfTears();
	}
	else if (*currentLocation == locations[IsleOfSorrow])
	{
		loadLocationObjects({ &characters[MockTurtle], &characters[Gryphon] }, { &items[FauxSoup], &items[AncientSword] });

		// Calls the isle of sorrow location function
		enterIsleOfSorrow();
	}
	else if (*currentLocation == locations[Garden])
	{
		loadLocationObjects({ &characters[Queen], &characters[Soldier], &characters[Duchess], &characters[WhiteRabbit] }, { &items[PaintedRose], &items[Hedgehog], &items[CourtierDiamond], &items[KingsCrown] });

		// Calls the garden location function
		enterGarden();
	}
	else if (*currentLocation == locations[Castle])
	{
		loadLocationObjects({ &characters[Queen], &characters[Duchess], &characters[WhiteRabbit] }, { &items[Tart], &items[Spectacles], &items[GuineaPig],  &items[HattersHat] });

		// Calls the castle location function
		enterCastle();
	}
	else
	{
		// Ends the game if an error occurs where the player is not in any of the locations
		std::cerr << "An error regarding the current location of the player has occurred, ending the game...";
		endGame = true;
	}
}

void Game::loadLocationObjects(std::vector<Character*> charactersAtLocation, std::vector<Item*> itemsAtLocation)
{
	clearLocationObjects(); // Clears any previous game objects
	setItemsAtLocation(itemsAtLocation); // Populates the itemsAtLocation vector
	setCharactersAtLocation(charactersAtLocation); // Populates the charactersAtLocation vector
}

// Clears any previous game objects
void Game::clearLocationObjects()
{
	itemsAtLocation.clear(); // Clears the itemsAtLocation vector
	charactersAtLocation.clear(); // Clears the charactersAtLocation vector
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Current Location Item Management Functions
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Populates the itemsAtLocation vector
void Game::setItemsAtLocation(std::vector<Item*> i)
{
	for (Item* item : i)
	{
		// Only respawn items that are set to respawn and are not already in the players inventory
		if (item->getRespawn() && !playerInventory.isInInventory(*item))
		{
			itemsAtLocation.push_back(item);
		}
	}
}

// Removes an item from itemsAtLocation
void Game::removeItemFromRoom(Item& item)
{
	// Source: https://www.geeksforgeeks.org/vector-erase-in-cpp-stl/
	auto it = find(itemsAtLocation.begin(), itemsAtLocation.end(), &item); // Searches itemsAtLocation for the item
	
	// Erases item only if found
	if (it != itemsAtLocation.end()) 
	{  
		itemsAtLocation.erase(it);
	}
}

// Searches the itemsAtLocation for a specific item
bool Game::isItemAtLocation(Item& item)
{
	// Cycles through items in itemsAtLocation
	for (int index = 0; index < itemsAtLocation.size(); index++) 
	{
		// Returns true only if the item is found in itemsAtLocation
		if (item == *itemsAtLocation[index]) 
		{
			return true;
		}
	}
	return false;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Current Location Character Management Functions
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Populates the charactersAtLocation vector
void Game::setCharactersAtLocation(std::vector<Character*> c)
{
	for (Character* character : c)
	{
		// Add any conditions to check for
		charactersAtLocation.push_back(character);
	}
}

// Removes an character from charactersAtLocation
void Game::removeCharacterFromRoom(Character& character)
{
	// Source: https://www.geeksforgeeks.org/vector-erase-in-cpp-stl/
	auto it = find(charactersAtLocation.begin(), charactersAtLocation.end(), &character); // Searches charactersAtLocation for the character
	
	// Erases character only if found
	if (it != charactersAtLocation.end()) 
	{  
		charactersAtLocation.erase(it); 
	}
}

// Searches the charactersAtLocation for a specific character
bool Game::isCharacterInRoom(Character& character)
{
	// Cycles through characters in charactersAtLocation
	for (int index = 0; index < charactersAtLocation.size(); index++)
	{
		// Returns true only if the character is found in charactersAtLocation
		if (character == *charactersAtLocation[index])
		{
			return true;
		}
	}
	return false;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Random Function
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Returns a random index
int Game::getRandomInt(int min, int max)
{
	// Creates a random device and seed the generator | Source: https://www.geeksforgeeks.org/how-to-generate-random-number-in-range-in-cpp/
	static std::random_device rd;
	static std::mt19937 generator(rd());

	// Defines the range [min, max]
	std::uniform_int_distribution<int> d(min, max);

	// Generates and return the random number
	return d(generator);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Random Item Function
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Creates a vector populated with a specific number of random item pointers of a specific item type ie. a vector of 3 random gifts
std::vector<Item*> Game::getRandomItems(int numItems, ItemType type)
{
	std::vector<Item*> itemVector; 
	int itemIndex;
	int isInVector;

	int min;
	int max;

	// The maximum number of each item type
	int numKeys = 3, numGifts = 8, numTreasure = 11, numKeyItems = 2, numWeapons = 2;

	// Sets the min/ max index for each item type
	// Ensures numItems is less than the maximum number of each type
	if (type == Key)
	{
		min = GardenKey;
		max = MushroomKey;

		if (numItems > numKeys)
		{
			numItems = numKeys;
		}
	}
	else if (type == Gift)
	{
		min = Milk;
		max = Spectacles;
		
		if (numItems > numGifts)
		{
			numItems = numGifts;
		}
	}
	else if (type == Treasure)
	{
		min = DaisyChain;
		max = HattersHat;

		if (numItems > numTreasure)
		{
			numItems = numTreasure;
		}
	}
	else if (type == KeyItem)
	{
		min = DrinkMeBottle;
		max = EatMeCake;

		if (numItems > numKeyItems)
		{
			numItems = numKeyItems;
		}
	}
	else if (type == Weapon)
	{
		min = MarmaladeJar;
		max = AncientSword;

		if (numItems > numWeapons)
		{
			numItems = numWeapons;
		}
	}

	// Populates itemVector with a specified number of random items of the correct item type
	while (itemVector.size() < numItems) // Continues until itemVector is populated with the number of items specified 
	{
		itemIndex = getRandomInt(min, max); // Gets a random item of the correct type
		
		isInVector = searchVectorOfGameObject(itemVector, items[itemIndex]); // Searches the itemVector for the random item

		// Only adds unique items to itemVector
		if (isInVector == -1)
		{
			itemVector.push_back(&items[itemIndex]);
		}
	}

	// Return the vector
	return itemVector;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Random Character Function
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Creates a vector populated with a specific number of random character pointers
std::vector<Character*> Game::getRandomCharacters(int numCharacters)
{
	std::vector<Character*> characterVector;
	int characterIndex;
	int isInVector;

	// Populates characterVector with a specified number of random characters
	while (characterVector.size() < numCharacters) // Continues until characterVector is populated with the number of characters specified 
	{
		characterIndex = getRandomInt(CheshireCat, MockTurtle); // Gets a random character of the correct type

		isInVector = searchVectorOfGameObject(characterVector, characters[characterIndex]); // Searches the characterVector for the random character

		// Only adds unique characters to characterVector
		if (isInVector == -1) 
		{
			characterVector.push_back(&characters[characterIndex]);
		}
	}

	// Return the vector
	return characterVector;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Common Action Check Functions
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Performs all of the action checks that need to be performed in every loaction, excluding checks tht require customization ie. checkTalkToCharacter needs to be checked in the location to display the correct dialogue
bool Game::commonActionChecks()
{
	// Player related action checks
	if (checkDisplayInventory()) return true;
	else if (checkDisplayStats()) return true;
	
	// Functions to help the player with their input
	else if (checkHelp()) return true; // Checks if the player needs help based on their input
	else if (checkEndGame()) return true; // Checks if the player wants to end based on their input

	// Location related action checks
	else if (checkEnter()) return true;
	else if (checkExplore()) return true;
	else if (checkExamineItem()) return true;
	else if (checkUnlockExit()) return true;
	else if (checkHint()) return true;

	// Item related action checks
	else if (checkStoreTreasure()) return true;

	// Prints a warning message for the player if their input is invalid
	else if (checkInvalidAction()) return true; 

	// Returns false if no action checks are valid
	return false;
}

// Prints a warning message for the player if their input is invalid
bool Game::checkInvalidAction()
{
	// Checks if the a Keyword or Verb has been entered if not there are no valid actions, so display a error message
	if (currentAction[K] == NullKeyword && currentAction[V] == NullVerb) 
	{
		std::cout << "Please try rephrasing your input\n";
		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Player Related Action Check Functions
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Checks if the player entered a valid Inventory action
bool Game::checkDisplayInventory()
{
	if (!matches(PlayerInventory))
	{
		return false;
	}
	
	displayInventory();
	return true;
}

// Checks if the player entered a valid Stats action
bool Game::checkDisplayStats()
{
	if (!matches(Stats))
	{
		return false;
	}
	
	displayStats();
	return true;
}

// Checks if the player entered a valid Help action
bool Game::checkHelp()
{
	if (!matches(Help))
	{
		return false;
	}
	displayInputInstructions();
	return true;
}

// Checks if the player entered a valid End action
bool Game::checkEndGame()
{
	if (!matches(End))
	{
		return false;
	}

	// Double checks the player wants to end the game
	std::cout << "Are you sure you want to end the game? (Yes/No)\n";
	setCurrentAction(); // Gets player input

	// Checks if player entered a valid Yes action
	if (matches(Yes))
	{
		endGame = true;
		std::cout << "Ending the game..." << std::endl;
		return true;
	}
	
	// If the player enters anything other than yes, continues the game
	std::cout << "Returning to the game\n";
	return true;
}

bool Game::checkPlayerWin()
{
	if (alice.getTotalScore() == WIN_SCORE)
	{
		endGame = true;
		win = true;
		return true;
	}
	else
	{
		return false;
	}
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Item Related Action Check Functions
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Checks if the player entered a valid PickUp action
int Game::checkPickUpItem()
{
	if (!matches(PickUp))
	{
		return NullItem;
	}

	// Checks that the player has specified an item
	if (matches(NullItem))
	{
		std::cout << "You must specify a valid item to pick up\n";
		return NullItem;
	}

	int item = currentAction[I]; // Gets the index of the item the player has entered
	int index = searchVectorOfGameObject(itemsAtLocation, items[item]); // Searches for the item in the itemsAtLocation vector

	// Checks if the item is a key
	// If it is do not let player pick it up (Keys are retrieved by triggering events)
	if (items[item].getItemType() == Key)
	{
		std::cout << "Please try rephrasing your input\n";
		return NullItem;
	}

	// Checks if the item is not present at the location
	if (index == -1)
	{
		std::cout << "There is no " << items[item].getName() << " in this location, try picking up something else\n";
		return NullItem;
	}
	// If the item is at the location allows player to pick it up and remove it from the location
	else
	{
		pickUpItem(items[item]);
		itemsAtLocation.erase(itemsAtLocation.begin() + index);
		return item; // Returns the item index so that the item being picked up can be checked by the location functions
	}
}

// Checks if the player entered a valid PlaceTreasure action
bool Game::checkStoreTreasure()
{
	if (!matches(PlaceTreasure)) 
	{
		return false;
	}

	// Players can only place treasure while at the cottage location
	if ((getCurrentLocation() != locations[Cottage])) 
	{
		std::cout << "Treasure cannot be placed here, you must return to your cottage" << std::endl;
		return false;
	}

	// Players must specify the item
	if (matches(NullItem))
	{
		std::cout << "You must specify what you would like to place in the cottage\n";
		return false;
	}

	int item = currentAction[I]; // Gets the item the player has selected

	// Checks if the item is not in the players inventory
	if (!playerInventory.isValidItem(items[item])) 
	{
		std::cout << items[item].getName() << " is not in your inventory\n";
		return false;
	}

	// Checks if the item is not of type Treasure
	if (items[item].getItemType() != ItemType::Treasure) 
	{
		std::cout << items[item].getName() << " is not considered a treasure, you can only place treasure in the cottage" << std::endl;
		return false;
	}

	// If all validations are successful store treasure and return true
	storeTreasure(items[item]);
	return true;

}

// Checks if the player entered a valid PlaceTreasure action
int Game::checkUseItem()
{
	if (!matches(Use))
	{
		return NullItem;
	}

	// Players must specify the item
	if (matches(NullItem))
	{
		std::cout << "You must specify what item you would like to use.\n";
		return NullItem;
	}

	int item = currentAction[I]; // Gets the item the player has selected

	// Checks if the item is not in the players inventory
	if (!playerInventory.isValidItem(items[item]))
	{
		std::cout << items[item].getName() << " is not in your inventory.\n";
		return NullItem;
	}

	// If all validations are successful return item index
	return item;
}

// Checks if the player entered a valid Examine action
bool Game::checkExamineItem()
{
	if (!matches(Examine))
	{
		return false;
	}
	
	// Players must specify the item
	if (matches(NullItem))
	{
		std::cout << "You must specify what item you would like to examine.\n";
		return false;
	}

	int item = currentAction[I]; // Gets the item the player has selected

	// The player can only examine items that are either in their inventory, in the room, or if they are in the Cottage they can examine treasure that has been stored
	if (!playerInventory.isValidItem(items[item]) && !isItemAtLocation(items[item]) && !(treasureInventory.isValidItem(items[item]) && *currentLocation == locations[Cottage]))
	{
		std::cout << items[item].getName() << " is not in your inventory or in this location.\n";
		return false;
	}

	// If all validations are successful examine item and return true
	examineItem(items[item]);
	return true;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Character Related Action Check Functions
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Checks if the player entered a valid Give action
bool Game::checkGiveGift()
{
	if (!matches(Give))
	{
		return false;
	}

	// Checks if either item or character is unspecified
	if (matches(NullItem) || matches(NullCharacter))
	{
		if (matches(NullItem))
		{
			std::cout << "You must specify the item you would like to give.\n";
		}
		if (matches(NullCharacter))
		{
			std::cout << "You must specify who you would like to give a gift to.\n";
		}
		return false;
	}

	int character = currentAction[C]; // Gets the character the player has selected
	int item = currentAction[I]; // Gets the item the player has selected

	// Searches for the character in the charactersAtLocation vector
	int characterIndex = searchVectorOfGameObject(charactersAtLocation, characters[character]);

	// Checks if the character is not at the current location
	if (characterIndex == -1)
	{
		std::cout << characters[character].getName() << " is not in the location\n";
		return false;
	}

	// Checks if the item is not in the inventory
	if (!playerInventory.isValidItem(items[item]))
	{
		std::cout << items[item].getName() << " is not in your inventory\n";
		return false;
	}

	// Checks if the item is not a gift
	if (items[item].getItemType() != Gift)
	{
		std::cout << items[item].getName() << " cannot be given as a gift\n";
		return false;
	}

	// If all validation checks pass give specified item to the specified character and return true
	giveGift(items[item], characters[character]);
	return true;
}

// Checks if the player entered a valid Talk action
int Game::checkTalkToCharacter()
{
	if (!matches(Talk))
	{
		return NullCharacter;
	}

	int character = currentAction[C]; // The character index the player specifed
	int index = searchVectorOfGameObject(charactersAtLocation, characters[character]); // Checks if the character is in the location
	if (matches(NullCharacter)) // Checks the player entered the name of a character
	{
		std::cout << "You must specify who you would like to talk to\n"; // The player did not specify any character to talk to
		return NullCharacter;
	}

	if (index == -1) // Checks if the character is not in the location
	{
		// The player has specified a character that is not in the location
		std::cout << characters[character].getName() << " is not in the location\n";
		return NullCharacter; // The character is not in the location
	}

	// The player has successfully specifed a character in the location to talk to
	return character; // Returns the index of the specifed character
}

// Checks if the player entered a valid Attack action
int Game::checkFight()
{
	if (!matches(Attack))
	{
		return NullCharacter;
	}

	// Checks if the player has not entered a valid character
	if (matches(NullCharacter))
	{
		std::cout << "You must specify who you would like to fight\n";
		return NullCharacter;
	}

	int character = currentAction[C]; // Gets the character the player has selected
	int index = searchVectorOfGameObject(charactersAtLocation, characters[character]); // Checks if the character is in the location

	// Checks if the character is not in the location
	if (index == -1)
	{
		std::cout << "You can't fight a character that is not in the location\n";
		return NullCharacter;
	}

	// Checks if player wins the fight returns the character index, used to specify win conditions depending on the character
	if (fight(characters[character]))
	{
		return character; 
	}

	return NullCharacter; // Returns NullCharacter if the player loses the fight
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Location Related Action Check Functions
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Checks if the player entered a valid Enter action
bool Game::checkEnter()
{
	if (matches(Enter))
	{
		// Checks which direction the player has entered
		// Then calls enterExit with the correct direction as a parameter
		if (matches(North))
		{
			enterExit(North);
			return true;
		}
		else if (matches(NorthEast))
		{
			enterExit(NorthEast);
			return true;
		}
		else if (matches(East))
		{
			enterExit(East);
			return true;
		}
		else if (matches(SouthEast))
		{
			enterExit(SouthEast);
			return true;
		}
		else if (matches(South))
		{
			enterExit(South);
			return true;
		}
		else if (matches(SouthWest))
		{
			enterExit(SouthWest);
			return true;
		}
		else if (matches(West))
		{
			enterExit(West);
			return true;
		}
		else if (matches(NorthWest))
		{
			enterExit(NorthWest);
			return true;
		}
		// If no direction is entered display error message
		else
		{
			std::cout << "You need to specify a direction\n";
		}
	}
	return false;
}

// Checks if the player entered a valid Explore action
bool Game::checkExplore()
{
	if (!matches(Explore))
	{
		return false;
	}

	int location = currentAction[L]; // Gets the location the player has selected

	// Checks if the player has entered a location other than the current location
	if (*currentLocation != locations[location] && !matches(NullLocation))
	{
		std::cout << "You can only explore areas where you are currently located\n";
		return false;
	}

	// Explores the location
	exploreLocation();
	return true;
}

// Checks if the player entered a valid Unlock action
bool Game::checkUnlockExit()
{
	if (!matches(Unlock))
	{
		return false;
	}

	// Checks if the player has not entered a valid direction
	if (matches(NullDirection))
	{
		std::cout << "You must specify the direction\n";
		return false;
	}

	try
	{
		int direction = currentAction[D]; // Gets the direction the player has selected
		Exit& exit = currentLocation->getExit(direction);
		
		// Checks if the specified direction is already unlocked
		if (exit.isUnlocked())
		{
			std::cout << "The exit was already unlocked" << std::endl;
			return true;
		}

		// Checks that the key for the exit is not in the player inventory
		if (!playerInventory.isValidItem(items[exit.getKey()])) 
		{
			std::cout << "You need the " << exit.getExitName() << " Key to unlock this exit\n";
			return false;
		}

		// If all validation checks pass unlock exit and return true
		unlockExit(exit);
		return true;
	}

	// If there is no exit in the direction specified by the player getExit throws an exception
	catch (const std::out_of_range& e)
	{
		std::cout << e.what() << '\n'; // Source: https://www.geeksforgeeks.org/exceptionwhat-in-c-with-examples/
		return false;
	}
}

// Checks if the player entered a valid Hint action
bool Game::checkHint()
{
	if (matches(Hint))
	{
		// Displays the location hint
		currentLocation -> displayHint();
		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Item Event Functions
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Adds items to the players inventory
void Game::pickUpItem(Item& item)
{
	std::string description = item.getShortDescription();
	std::cout << "You found " << toLower(description) << "\n";
	playerInventory.addToInventory(item);
}

// Stores treasures in the treasure inventory
void Game::storeTreasure(Item& item)
{
	// Adds the item to the treasure inventory
	treasureInventory.addToInventory(item);
	std::cout << "The treasure has been placed in the cottage" << std::endl;
	
	// Removes the item from the player inventory
	playerInventory.removeFromInventory(item);

	// Update the player's scores
	alice.addToTreasureScore(item.getPoints());
	alice.updateFriendshipScore(characters);
	alice.updateTotalScore();
	
	// Check if player wins
	checkPlayerWin();
}

// Lets the player view attributes of a specified item
void Game::examineItem(Item& item)
{
	item.displayItem();
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Character Event Functions
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Gives an item to a character
void Game::giveGift(Item item, Character& character)
{
	// Implements the give gift mechanic
	std::cout << "You give " << character.getName() << " the " << item.getName() << std::endl;
	character.receiveGift(item);
	playerInventory.removeFromInventory(item);
	
	// Update the player's scores
	alice.updateFriendshipScore(characters);
	alice.updateTotalScore();

	

	// Check if player wins
	checkPlayerWin();
}

// Allows the player to talk to a character if they are a friend, initiates a fight if they are not a friend
bool Game::talkToCharacter(int character)
{
	// Checks if a character is a friend 
	if (characters[character].isCharacterFriend())
	{
		std::cout << "You start talking to " << characters[character].getName() << "\n";
		return true; // The player successfully talks to the specified character
	}
	// If the character is not a friend fights character
	else
	{
		std::cout << "It looks like you've made an enemy of " << characters[character].getName() << "\n";
		std::cout << "You should consider giving them a gift they really like, such as " << characters[character].getMostLikedGift() << "\n";
		std::cout << "If you survive that is...\n\n";
		fight(characters[character]); // Initiates a fight
	}
	return false;
}

// Starts a fight sequence with a specified character
bool Game::fight(Character& character)
{
	// Gets the player and the character's current hit points
	int characterHP = character.getHitPoints();
	int playerHP = alice.getHitPoints();

	// Keeps track of the random 
	int playerCurrentDamage;
	int characterCurrentDamage;

	int playerMaxDamage = alice.getMaxAttackDamage();
	int playerMinDamage = (alice.getMaxAttackDamage() / 2) + 1;

	int characterMaxDamage = character.getMaxAttackDamage();
	int characterMinDamage = (character.getMaxAttackDamage() / 2) + 1;;

	std::cout << "The fight begins...\n";
	std::cout << "Your HP: " << playerHP << "\n";
	std::cout << character.getName() << "s HP: " << characterHP << "\n\n";
	std::this_thread::sleep_for(std::chrono::seconds(3));

	// The player and the character attack each other until one wins
	while (characterHP > 0 && playerHP > 0)
	{
		// Randomizes the players attack damage
		playerCurrentDamage = getRandomInt(playerMinDamage, playerMaxDamage);
		
		characterHP -= playerCurrentDamage;
		std::cout << "You attack " << character.getName() << "\n";
		std::this_thread::sleep_for(std::chrono::seconds(2));
		std::cout << "Their HP drops to " << characterHP << "\n\n";
		std::this_thread::sleep_for(std::chrono::seconds(2));

		if (characterHP > 0)
		{
			// Randomizes the characters attack damage
			characterCurrentDamage = getRandomInt(characterMinDamage, characterMaxDamage);
			
			playerHP -= characterCurrentDamage;
			std::cout << character.getName() << " attacks you" << "\n";
			std::this_thread::sleep_for(std::chrono::seconds(2));
			std::cout << "Your HP drops to " << playerHP << "\n\n";
			std::this_thread::sleep_for(std::chrono::seconds(2));
		}
	}

	// Checks if the player perishes in the fight
	if (playerHP > 0) // Win condition
	{
		std::cout << "You win the fight\n"
			<< character.getName() << " flees the fight\n";

		removeCharacterFromRoom(character);

		// Reduce the character's friendship score
		int newScore = character.getFriendshipScore() - 20;
		character.setFriendshipScore(newScore);

		// Update the player's scores
		alice.updateFriendshipScore(characters);
		alice.updateTotalScore();

		return true;
	}
	else // Loose condition
	{
		std::cout << "Tragically you perish in the fight\n";
		std::this_thread::sleep_for(std::chrono::seconds(2));
		std::cout << "Ending the game...\n";
		std::this_thread::sleep_for(std::chrono::seconds(2));

		endGame = true;
		return false;
	}
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Location Event Functions
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Enters the exit of the current location depending on the direction specified
bool Game::enterExit(int direction)
{
	try
	{
		// Gets the exit facing the specified direction
		Exit& exit = currentLocation->getExit(direction);
		
		// Finds the index of the location the exit leads to by matching the name
		int index = findExitIndex(locations, exit);

		// Checks if the exit is unlocked
		if (exit.isUnlocked())
		{
			// Checks that the index was found in the locations vector
			if (index != -1)
			{
				// Sets the current location to the location which the exit leads to
				currentLocation = &locations[index];
				return true;
			}
		}
		// If the exit is not unlocked displays an error message
		else
		{
			std::cout << "You are unable to go this way right now\n"; //Locked
			
			// Checks if the exit requires a key and lets the player know which key if one exists 
			if (exit.getKey() != NullItem)
			{
				std::cout << "You need to unlock it with the " << exit.getExitName() << " key\n";
			}
		}
	}
	// Catches exceptions thrown by the getExit function
	catch (const std::out_of_range& e)
	{
		std::cout << e.what() << '\n';
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return false;
}

// Unlocks the specified exit
void Game::unlockExit(Exit& exit)
{
	exit.unlock();
	std::cout << "You unlock the " << exit.directionToString() << "ern exit" << std::endl;
}

// Explores the current location
void Game::exploreLocation()
{
	// Displays the long description of the current location
	std::string description = currentLocation->getLongDescription();
	std::cout << "You are in " << toLower(description) << "\n";
	
	// Displays the exits of the current location
	std::cout << "\nFirst you scan the perimeter and make a mental note of all of the exits:\n";
	currentLocation->displayLocationExits();

	// Displays the characters in the current location
	if (!charactersAtLocation.empty())
	{
		std::cout << "\nNext you look around to see if there is anyone else here with you:\n";
		for (Character* character : charactersAtLocation)
		{
			std::cout << character->getLongDescription() << "\n";
		}
	}
	
	// Displays the items in the current location
	if (!itemsAtLocation.empty())
	{
		std::cout << "\nFinally you look around to see if there is anything useful here that you can take with you:\n";
		for (Item* item : itemsAtLocation)
		{
			// Checks if the item type is a key, does not display keys
			if (item->getItemType() != Key)
			{
				std::cout << item->getLongDescription() << "\n";
			}
		}
	}
}

// Checks if the player wins or loses a game of croquet
bool Game::croquetOutcome()
{
	// Randomly gets a 0 or a 1
	int score = getRandomInt(0, 1);

	// Checks if the score was set to 0
	if (score == 0)
	{
		return false; // If the score is 0, the player "loses"
	}

	// If the score is 1, the player "wins"
	return true;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Display Functions
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Displays the players final stats 
void Game::displayFinalStats()
{
	std::cout << "\nFinal stats:\n";
	displayStats();

	// Displays the treasure and player inventories
	displayInventory();
}

// Displays instructions to help the user form their input
void Game::displayInputInstructions()
{
	std::cout << "Input instructions\n";
	std::cout << "\tThis game works by reading your input.\n";
	std::cout << "\tIt parses out different words and classifies them as a type of action [Keyword, Verb, Character, Location, Item, or Direction ]\n";
	std::cout << "\tThen the computer uses that input to figure out what to do next.\n\n";
	std::cout << "\tThe game only keeps track of the last word entered from each category\n";
	std::cout << "\tTherefore it is best to enter actions one at a time\n";
	std::cout << "\t\tExample: The game will read [go north and talk to rabbit], as talk to rabbit\n\n";
	std::cout << "Tips\n";
	std::cout << "\tIf you want two words to be considered as one entry use a hyphen\n";
	std::cout << "\t\tExample: north-east or south-west\n";
	std::cout << "\tTo unlock a door you need the right key\n";
	std::cout << "\tTo unlock a door you must specify the direction, try structuring your response like \"Unlock the southern door\"\n\n";
	std::cout << "Would you like a list of potential actions? (Yes/ No)\n";

	//read the player input again
	setCurrentAction();

	// Checks if the player wants to view a list of the potential input actions
	if (matches(Yes))
	{
		c.displayPotentialActions();
	}
	// If the player enters anything but "yes" control returns to the game
	else
	{
		std::cout << "Returning to the game\n";
	}
}

// Displays the players inventory and the cottage treasure inventory 
void Game::displayInventory()
{
	std::cout << "Alice's Inventory:\n";
	playerInventory.displayInventory();

	// Only displays the cottage inventory once the player has entered it
	if (locations[Cottage].getHasBeenEntered())
	{
		std::cout << "\nCottage Inventory:\n";
		treasureInventory.displayInventory();
	}
}

void Game::displayStats()
{
	// Displays the final friendship scores for each character
	std::cout << "Character Friendship Scores:\n";
	for (int i = 1; i < characters.size(); i++)
	{
		std::cout << characters[i].getName() << ": " << characters[i].getFriendshipScore() << "\n";
	}
	std::cout << "\n";

	// Updates and displays the players total score 
	alice.updateFriendshipScore(characters);
	alice.updateTotalScore();
	alice.displayTotalScore();
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Overloaded Matches Functions
// Tests if the current action element matches the value passed
// Used to check the player input currentAction against the conditions of certain events 
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool Game::matches(Keywords keyword)
{
	return currentAction[K] == keyword;
}

bool Game::matches(Verbs verb)
{
	return currentAction[V] == verb;
}

bool Game::matches(Characters character)
{
	return currentAction[C] == character;
}

bool Game::matches(Locations location)
{
	return currentAction[L] == location;
}

bool Game::matches(Items item)
{
	return currentAction[I] == item;
}

bool Game::matches(Directions direction)
{
	return currentAction[D] == direction;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Current Action Functions
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Sets the current action using an array
// Used for initializing currentAction and for debugging/ hard coding a path for testing
void Game::setCurrentAction(std::array<int, 6> a)
{
	currentAction = a;
}

// Sets the currentAction attribute using player input
// Used for player driven gameplay
void Game::setCurrentAction()
{
	// Prompts player for input
	std::cout << "\nWhat do you want to do next?\n";
	
	// Parse user input
	currentAction = c.parseUserInput();
}

// Returns the current action
std::array<int, 6> Game::getCurrentAction()
{
	return currentAction;
}

// Clears the current action
void Game::resetCurrentAction()
{
	setCurrentAction({ Keywords::NullKeyword, Verbs::NullVerb, Characters::NullCharacter, Directions::NullDirection });
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Current Location Functions
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Sets the current location
void Game::setCurrentLocation(Location* location)
{
	if (location != nullptr)
	{
		currentLocation = location;
	}
	else
	{
		std::cerr << "Error: Attempted to set null location" << std::endl;
	}
}

// Returns the current location
Location Game::getCurrentLocation()
{
	return *currentLocation;
}

// Gets the current locations description depending on whether or not the player has entered the location previously
std::string Game::getCurrentLocationDescription()
{
	std::string description;
	
	// Checks if the location has already been entered returns a short description of the current room
	if (currentLocation->getHasBeenEntered()) 
	{
		description = currentLocation->getShortDescription();
		return toLower(description);
	}

	// If the location has not yet been entered return a detailed description of the location
	else 
	{
		description = currentLocation->getLongDescription();
		return toLower(description);
	}
}