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

constexpr int MAX_SIZE_INPUT = 1024;

bool isGridSizeValid(const char* gridSize)
{
	unsigned size = gridSize[0] - '0';
	return size >= 4 && size <= 10;
}

void getNickname(char* nickname)
{
	std::cout << "Enter your Nickname here: ";
	std::cin.getline(nickname, MAX_SIZE_INPUT);
}

int getGridSize()
{
	char gridSize[MAX_SIZE_INPUT];
	std::cout << "Enter grid size between 4 and 10: ";
	std::cin.getline(gridSize, MAX_SIZE_INPUT);

	while (!isGridSizeValid(gridSize))
	{
		std::cout << "Entered grid size is not valid! Enter grid size between 4 and 10: ";
		std::cin >> gridSize;
	}
	return gridSize[0] - '0';
}

void printGrid(int** grid, size_t size)
{
	for (size_t row = 0; row < size; row++)
	{
		for (size_t col = 0; col < size; col++)
		{
			std::cout << grid[row][col] << std::endl;
		}
	}
}

int** createGrid(size_t size)
{
	int** grid = new int* [size];

	for (size_t i = 0; i < size; i++)
	{
		grid[i] = new int[size] { 0 };
	}

	return grid;
}

void deleteGrid(int** grid, size_t size)
{
	for (size_t i = 0; i < size; i++) {
		delete[] grid[i];
	}

	delete[] grid;
}

void startGame()
{
	// get nickname
	char nickname[MAX_SIZE_INPUT];
	getNickname(nickname);

	// get size of grid
	size_t gridSize = getGridSize();

	// create grid by given size
	int** grid = createGrid(gridSize);

	// print the grid
	printGrid(grid, gridSize);



	// delete grid
	deleteGrid(grid, gridSize);
	
	// print score
}

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

void runGame()
{
	char inputCommand[MAX_SIZE_INPUT];

	std::cout << "Menu:\n1. Start game \n2. Leaderboard \n3. Quit" << "\n\n";

	while (true)
	{
		std::cout << "Enter your selection here: ";
		std::cin.getline(inputCommand, MAX_SIZE_INPUT);

		if (isEqual(inputCommand, "Start game"))
		{
			// functions when given start game
			startGame();
			std::cout << "start";
		}
		else if (isEqual(inputCommand, "Leaderboard"))
		{
			// functions when given leaderboard

			std::cout << "leaderboard";
		}
		else if (isEqual(inputCommand, "Quit"))
		{
			return;
		}
	}
}

int main()
{
	runGame();

}