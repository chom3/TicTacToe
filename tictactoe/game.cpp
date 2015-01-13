#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>

//A spot on the board will contain a visited value and a X or O
struct spot{
	bool visited;
	std::string val;
	std::string spc;
	int init;
};

//Function to create a TTT board.
std::vector<std::vector<spot>> createBoard()
{
	int counter = 0;
	std::vector<std::vector<spot>> board(3, std::vector<spot>(3));
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			board[i][j].visited = false;
			board[i][j].init = counter;
			counter++;
		}
	}
	//initialize .val to different letters to avoid winning conditions early
	board[0][0].spc = "a";
	board[0][1].spc = "b";
	board[0][2].spc = "c";
	board[1][0].spc = "d";
	board[1][1].spc = "e";
	board[1][2].spc = "f";
	board[2][0].spc = "g";
	board[2][1].spc = "h";
	board[2][2].spc = "i";
	return board;
}
//Function to print a TTT board.
void printBoard(std::vector<std::vector<spot>> board)
{
	std::cout << board[0][0].val << " | ";
	std::cout << board[0][1].val << " | ";
	std::cout << board[0][2].val << std::endl;
	std::cout << " -------" << std::endl;
	std::cout << board[1][0].val << " | ";
	std::cout << board[1][1].val << " | ";
	std::cout << board[1][2].val << std::endl;
	std::cout << " -------" << std::endl;
	std::cout << board[2][0].val << " | ";
	std::cout << board[2][1].val << " | ";
	std::cout << board[2][2].val;
}

//Function to print initial board to demonstrate key values.
void printInitBoard(std::vector<std::vector<spot>> board)
{
	std::cout << board[0][0].init << " | ";
	std::cout << board[0][1].init << " | ";
	std::cout << board[0][2].init << std::endl;
	std::cout << " -------" << std::endl;
	std::cout << board[1][0].init << " | ";
	std::cout << board[1][1].init << " | ";
	std::cout << board[1][2].init << std::endl;
	std::cout << " -------" << std::endl;
	std::cout << board[2][0].init << " | ";
	std::cout << board[2][1].init << " | ";
	std::cout << board[2][2].init;
}

//Function to simulate winning conditions.
bool winningCheck(std::vector<std::vector<spot>> board)
{
	//win by rows
	if (board[0][0].spc == board[0][1].spc && board[0][1].spc == board[0][2].spc){ return false; }
	if (board[1][0].spc == board[1][1].spc && board[1][1].spc == board[1][2].spc){ return false; }
	if (board[2][0].spc == board[2][1].spc && board[2][1].spc == board[2][2].spc){ return false; }
	//win by columns
	if (board[0][0].spc == board[1][0].spc && board[1][0].spc == board[2][0].spc){ return false; }
	if (board[0][1].spc == board[1][1].spc && board[1][1].spc == board[2][1].spc){ return false; }
	if (board[0][2].spc == board[1][2].spc && board[1][2].spc == board[2][2].spc){ return false; }
	//win by diagonals
	if (board[0][0].spc == board[1][1].spc && board[1][1].spc == board[2][2].spc){ return false; }
	if (board[0][2].spc == board[1][1].spc && board[1][1].spc == board[2][0].spc){ return false; }
	return true;
}

//Function for single player, easy mode. The computer will pick a random square.
void OPGameE(std::vector<std::vector<spot>> board, std::string name)
{
	int counter = 0;
	int turnInput = -1;
	bool winCon = true;
	while (winCon)
	{
		printBoard(board);
		if (counter % 2 == 0)
		{
			std::cout << std::endl;
			std::cout << name << "'s turn! \nChoose a place to mark." << std::endl;
			std::cin >> turnInput;
			std::cin.clear();
			std::cin.ignore(100, '\n');
			if (turnInput >= 0)
			{
				if (turnInput < 9)
				{
					for (int i = 0; i < 3; i++)
					{
						for (int j = 0; j < 3; j++)
						{
							if (turnInput == board[i][j].init)
							{
								if (board[i][j].visited == false)
								{
									board[i][j].visited = true;
									board[i][j].val = "X";
									board[i][j].spc = "X";
									counter++;
								}
								else
								{
									std::cout << "That spot is already taken!" << std::endl;
								}
							}
						}
					}
				}
				else
				{
					std::cout << "Invalid input." << std::endl;
				}
			}
			else
			{
				std::cout << "Invalid input." << std::endl;
				turnInput = -1;
			}
		}
		else
		{
			std::cout << "Computer's turn!" << std::endl;
			bool cGo = true;
			while (cGo)
			{
				int v1 = rand() % 2;
				int v2 = rand() % 2;
				if (board[v1][v2].visited == false)
				{
					board[v1][v2].visited = true;
					board[v1][v2].val = "O";
					board[v1][v2].spc = "O";
					counter++;
					cGo = false;
				}
			}
		}
		winCon = winningCheck(board);
		int tieCount = 0;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (board[i][j].visited)
				{
					tieCount++;
				}
			}
		}
		if (tieCount == 9)
		{
			std::cout << "It's a tie!" << std::endl;
			printBoard(board);
			break;
		}
	}
	if (winCon == false)
	{
		counter--;
		if (counter % 2 == 0)
		{
			std::cout << name << " has won!" << std::endl;
			printBoard(board);
		}
		else
		{
			std::cout << "Computer" << " has won!" << std::endl;
			printBoard(board);
		}
	}
}
//Function for single player, hard mode. The computer will play to tie and never lose.
void OPGameH(std::vector<std::vector<spot>> board, std::string name)
{
	int counter = 0;
	int turnInput = -1;
	bool winCon = true;
	while (winCon)
	{
		printBoard(board);
		if (counter % 2 == 0)
		{
			std::cout << std::endl;
			std::cout << '\n' << name << "'s turn! \nChoose a place to mark." << std::endl;
			std::cin >> turnInput;
			std::cin.clear();
			std::cin.ignore(100, '\n');
			if (turnInput >= 0)
			{
				if (turnInput < 9)
				{
					for (int i = 0; i < 3; i++)
					{
						for (int j = 0; j < 3; j++)
						{
							if (turnInput == board[i][j].init)
							{
								if (board[i][j].visited == false)
								{
									board[i][j].visited = true;
									board[i][j].val = "X";
									board[i][j].spc = "X";
									counter++;
								}
								else
								{
									std::cout << "That spot is already taken!" << std::endl;
								}
							}
						}
					}
				}
				else
				{
					std::cout << "Invalid input." << std::endl;
				}
			}
			else
			{
				std::cout << "Invalid input." << std::endl;
				turnInput = -1;
			}
		}
		else
		{
			std::cout << "\nComputer's turn!" << std::endl;
			//check for win by rows
			if (board[0][0].val == "X" && board[0][1].val == "X" && board[0][2].visited == false)
			{
				board[0][2].visited = true;
				board[0][2].val = "O";
				board[0][2].spc = "O";
				counter++;
			}
			else if (board[0][0].val == "X" && board[0][2].val == "X" && board[0][1].visited == false)
			{
				board[0][1].visited = true;
				board[0][1].val = "O";
				board[0][1].spc = "O";
				counter++;
			}
			else if (board[0][1].val == "X" && board[0][2].val == "X" && board[0][0].visited == false)
			{
				board[0][0].visited = true;
				board[0][0].val = "O";
				board[0][0].spc = "O";
				counter++;
			}
			else if (board[1][0].val == "X" && board[1][1].val == "X" && board[1][2].visited == false)
			{
				board[1][2].visited = true;
				board[1][2].val = "O";
				board[1][2].spc = "O";
				counter++;
			}
			else if (board[1][0].val == "X" && board[1][2].val == "X" && board[1][1].visited == false)
			{
				board[1][1].visited = true;
				board[1][1].val = "O";
				board[1][1].spc = "O";
				counter++;
			}
			else if (board[1][1].val == "X" && board[1][2].val == "X" && board[1][0].visited == false)
			{
				board[1][0].visited = true;
				board[1][0].val = "O";
				board[1][0].spc = "O";
				counter++;
			}
			else if (board[2][0].val == "X" && board[2][1].val == "X" && board[2][2].visited == false)
			{
				board[2][2].visited = true;
				board[2][2].val = "O";
				board[2][2].spc = "O";
				counter++;
			}
			else if (board[2][0].val == "X" && board[2][2].val == "X" && board[2][1].visited == false)
			{
				board[2][1].visited = true;
				board[2][1].val = "O";
				board[2][1].spc = "O";
				counter++;
			}
			else if (board[2][1].val == "X" && board[2][2].val == "X" && board[2][0].visited == false)
			{
				board[2][0].visited = true;
				board[2][0].val = "O";
				board[2][0].spc = "O";
				counter++;
			}
			//wins by columns
			else if (board[0][0].val == "X" && board[1][0].val == "X" && board[2][0].visited == false)
			{
				board[2][0].visited = true;
				board[2][0].val = "O";
				board[2][0].spc = "O";
				counter++;
			}
			else if (board[0][0].val == "X" && board[2][0].val == "X" && board[1][0].visited == false)
			{
				board[1][0].visited = true;
				board[1][0].val = "O";
				board[1][0].spc = "O";
				counter++;
			}
			else if (board[1][0].val == "X" && board[2][0].val == "X" && board[0][0].visited == false)
			{
				board[0][0].visited = true;
				board[0][0].val = "O";
				board[0][0].spc = "O";
				counter++;
			}
			else if (board[0][1].val == "X" && board[1][1].val == "X" && board[2][1].visited == false)
			{
				board[2][1].visited = true;
				board[2][1].val = "O";
				board[2][1].spc = "O";
				counter++;
			}
			else if (board[0][1].val == "X" && board[2][1].val == "X" && board[1][1].visited == false)
			{
				board[1][1].visited = true;
				board[1][1].val = "O";
				board[1][1].spc = "O";
				counter++;
			}
			else if (board[1][1].val == "X" && board[2][1].val == "X" && board[0][1].visited == false)
			{
				board[0][1].visited = true;
				board[0][1].val = "O";
				board[0][1].spc = "O";
				counter++;
			}
			else if (board[0][2].val == "X" && board[1][2].val == "X" && board[2][2].visited == false)
			{
				board[2][2].visited = true;
				board[2][2].val = "O";
				board[2][2].spc = "O";
				counter++;
			}
			else if (board[0][2].val == "X" && board[2][2].val == "X" && board[1][2].visited == false)
			{
				board[1][2].visited = true;
				board[1][2].val = "O";
				board[1][2].spc = "O";
				counter++;
			}
			else if (board[1][2].val == "X" && board[2][2].val == "X" && board[0][2].visited == false)
			{
				board[0][2].visited = true;
				board[0][2].val = "O";
				board[0][2].spc = "O";
				counter++;
			}
			//wins by diagonals
			else if (board[0][0].val == "X" && board[1][1].val == "X" && board[2][2].visited == false)
			{
				board[2][2].visited = true;
				board[2][2].val = "O";
				board[2][2].spc = "O";
				counter++;
			}
			else if (board[0][0].val == "X" && board[2][2].val == "X" && board[1][1].visited == false)
			{
				board[1][1].visited = true;
				board[1][1].val = "O";
				board[1][1].spc = "O";
				counter++;
			}
			else if (board[1][1].val == "X" && board[2][2].val == "X" && board[0][0].visited == false)
			{
				board[0][0].visited = true;
				board[0][0].val = "O";
				board[0][0].spc = "O";
				counter++;
			}
			else if (board[0][2].val == "X" && board[1][1].val == "X" && board[2][0].visited == false)
			{
				board[2][2].visited = true;
				board[2][2].val = "O";
				board[2][2].spc = "O";
				counter++;
			}
			else if (board[0][2].val == "X" && board[2][0].val == "X" && board[1][1].visited == false)
			{
				board[1][1].visited = true;
				board[1][1].val = "O";
				board[1][1].spc = "O";
				counter++;
			}
			else if (board[1][1].val == "X" && board[2][0].val == "X" && board[0][2].visited == false)
			{
				board[0][2].visited = true;
				board[0][2].val = "O";
				board[0][2].spc = "O";
				counter++;
			}
			else
			{
				bool cGo = true;
				while (cGo)
				{
					int v1 = rand() % 2;
					int v2 = rand() % 2;
					if (board[v1][v2].visited == false)
					{
						board[v1][v2].visited = true;
						board[v1][v2].val = "O";
						board[v1][v2].spc = "O";
						counter++;
						cGo = false;
					}
				}
			}
		}
		winCon = winningCheck(board);
		int tieCount = 0;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (board[i][j].visited)
				{
					tieCount++;
				}
			}
		}
		if (tieCount == 9)
		{
			std::cout << "It's a tie!" << std::endl;
			printBoard(board);
			break;
		}
	}
	if (winCon == false)
	{
		counter--;
		if (counter % 2 == 0)
		{
			std::cout << name << " has won!" << std::endl;
			printBoard(board);
		}
		else
		{
			std::cout << "Computer" << " has won!" << std::endl;
			printBoard(board);
		}
	}
}
//Two Player Game turn based game.
void TPGame(std::vector<std::vector<spot>> board, std::string name1, std::string name2)
{
	int counter = 0;
	int turnInput = -1;
	bool winCon = true;
	while (winCon)
	{
		printBoard(board);
		if (counter % 2 == 0)
		{
			std::cout << std::endl;
			std::cout << name1 << "'s turn!\nChoose a place to mark." << std::endl;
			std::cin >> turnInput;
			std::cin.clear();
			std::cin.ignore(100, '\n');
			if (turnInput >= 0)
			{
				if (turnInput < 9)
				{
					for (int i = 0; i < 3; i++)
					{
						for (int j = 0; j < 3; j++)
						{
							if (turnInput == board[i][j].init)
							{
								if (board[i][j].visited == false)
								{
									board[i][j].visited = true;
									board[i][j].val = "X";
									board[i][j].spc = "X";
									counter++;
								}
								else
								{
									std::cout << "That spot is already taken!" << std::endl;
								}
							}
						}
					}
				}
				else
				{
					std::cout << "Invalid input." << std::endl;
				}
			}
			else
			{
				std::cout << "Invalid input." << std::endl;
				turnInput = -1;
			}
		}
		else
		{
			std::cout << std::endl;
			std::cout << name2 << "'s turn!\nChoose a place to mark." << std::endl;
			std::cin >> turnInput;
			std::cin.clear();
			std::cin.ignore(100, '\n');
			if (turnInput >= 0)
			{
				if (turnInput < 9)
				{
					for (int i = 0; i < 3; i++)
					{
						for (int j = 0; j < 3; j++)
						{
							if (turnInput == board[i][j].init)
							{
								if (board[i][j].visited == false)
								{
									board[i][j].visited = true;
									board[i][j].val = "O";
									board[i][j].spc = "O";
									counter++;
								}
								else
								{
									std::cout << "That spot is already taken!" << std::endl;
								}
							}
						}
					}
				}
				else
				{
					std::cout << "Invalid input." << std::endl;
				}
			}
			else
			{
				std::cout << "Invalid input." << std::endl;
				turnInput = -1;
			}
		}
		winCon = winningCheck(board);
		int tieCount = 0;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (board[i][j].visited)
				{
					tieCount++;
				}
			}
		}
		if (tieCount == 9)
		{
			std::cout << "It's a tie!" << std::endl;
			printBoard(board);
			break;
		}
	}
	if (winCon == false)
	{
		counter--;
		if (counter % 2 == 0)
		{
			std::cout << name1 << " has won!" << std::endl;
			printBoard(board);
		}
		else
		{
			std::cout << name2 << " has won!" << std::endl;
			printBoard(board);
		}
	}
}


int main()
{
	std::string option;
	std::string quit;
	bool play = true;
	std::cout << "Welcome to Tic-Tac-Toe!" << std::endl;
	std::vector<std::vector<spot>> board = createBoard();
	std::cout << "Board created. " << std::endl;
	printInitBoard(board);
	std::cout << "\nType in the corresponding numbers in order to fill the spaces on your turn. \nSelect an option: " << std::endl;
	while (play)
	{
		std::cout << "1. 1P Game \n2. 2P Game" << std::endl;
		std::cin >> option;
		std::cin.clear();
		std::cin.ignore(100, '\n');
		if (option == "1")
		{
			std::string name;
			std::cout << "You have chosen 1P Game." << std::endl;
			std::cout << "Enter name." << std::endl;
			std::cin >> name;
			std::cout << "Select difficulty: " << std::endl;
			std::cout << "1. Easy \n2. Hard" << std::endl;
			std::cin >> option;
			std::cin.clear();
			std::cin.ignore(100, '\n');
			if (option == "1")
			{
				OPGameE(board, name);
				std::cout << std::endl;
				if (quit == "q")
				{
					std::cout << "Quit." << std::endl;
					break;
				}
			}
			else if (option == "2")
			{
				OPGameH(board, name);
				std::wcout << std::endl;
				if (quit == "q")
				{
					std::wcout << "Quit." << std::endl;
					break;
				}
			}
			else
			{
				std::cout << "That wasn't an option." << std::endl;
			}
		}
		else if (option == "2")
		{
			std::string name1;
			std::string name2;
			std::string valid;
			int confirm = 0;
			std::cout << "You have chosen 2P Game." << std::endl;
			std::cout << "Enter name for player 1: " << std::endl;
			std::cin >> name1;
			std::cin.clear();
			std::cin.ignore(100, '\n');
			std::cout << "Enter name for player 2: " << std::endl;
			std::cin >> name2;
			std::cin.clear();
			std::cin.ignore(100, '\n');
			while (confirm == 0)
			{
				std::cout << "P1 is " << name1 << " and P2 is " << name2 << " \n Is this correct? (y/n)" << std::endl;
				std::cin >> valid;
				std::cin.clear();
				std::cin.ignore(100, '\n');
				if (valid == "Y" || valid == "y")
				{
					confirm = 1;
				}
				else if (valid == "N" || valid == "n")
				{
					confirm = 0;
					std::cout << "Enter name for player 1: " << std::endl;
					std::cin >> name1;
					std::cin.clear();
					std::cin.ignore(100, '\n');
					std::cout << "Enter name for player 2: " << std::endl;
					std::cin >> name2;
					std::cin.clear();
					std::cin.ignore(100, '\n');
				}
				else
				{
					std::cout << "Invalid option." << std::endl;
					confirm = 0;
				}
			}
			TPGame(board, name1, name2);
			std::cout << "\nType a key to play again or type q to quit!" << std::endl;
			std::cin >> quit;
			std::cin.clear();
			std::cin.ignore(100, '\n');
			if (quit == "q")
			{
				std::cout << "Quit." << std::endl;
				break;
			}
		}
		else if (option == "q")
		{
			std::cout << "Quit." << std::endl;
			play = false;
		}
		else
		{
			std::cout << "Invalid option! Type q to quit." << std::endl;
		}
	}
}