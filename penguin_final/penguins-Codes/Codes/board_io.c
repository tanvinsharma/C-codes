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
            if(strcmp(players[count].id, "Ping0r") == 0){
                players[9].score = players[count].score;
            }
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
            if(strcmp(players[count].id, "Ping0r") == 0){
                players[9].score = players[count].score;
            }
  		count++;
	}

    for(;;){
	    char tempname[100];
	    int newPlayer = 1; //1 or 0
	    int nameTaken = 0; //1 or 0

        //printf("Input player's ID: ");
        //scanf("%s", tempname);
        strcpy(tempname, "Ping0r");
        printf("Player's ID: %s. ", tempname);

        for(i = 0; i <= 5; i++){                                                    // 5 BC WE ARE TEAM NUMBER 6 (you know, team numbers start from 0)
            if(strcmp(tempname, players[i].id) == 0){
               printf("player '%s' already exists. proceeding\n", tempname);
                newPlayer = 0;                                                      //You're not a new player! You are already on the board!
                /*//if(i != 5){
                if(players[i].player_number != 6){
                    printf("it's not you. Input a new name\n");
                    nameTaken = 1;
                }*/
                break;
            }
        }
        if(newPlayer == 1){
        strcpy(players[9].id, tempname);                                            // 5 BC WE ARE TEAM NUMBER 6
        players[9].score = 0;
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

//This is the function for writing the board in the file during the placement phase

int write_board(const char *inFile, const char *outFile, int phase, struct Player players[9], int **board, int size[], int no_of_players, int how_many_penguins) {

	int row, col;
	row = size[0];
	col = size[1];

	// PRINTING BOARD DIMENSIONS

	FILE *outfile = fopen(outFile, "w+");
	fprintf(outfile, "%d %d\n", row, col);

	if (phase == 1) {

		int temp[10];
		int place_row, place_col;
		srand(time(NULL));

        int our_player;

        int i;

		for(i = 0; i < 10; i++){
            if((strcmp(players[i].id, "Ping0r") == 0)||(players[i].score == 0)){
                our_player = i;
                break;
            }
		}

		players[9].player_number = our_player + 1;


		//initialising ID to each player and each penguin / EDIT: TO OUR PENGUIN
		/*
		for(int play = 0; play < no_of_players; ++play) {
			for(int i = 0; i < how_many_penguins; ++i) {
				players[play].player_number = (play + 1);
				players[play].penguins[i].peng_no = i + 1;
			}
		}*/

		for(int i = 0; i < how_many_penguins; ++i) {
		    players[9].penguins[i].peng_no = i + 1;
		}

        if(players[9].score < how_many_penguins){                               //CHECK IF NOT TOO MUCH PENGUINS ON BOARD
            place_row = rand() % row;
			place_col = rand() % col;

			while(!(board[place_row][place_col] == 10)){                        //IF INCORRECT TILE RANDOMLY CHOSEN, FINDING BETTER ONE IS ATTEMPTED IN A LOOP
					place_row = rand() % row;
					place_col = rand() % col;
			}

			for (int i = 0; i < row; ++i) {
				for (int j = 0; j < col; ++j) {
					if(i == place_row && j == place_col) {
						temp[9] = board[i][j];
						board[i][j] = players[9].player_number;                 //NAMELY 6 <- not really
						players[9].score += 1;                                  //INCREMENT POINTS FOR PINGU PLACEMENT. IT'S += 1 INSTEAD OF ++ BECAUSE LATTER DOESN'T WANT TO WORK
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

        int forbiddenNum = 0;

		for (int i = 0; i < 10; ++i){
            if(strcmp(players[i].id, "Ping0r") == 0){
               fprintf(outfile, "%s %d %d\n", players[i].id, players[i].player_number, players[9].score);
               forbiddenNum = players[i].player_number;
            }else if((players[i].player_number > 0)&&(players[i].player_number < 10)&&(players[i].player_number != forbiddenNum)){  //THANKS TO THIS LINE THE PROGRAM WILL NOT PRINT RANDOM TRASHY DATA OF NONEXISTENT PLAYERS
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

		int our_player;

        for(int i = 0; i < 10; i++){
            if(strcmp(players[i].id, "Ping0r") == 0){
                our_player = i;
            break;
            }
		}

		players[9].player_number = our_player + 1;

		fclose(file);

		//LOOKING FOR PENGUINS

		int k=0;
    	int pengCoords[9][9];
    	int found_penguins=0;

for(;;){
    
        k=0;
        found_penguins=0;
        
		for(int i=0; i<row; i++)
		{
        	for(int j=0; j<col; j++)
        	{
            	if(board[i][j]== players[9].player_number)
            	{
              		found_penguins++;
               		pengCoords[k][0]=found_penguins;
              		pengCoords[k][1]=j;
              		pengCoords[k][2]=i;
					k++;
            	}
        	}
		}

 		int chosen_penguin;
		printf("\nfound %d\n", found_penguins);

		if (found_penguins == 0){
            break;
		}

		//CHOOSE ONE PENGUIN RANDOMLY

    	srand(time(NULL));
    	chosen_penguin= rand()% (found_penguins) +1;
		//printf("how many: %d\nchosen peng: %d\n", found_penguins, chosen_penguin);
    	printf("chosen penguin coords: x: %d y: %d\n", pengCoords[chosen_penguin-1][1], pengCoords[chosen_penguin-1][2]);


		int x=pengCoords[chosen_penguin-1][1];
		int y=pengCoords[chosen_penguin-1][2];

		//==============AI==============
		//==============AI==============
		//==============AI==============
		//==============AI==============
        //==============AI==============

		int i, j;
		int score = 0;      //TO BE DELETED
		int score4ai=0;     //SCORE POSSIBLE TO GATHER BY GOING IN A STRAIGHT LINE IN ONE OF THE DIRECTIONS. STANDS FOR 'SCORE FOR AI'
		int score3tiles=0;  //AS ABOVE BUT ONLY FOR THE FIRST 3 TILES (ACTUALLY CAN BE 5 TILES OR 1 TILE OR WHATEVER. THE VARIABLE NAME HAS NO EFFECT ON THAT ANYWAY)
		int firsttile;      //FIRST TILE SCORE
		int dir;            //MOVEMENT DIRECTION
		/*
		int scoreUP=0;
		int score5UP=0;
		int scoreDOWN=0;
		int score5DOWN=0;                                                       //LOL. DON'T DELET PLEASE (YET)
		int scoreLEFT=0;
		int score5LEFT=0;
		int scoreRIGHT=0;
		int score5RIGHT=0;
		*/
		float coeffUP = 0;    //NERDY COEFFICIENTS USED TO EVALUATE THE BEST PATH. CALCULATED WITH score4ai and score5tiles. THE BIGGER COEFF THE BETTER
		float coeffDOWN = 0;
		float coeffLEFT = 0;
		float coeffRIGHT = 0;

		//MOVEMENT PHASE (there is still one possibility to get a segmentation error, I will fix it later)
		//NOTE THAT X AND Y COORDINATES ARE SWAPPED IN THE BOARD[][] ARRAY (BECAUSE THE BEGINNING OF THE BOARD FILE IS FIRST ROW NUMBER AND THEN COL NUM.)

		//FRIST: SURROUNDINGS SCAN

		for(i = y; i > 0; i--){                                                 //up
		    if(board[i - 1][x] >= 10)
		    score4ai += board[i - 1][x];
		    else
		    break;
		    if((y - i) <= 2){
		        score3tiles += board[i - 1][x];
		    }
		    firsttile = board[y - 1][x];
		}
		if((y - i) != 0)
		coeffUP = (float) score4ai / (y - i) + score3tiles / 6 + firsttile / 5;
		else
		coeffUP = 0;
		//printf("sc4ai: %d, sc3t: %d dist: %d\n", score4ai, score3tiles, y - i);
		score4ai = score3tiles = 0;

		for(i = y; i < (row - 1); i++){                                         //down
		    if(board[i + 1][x] >= 10)
		    score4ai += board[i + 1][x];
		    else
		    break;
		    if((i - y) <= 2){
		        score3tiles += board[i + 1][x];
		    }
		    firsttile = board[y + 1][x];
		}
		if((i - y) != 0)
		coeffDOWN = (float) score4ai / (i - y) + score3tiles / 6 + firsttile / 5;
		else
		coeffDOWN = 0;
		//printf("sc4ai: %d, sc3t: %d dist: %d\n", score4ai, score3tiles, i - y);
		score4ai = score3tiles = 0;

		for(i = x; i < (col - 1); i++){                                         //right
		    if(board[y][i + 1] >= 10)
		    score4ai += board[y][i + 1];
		    else
		    break;
		    if((i - x) <= 3){
		        score3tiles += board[y][i + 1];
		    }
		    firsttile = board[y][x + 1];
		}
		if((i - x) != 0)
		coeffRIGHT = (float) score4ai / (i - x) + score3tiles / 6 + firsttile / 5;
		else
		coeffRIGHT = 0;
		//printf("sc4ai: %d, sc3t: %d dist: %d\n", score4ai, score3tiles, i - x);
		score4ai = score3tiles = 0;

		for(i = x; i > 0; i--){                                                 //left
		    if(board[y][i - 1] >= 10)
		    score4ai += board[y][i - 1];
		    else
		    break;
		    if((x - i) <= 3){
		        score3tiles += board[y][i - 1];
		    }
		    firsttile = board[y][x - 1];
		}
		if((x - i) != 0)
		coeffLEFT = (float) score4ai / (x - i) + score3tiles / 6 + firsttile / 5;
		else
		coeffLEFT = 0;
		//printf("sc4ai: %d, sc3t: %d dist: %d\n", score4ai, score3tiles, x - i);
		score4ai = score3tiles = 0;

		//PATH COMPARISON

		float evtab[4];
		float temp;

		//printf("coefficients: up: %f down: %f left: %f right: %f\n", coeffUP, coeffDOWN, coeffLEFT, coeffRIGHT);

		evtab[0] = coeffUP;
        evtab[1] = coeffDOWN;
        evtab[2] = coeffLEFT;
        evtab[3] = coeffRIGHT;

        for(j = 0; j < 1;){
            for(i = 1; i < 4; i++){
                if(evtab[i] < evtab[(i - 1)]){
                    temp = evtab[i];
                    evtab[i] = evtab[(i - 1)];
                    evtab[(i - 1)] = temp;
                }
                else{
                    j++;
                }
            }
        }



		//NEXT: ACTUAL MOVEMENT

		//if((y != 0) && (board[y - 1][x] >= 10) && (board[y - 1][x] <= 30)) //up
		if((y != 0) && (board[y - 1][x] >= 10) && (board[y - 1][x] <= 30) && evtab[3] == coeffUP) //up
		{
			score+=board[y-1][x]/10;
			players[9].score+=board[y-1][x]/10;                          //players[5].score, because we're team 6, so we're player 5
			board[y][x]=0;
			board[y-1][x]= players[9].player_number;
			printf("Decided to move penguin up\n");
			break;
		}
		//else if((y != (row - 1)) && (board[y + 1][x] >= 10) && (board[y + 1][x] <= 30) && (y != (row - 1))) //down
		else if((y != (row - 1)) && (board[y + 1][x] >= 10) && (board[y + 1][x] <= 30) && (y != (row - 1)) && evtab[3] == coeffDOWN) //down
		{
			score+=board[y+1][x]/10;
			players[9].score+=board[y+1][x]/10;
			board[y][x]=0;
			board[y+1][x]= players[9].player_number;
			printf("Decided to move penguin down\n");
			break;
		}
		//else if((x != (col - 1)) && (board[y][x+1] >= 10) && (board[y][x+1] <= 30)) //right
		else if((x != (col - 1)) && (board[y][x+1] >= 10) && (board[y][x+1] <= 30) && evtab[3] == coeffRIGHT) //right
		{
			score+=board[y][x+1]/10;
			players[9].score+=board[y][x+1]/10;
			board[y][x]=0;
			board[y][x+1]= players[9].player_number;
			printf("Decided to move penguin to the right\n");
			break;
		}
		//else if((x != 0) && (board[y][x-1] >= 10) && (board[y][x-1] <= 30)) //left
		else if((x != 0) && (board[y][x-1] >= 10) && (board[y][x-1] <= 30) && evtab[3] == coeffLEFT) //left
		{
			score+=board[y][x-1]/10;
			players[9].score+=board[y][x-1]/10;
			board[y][x]=0;
			board[y][x-1]= players[9].player_number;
			printf("Decided to move penguin to the left\n");
			break;
		}
		else
		{
			printf("Penguin can't move");
			board[y][x]=0;
			if (found_penguins == 1){
            break;
		}
		}

		printf("\nscore after this move: %d\n", score);
		printf("score which you'll see updated in a file: %d\n", players[9].score);
}

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

		//printf("players: %d\n", no_of_players);
		for (int i = 0; i < no_of_players; ++i)
            if(strcmp(players[i].id, "Ping0r") == 0){
               fprintf(outfile, "%s %d %d\n", players[i].id, players[i].player_number, players[9].score);
            }else{
			fprintf(outfile, "%s %d %d\n", players[i].id, players[i].player_number, players[i].score);
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

//PROGRAM PRINTS SOME INFORMATIONS WHICH ARE USELESS IN FINAL GAME, BUT IT IS FOR US TO CHECK IF EVERYTHING IS OKEY

// printing players id function
int give_id()
{
    printf("Ping0r\n");

	return 0;
}
