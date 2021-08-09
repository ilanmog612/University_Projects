/*-------------------------------------------------------------------------
	Include files:
-------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdbool.h>
//#pragma warning(disable:4996) //something that i use to ignore warnings in VS19.
/*-------------------------------------------------------------------------
	Constants and definitions:
-------------------------------------------------------------------------*/
#define N 11
#define TIC 'X'
#define TAC 'O'
#define TOE '_'
#define MAX_MOVES 121
#define EMPTY 0
#define INDEX_HELPER 1
#define EVEN_HELPER 2
#define DIVIDE_HELPER 100
#define TIC_IS_THE_WINNER 101
#define TAC_IS_THE_WINNER 200
#define TIE 300

/*-------------------------------------------------------------------------
	Function declaration
-------------------------------------------------------------------------*/
void print_welcome();
void print_enter_board_size();
void print_board(char board[N][N], int n);
void print_player_turn(int player_index);
void print_error();
void print_winner(int player_index);
void print_tie();
int beginning_the_game(char board[N][N]);
int move(char board[N][N], int size, int moves_count, int moves[MAX_MOVES], int* to_print);
int lindex_check(int lindex, int moves_count, int* to_print);
int movecheck(int lindex, int rindex, int size, char board[N][N], int* to_print);
void should_i_print(int* to_print, int player_index);
void printing_the_winner(int winner);
void undo(char board[N][N], int numofundos, int moves[MAX_MOVES], int size, int* to_print);
void archive_move(int moves[MAX_MOVES], int lindex, int rindex, char board[N][N], int size, int player_index, int* to_print);
int winner_scan_rows(char board[N][N], int size);
int winner_scan_col(char board[N][N], int size);
int winner_scan_diagonal1(char board[N][N], int size);
int winner_scan_diagonal2(char board[N][N], int size);
int winner_status(char board[N][N], int size);

/*-------------------------------------------------------------------------
	Implementation
-------------------------------------------------------------------------*/
//here all the megic heppens. here the game takes place.
//16 lines
int main()
{
	char board[N][N];
	int bsize = beginning_the_game(board), moves[MAX_MOVES] = { EMPTY }, movescount = EMPTY, winner = INDEX_HELPER, tie_count = bsize * bsize, print = INDEX_HELPER;
	while (true)
	{
		movescount += move(board, bsize, movescount, moves, &print);
		winner = winner_status(board, bsize);
		if (winner != INDEX_HELPER)
		{
			break;
		}
		else if (tie_count == movescount)

		{
			winner = TIE;
			break;
		}
	}
	printing_the_winner(winner);
	return EMPTY;
}

//print welcome message
//1 lines
void print_welcome()
{
	printf("*** Welcome to AVOIDANCE TIC-TAC-TOE game ***\n\n");
}

//print message to enter board size
//1 lines
void print_enter_board_size()
{
	printf("Please enter board size (1 to %d):\n", N);
}

//print the board
//7 lines
void print_board(char board[N][N], int n)
{
	printf("\nCurrent board:\n");
	for (int i = 0; i < n; i++)
	{
		printf("|");
		for (int j = 0; j < n; j++)
		{
			printf("%c|", board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

//print a request for player with index "player_index" to move
//1 lines
void print_player_turn(int player_index)
{
	printf("\nPlayer ** %d **, enter next move:\n", player_index);
}

//print error message
//1 lines
void print_error()
{
	printf("Illegal move!!!, please try again:\n");
}

//print the winner
//1 lines
void print_winner(int player_index)
{
	printf("Player %d Wins! Hooray!\n", player_index);
}

//print message to announce there is a tie (no one wins)
//1 lines
void print_tie()
{
	printf("It's a tie!\n");
}

//setting up the game in the beginning.
//9 lines
int beginning_the_game(char board[N][N])
{
	int size = EMPTY;
	print_welcome();
	print_enter_board_size();
	scanf(" %d", &size);
	for (int i = EMPTY; i < size; i++)
	{
		for (int j = EMPTY; j < size; j++)
		{
			board[i][j] = TOE;
		}
	}
	print_board(board, size);
	return size;
}
//function that get the move that the player wants to do. validats the input and works acording to it.
//15 lines
int move(char board[N][N], int size, int moves_count, int moves[MAX_MOVES], int* to_print)
{
	int player_index = EMPTY, lindex = EMPTY, rindex = EMPTY, moves_count1 = moves_count;
	player_index = ((moves_count1 % EVEN_HELPER) + (INDEX_HELPER));
	should_i_print(to_print, player_index);
	scanf(" %d", &lindex);
	if (lindex < EMPTY)
	{
		if (lindex_check(lindex, moves_count1,to_print) == INDEX_HELPER)
			undo(board, -lindex, moves, size, to_print);
			return lindex;
		
	}
	scanf(" %d", &rindex);
	if ((movecheck(lindex, rindex, size, board , to_print)) == INDEX_HELPER)
	{
		archive_move(moves, lindex, rindex, board, size, player_index, to_print);
		return INDEX_HELPER;
	}
	return EMPTY;
}
// first index check
//7 lines
int lindex_check(int lindex, int moves_count, int* to_print)
{
	lindex = lindex * (-INDEX_HELPER);
	if ((lindex > moves_count) || ((lindex % EVEN_HELPER) == EMPTY))
	{
		*to_print = EMPTY;
		print_error();
		return EMPTY;
	}
	else
	{
		return INDEX_HELPER;
	}
}
// valdating the the move input.
//11 lines
int movecheck(int lindex, int rindex, int size, char board[N][N],int* to_print)
{

	if ((lindex > size) || (rindex > size) || (rindex < EMPTY))
	{
		*to_print = EMPTY;
		print_error();
		return EMPTY;
	}
	else if ((board[lindex - INDEX_HELPER][rindex - INDEX_HELPER]) != TOE)
	{
		*to_print = EMPTY;
		print_error();
		return EMPTY;
	}
	else
	{
		return INDEX_HELPER;

	}
}
//checks if a player diclarations is needed
//2 lines
void should_i_print(int* to_print, int player_index)
{
	if (*to_print == INDEX_HELPER)
	{
		print_player_turn(player_index);
	}
}
//a smart winner printing function  for all options.
//5 lines
void printing_the_winner(int winner)
{
	if (winner == TIC_IS_THE_WINNER)
	{
		print_winner(INDEX_HELPER);
	}
	else if (winner == TAC_IS_THE_WINNER)
	{

		print_winner(EVEN_HELPER);
	}

	else
	{
		print_tie();
	}

}
//undo function
//11 lines
void undo(char board[N][N], int numofundos, int moves[MAX_MOVES], int size, int* to_print)
{
	int index = EMPTY, lindex = EMPTY, rindex = EMPTY;
	while (moves[index] != EMPTY)
	{
		index++;
	}
	index--;
	for (int i = EMPTY; i < numofundos; i++)
	{

		lindex = (moves[index - i] / DIVIDE_HELPER - INDEX_HELPER);
		rindex = (moves[index - i] % DIVIDE_HELPER - INDEX_HELPER);
		board[lindex][rindex] = TOE;
		moves[index - i] = EMPTY;

	}
	print_board(board, size);
	*to_print = INDEX_HELPER;

}
//if the move was ok this function puts the move into the moves archive arry
//11 lines
void archive_move(int moves[MAX_MOVES], int lindex, int rindex, char board[N][N], int size, int player_index, int* to_print)
{
	if (player_index == INDEX_HELPER)
		board[lindex - INDEX_HELPER][rindex - INDEX_HELPER] = TIC;
	else
		board[lindex - INDEX_HELPER][rindex - INDEX_HELPER] = TAC;
	int index = EMPTY, move = EMPTY;
	while (moves[index] != EMPTY)
	{
		index++;
	}
	lindex = (lindex * DIVIDE_HELPER);
	move = lindex + rindex;
	moves[index] = move;
	print_board(board, size);
	*to_print = INDEX_HELPER;

}
//scans the rows of the board to see if someone won.
//15 lines
int winner_scan_rows(char board[N][N], int size)
{
	int count1 = EMPTY, count2 = EMPTY;

	for (int i = EMPTY; i < size; i++)
	{
		count1 = EMPTY;
		count2 = EMPTY;

		for (int j = EMPTY; j < size; j++)
		{
			if (board[i][j] == TIC)
				count1++;
			else if (board[i][j] == TAC)
				count2++;

		}
		if ((count1 == size) || (count2 == size))
		{
			if (count1 == size)
			{
				return TAC_IS_THE_WINNER;
			}
			else
			{
				return TIC_IS_THE_WINNER;
			}
		}
	}
	return EMPTY;
}
//scans the collums of the board to see if someone won.
//15 lines
int winner_scan_col(char board[N][N], int size)
{
	int count1 = EMPTY, count2 = EMPTY;
	for (int i = EMPTY; i < size; i++)
	{
		count1 = EMPTY;
		count2 = EMPTY;
		for (int j = EMPTY; j < size; j++)
		{
			if (board[j][i] == TIC)
				count1++;
			else if (board[j][i] == TAC)
			{
				count2++;
			}

		}
		if ((count1 == size) || (count2 == size))
		{
			if (count1 == size)
			{
				return TAC_IS_THE_WINNER;
			}
			else
			{
				return TIC_IS_THE_WINNER;
			}
		}
	}
	return EMPTY;

}
//scans the main diagonal of the board to see if someone won.
//13 lines
int winner_scan_diagonal1(char board[N][N], int size)
{
	int count1 = EMPTY;
	int count2 = EMPTY;

	for (int j = EMPTY; j < size; j++)
	{
		if (board[j][j] == TIC)
			count1++;
		else if (board[j][j] == TAC)
		{
			count2++;
		}

	}
	if ((count1 == size) || (count2 == size))
	{
		if (count1 == size)
		{
			return TAC_IS_THE_WINNER;
		}
		else
		{
			return TIC_IS_THE_WINNER;
		}
	}
	return EMPTY;

}

//scans the secondary diagonal of the board to see if someone won.
//15 lines
int winner_scan_diagonal2(char board[N][N], int size)
{
	int count1 = EMPTY;
	int count2 = EMPTY;
	int temp = size - INDEX_HELPER;

	for (int j = EMPTY; j < size; j++)
	{
		if (board[temp][j] == TIC)
			count1++;
		else if (board[temp][j] == TAC)
		{
			count2++;
		}
		temp--;

	}
	if ((count1 == size) || (count2 == size))
	{
		if (count1 == size)
		{
			return TAC_IS_THE_WINNER;
		}
		else
		{
			return TIC_IS_THE_WINNER;
		}
	}
	return EMPTY;
}
//combiens the 4 privious functions to see if someone won.
//13 lines
int winner_status(char board[N][N], int size)
{

	if (winner_scan_rows(board, size) != EMPTY)
	{
		return  winner_scan_rows(board, size);
	}

	if (winner_scan_col(board, size) != EMPTY)
	{
		return winner_scan_col(board, size);
	}

	if (winner_scan_diagonal1(board, size) != EMPTY)
	{
		return winner_scan_diagonal1(board, size);
	}

	if (winner_scan_diagonal2(board, size) != EMPTY)
	{
		return winner_scan_diagonal2(board, size);
	}
	return INDEX_HELPER;

}





