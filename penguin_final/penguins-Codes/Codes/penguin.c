#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "board_io.h"
#include "player.h"
#include "penguin.h"

#define debug 1
// #define interactive 1
int main(int argc, char const *argv[]) {
	/* declare structures and some variables  */
	struct Player players[9];
	int **board;
	int b_size[2];
	const char *phase;
	const char *penguins;
	int how_many_penguins;
	const char *inFile, *outFile;
    // check if arguments are less than 3
	if(argc == 1) {
		printf("No Command Line Arguments\n");
	} else {
		phase = argv[1];
		if((strcmp(phase, "phase=placement") == 0) && (argc == 5)) {
			int NumberOfplayers = 0;
			penguins = argv[2];
			inFile = argv[3];
			outFile = argv[4];

			const char *ptr = penguins;
			for(int i = 0 ; i < strlen(penguins); ++i){
				if(isdigit(*ptr))
					how_many_penguins = atoi(ptr) ;
				else
					ptr++ ;
			}

			board_size(inFile, b_size);

			//allocating board size
			board = (int **)malloc(b_size[0] * sizeof(int *));
			for (int i = 0; i < b_size[0]; ++i)
				board[i] = (int *)malloc(b_size[1] * sizeof(int));

            //newly added: no of players
            /*
			printf("Enter number of players \n");
			scanf("%d", &NumberOfplayers);
			*/
			NumberOfplayers = 9;                        //HARDCODED TO BE 9. DOESNT DO ANYTHING (except for occasionally crashing program and/or corrupting data) ANYWAY
			while(!(NumberOfplayers >= 2 && NumberOfplayers <= 9)) {
				printf("Wrong input \n");
				scanf("%d", &NumberOfplayers);
			}

            //initialise each players score to 0
    			for(int i = 0; i < NumberOfplayers; ++i) {
				for(int j = 0; j < how_many_penguins; ++j) {
					players[i].score = 0;
					players[i].penguins[j].score_of_penguin = 0;
				}
			}

			read_board(inFile, players, board, NumberOfplayers, how_many_penguins);
			write_board(inFile, outFile, 1, players, board, b_size, NumberOfplayers, how_many_penguins);
			printf("Placement is complete :)\n");

			return 1; //placement is complete
		}
			else if((strcmp(phase, "phase=movement") == 0) && (argc == 4)) {
			int NumberOfplayers = 0;
			inFile = argv[2];
			outFile = argv[3];
			int how_many_penguins;

			board_size(inFile, b_size);

			//allocating board size
			board = (int **)malloc(b_size[0] * sizeof(int *));
			for (int i = 0; i < b_size[0]; ++i)
				board[i] = (int *)malloc(b_size[1] * sizeof(int));

			if(strcmp(inFile, "board1.txt") == 0) {
				FILE *file = fopen("pengus", "w+");
				fprintf(file, "%d\n", read_board_mov(inFile, players, board, 1));
				how_many_penguins =  read_board_mov(inFile, players, board, 1);
				printf("%d\n",how_many_penguins );
				fclose(file);
			}

			NumberOfplayers = read_board_mov(inFile, players, board, 0);
			// printf("Number of players: %d\n", NumberOfplayers);

	    	//check_move(players[0].player_number, how_many_penguins, b_size, board );
			write_board(inFile, outFile, 2, players, board, b_size, NumberOfplayers, how_many_penguins);
		}
		else{
			give_id();
		}
	}

	return 0;
}
