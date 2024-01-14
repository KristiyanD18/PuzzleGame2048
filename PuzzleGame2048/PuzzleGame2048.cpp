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
#include <random> // for creating random
#include <conio.h> // for non-blocking input in Windows
#include <fstream>
using namespace std;

constexpr size_t MAX_SIZE_INPUT = 1024;

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

bool isNicknameValid(const char* nickname)
{
	return nickname[0] != '\0';
}

char* getNickname()
{
	char nickname[MAX_SIZE_INPUT];
	std::cout << "Enter your nickname here: ";
	std::cin.getline(nickname, MAX_SIZE_INPUT);
	while (!isNicknameValid(nickname))
	{
		std::cout << "Nickname is not valid!\nEnter your nickname here: ";
		std::cin.getline(nickname, MAX_SIZE_INPUT);
	}
	return nickname;
}

bool isGridSizeValid(int gridSize)
{
	return gridSize >= 4 && gridSize <= 10;
}

int getGridSize()
{
	int gridSize;
	std::cout << "Enter grid size between 4 and 10: ";
	std::cin >> gridSize;

	while (!isGridSizeValid(gridSize))
	{
		std::cout << std::endl << "Entered grid size is not valid! Enter grid size between 4 and 10: ";
		std::cin >> gridSize;
	}
	return gridSize;
}

void printGrid(int** grid, size_t size)
{
	system("cls");
	for (int row = 0; row < size; row++)
	{
		std::cout << "|";
		for (int col = 0; col < size; col++)
		{
			if (grid[row][col] == 0)
			{
				std::cout << "\t|";
			}
			else
			{
				std::cout << grid[row][col] << "\t|";
			}
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

bool isCommandValid(char command)
{
	return command == 'w' || command == 'a' || command == 's' || command == 'd';
}

char getCommand()
{
	std::cout << "\nEnter command (wasd): ";
	char command = _getch();

	if (!isCommandValid(command))
	{
		return 0;
	}
	return command;
}

void generaterRandomTwoAtEmptyPosition(int** grid, size_t size)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> rowDist(0, size - 1);
	std::uniform_int_distribution<int> colDist(0, size - 1);

	int count = 0;
	while (count < 2)
	{
		int row = rowDist(gen);
		int col = colDist(gen);

		if (grid[row][col] == 0) {
			grid[row][col] = 2; // Setting 2 at the empty position
			count++;
			break;
		}
	}
}

void moveUp(int** grid, int gridSize)
{
	for (int j = 0; j < gridSize; ++j) {
		int mergeIndex = 0; // Index for merging tiles

		// Start from the top and move downwards
		for (int i = 0; i < gridSize; ++i) {
			if (grid[i][j] != 0) {
				int currentVal = grid[i][j];
				grid[i][j] = 0;
				grid[mergeIndex][j] = currentVal;
				mergeIndex++;
			}
		}

		// Merge tiles with the same value
		for (int i = 0; i < gridSize - 1; ++i) {
			if (grid[i][j] == grid[i + 1][j]) {
				grid[i][j] *= 2;
				grid[i + 1][j] = 0;
			}
		}

		// Shift merged tiles to the top
		mergeIndex = 0;
		for (int i = 0; i < gridSize; ++i)
		{
			if (grid[i][j] != 0)
			{
				int currentVal = grid[i][j];
				grid[i][j] = 0;
				grid[mergeIndex][j] = currentVal;
				mergeIndex++;
			}
		}
	}
}

void moveLeft(int** grid, int gridSize)
{
	for (int i = 0; i < gridSize; ++i) {
		int mergeIndex = 0; // Index for merging tiles

		// Start from the left and move towards the right
		for (int j = 0; j < gridSize; ++j) {
			if (grid[i][j] != 0) {
				int currentVal = grid[i][j];
				grid[i][j] = 0;
				grid[i][mergeIndex] = currentVal;
				mergeIndex++;
			}
		}

		// Merge tiles with the same value
		for (int j = 0; j < gridSize - 1; ++j) {
			if (grid[i][j] == grid[i][j + 1]) {
				grid[i][j] *= 2;
				grid[i][j + 1] = 0;
			}
		}

		// Shift merged tiles to the left
		mergeIndex = 0;
		for (int j = 0; j < gridSize; ++j) {
			if (grid[i][j] != 0) {
				int currentVal = grid[i][j];
				grid[i][j] = 0;
				grid[i][mergeIndex] = currentVal;
				mergeIndex++;
			}
		}
	}
}

void moveDown(int** grid, int gridSize)
{
	for (int j = 0; j < gridSize; ++j) {
		int mergeIndex = gridSize - 1; // Index for merging tiles

		// Start from the bottom and move upwards
		for (int i = gridSize - 1; i >= 0; --i) {
			if (grid[i][j] != 0) {
				int currentVal = grid[i][j];
				grid[i][j] = 0;
				grid[mergeIndex][j] = currentVal;
				mergeIndex--;
			}
		}

		// Merge tiles with the same value
		for (int i = gridSize - 1; i > 0; --i) {
			if (grid[i][j] == grid[i - 1][j]) {
				grid[i][j] *= 2;
				grid[i - 1][j] = 0;
			}
		}

		// Shift merged tiles to the bottom
		mergeIndex = gridSize - 1;
		for (int i = gridSize - 1; i >= 0; --i) {
			if (grid[i][j] != 0) {
				int currentVal = grid[i][j];
				grid[i][j] = 0;
				grid[mergeIndex][j] = currentVal;
				mergeIndex--;
			}
		}
	}
}

void moveRight(int** grid, int gridSize)
{
	for (int i = 0; i < gridSize; ++i) {
		int mergeIndex = gridSize - 1; // Index for merging tiles
		// Start from the right and move towards the left
		for (int j = gridSize - 1; j >= 0; --j) {
			if (grid[i][j] != 0) {
				int currentVal = grid[i][j];
				grid[i][j] = 0;
				grid[i][mergeIndex] = currentVal;
				mergeIndex--;
			}
		}

		// Merge tiles with the same value
		for (int j = gridSize - 1; j > 0; --j) {
			if (grid[i][j] == grid[i][j - 1]) {
				grid[i][j] *= 2;
				grid[i][j - 1] = 0;
			}
		}

		// Shift merged tiles to the right
		mergeIndex = gridSize - 1;
		for (int j = gridSize - 1; j >= 0; --j) {
			if (grid[i][j] != 0) {
				int currentVal = grid[i][j];
				grid[i][j] = 0;
				grid[i][mergeIndex] = currentVal;
				mergeIndex--;
			}
		}
	}
}

bool isMoved(int** grid, bool** isMovedGrid, int size)
{
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			if (grid[i][j] != isMovedGrid[i][j])
			{
				return true;
			}
		}
	}
	return false;
}

bool isEndGame(int** grid, size_t gridSize)
{
	for (int i = 0; i < gridSize - 1; i++)
	{
		for (int j = 0; j < gridSize - 1; j++)
		{
			if (grid[i][j] == 0 || grid[i][j + 1] == 0 || grid[i + 1][j] == 0 || grid[i][j] == grid[i][j + 1] || grid[i][j] == grid[i + 1][j])
			{
				return true;
			}
		}
	}
	return false;
}

void printScore(int score)
{
	std::cout << "\nYour score is: " << score;
}

void startGame()
{
	// get nickname
	char* nickname = getNickname();

	// get size of grid
	size_t gridSize = getGridSize();

	// create grid by given size
	int** grid = createGrid(gridSize);

	// generate 2 at random empty position
	generaterRandomTwoAtEmptyPosition(grid, gridSize);

	// score is added as new 2 is generated
	int score = 2;

	while (isEndGame(grid, gridSize))
	{
		// print grid with the generated 2
		printGrid(grid, gridSize);

		printScore(score);

		// take command wasd from user
		char command = getCommand();

		bool isMoved = true;
		// move by given command
		switch (command)
		{
		case 'w':
			moveUp(grid, gridSize);  break;
		case 'a':
			moveLeft(grid, gridSize); break;
		case 's':
			moveDown(grid, gridSize); break;
		case 'd':
			moveRight(grid, gridSize); break;
		}

		if (isMoved)
		{
			// generate 2 at random empty position
			generaterRandomTwoAtEmptyPosition(grid, gridSize);
			score += 2;
		}
		
	}

	// delete grid
	deleteGrid(grid, gridSize);

	// print score
	

}

void showMenu()
{
	std::cout << "Menu:\n1. Start game \n2. Leaderboard \n3. Quit" << "\n\n";
}

void runGame()
{
	char inputCommand[MAX_SIZE_INPUT];
	showMenu();

	while (true)
	{
		std::cout << "Enter your selection here: ";
		std::cin.getline(inputCommand, MAX_SIZE_INPUT);

		if (isEqual(inputCommand, "Start game"))
		{
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
		std::cout << "\nMenu:\n1. Start game \n2. Leaderboard \n3. Quit" << "\n\n";
	}
}

int main()
{
	runGame();

	return 0;
}