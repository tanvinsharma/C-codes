#include "player.h"

// read the input board if arg 2 is 1 then placement else movement 
int read_board(const char *filename, struct Player [], int **board, int, int);

int read_board_mov(const char *filename, struct Player [], int **board, int return_score_for_pengus_file);

// read the input board if arg 2 is 1 then placement else movement 
int write_board(const char *, const char *, int phase, struct Player [], int **, int size[], int, int);

// find board size for memory allocation
int board_size(const char *, int size[]);

//printing players id
//int give_id(const char *filename);