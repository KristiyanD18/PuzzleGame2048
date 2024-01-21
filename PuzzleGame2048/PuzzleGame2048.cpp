/**
*
* Solution to course project #4
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
#include <fstream> // for file handling functions

bool myStrCmp(const char* firstString, const char* secondString) // comapare strings
{
	if (!firstString || !secondString) // check for nullptr
		return 0; //some error value

	while ((*firstString) && (*secondString) && ((*firstString) == (*secondString)))
	{
		firstString++;
		secondString++;
	}

	return !(*firstString - *secondString); // true if equals 0 and false if equals 1
}

bool isNicknameValid(const char* nickname)
{
	return nickname[0] != '\0';
}

char* getNickname()
{
	constexpr size_t MAX_SIZE_INPUT = 1024;
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
	std::cout << "Enter grid size between 4 and 10: ";
	int gridSize;
	std::cin >> gridSize;

	while (!isGridSizeValid(gridSize))
	{
		std::cout << std::endl << "Entered grid size is not valid! Enter grid size between 4 and 10: ";
		std::cin >> gridSize;
	}
	return gridSize;
}

void printGrid(int** grid, size_t size, int newTwoRow, int newTwoCol)
{
	system("cls"); // clean console text
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // for coloring the new 2

	for (int row = 0; row < size; row++)
	{
		std::cout << "|";
		for (int col = 0; col < size; col++)
		{
			if (grid[row][col] == 0)
			{
				std::cout << "\t|"; // if cell is 0, print tab instead of 0
			}
			else if (row == newTwoRow && col == newTwoCol)
			{
				SetConsoleTextAttribute(hConsole, 13); // 13 is for purple color
				std::cout << grid[row][col] << "\t";
				SetConsoleTextAttribute(hConsole, 15); // 15 is for white color
				std::cout << "|";
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
	char command = _getch(); // read a character input from the keyboard

	if (!isCommandValid(command))
	{
		return 0;
	}
	return command;
}

void generateRandomTwoAtEmptyPosition(int** grid, size_t size, int& newTwoRow, int& newTwoCol)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> rowDist(0, size - 1); // random row number from 0 to size - 1
	std::uniform_int_distribution<int> colDist(0, size - 1); // random col number from 0 to size - 1 

	int count = 0;
	while (true)
	{
		int row = rowDist(gen);
		int col = colDist(gen);

		if (grid[row][col] == 0)
		{
			grid[row][col] = 2; // sets 2 at the empty position
			newTwoRow = row;
			newTwoCol = col;
			break;
		}
	}
}

bool hasEmptySpace(int** matrix, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (matrix[i][j] == 0)
			{
				return true;
			}
		}
	}

	return false;
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

bool isMovePossible(int** grid, size_t gridSize)
{
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			if (grid[i][j] == 0 || (j + 1 < gridSize && grid[i][j] == grid[i][j + 1]) ||
				(i + 1 < gridSize && grid[i][j] == grid[i + 1][j])) // checks if there are empty spaces or same neighbours
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

char* getFileName(size_t dimension)
{
	constexpr size_t LENGTH_PATH = 7;
	char* fileName = new char[LENGTH_PATH];
	size_t i = 0;

	if (dimension < 10)
	{
		fileName[i++] = dimension + '0';
	}
	else
	{
		fileName[i++] = '1';
		fileName[i++] = '0';
	}

	fileName[i++] = '.';
	fileName[i++] = 't';
	fileName[i++] = 'x';
	fileName[i++] = 't';
	fileName[i++] = '\0';

	return fileName;
}

int parseCharToInt(const char* input)
{
	size_t iter = 0;
	size_t result = 0;
	while (input[iter] != '\0')
	{
		if (input[iter] < '0' || input[iter]>'9')
		{
			return -1;
		}

		result = result * 10 + input[iter] - '0';
		iter++;
	}

	return result;
}

void myStrcpy(const char* source, char* dest)
{
	if (!source || !dest)
		return;
	while (*source)
	{
		*dest = *source;
		dest++;
		source++;
	}
	*dest = '\0';
}

void updateLeaderboard(int dimension, char* name, int score)
{
	char* fileName = getFileName(dimension);
	std::ifstream leaderboardFile(fileName);

	constexpr size_t MAX_PLAYERS_LEADERBOARD = 5;
	constexpr size_t BUFFER_SIZE = 1024;

	char names[MAX_PLAYERS_LEADERBOARD][BUFFER_SIZE]{ 0 };
	int scores[MAX_PLAYERS_LEADERBOARD]{ 0 };
	char buffer[BUFFER_SIZE];

	for (int i = 0; i < 5; i++)
	{
		leaderboardFile.getline(buffer, BUFFER_SIZE);

		scores[i] = parseCharToInt(buffer);
		leaderboardFile.getline(names[i], BUFFER_SIZE);

		if (score > scores[i])
		{
			scores[i] = score;

			myStrcpy(name, names[i]);
			scores[i] = score;

			break;
		}
	}
	leaderboardFile.close();

	std::ofstream leaderboardFileOut(fileName);

	int i = 0;
	while (names)
	{
		leaderboardFileOut << scores[i] << std::endl;
		leaderboardFileOut << names[i] << std::endl;
		i++;
	}

	leaderboardFileOut.close();

	delete[] fileName;
}

void startGame()
{
	char* nickname = getNickname(); // get nickname

	size_t gridSize = getGridSize(); // get size of grid

	int** grid = createGrid(gridSize); // create grid by given size

	int newTwoRow, newTwoCol;
	generateRandomTwoAtEmptyPosition(grid, gridSize, newTwoRow, newTwoCol); // generate 2 at random empty position in grid

	int score = 2; // score is added as new 2 is generated

	printGrid(grid, gridSize, newTwoRow, newTwoCol); // print grid with the generated 2

	printScore(score); // print score

	while (isMovePossible(grid, gridSize))
	{
		char command = getCommand(); // take command wasd from user

		switch (command) // move by given command
		{
			//case 0: isMoved = false;
		case 'w': moveUp(grid, gridSize);  break;
		case 'a': moveLeft(grid, gridSize); break;
		case 's': moveDown(grid, gridSize); break;
		case 'd': moveRight(grid, gridSize); break;
		}

		if (hasEmptySpace(grid, gridSize))
		{
			generateRandomTwoAtEmptyPosition(grid, gridSize, newTwoRow, newTwoCol); // generate 2 at random empty position
			score += 2;
		}

		printGrid(grid, gridSize, newTwoRow, newTwoCol); // print grid with the generated 2

		printScore(score); // print score
	}

	updateLeaderboard(gridSize, nickname, score);
	deleteGrid(grid, gridSize); // delete grid
}

char* inputStr()
{
	constexpr size_t BUFFER_SIZE = 1024;
	char* input = new char[BUFFER_SIZE];
	std::cin.getline(input, BUFFER_SIZE);
	return input;
}

int parseNum(const char* input)
{
	size_t iter = 0;
	size_t result = 0;
	while (input[iter] != '\0')
	{
		if (input[iter] < '0' || input[iter]>'9')
		{
			return -1;
		}

		result = result * 10 + input[iter] - '0';
		iter++;
	}

	return result;
}

int inputNum()
{
	char* input = inputStr();
	int result = parseNum(input);
	delete[] input;
	return result;
}

void leaderboard()
{
	std::cout << "Enter dimension you want to see leaderboard in: ";

	int dimension = inputNum();
	while (dimension < 4 || dimension > 10)
	{
		void clearScreen();
		std::cout << "Invalid dimension! Should be a number between 4  and 10.\n"
			<< "Enter new: ";
		dimension = inputNum();
	}

	size_t count = 0;
	char* fileName = getFileName(dimension);
	std::ifstream leaderboardFile(fileName);

	constexpr size_t BUFFER_SIZE = 1024;

	char name[BUFFER_SIZE];
	size_t score;
	char buffer[BUFFER_SIZE];
	int i = 5;

	for (size_t i = 1; i <= 5; i++)
	{
		leaderboardFile.getline(buffer, BUFFER_SIZE);
		if (buffer == "")
		{
			break;
		}

		score = parseNum(buffer);
		leaderboardFile.getline(name, BUFFER_SIZE);
		std::cout << (i) << ". " << score << " " << name << std::endl;
	}

	leaderboardFile.close();
	std::cout << "---------" << std::endl;

	delete[] fileName;
}

void showMenu()
{
	std::cout << "Menu:\n1. Start game \n2. Leaderboard \n3. Quit" << "\n";
}

void runGame()
{
	constexpr size_t MAX_SIZE_INPUT = 1024;
	char inputCommand[MAX_SIZE_INPUT];
	showMenu();

	while (true)
	{
		std::cout << "\nChoose from the menu here: ";
		std::cin.getline(inputCommand, MAX_SIZE_INPUT);

		if (myStrCmp(inputCommand, "Start game"))
		{
			startGame();
		}
		else if (myStrCmp(inputCommand, "Leaderboard"))
		{
			leaderboard();
		}
		else if (myStrCmp(inputCommand, "Quit"))
		{
			std::cout << "Exited game successfully!" << std::endl;
			return;
		}
		else
		{
			std::cout << "Entered selection is not valid!" << std::endl;
		}
	}
}

int main()
{
	runGame();

	return 0;
}