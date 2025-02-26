#include "inputUI.h"

/*******************************************************************************************************************************************************************************************
* The InputUI Class
* Manages the input user interface
*******************************************************************************************************************************************************************************************/


//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Input processing functions
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void InputUI::setAction(Actions a)
{
	action = a;
}

Actions InputUI::getAction()
{
	return action;
}

void InputUI::setCurrentGame(Game* g)
{
	currentGame = g;
}

Game* InputUI::getCurrrentGame()
{
	return currentGame;
}

std::array<int, 4> InputUI::setCurrentAction()
{
	currentGame->setCurrentAction(parseUserInput());

	checkNeedHelp(); // Everytime a the current action is updated it checks if the user needs help
	return currentGame->getCurrentAction();
}

std::string InputUI::setUserInput()
{
	std::string input;

	// Get a line from a user
	std::getline(std::cin, input);

	return input;
}

std::array<int, 4> InputUI::parseUserInput()
{
	int keyword = NullKeyword;
	int verb = NullVerb;
	int noun = NullNoun;
	int adjective = NullAdjective;

	std::string input = setUserInput();

	toLower(input);

	while (input.empty())  // Need to test that this actually works after getUserInput is implmented
	{
		std::cout << "Line was empty, please re-enter input\n";
		input = setUserInput();
	}

	std::stringstream inputStream(input);
	std::string token;

	while (std::getline(inputStream, token, ' '))
	{
		if (token.empty()) continue;

		if (searchMap(action.getKeywordMap(), token, keyword))
		{
			continue;
		}

		if (searchMap(action.getVerbMap(), token, verb))
		{
			continue;
		}

		if (searchMap(action.getNounMap(), token, noun))
		{
			continue;
		}

		if (searchMap(action.getAdjectiveMap(), token, adjective))
		{
			continue;
		}
	}

	std::cout //For debugging
		<< "Keyword: " << keyword
		<< "\nVerb: " << verb
		<< "\nNoun: " << noun
		<< "\nAdj: " << adjective
		<< std::endl;

	return { keyword, verb, noun, adjective }; // Returns a temporary array
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Functions to help the user with their input
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void InputUI::checkNeedHelp()
{
	if (currentGame->getCurrentAction()[Keyword] == Help)
	{
		displayInputInstructions();
	}
}

void InputUI::displayInputInstructions()
{
	std::cout << "This game works by reading your input."
		<< "\nIt parses out different words and classifies them as a verb, a noun, or an adjective."
		<< "\nThen the computer uses that input to figure out what to do next."
		<< "\nFor example try structuring your response like \"walk through door to the north\"."
		<< "\nWould you like a list of potential actions?" << std::endl;

	// std::array<int, 4> currentAction = getCurrentAction(); //read the user input again
	currentGame->setCurrentAction(parseUserInput());

	if (currentGame->getCurrentAction()[Keyword] == Yes)
	{

		displayPotentialActions();
	}
	else if (currentGame->getCurrentAction()[Keyword] == No)
	{
		std::cout << "Alright lets get back to the game" << std::endl;
	}
}

void InputUI::displayPotentialActions()
{
	std::cout << "PotentialActions:\n";
	action.print();
}