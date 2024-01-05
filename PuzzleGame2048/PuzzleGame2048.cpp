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
#include <windows.h> // for coloring output text
using namespace std;

constexpr size_t MAX_SIZE_INPUT = 1024;
int randomIndex = 0;

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

void getNickname(char* nickname)
{
	std::cout << "Enter your Nickname here: ";
	std::cin.getline(nickname, MAX_SIZE_INPUT);
}

bool isGridSizeValid(const char* gridSize)
{
	unsigned size = gridSize[0] - '0';
	return size >= 4 && size <= 10;
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
	system("cls");
	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			std::cout << grid[row][col] << " ";
		}
		std::cout << std::endl;
	}
}

int** createGrid(size_t size)
{
	int** grid = new int* [size];

	for (int i = 0; i < size; i++)
	{
		grid[i] = new int[size] { 0 };
	}

	return grid;
}

void deleteGrid(int** grid, int size)
{
	for (int i = 0; i < size; i++) 
	{
		delete[] grid[i];
	}

	delete[] grid;
}

void getCommand(char* command)
{
	std::cout << "Enter command (wasd): ";
	std::cin.getline(command, MAX_SIZE_INPUT);
}

void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

int randomTwoOrFour()
{
	if ((randomIndex++) % 3 == 0)
	{
		return 2;
	}
	return 4;
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


	// move logic here:
	// create random 2 or 4 at empty position
	// function

	// get command wasd
	char command[MAX_SIZE_INPUT];

	while (true)
	{
		// here make a cell 2
		//int randomCol = random();
		bool stop = false;
		for (int row = 0; row < gridSize && !stop; row++)
		{
			for (int col = 0; col < gridSize && !stop; col++)
			{
				if (grid[row][col] == 0)
				{
					grid[row][col] = 2;
					stop = true;
				}
			}
		}

		// print grid with the new 2
		printGrid(grid, gridSize);

		// take command from user
		getCommand(command);

		// move with wasd
		if (isEqual(command, "d"))
		{
			for (int row = 0; row < gridSize; row++) 
			{
				for (int col = 0; col < gridSize - 1; col++)
				{
					if (grid[row][col] != 0)
					{
						if (grid[row][col + 1] == 0)
						{
							swap(grid[row][col + 1], grid[row][col]);
						}
						else if (grid[row][col + 1] == grid[row][col])
						{
							grid[row][col + 1] += grid[row][col];
							grid[row][col] = 0;
						}
					}
				}
			}
		}

		if (isEqual(command, "a"))
		{
			for (int row = 0; row < gridSize; row++)
			{
				for (int col = gridSize - 1; col > 0; col--)
				{
					if (grid[row][col] != 0)
					{
						if (grid[row][col - 1] == 0)
						{
							swap(grid[row][col - 1], grid[row][col]);
						}
						else if (grid[row][col - 1] == grid[row][col])
						{
							grid[row][col - 1] += grid[row][col];
							grid[row][col] = 0;
						}
					}
				}
			}
		}

		if (isEqual(command, "s"))
		{
			for (int row = 0; row < gridSize - 1; row++)
			{
				for (int col = 0; col < gridSize; col++)
				{
					if (grid[row][col] != 0)
					{
						if (grid[row + 1][col] == 0)
						{
							swap(grid[row + 1][col], grid[row][col]);
						}
						else if (grid[row + 1][col] == grid[row][col])
						{
							grid[row + 1][col] += grid[row][col];
							grid[row][col] = 0;
						}
					}
				}
			}
		}

		if (isEqual(command, "w"))
		{
			for (int row = gridSize - 1; row > 0 ; row--)
			{
				for (int col = 0; col < gridSize; col++)
				{
					if (grid[row][col] != 0)
					{
						if (grid[row - 1][col] == 0)
						{
							swap(grid[row - 1][col], grid[row][col]);
						}
						else if (grid[row - 1][col] == grid[row][col])
						{
							grid[row - 1][col] += grid[row][col];
							grid[row][col] = 0;
						}
					}
				}
			}
		}
	}

	// delete grid
	deleteGrid(grid, gridSize);

	// print score
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

	return 0;
}