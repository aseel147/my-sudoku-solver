/*
 * source.c
 *
 *  Created on: Apr 5, 2019
 *      Author: aseel
 *	ID: 207051608
 */





#include <stdio.h>
#include "header.h"


#define SIZE 8



int main()
{
	RunProgram();
	return 0;
}



void RunProgram()
{
	int Choice;

	PrintMenu();
	do {

		scanf("%d", &Choice);
		getchar();
	} while (!((Choice != 1) || (Choice != 2) || (Choice != 3)));



	switch (Choice)
	{
	case 1:
		Encryption();
		break;
	case 2:
		Reversi();
		break;
	case 3:
		return;
	}


	RunProgram();

}
void PrintMenu()
{
	printf("1. Encryption\n");
	printf("2. Reversi\n");
	printf("3. Exit\n");


}

void Reversi()
{
	char board[SIZE][SIZE] = { 0 };  /* The board           */
	int moves[SIZE][SIZE] = { 0 };    /* Valid moves         */
	int row = 0;                      /* Board row index     */
	int col = 0;                      /* Board column index  */
	int no_of_games = 0;              /* Number of games     */
	int no_of_moves = 0;              /* Count of moves      */
	int invalid_moves = 0;            /* Invalid move count  */
	int comp_score = 0;               /* Computer score      */
	int user_score = 0;               /* Player score        */
	char y = 0;
	int y_int=0;                       /* Column letter       */
	int x = 0;                        /* Row number          */
	char again = 0;                   /* Replay choice input */
	int player = 0;                   /* Player indicator    */
	int choice;

	char input[50];
	printf("1. computer VS\n2. 2 players\n");
	scanf("%d", &choice);



	printf("\nGood luck!  Press Enter to start.\n");
	scanf("%c", &again);

	/* Prompt for how to play - as before */

	/* The main game loop */
	do
	{
		/* On even games the player starts; */
		/* on odd games the computer starts */
		player = ++no_of_games % 2;
		no_of_moves = 4;                /* Starts with four counters */

										/* Blank all the board squares */
		for (row = 0; row < SIZE; row++)
			for (col = 0; col < SIZE; col++)
				board[row][col] = '-';

		/* Place the initial four counters in the center */
		board[SIZE / 2 - 1][SIZE / 2 - 1] = board[SIZE / 2][SIZE / 2] = 'O';
		board[SIZE / 2 - 1][SIZE / 2] = board[SIZE / 2][SIZE / 2 - 1] = 'X';


		if (choice == 2) {
			playerVsplayer(board, moves);
		}
		else {




			/* The game play loop */
			do
			{
				display(board);             /* Display the board  */
				if (player++ % 2)
				{ /*   It is the player's turn                    */
					if (valid_moves(board, moves, 'O'))
					{
						/* Read player moves until a valid move is entered */
						for (;;)
						{
							//fflush(stdin);              /* Flush the keyboard buffer */
							//getchar();
							printf("Please enter your move (row column): ");

							fgets(input, 50,stdin);

							x = input[0] - '0';
							y = input[1];

							if (input[2] != '\n') {
								printf("Not a valid move, try again.\n");
								continue;
							}

							if (y <= 'Z' && y >= 'A') {
								y_int = y - 'A';
							}
							else if (y <= 'z' && y >= 'a') {
								y_int = y - 'a';
							}
							else {
								printf("Not a valid move, try again.\n");
								continue;
							}

							//y = tolower(y) - 'a';         /* Convert to column index */
							x--;
							                         /* Convert to row index    */
							if (x >= 0 && y_int >= 0 && x < SIZE && y_int < SIZE && moves[x][y_int])
							{
								make_move(board, x, y_int, 'O');
								no_of_moves++;              /* Increment move count */
								break;
							}
							else {
								printf("Not a valid move, try again.\n");
								//getchar();
							}

						}
					}
					else                              /* No valid moves */
						if (++invalid_moves < 2)
						{
							fflush(stdin);
							printf("\nYou have to pass, press return");
							scanf("%c", &again);
						}
						else
							printf("\nNeither of us can go, so the game is over.\n");
				}
				else
				{ /* It is the computer's turn                    */
					if (valid_moves(board, moves, 'X')) /* Check for valid moves */
					{
						invalid_moves = 0;               /* Reset invalid count   */
						computer_move(board, moves, 'X');
						no_of_moves++;                   /* Increment move count  */

					}
					else
					{
						if (++invalid_moves < 2)
							printf("\nI have to pass, your go\n"); /* No valid move */
						else
							printf("\nNeither of us can go, so the game is over.\n");
					}
				}
			} while (no_of_moves < SIZE*SIZE && invalid_moves < 2);



			/* Game is over */
			display(board);  /* Show final board */

							 /* Get final scores and display them */
			comp_score = user_score = 0;
			for (row = 0; row < SIZE; row++)
				for (col = 0; col < SIZE; col++)
				{
					comp_score += board[row][col] == 'X';
					user_score += board[row][col] == 'O';
				}
			printf("The final score is:\n");
			printf("Computer %d\n    User %d\n\n", comp_score, user_score);


		}
		fflush(stdin);               /* Flush the input buffer */
		printf("Do you want to play again (y/n): ");
		scanf("%c", &again);

	} while (again == 'y' || again == 'Y'); /* Go again on y          */

	printf("\nGoodbye\n");


}


void playerVsplayer(char board[][SIZE], int moves[][SIZE])
{

	int row = 0;                      /* Board row index     */
	int col = 0;                      /* Board column index  */
	int no_of_moves = 0;              /* Count of moves      */
	int invalid_moves = 0;            /* Invalid move count  */
	int user1_score = 0;               /* Computer score      */
	int user2_score = 0;               /* Player score        */
	char y = 0;
	int y_int=0;                      /* Column letter       */
	int x = 0;                        /* Row number          */
	char again = 0;                   /* Replay choice input */
	int player = 1;                   /* Player indicator    */
	char input[50];


	/* The game play loop */
	do
	{
		display(board);             /* Display the board  */
		if (player++ % 2)
		{ /*   It is the player's 1 turn                    */
			if (valid_moves(board, moves, 'O'))
			{
				/* Read player moves until a valid move is entered */
				for (;;)
				{


					printf("Please enter your move (row column): ");

					fgets(input,50,stdin);

					x = input[0] - '0';
					y = input[1];

					if (input[2] != '\n') {
						printf("Not a valid move, try again.\n");
						continue;
					}

					if (y <= 'Z' && y >= 'A') {
						y_int = y - 'A';
					}
					else if (y <= 'z' && y >= 'a') {
						y_int = y - 'a';
					}
					else {
						printf("Not a valid move, try again.\n");
						continue;
					}
					x--;                          /* Convert to row index    */
					if (x >= 0 && y_int >= 0 && x < SIZE && y_int < SIZE && moves[x][y_int])
					{
						make_move(board, x, y_int, 'O');
						no_of_moves++;              /* Increment move count */
						break;
					}
					else
						printf("Not a valid move, try again.\n");
				}
			}
			else                              /* No valid moves */
				if (++invalid_moves < 2)
				{
					fflush(stdin);
					printf("\nYou have to pass, press return");
					scanf("%c", &again);
				}
				else
					printf("\nNeither of us can go, so the game is over.\n");
		}
		else
		{ /*   It is the player's 2 turn                    */
			if (valid_moves(board, moves, 'X'))
			{
				invalid_moves = 0;
				/* Read player moves until a valid move is entered */
				for (;;)
				{
					printf("Please enter your move (row column): ");

					fgets(input,50,stdin);

					x = input[0] - '0';
					y = input[1];

					if (input[2] != '\n') {
						printf("Not a valid move, try again.\n");
						continue;
					}

					if (y <= 'Z' && y >= 'A') {
						y_int = y - 'A';
					}
					else if (y <= 'z' && y >= 'a') {
						y_int = y - 'a';
					}
					else {
						printf("Not a valid move, try again.\n");
						continue;
					}
					/* Convert to column index */
					x--;                          /* Convert to row index    */
					if (x >= 0 && y_int >= 0 && x < SIZE && y_int < SIZE && moves[x][y_int])
					{
						make_move(board, x, y_int, 'X');
						no_of_moves++;              /* Increment move count */
						break;
					}
					else
						printf("Not a valid move, try again.\n");
				}
			}
			else                              /* No valid moves */
				if (++invalid_moves < 2)
				{
					fflush(stdin);
					printf("\nYou have to pass, press return");
					scanf("%c", &again);
				}
				else
					printf("\nNeither of us can go, so the game is over.\n");
		}
	} while (no_of_moves < SIZE*SIZE && invalid_moves < 2);


	/* Game is over */
	display(board);  /* Show final board */

					 /* Get final scores and display them */
	for (row = 0; row < SIZE; row++)
		for (col = 0; col < SIZE; col++)
		{
			user2_score += board[row][col] == 'X';
			user1_score += board[row][col] == 'O';
		}
	printf("The final score is:\n");
	printf("Computer %d\n    User %d\n\n", user2_score, user1_score);


}


void display(char board[][SIZE])
{
	int row = 0;          /* Row index      */
	int col = 0;           /* Column index   */
	char col_label = 'a';  /* Column label   */

	printf("\n ");         /* Start top line */
	for (col = 0; col<SIZE;col++)
		printf("   %c", col_label + col); /* Display the top line */
	printf("\n");                     /* End the top line     */

									  /* Display the intermediate rows */
	for (row = 0; row < SIZE; row++)
	{
		printf("   ");
		for (col = 0; col < SIZE; col++)
			printf("    ");
		printf("\n%2d ", row + 1);

		for (col = 0; col<SIZE; col++)
			printf(" %c  ", board[row][col]);  /* Display counters in row */
		printf("\n");
	}

	printf("   ");                 /* Start the bottom line   */
	for (col = 0; col < SIZE;col++)
		printf("    ");           /* Display the bottom line */
	printf("\n");












}


int valid_moves(char board[][SIZE], int moves[][SIZE], char player)
{
	int rowdelta = 0;     /* Row increment around a square    */
	int coldelta = 0;     /* Column increment around a square */
	int row = 0;          /* Row index                        */
	int col = 0;          /* Column index                     */
	int x = 0;            /* Row index when searching         */
	int y = 0;            /* Column index when searching      */
	int no_of_moves = 0;  /* Number of valid moves            */

						  /* Set the opponent            */
	char opponent = (player == 'O') ? 'X' : 'O';

	/* Initialize moves array to zero */
	for (row = 0; row < SIZE; row++)
		for (col = 0; col < SIZE; col++)
			moves[row][col] = 0;

	/* Find squares for valid moves.                           */
	/* A valid move must be on a blank square and must enclose */
	/* at least one opponent square between two player squares */
	for (row = 0; row < SIZE; row++)
		for (col = 0; col < SIZE; col++)
		{
			if (board[row][col] != '-')   /* Is it a blank square?  */
				continue;                  /* No - so on to the next */

										   /* Check all the squares around the blank square  */
										   /* for the opponents counter                      */
			for (rowdelta = -1; rowdelta <= 1; rowdelta++)
				for (coldelta = -1; coldelta <= 1; coldelta++)
				{
					/* Don't check outside the array, or the current square */
					if (row + rowdelta < 0 || row + rowdelta >= SIZE ||
						col + coldelta < 0 || col + coldelta >= SIZE ||
						(rowdelta == 0 && coldelta == 0))
						continue;

					/* Now check the square */
					if (board[row + rowdelta][col + coldelta] == opponent)
					{
						/* If we find the opponent, move in the delta direction  */
						/* over opponent counters searching for a player counter */
						x = row + rowdelta;                /* Move to          */
						y = col + coldelta;                /* opponent square  */

														   /* Look for a player square in the delta direction */
						for (;;)
						{
							x += rowdelta;                  /* Go to next square */
							y += coldelta;                  /* in delta direction*/

															/* If we move outside the array, give up */
							if (x < 0 || x >= SIZE || y < 0 || y >= SIZE)
								break;

							/* If we find a blank square, give up */
							if (board[x][y] == '-')
								break;
							/*  If the square has a player counter */
							/*  then we have a valid move          */
							if (board[x][y] == player)
							{
								moves[row][col] = 1;   /* Mark as valid */
								no_of_moves++;         /* Increase valid moves count */
								break;                 /* Go check another square    */
							}
						}
					}
				}
		}
	return no_of_moves;
}


void computer_move(char board[][SIZE], int moves[][SIZE], char player)
{
	int row = 0;                          /* Row index               */
	int col = 0;                          /* Column index            */
	int best_row = 0;                     /* Best row index          */
	int best_col = 0;                     /* Best column index       */
	int i = 0;                            /* Loop index              */
	int j = 0;                            /* Loop index              */
	int new_score = 0;                    /* Score for current move  */
	int score = 100;                      /* Minimum opponent score  */
	char temp_board[SIZE][SIZE];          /* Local copy of board     */
	int temp_moves[SIZE][SIZE];           /* Local valid moves array */
	char opponent = (player == 'O') ? 'X' : 'O'; /* Identify opponent */

												 /* Go through all valid moves */
	for (row = 0; row < SIZE; row++)
		for (col = 0; col < SIZE; col++)
		{
			if (moves[row][col] == 0)
				continue;

			/* First make copies of the board and moves arrays */
			for (i = 0; i < SIZE; i++)
				for (j = 0; j < SIZE; j++)
					temp_board[i][j] = board[i][j];

			/* Now make this move on the temporary board */
			make_move(temp_board, row, col, player);

			/* find valid moves for the opponent after this move */
			valid_moves(temp_board, temp_moves, opponent);

			/* Now find the score for the opponents best move */
			new_score = best_move(temp_board, temp_moves, opponent);

			if (new_score<score)    /* Is it worse?           */
			{                      /* Yes, so save this move */
				score = new_score;   /* Record new lowest opponent score */
				best_row = row;  /* Record best move row             */
				best_col = col;  /* and column                       */
			}
		}


	printf("Computer's move is: %d%c : ", best_row + 1, (best_col + 'a'));

	/* Make the best move */
	make_move(board, best_row, best_col, player);
}


int get_score(char board[][SIZE], char player)
{
	int score = 0;      /* Score for current position */
	int row = 0;        /* Row index                  */
	int col = 0;        /* Column index               */
	char opponent = player == 'O' ? 'X' : 'O';  /* Identify opponent */

												/* Check all board squares */
	for (row = 0; row < SIZE; row++)
		for (col = 0; col < SIZE; col++)
		{
			score -= board[row][col] == opponent; /* Decrement for opponent */
			score += board[row][col] == player;   /* Increment for player   */
		}
	return score;
}


int best_move(char board[][SIZE], int moves[][SIZE], char player)
{
	int row = 0;     /* Row index    */
	int col = 0;     /* Column index */
	int i = 0;       /* Loop index   */
	int j = 0;       /* Loop index   */

	//char opponent = player == 'O' ? 'X' : 'O'; /* Identify opponent */

	char new_board[SIZE][SIZE] = { 0 };  /* Local copy of board    */
	int score = 0;                       /* Best score             */
	int new_score = 0;                   /* Score for current move */

										 /* Check all valid moves to find the best */
	for (row = 0; row<SIZE; row++)
		for (col = 0; col<SIZE; col++)
		{
			if (!moves[row][col])             /* Not a valid move?      */
				continue;                      /* Go to the next         */

											   /* Copy the board */
			for (i = 0; i<SIZE; i++)
				for (j = 0; j<SIZE; j++)
					new_board[i][j] = board[i][j];

			/* Make move on the board copy */
			make_move(new_board, row, col, player);

			/* Get score for move */
			new_score = get_score(new_board, player);

			if (score<new_score)         /* Is it better?               */
				score = new_score;  /* Yes, save it as best score  */
		}
	return score;                   /* Return best score           */
}

void make_move(char board[][SIZE], int row, int col, char player)
{
	int rowdelta = 0;                   /* Row increment              */
	int coldelta = 0;                   /* Column increment           */
	int x = 0;                          /* Row index for searching    */
	int y = 0;                          /* Column index for searching */
	char opponent = (player == 'O') ? 'X' : 'O';  /* Identify opponent */

	board[row][col] = player;           /* Place the player counter   */

										/* Check all the squares around this square */
										/* for the opponents counter                */
	for (rowdelta = -1; rowdelta <= 1; rowdelta++)
		for (coldelta = -1; coldelta <= 1; coldelta++)
		{
			/* Don't check off the board, or the current square */
			if (row + rowdelta < 0 || row + rowdelta >= SIZE ||
				col + coldelta < 0 || col + coldelta >= SIZE ||
				(rowdelta == 0 && coldelta == 0))
				continue;

			/* Now check the square */
			if (board[row + rowdelta][col + coldelta] == opponent)
			{
				/* If we find the opponent, search in the same direction */
				/* for a player counter                                  */
				x = row + rowdelta;        /* Move to opponent */
				y = col + coldelta;        /* square           */

				for (;;)
				{
					x += rowdelta;           /* Move to the      */
					y += coldelta;           /* next square      */

											 /* If we are off the board give up */
					if (x < 0 || x >= SIZE || y < 0 || y >= SIZE)
						break;

					/* If the square is blank give up */
					if (board[x][y] == '-')
						break;

					/* If we find the player counter, go backwards from here */
					/* changing all the opponents counters to player         */
					if (board[x][y] == player)
					{
						while (board[x -= rowdelta][y -= coldelta] == opponent) /* Opponent? */
							board[x][y] = player;    /* Yes, change it */
						break;                     /* We are done    */
					}
				}
			}
		}

}





void Encryption()
{

	char word[20];

	do {
		printf("enter word consisting of large letters and numbers of at least two letters and at last two numbers:\n");
		fgets(word,20,stdin);

		if(word[8] == '\n'){
			word[8] = '\0';
		}


	} while (check_pass(word));
	Plus3(word);
	//printf("%s\n", word);
	Encryptiontable(word);
	//printf("%s\n", word);
	Swap(word);
	//printf("%s\n", word);

	Reverse(word);
	//printf("%s\n", word);
	ROL_RIGHT(word);

printf("%s\n", word);





}
int check_pass(char pass[20])
{
	int count = 0, countletter = 0, countnumber = 0, i;
	for (i = 0;pass[i] != '\0';i++)
	{
		if (pass[i] >= 'A'&&pass[i] <= 'Z')
			countletter++;
		else if (pass[i] >= '0'&&pass[i] <= '9')
			countnumber++;
		else {
			return 1;

		}



		count++;
	}

	if (countletter < 2 || countnumber < 2 || count != 8)
		return 1;
	return 0;

}



void ROL_RIGHT(char word[20])
{
	char wordnew[9] = { 0 };
	int i = 0;
	for (i = 0;word[i] != '\0';i++)
	{
		if (i==7)
			wordnew[1] = word[i];


		else if (i==6)
			wordnew[0] = word[i];


		else
			wordnew[i+2] = word[i];




	}
	//printf("%s\n", wordnew);

	for (i = 0;word[i] != '\0';i++)
		word[i] = wordnew[i];

}

void Swap(char word[])
{
	char wordnew[9] = { 0 };
	int i = 0;
	//	int size = sizeof(word) - 1;
	for (i = 0;word[i] != '\0';i++)
	{
		if ((i % 2) == 0)
			wordnew[i + 1] = word[i];
		if ((i % 2) == 1)
			wordnew[i - 1] = word[i];


	}
	//printf("%s\n", wordnew);
	for (i = 0;word[i] != '\0';i++)
		word[i] = wordnew[i];
	//printf("%c", wordnew[i]);
}
void Encryptiontable(char word[20])
{
	char encryptedLetters[] = { 'S', '5', 'P','W','A', 'R','8','Q','I','V','B','0','D','Z','3','C','2','H','4','1','K','7' ,'G', 'Y', '6', 'O' };
	char encryptedDigits[] = { 'J', 'E', 'U', 'N', 'F', '9', 'M', 'L', 'T', 'X' };

	int i = 0,j=0;
	int flag = 0;

	for (;word[i] != 0; i++) {

		flag = 0;
		//letters


			for (j=0;j<26;j++) {

					if (word[i] == encryptedLetters[j]) {
						word[i] = j + 'A';
						flag = 1;
						break;
					}

			}


		//digits

			for (j = 0;j < 10 && flag == 0;j++) {
				if (word[i] == encryptedDigits[j]) {
					word[i] = j+'0';
					break;
				}
			}

	}



}



void Reverse(char word[20])
{
	char wordnew[9] = { 0 };
	int i = 0, J = 0;
	int size = 7;

	for (;size >= 0;size--) {
		wordnew[i] = word[size];
		i++;
	}
	for (J = 0;word[J] != '\0';J++)
		word[J] = wordnew[J];

	//printf("%s\n", wordnew);

}
void  Plus3(char word[20])
{
	char CH;
	char wordnew[9] = { 0 };
	int i = 0;
	for (i = 0;word[i] != '\0';i++)
	{
		CH = word[i];
		if (CH >= 'A'&&CH <= 'Z')
			wordnew[i] = (CH + 'A' - 3) % 26 + 'A';

		else if (CH >= '0'&&CH <= '9')
			wordnew[i] = (CH - 3) % 10 + 50;
	}


	for (i = 0;word[i] != '\0';i++)
		word[i] = wordnew[i];
}
