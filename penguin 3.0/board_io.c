#include <stdio.h>
#include "board_io.h"
#include <stdlib.h>
#include <time.h>
#include "player.h"
#include <string.h>
#define debug 1

// Reading function for files in movement phase
int read_board_mov(const char *filename, struct Player players[9], int **arr, int return_score) {
	int row, col, i = 0;
	int **board;

	FILE *file = fopen(filename, "r");
	
	//we scan the first two integers which are the row and column of the board 
	fscanf(file, "%d %d", &row, &col);
	//memory allocaton for the board using malloc
	board = (int **)malloc(row * sizeof(int *));

	for (int i = 0; i < row; ++i) {
		board[i] = (int *)malloc(col * sizeof(int));
		for (int j = 0; j < col; ++j) {
			fscanf(file, "%d ", &board[i][j]);
		}
		fscanf(file, "\n");
	}

	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
		    
		    //copy the contents of the board into 'arr' which is passed as paramter to the function 
			arr[i][j] = board[i][j];
		}
	}
	int count = 0;
	while (fscanf(file, "%s %d %d", players[count].id, &players[count].player_number, &players[count].score) != EOF && count < 9) {
  		
  		//did this to find the number of players
  		count++;
	}

	for( int i=0; i<row; i++)
    {
        for (int j=0; j<col; j++)
        {
			if(board[i][j] < 10)
				printf("0%d ", board[i][j]);
			else
				printf("%d ", board[i][j]);
        }
        printf("\n");
    }

	fclose(file);
	
	// Now to find the no of players, depending on the 'return_score' parameter the function will return the no of players or the no of penguins(for more clarity go to penguin.c)
	if(return_score)
		return players[0].score;
	else
		return count;
}

//This is the reading function for the placement phase 

int read_board(const char *filename, struct Player players[9], int **arr, int no_of_players, int how_many_penguins) {
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

    int count = 0;
	while (fscanf(file, "%s %d %d", players[count].id, &players[count].player_number, &players[count].score) != EOF && count < 9) {
  		count++;
	}

    for(;;){
	    char tempname[100];
	    int newPlayer = 1; //1 or 0
	    int nameTaken = 0; //1 or 0

        printf("Input player's ID: ");
        scanf("%s", tempname);

        for(i = 0; i <= 5; i++){                                                    // 5 BC WE ARE TEAM NUMBER 6 (you know, team numbers start from 0)
            if(strcmp(tempname, players[i].id) == 0){
               printf("player '%s' already exists. proceeding\n", tempname);
                newPlayer = 0;                                                      //You're not a new player! You are already on the board!
                if(i != 5){
                    printf("it's not you. Input a new name\n");
                    nameTaken = 1;
                }
                break;
            }
        }
        if(newPlayer == 1){
        strcpy(players[5].id, tempname);                                            // 5 BC WE ARE TEAM NUMBER 6
        players[5].score = 0;
	    }
	    if(nameTaken == 0){
	        break;
	    }
	    nameTaken = 0;
    }

/*                                                                              COMMENTED OUT. DOESN'T DO ANYTHING ANYWAY. I AM LEAVING IT HERE JUST IN CASE.

	for(int i = 0; i < no_of_players; i++) {
		fprintf(file, "%s %d %d \n", players[i].id, i + 1, players[i].score);
	}
*/

	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			arr[i][j] = board[i][j];
		}
	}

	fclose(file);
	return 0;
}

//This is the function for writing the boardd in the file during the placement phase  

int write_board(const char *inFile, const char *outFile, int phase, struct Player players[9], int **board, int size[], int no_of_players, int how_many_penguins) {

	int row, col;
	row = size[0];
	col = size[1];

	// PRINTING BOARD DIMENSIONS

	FILE *outfile = fopen(outFile, "w+");
	fprintf(outfile, "%d %d\n", row, col);

	if (phase == 1) {

		int temp[no_of_players];
		int place_row, place_col;
		srand(time(NULL));
		
		//initialising ID to each player and each penguin / EDIT: TO OUR PENGUIN
		/*
		for(int play = 0; play < no_of_players; ++play) {
			for(int i = 0; i < how_many_penguins; ++i) {
				players[play].player_number = (play + 1);
				players[play].penguins[i].peng_no = i + 1;
			}
		}*/

		players[5].player_number = 6;

		for(int i = 0; i < how_many_penguins; ++i) {
		    players[5].penguins[i].peng_no = i + 1;
		}

        if(players[5].score < how_many_penguins){                               //CHECK IF NOT TOO MUCH PENGUINS ON BOARD
            place_row = rand() % row;
			place_col = rand() % col;

			while(!(board[place_row][place_col] == 10)){                        //IF INCORRECT TILE RANDOMLY CHOSEN, FINDING BETTER ONE IS ATTEMPTED IN A LOOP
					place_row = rand() % row;
					place_col = rand() % col;
			}

			for (int i = 0; i < row; ++i) {
				for (int j = 0; j < col; ++j) {
					if(i == place_row && j == place_col) {
						temp[5] = board[i][j];
						board[i][j] = players[5].player_number;                 //NAMELY 6
						players[5].score += 1;                                  //INCREMENT POINTS FOR PINGU PLACEMENT. IT'S += 1 INSTEAD OF ++ BECAUSE LATTER DOESN'T WANT TO WORK
					}
				}
			}

        }
        else
        {
            printf("ALL PENGUINS ALREADY PLACED\n");
        }

        /*
		for (int play = 0; play < no_of_players; ++play) {                      //TO THE TRASHCAN IT GOOOOOOEEEEEEEEESSSS!!! (leaving just in case)
			for(int i = 0; i < how_many_penguins; ++i){

				place_row = rand() % row;
				place_col = rand() % col;

				while(!(board[place_row][place_col] == 10)){
					place_row = rand() % row;
					place_col = rand() % col;
				}

				// printf("row = %d col = %d\n", place_row, place_col );
				for (int i = 0; i < row; ++i) {
					for (int j = 0; j < col; ++j) {

						if(i == place_row && j == place_col) {
							temp[play] = board[i][j];
							board[i][j] = players[play].player_number;
						}
					}
				}

			}
		}*/

    // PRINTING THE CONTENTS OF THE BOARD

		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < col; ++j) {
				if(board[i][j] < 10)
					fprintf(outfile, "0%d ", board[i][j]);
				else
					fprintf(outfile, "%d ", board[i][j]);
			}
			fprintf(outfile, "\n");
		}

		// Updating the score of each player's penginus and also the player's total score           //NOT NEEDED NOW; LEAVING JUST IN CASE
		/*for(int play = 0; play < no_of_players; ++play) {
			for(int q = 0; q < how_many_penguins;++q) {
				players[play].penguins[q].score_of_penguin += (temp[play] / 10);
				// printf("%d %d \n", players[play].player_number, players[play].penguins[q].score_of_penguin );

				players[play].score += players[play].penguins[q].score_of_penguin;
				// printf("%d %d\n",players[play].player_number,players[play].score  );
			}
		}	*/

        // PRINTING THOSE SCORES AT THE END

		for (int i = 0; i < no_of_players; ++i){
		    if((players[i].player_number > 0)&&(players[i].player_number < 10)){  //THANKS TO THIS LINE THE PROGRAM WILL NOT PRINT RANDOM TRASHY DATA OF NONEXISTENT PLAYERS
			fprintf(outfile, "%s %d %d\n", players[i].id, players[i].player_number, players[i].score);
		    }
		}


				                //===================================SECOND PHASE HERE!!!===================================
			                    //===================================SECOND PHASE HERE!!!===================================
	} else if(phase == 2) {     //===================================SECOND PHASE HERE!!!===================================
	                            //===================================SECOND PHASE HERE!!!===================================
	                            //===================================SECOND PHASE HERE!!!===================================


		FILE *file = fopen("pengus", "r");                                      //pengus?
		fscanf(file, "%d", &how_many_penguins);
		fclose(file);

		//LOOKING FOR PENGUINS
		
		int k=0;
    	int pengCoords[3][9];
    	int found_penguins=0;

		for(int i=0; i<row; i++)
		{
        	for(int j=0; j<col; j++)
        	{
            	if(board[i][j]==6)  //TEAM NUMBER 6!!!!!!!
            	{
              		found_penguins++;
               		pengCoords[k][0]=found_penguins;
              		pengCoords[k][2]=i;
              		pengCoords[k][1]=j;
					k++;
            	}
        	}
		}

 		int chosen_penguin;
		printf("found %d\n", found_penguins);
		
		//CHOOSE ONE PENGUIN RANDOMLY
		
    	srand(time(NULL));
    	chosen_penguin= rand()% (found_penguins) +1;
		printf("how many: %d\nchosen peng: %d\n", found_penguins, chosen_penguin);
    	printf("peng number: %d x: %d y: %d\n", pengCoords[chosen_penguin-1][0], pengCoords[chosen_penguin-1][1], pengCoords[chosen_penguin-1][2]);


		int y=pengCoords[chosen_penguin-1][1];
		int x=pengCoords[chosen_penguin-1][2];
		
		//==============AI==============
		//moving penguin
		int score=0;			
		
		//MOVEMENT PHASE (there is still one possibility to get a segmentation error, I will fix it later)
		
		if(board[x - 1][y] >= 10 && board[x - 1][y] <= 30) //up
		{
			score+=board[x-1][y]/10;
			players[5].score+=board[x-1][y]/10;                          //players[5].score, because we're team 6, so we're player 5
			board[x][y]=0;
			board[x-1][y]=6;
			printf("Decided to move penguin up\n");
		}
		else if(board[x + 1][y] >= 10 && board[x + 1][y] <= 30) //down
		{
			score+=board[x+1][y]/10;
			players[5].score+=board[x+1][y]/10;
			board[x][y]=0;
			board[x+1][y]=6;
			printf("Decided to move penguin down\n");
		}
		else if(board[x][y+1] >= 10 && board[x][y+1] <= 30) //right
		{
			score+=board[x][y+1]/10;
			players[5].score+=board[x][y+1]/10;
			board[x][y]=0;
			board[x][y+1]=6;
			printf("Decided to move penguin to the right\n");
		}
		else if(board[x][y-1] >= 10 && board[x][y-1] <= 30) //left
		{
			score+=board[x][y-1]/10;
			players[5].score+=board[x][y-1]/10;
			board[x][y]=0;
			board[x][y-1]=6;
			printf("Decided to move penguin to the left\n");
		}
		else
		{
			printf("Penguin can't move");
		}

		printf("\nscore after this move: %d\n", score);
		printf("score which you'll see updated in a file: %d\n", players[5].score);
/////////

		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < col; ++j) {
				if(board[i][j] < 10)
					fprintf(outfile, "0%d ", board[i][j]);
				else
					fprintf(outfile, "%d ", board[i][j]);
			}
			fprintf(outfile, "\n");
		}

		printf("players: %d\n", no_of_players);
		for (int i = 0; i < no_of_players; ++i)
			fprintf(outfile, "%s %d %d\n", players[i].id, players[i].player_number, players[i].score);
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

//PROGRAM PRINTS SOME INFORMATIONS WHICH ARE USELESS IN FINAL GAME, BUT IT IS FOR US TO CHECK IF EVERYTHING IS OKEY

// printing players id function
/*int give_id()
{


	return 0;
}
*/


