#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdbool.h>

#define ROWS 20
#define COLS 20

#define HAS_NO_MOVES -2
#define INVALID -1
#define VALID 0
#define WIN 1
#define TIE 2

void printBoard(char board[][COLS], int size);
void cleanBoard(char board[][COLS], int size);

int printMenu();
int sizeChoise(int choise);
char findOppenent(char player);
void declareWinner();

int newMove(char board[][COLS], int size, char player);
int checkValidMove(char board[][COLS], int choiseRow, int choiseCol);
int checkIfHasMoves(char board[][COLS], int size, char player);

int isWin(char board[][COLS], int size, char player);
int isTie(char board[][COLS], int size, char player);
int findScore(char board[][COLS], int size, char player);

int checkRight(char board[][COLS], int row, int col, int size, char player);
int checkLeft(char board[][COLS], int row, int col, int size, char player);
int checkUp(char board[][COLS], int row, int col, int size, char player);
int checkDown(char board[][COLS], int row, int col, int size, char player);
int checkDiagonalDownLeft(char board[][COLS], int row, int col, int size, char player);
int checkDiagonalDownRight(char board[][COLS], int row, int col, int size, char player);
int checkDiagonalUpRight(char board[][COLS], int row, int col, int size, char player);
int checkDiagonalUpLeft(char board[][COLS], int row, int col, int size, char player);

void changeRight(char board[][COLS], int row, int col, int size, char player);
void changeLeft(char board[][COLS], int row, int col, int size, char player);
void changeUp(char board[][COLS], int row, int col, int size, char player);
void changeDown(char board[][COLS], int row, int col, int size, char player);
void changeDiagonalDownLeft(char board[][COLS], int row, int col, int size, char player);
void changeDiagonalDownRight(char board[][COLS], int row, int col, int size, char player);
void changeDiagonalUpLeft(char board[][COLS], int row, int col, int size, char player);
void changeDiagonalUpRight(char board[][COLS], int row, int col, int size, char player);



void main()
{
	char board[ROWS][COLS];
	int logicBoardSize = 0;
	char player = 'x';
	int moveResault, noMovesCouner = 0;// noMovesCounter counts how many times in a raw the player had no moves
	int scoreX, scoreO;

	logicBoardSize = sizeChoise(printMenu());

	if (logicBoardSize > 0)
	{
		cleanBoard(board, logicBoardSize);
		printBoard(board, logicBoardSize);

		moveResault = newMove(board, logicBoardSize, player);
		while (moveResault < 1)// while not win or tie
		{

			if (moveResault == INVALID)
				printf("Invalid move, please choose another cell.\n");

			else if (moveResault == VALID)
			{
				system("cls");
				noMovesCouner = 0;

				scoreX = findScore(board, logicBoardSize, 'x');
				scoreO = findScore(board, logicBoardSize, 'o');
				printf("Score: x - %d,  o - %d\n\n", scoreX, scoreO);
				
				printBoard(board, logicBoardSize);
				player = findOppenent(player);
			}
			else if (moveResault == HAS_NO_MOVES)
			{
				printf("Player %c has no moves.\n", player);
				player = findOppenent(player);
				noMovesCouner++;
			}

			if (noMovesCouner < 2)
				moveResault = newMove(board, logicBoardSize, player);
			else// means that both players can't play
				moveResault = TIE;
		}

		scoreX = findScore(board, logicBoardSize, 'x');
		scoreO = findScore(board, logicBoardSize, 'o');
	
			declareWinner(scoreX, scoreO);
			printBoard(board, logicBoardSize);

	}

}

int sizeChoise(int choise)
{
		switch (choise)
		{
		case 1:
			return 10;
		case 2:
			return 15;
		case 3:
			return 20;
		case 4:
			return 4;
		case 0:
			return 0;
		}
}//gets the client's choise and returns the logic size
int printMenu()// prints the menu and returnes the choise;
{
	int boardSize;

	printf("Please choose board size:\n0. Exit\n1. 10 x 10\n2. 15 x 15\n3. 20 x 20\n");
	scanf("%d", &boardSize);

	while (boardSize < 0 || boardSize > 4)
	{
		system("cls");
		printf("Invalid choise, please try again.\n");		
		printf("Please choose board size:\n0. Exit\n1. 10 x 10\n2. 15 x 15\n3. 20 x 20\n");
		scanf("%d", &boardSize);
	}

	return boardSize;
}
char findOppenent(char player)
{
	if (player == 'x')
		return 'o';
	return 'x';
}//returns the opponent's character
void declareWinner(int scoreX, int scoreO)
{
	char winner = 'o';

	if (scoreX > scoreO)
		winner = 'x';

	system("cls");
	printf("Score: x - %d,  o - %d\n\n", scoreX, scoreO);

	if (scoreX != scoreO)
		printf("The winner is: %c\n\n\n", winner);
	else
		printf("Its a tie!\n");

}

void cleanBoard(char board[][COLS], int size)
{
	int i, j;
	int half = size / 2;

	for (i=0; i<size; i++)
	{
		for (j = 0; j < size; j++)
		{
			if (i == half && j == half)
				board[i][j] = 'x';
			else if (i == half - 1 && j == half)
				board[i][j] = 'o';
			else if (i == half - 1 && j == half - 1)
				board[i][j] = 'x';
			else if (i == half && j == half - 1)
				board[i][j] = 'o';
			else
				board[i][j] = '_';
		}
	}
}// Initiating the board
void printBoard(char board[][COLS], int size)
{
	int i, j;

	printf("    ");
	for (i = 1; i <= size; i++)// prints first row of numbers
	{
		if (i < 9)
			printf("%d   ", i);
		else
			printf("%d  ", i);
	}
	printf("\n");

	for (i = 0; i < size; i++)
	{
		if (i + 1 > 9)
			printf("%d  ", i + 1);
		else
			printf("%d   ", i + 1);

		for (j = 0; j < size; j++)
			printf("%c   ",board[i][j]);
		printf("\n");
	}
}

int checkRight(char board[][COLS], int row, int col, int size, char player)
{
	int i;
	char opponent = findOppenent(player);

	if (board[row - 1][col] == opponent)
	{
		row--;
		for (i = col; i < size; i++)
		{
			if (board[row][i] == '_')
				return INVALID;
			if (board[row][i] == player)
				return VALID;
		}
	}

	return INVALID;
}
int checkLeft(char board[][COLS], int row, int col, int size, char player)
{
	int i;
	char opponent = findOppenent(player);

	if (board[row - 1][col - 2] == opponent)
	{
		col -=2;
		row--;

		for (i = col; i >= 0; i--)
		{
			if (board[row][i] == '_')
				return INVALID;
			if (board[row][i] == player)
				return VALID;
		}
	}

	return INVALID;

}
int checkUp(char board[][COLS], int row, int col, int size, char player)
{
	int i;
	char opponent = findOppenent(player);

	if (board[row - 2][col - 1] == opponent)
	{
		row = row - 2;
		col--;

		for (i = row; i >= 0; i--)
		{
			if (board[i][col] == '_')
				return INVALID;
			if (board[i][col] == player)
				return VALID;
		}
	}

	return INVALID;
}
int checkDown(char board[][COLS], int row, int col, int size, char player)
{
	int i;
	char opponent = findOppenent(player);

	if (board[row][col - 1] == opponent)
	{
		col--;

		for (i = row; i < size; i++)
		{
			if (board[i][col] == '_')
				return INVALID;
			if (board[i][col] == player)
				return VALID;
		}
	}

	return INVALID;
}
int checkDiagonalDownLeft(char board[][COLS], int row, int col, int size, char player)
{
	char opponent = findOppenent(player);
	

	if (board[row][col - 2] == opponent)
	{
		col = col -2;

		for (; row < size && col >= 0; row++, col--)
		{
			if (board[row][col] == '_')
				return INVALID;
			if (board[row][col] == player)
				return VALID;
		}
	}

	return INVALID;
}
int checkDiagonalDownRight(char board[][COLS], int row, int col, int size, char player)
{
	char opponent = findOppenent(player);

	if (board[row][col] == opponent)
	{

		for (; row < size && col < size; row++, col++)
		{
			if (board[row][col] == '_')
				return INVALID;
			if (board[row][col] == player)
				return VALID;
		}
	}
	return INVALID;
}
int checkDiagonalUpRight(char board[][COLS], int row, int col, int size, char player)
{
	char opponent = findOppenent(player);

	if (board[row - 2][col] == opponent)
	{
		row = row - 2;

		for (; row >= 0 && col < size; row--, col++)
		{
			if (board[row][col] == '_')
				return INVALID;
			if (board[row][col] == player)
				return VALID;
		}
	}
	return INVALID;
}
int checkDiagonalUpLeft(char board[][COLS], int row, int col, int size, char player)
{
	char opponent = findOppenent(player);

	if (board[row - 2][col - 2] == opponent)
	{
		row = row - 2;
		col = col - 2;

		for (; row >= 0 && col >= 0; row--, col--)
		{
			if (board[row][col] == '_')
				return INVALID;
			if (board[row][col] == player)
				return VALID;
		}
	}
	return INVALID;
}

int checkIfHasMoves(char board[][COLS], int size, char player)
{
	int i, j;
	int able = INVALID;

	for (i = 1; i <= size; i++)
	{
		for (j = 1; j <= size; j++)
		{
			if (board[i][j] == '_')
			{
				able *= checkRight(board, i, j, size, player); 
				able *= checkLeft(board, i, j, size, player);
				able *= checkUp(board, i, j, size, player);
				able *= checkDown(board, i, j, size, player);
				able *= checkDiagonalDownLeft(board, i, j, size, player);
				able *= checkDiagonalDownRight(board, i, j, size, player);
				able *= checkDiagonalUpRight(board, i, j, size, player);
				able *= checkDiagonalUpLeft(board, i, j, size, player);
				if (able == VALID)
					return VALID;
			} 
		}
	}
	return INVALID;
}

int checkValidMove(char board[][COLS], int choiseRow, int choiseCol, int size, char player)
{
	char opponent = findOppenent(player);
	int isValid = INVALID;


	if (choiseRow - 1 >= size || choiseRow - 1 < 0 || choiseCol - 1 < 0 || choiseCol - 1 >= size)
		return INVALID;// checks that choise is valid.
	
	if (board[choiseRow - 1][choiseCol - 1] != '_')// checks choised value isn't '_' 
		return INVALID;

	if (board[choiseRow - 1][choiseCol] == opponent)//opponent on the right
	{
		if (checkRight(board, choiseRow, choiseCol, size, player) == VALID)
		{
			changeRight(board, choiseRow, choiseCol, size, player);
			if (isValid == INVALID)
				isValid = VALID;
		}
	}
	
	if (board[choiseRow - 1][choiseCol - 2] == opponent)//opponent on the Left
	{
		if (checkLeft(board, choiseRow, choiseCol, size, player) == VALID)
		{
			changeLeft(board, choiseRow, choiseCol, size, player);
			if (isValid == INVALID)
				isValid = VALID;
		}
	}
	
	if (board[choiseRow - 2][choiseCol - 1] == opponent)//opponent on top
	{
		if (checkUp(board, choiseRow, choiseCol, size, player) == VALID)
		{
			changeUp(board, choiseRow, choiseCol, size, player);
			if (isValid == INVALID)
				isValid = VALID;
		}
	}

	
	if (board[choiseRow][choiseCol - 1] == opponent)//opponent below
	{
		if (checkDown(board, choiseRow, choiseCol, size, player) == VALID)
		{
			changeDown(board, choiseRow, choiseCol, size, player);
			if (isValid == INVALID)
				isValid = VALID;
		}
	}

	if (board[choiseRow][choiseCol - 2] == opponent)//opponent on the down-left
	{
		if (checkDiagonalDownLeft(board, choiseRow, choiseCol, size, player) == VALID)
		{
			changeDiagonalDownLeft(board, choiseRow, choiseCol, size, player);
			if (isValid == INVALID)
				isValid = VALID;
		}
	}

	if (board[choiseRow][choiseCol] == opponent)//opponent on the down-right
		if (checkDiagonalDownRight(board, choiseRow, choiseCol, size, player) == VALID)
		{
			changeDiagonalDownRight(board, choiseRow, choiseCol, size, player);
			if (isValid == INVALID)
				isValid = VALID;
		}


	if (board[choiseRow - 2][choiseCol] == opponent)//opponent on the top-right
		if (checkDiagonalUpRight(board, choiseRow, choiseCol, size, player) == VALID)
		{
			changeDiagonalUpRight(board, choiseRow, choiseCol, size, player);
			if (isValid == INVALID)
				isValid = VALID;
		}

	if (board[choiseRow - 2][choiseCol - 2] == opponent)//opponent on the top-left
		if (checkDiagonalUpLeft(board, choiseRow, choiseCol, size, player) == VALID)
		{
			changeDiagonalUpLeft(board, choiseRow, choiseCol, size, player);
			if (isValid == INVALID)
				isValid = VALID;
		}

	
	return isValid;
}
int newMove(char board[][COLS], int size, char player)
{
	int choiseRow, choiseCol;


	if (checkIfHasMoves(board, size, player) == VALID)
	{

		printf("Player %c please enter Row and Column: \n", player);
		scanf("%d%d", &choiseRow, &choiseCol);

		if (checkValidMove(board, choiseRow, choiseCol, size, player) == VALID)
		{
			board[choiseRow - 1][choiseCol - 1] = player;//current step

			if (isWin(board, size, player) == VALID)
				return WIN;
			else if (isTie(board, size, player) == VALID)
				return TIE;
			else
				return VALID;
		}


		return INVALID;
	}
	return HAS_NO_MOVES;
}

int isWin(char board[][COLS], int size, char player)
{
	int i, j;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			if (board[i][j] != player && board[i][j] != '_')
				return INVALID;
		}
	}
	return VALID;
}
int isTie(char board[][COLS], int size, char player)
{
	int i, j;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			if (board[i][j] != '_')
				return INVALID;
		}
	}
	return VALID;
}
int findScore(char board[][COLS], int size, char player)
{
	int i, j;
	int count = 0;

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			if (board[i][j] == player)
				count++;
		}

	}

	return count;
}

void changeRight(char board[][COLS], int row, int col, int size, char player)
{
	row--;
	col--;

	while (board[row][col+1] != player)
	{
		board[row][col+1] = player;
		col++;
	}

	return;

}
void changeLeft(char board[][COLS], int row, int col, int size, char player)
{
	row--;
	col--;

	while (board[row][col - 1] != player)
	{
		board[row][col - 1] = player;
		col--;
	}

	return;

}
void changeUp(char board[][COLS], int row, int col, int size, char player)
{
	row--;
	col--;

	while (board[row - 1][col] != player)
	{
		board[row - 1][col] = player;
		row--;
	}

	return;

}
void changeDown(char board[][COLS], int row, int col, int size, char player)
{
	row--;
	col--;

	while (board[row + 1][col] != player)
	{
		board[row + 1][col] = player;
		row++;
	}

	return;

}
void changeDiagonalDownLeft(char board[][COLS], int row, int col, int size, char player)
{
	row--;
	col--;

	while (board[row + 1][col - 1] != player)
	{
		board[row + 1][col - 1] = player;
		row++;
		col--;
	}

	return;

}
void changeDiagonalDownRight(char board[][COLS], int row, int col, int size, char player)
{
	row--;
	col--;

	while (board[row + 1][col + 1] != player)
	{
		board[row + 1][col + 1] = player;
		row++;
		col++;
	}

	return;

}
void changeDiagonalUpLeft(char board[][COLS], int row, int col, int size, char player)
{
	row--;
	col--;

	while (board[row - 1][col - 1] != player)
	{
		board[row - 1][col - 1] = player;
		row--;
		col--;
	}

	return;

}
void changeDiagonalUpRight(char board[][COLS], int row, int col, int size, char player)
{
	row--;
	col--;

	while (board[row - 1][col + 1] != player)
	{
		board[row - 1][col + 1] = player;
		row--;
		col++;
	}

	return;

}