#include <stdio.h>
#include "board_io.h"
#include <stdlib.h>
#include <time.h>
#include "player.h"
#define debug 1

// phase=1 placement , phase=2 movement

// This code is perfect when it comes to placement phase 

// int read_board(const char *filename, int phase, struct Player players[9], int **arr, int no_of_players, int how_many_penguins) 
// {
// 	int row, col, i = 0;
// 	int **board;

// 	FILE *file = fopen(filename, "r");
// 	fscanf(file, "%d %d", &row, &col);
// 	board = (int **)malloc(row * sizeof(int *)); 
// 	for (int i = 0; i < row; ++i) {
// 		board[i] = (int *)malloc(col * sizeof(int)); 
// 		for (int j = 0; j < col; ++j) {
// 			fscanf(file, "%d ", &board[i][j]);
// 		}
// 		fscanf(file, "\n");
// 	}

// 	if (phase == 1) {


// 		for(int i= 0; i< no_of_players; i++)
// 		{
// 			printf("Player %d: ", i+1);

// 			scanf("%s", players[i].id);

// 		}

// 		for(int i= 0; i< no_of_players; i++)
// 		{

// 			fprintf(file, "%s %d %d \n",players[i].id, i+1, players[i].score);

// 		}

// 		for (int i = 0; i < row; ++i) {
// 			for (int j = 0; j < col; ++j) {
// 				arr[i][j] = board[i][j];
// 			}
// 		}
// 	}

// 	else 
		
// 		if (phase == 2) {

       
// 		for (int i = 0; i < row; ++i) {
// 			for (int j = 0; j < col; ++j) {
// 				arr[i][j] = board[i][j];
// 			}
// 		}

// 	}

// 	fclose(file);

// 	return 0;
// }

// int write_board(const char *inFile, const char *outFile, int phase, struct Player players[9], int **board, int size[], int no_of_players, int how_many_penguins) {
// 	int row, col;
// 	row = size[0];
// 	col = size[1];

// 	FILE *outfile = fopen(outFile, "w+");
// 	fprintf(outfile, "%d %d\n", row, col);

// 	if (phase == 1) {

// 		int temp[no_of_players];        
// 		int place_row, place_col;
// 		srand(time(NULL));


// 		//initialising ID to each player and each penguin 

// 		for(int play=0; play< no_of_players ; ++play){

// 			for(int i=0; i<how_many_penguins; ++i){

// 				players[play].player_number = (play+1);
// 				players[play].penguins[i].peng_no = i+1;
// 			}
// 		}


// 		for (int play = 0; play < no_of_players; ++play) {

// 			for(int i=0; i < how_many_penguins; ++i){

// 				place_row = rand() % row;
// 				place_col = rand() % col;

// 				while(!(board[place_row][place_col]==10)){
// 					place_row = rand() % row;
// 					place_col = rand() % col;
// 				}

// 				// printf("row = %d col = %d\n", place_row, place_col );
				
// 				for (int i = 0; i < row; ++i) {
// 					for (int j = 0; j < col; ++j) {

// 						if(i == place_row && j == place_col) {
// 							temp[play]=board[i][j];
// 							board[i][j] = players[play].player_number;
// 							// printf("%d\n",players[play].player_number );
// 							// printf("lauda lele \n");

// 						}
// 					}
// 				}
// 			}

// 		}			


// 		for (int i = 0; i < row; ++i) {
// 			for (int j = 0; j < col; ++j) {
// 				if(board[i][j] < 10)
// 					fprintf(outfile, "0%d ", board[i][j]);
// 				else 
// 					fprintf(outfile, "%d ", board[i][j]);
// 			}
// 			fprintf(outfile, "\n");
// 		}


// 		// Updating the score of each player's penginus and also the player's total score 

// 		for(int play=0; play<no_of_players; ++play) {

// 			for(int q=0; q<how_many_penguins;++q) {

// 				players[play].penguins[q].score_of_penguin += (temp[play]/10) ;
// 				// printf("%d %d \n", players[play].player_number, players[play].penguins[q].score_of_penguin );

// 				players[play].score += players[play].penguins[q].score_of_penguin ;
// 				// printf("%d %d\n",players[play].player_number,players[play].score  );
// 			}
// 		}	
		


// 		for (int i = 0; i < no_of_players; ++i) {

// 			fprintf(outfile, "%s %d %d\n", players[i].id, players[i].player_number, players[i].score);
// 		}

// 	}

// 	else if(phase == 2) {

// 		// movement

// 		for(int play=0; play<no_of_players; ++play) {

// 			for(int q=0; q<how_many_penguins;++q) {

// 				printf("%d\n",players[play].player_number );

// 				// find_player_position(players[play],board,size,how_many_penguins);
// 				//player choses one of his
// 				//check if penguin can move is surrounded
// 				//check if penguin can move in a straight line 
// 				//

// 			}
// 		}
// 	}

// 	fclose(outfile);


// 	return 0;
// }


// int board_size(const char *filename, int size[]) {
// 	FILE *file = fopen(filename, "r");	
// 	fscanf(file, "%d %d", &size[0], &size[1]);
// 	fclose(file);
// 	return 0;
// }

// shit for movement phase 

int read_board(const char *filename, int phase, struct Player players[9], int **arr, int no_of_players, int how_many_penguins) {
	int row, col, i = 0;
	int **board;

	FILE *file = fopen(filename, "r");
	fscanf(file, "%d %d", &row, &col);
	board = (int **)malloc(row * sizeof(int *)); 
	for (int i = 0; i < row; ++i) {
		board[i] = (int *)malloc(col * sizeof(int)); 
		for (int j = 0; j < col; ++j) {
			fscanf(file, "%d ", &board[i][j]);
		}
		fscanf(file, "\n");
	}

	if (phase == 1) {
		for(int i= 0; i< no_of_players; i++) {
			printf("Player %d: ", i+1);
			scanf("%s", players[i].id);
		}

		for(int i= 0; i< no_of_players; i++) {
			fprintf(file, "%s %d %d \n",players[i].id, i+1, players[i].score);
		}

		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < col; ++j) {
				arr[i][j] = board[i][j];
			}
		}
	} else { 
		if (phase == 2) {
       	// printf("lauda lele bc xD\n");
			for (int i = 0; i < row; ++i) {
				for (int j = 0; j < col; ++j) {
					// printf("lauda lele \n");
					arr[i][j] = board[i][j];
				}
			}
		}
	}

	fclose(file);
	return 0;
}

int write_board(const char *inFile, const char *outFile, int phase, struct Player players[9], int **board, int size[], int no_of_players, int how_many_penguins) {
	int row, col;
	row = size[0];
	col = size[1];

	FILE *outfile = fopen(outFile, "w+");
	fprintf(outfile, "%d %d\n", row, col);

	if (phase == 1) {

		int temp[no_of_players];        
		int place_row, place_col;
		srand(time(NULL));


		//initialising ID to each player and each penguin 

		for(int play=0; play< no_of_players ; ++play){

			for(int i=0; i<how_many_penguins; ++i){

				players[play].player_number = (play+1);
				players[play].penguins[i].peng_no = i+1;
			}
		}


		for (int play = 0; play < no_of_players; ++play) {

			for(int i=0; i < how_many_penguins; ++i){

				place_row = rand() % row;
				place_col = rand() % col;

				while(!(board[place_row][place_col]==10)){
					place_row = rand() % row;
					place_col = rand() % col;
				}

				// printf("row = %d col = %d\n", place_row, place_col );
				
				for (int i = 0; i < row; ++i) {
					for (int j = 0; j < col; ++j) {

						if(i == place_row && j == place_col) {
							temp[play]=board[i][j];
							board[i][j] = players[play].player_number;
							// printf("%d\n",players[play].player_number );
							// printf("lauda lele \n");

						}
					}
				}
			}

		}			


		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < col; ++j) {
				if(board[i][j] < 10)
					fprintf(outfile, "0%d ", board[i][j]);
				else 
					fprintf(outfile, "%d ", board[i][j]);
			}
			fprintf(outfile, "\n");
		}


		// Updating the score of each player's penginus and also the player's total score 

		for(int play=0; play<no_of_players; ++play) {

			for(int q=0; q<how_many_penguins;++q) {

				players[play].penguins[q].score_of_penguin += (temp[play]/10) ;
				// printf("%d %d \n", players[play].player_number, players[play].penguins[q].score_of_penguin );

				players[play].score += players[play].penguins[q].score_of_penguin ;
				// printf("%d %d\n",players[play].player_number,players[play].score  );
			}
		}	
		


		for (int i = 0; i < no_of_players; ++i) {

			fprintf(outfile, "%s %d %d\n", players[i].id, players[i].player_number, players[i].score);
		}

	}

	else if(phase == 2) {

		// movement

		for(int play=0; play<no_of_players; ++play) {

			for(int q=0; q<how_many_penguins;++q) {

				printf("%d\n",players[play].player_number );

				// find_player_position(players[play],board,size,how_many_penguins);
				//player choses one of his
				//check if penguin can move is surrounded
				//check if penguin can move in a straight line 
				//

			}
		}
	}

	fclose(outfile);


	return 0;
}


int board_size(const char *filename, int size[]) {
	FILE *file = fopen(filename, "r");	
	fscanf(file, "%d %d", &size[0], &size[1]);
	fclose(file);
	return 0;
}