#pragma once 
#include "penguin.h"

struct Player {
	char id[100];
	int player_number;
  	int score;
  	struct penguin penguins[9];
};

// int give_ID (const char *filename ,struct Player player) ;

// int find_player_position(struct Player , int  **board, int size[], int );