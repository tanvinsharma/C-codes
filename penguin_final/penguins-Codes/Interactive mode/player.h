#pragma once 
#include "penguin.h"

struct Player {
	char id[100];
	int player_number;
  	int score;
  	struct penguin penguins[9];
};