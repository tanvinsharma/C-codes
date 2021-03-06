#include <stdio.h>
#include "board_io.h"
#include <stdlib.h>
#include <time.h>
#define debug 1

// phase=1 placement , phase=2 movement


int read_board(const char *filename, int phase, struct Player players[9], int **arr, int no_of_players, int how_many_penguins) 
{
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

		printf("Please input player's ids\n");
		for(int i= 0; i< no_of_players; i++)
		{
			printf("Player %d: ", i+1);

			scanf("%s", players[i].id);

		}

		for(int i= 0; i< no_of_players; i++)
		{

			fprintf(file, "%s %d %d \n",players[i].id, i+1, players[i].score);

		}

		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < col; ++j) {
				arr[i][j] = board[i][j];
			}
		}
	}

	else if (phase == 2){

    	//movement
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

		for(int play2=0; play2< no_of_players; ++play2)
			players[play2].player_number = (play2+1);

		printf("\nThis is your board:\n");
		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < col; ++j) {
				if(board[i][j] < 10)
					printf("0%d ", board[i][j]);
				else 
					printf("%d ", board[i][j]);
			}
			printf("\n");
		}

		for (int play = 0; play < no_of_players; ++play) {

			for(int i=0; i < how_many_penguins; ++i){
				
				printf("\n\n%s, where do you want to place your %d penguin?\n", players[play].id, i+1);
				printf("x= ");
				scanf("%d", &place_col);
				printf("\ny= ");
				scanf("%d", &place_row); 

				while(board[place_row][place_col]>10 && !(board[place_row][place_col]==10)){
					printf("\t=====WARNING===== \nYou can place your penguin on tiles with only one fish on it! Try one more time\n");
					printf("\n%s, where do you want to place your %d penguin?\n", players[play].id, i+1);
					printf("x= ");
					scanf("%d", &place_col);
					printf("\ny= ");
					scanf("%d", &place_row);
				}
				while((board[place_row][place_col]<10)){
					printf("\t=====WARNING===== \nThis tile is already occupied! Try one more time\n");
					printf("\n%s, where do you want to place your %d penguin?\n", players[play].id, i+1);
					printf("x= ");
					scanf("%d", &place_col);
					printf("\ny= ");
					scanf("%d", &place_row);  				
				}

				
				for (int i = 0; i < row; ++i) {
					for (int j = 0; j < col; ++j) {
						
						if(i == place_row && j == place_col) {
							temp[play]=board[i][j];
							board[i][j] = players[play].player_number;
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

		for(int play=0; play<no_of_players; ++play) {

			for(int q=0; q<how_many_penguins;++q) {

				players[play].penguins[q].score_of_penguin += (temp[play]/10) ;
				players[play].score += players[play].penguins[q].score_of_penguin ;
			}
		}	
		


		for (int i = 0; i < no_of_players; ++i) {

			fprintf(outfile, "%s %d %d\n", players[i].id, players[i].player_number, players[i].score);
		}

		printf("\nThis is your board after placement phase:\n");
		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < col; ++j) {
				if(board[i][j] < 10)
					printf("0%d ", board[i][j]);
				else 
					printf("%d ", board[i][j]);
			}
			printf("\n");
		}

	}

	else if(phase == 2) {

		//movement
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