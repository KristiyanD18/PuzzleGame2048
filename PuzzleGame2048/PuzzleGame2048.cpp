/**
*
* Solution to course project # 4
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2023/2024
*
* @author Kristiyan Dimov
* @idnumber 5MI0600358
* @compiler VS
*
* <main code>
*
*/

#include <iostream>
using namespace std;

bool isEqual(const char* firstWord, const char* secondWord)
{
	if (!firstWord || !secondWord)
	{
		return 0; //some error value
	}

	int index = 0;
	while (firstWord[index] != '\0' && secondWord[index] != '\0')
	{
		if (firstWord[index] != secondWord[index])
		{
			return false;
		}

		index++;
	}

	return true;
}

void startGame() 
{
	constexpr int MAX_SIZE_INPUT = 1024;
	char inputCommand[MAX_SIZE_INPUT];

	std::cout << "Select command:\n1. Start game \n2. Leaderboard \n3. Quit" << std::endl;

	while (true)
	{
		unsigned a = 1;
		std::cout << "Input your selection here: ";
		std::cin.getline(inputCommand, MAX_SIZE_INPUT);

		if (isEqual(inputCommand, "Start game"))
		{
			// functions when given start game
			std::cout << "start";
		}
		else if (isEqual(inputCommand, "Leaderboard"))
		{
			// functions when given leaderboard

			std::cout << "leaderboard";
		}
		else if (isEqual(inputCommand, "Quit"))
		{
			// functions when given quit

			std::cout << "quit";
		}
		else
		{
			continue;
		}
	}
}

int main()
{
	startGame();
}
