#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "board_io.h"
#include "player.h"
#include "penguin.h"
#include <ctype.h>

#define debug 1

int main(int argc, char const *argv[]) {
	/* declare structures and some variables  */
	struct Player players[9];
	int **board;
	int b_size[2];
	const char *phase;
	const char *penguins;
	int how_many_penguins;
	const char *inFile, *outFile;
	int sizeX, sizeY, NumberOfplayers=0;
    // check if arguments are less than 3
	if(argc == 0) {
		printf("no command line arguments\n");
	} else {
		phase = argv[1];
		if((strcmp(phase, "phase=placement") == 0) && (argc == 5)) {
			penguins = argv[2];
			inFile = argv[3];
			outFile = argv[4];

			const char *ptr = penguins;
			for(int i=0 ; i<strlen(penguins); ++i){

				if(isdigit(*ptr))
					how_many_penguins = atoi(ptr) ; 
				else 
					ptr++ ; 

			}
			printf("\n\n\t=======WELCOME TO PENGUINS=======\n\n");
			
			/*#ifdef debug
			printf("%s\n",penguins);
			printf("%d\n",how_many_penguins );
			#endif
*/

			board_size(inFile, b_size);

			//allocating board size
			board = (int **)malloc(b_size[0] * sizeof(int *)); 
			for (int i = 0; i < b_size[0]; ++i) 
				board[i] = (int *)malloc(b_size[1] * sizeof(int)); 

            //newly added: no of players 

			printf("Enter number of players \n");
			scanf("%d", &NumberOfplayers);
			while(!(NumberOfplayers>=2 && NumberOfplayers<=9)){
				printf("Wrong input \n");
				scanf("%d", &NumberOfplayers);
			}

            //initialise each players score to 0
			for(int i=0;i<NumberOfplayers;++i){

				for(int j=0; j < how_many_penguins; ++j){
					players[i].score=0;
					players[i].penguins[j].score_of_penguin=0;
				}
			}



			read_board(inFile, 1, players, board, NumberOfplayers,how_many_penguins);
			
			write_board(inFile, outFile, 1, players, board, b_size, NumberOfplayers,how_many_penguins);

		} else if((strcmp(phase, "phase=movement") == 0) && (argc == 3)){           //NOT COMPLETE
			inFile = argv[2];
			outFile = argv[3];
		} else {    
    	//create give_Id()
        	// printf("Player's Id: %d\n", give_Id());
		}
	}

	return 0;
}