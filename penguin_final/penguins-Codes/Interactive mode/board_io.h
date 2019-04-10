#include "player.h"

// read the input board if arg 2 is 1 then placement else movement 
int read_board(const char *filename, int phase, struct Player [], int **board, int, int);

// read the input board if arg 2 is 1 then placement else movement 
int write_board(const char *, const char *, int phase, struct Player [], int **, int size[], int, int);

// find board size for memory allocation
int board_size(const char *, int size[]);

// int find_player_position(int player_id);