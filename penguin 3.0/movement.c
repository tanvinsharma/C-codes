//primary functions for movement

//I ALREADY IMPLEMENTED IT IN OTHER PLACES 
//LEAVING JUST IN CASE

/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct smart{
    int x;
    int y;
};

typedef smart;

static struct smart **board;
int row, col;

void board_mov(const char *filename) {

    int i = 0;

    FILE *file = fopen(filename, "r");
    fscanf(file, "%d %d", &row, &col);
    board = malloc(sizeof(struct smart*) * row);
    for (int i = 0; i < row; i++)
        board[i] = malloc(sizeof(struct smart) * col);

    char string[3];

    for (i = 0; i < row; ++i) {

        for (int j = 0; j < col; ++j) {
            //char string[2];
            fscanf(file, "%s", &string);

            board[i][j].x = string[0] - '0';
            board[i][j].y = string[1] - '0';

        }

    }

    fclose(file);
}


void print_array()
{
    for( int i=0; i<row; i++)
    {
        for (int j=0; j<col; j++)
        {
            printf("%d%d ", board[i][j].x, board[i][j].y);
        }
        printf("\n");
    }
}

struct smart find_penguin()
{
    int i, j;
    struct smart pingu[9];
    int found_penguins=0;

    for(i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
            if(board[i][j].y == 6) // THIS IS THE ID OF THE PLAYER WHO IS TO BE CONTROLLED
            {
                found_penguins++;
                pingu[found_penguins].x = i;
                pingu[found_penguins].y = j;
            }
        }
    }
    int chosen_penguin;
    printf("found %d\n", found_penguins);
    srand(time(NULL));
    chosen_penguin= rand()% (found_penguins) +1;

    return pingu[chosen_penguin];
}


//Checks if penguin can move. First checks left direction, if penguin can move it moves penguin, if not, it checks right direction and so on...
void move(int x, int y)
{
    int score=0;
    if(board[x - 1][y].x == 1 || board[x - 1][y].x == 2 || board[x - 1][y].x == 3) //left
    {
        board[x][y].x=0; //remove penguin from his tile
        score+=board[x-1][y].x; //add collected fishes to the player's score
        board[x-1][y].x=0; //remove fishes from the tile
        board[x-1][y].y=1; //place penguin from team 1 on another tile
    }
    else if(board[x + 1][y].x == 1 || board[x + 1][y].x == 2 || board[x + 1][y].x == 3) //right
    {
        board[x][y].x=0; //remove penguin from his tile
        score+=board[x+1][y].x; //add collected fishes to the player's score
        board[x+1][y].x=0; //remove fishes from the tile
        board[x+1][y].y=1; //place penguin from team 1 on another tile
    }
    else if(board[x][y-1].x == 1 || board[x][y-1].x == 2 || board[x][y-1].x == 3) //down
    {
        board[x][y].x=0; //remove penguin from his tile
        score+=board[x][y-1].x; //add collected fishes to the player's score
        board[x][y-1].x=0; //remove fishes from the tile
        board[x][y-1].y=1; //place penguin from team 1 on another tile
    }
    else if(board[x][y+1].x == 1 || board[x][y+1].x == 2 || board[x][y+1].x == 3) //up
    {
        board[x][y].x=0; //remove penguin from his tile
        score+=board[x][y+1].x; //add collected fishes to the player's score
        board[x][y+1].x=0; //remove fishes from the tile
        board[x][y+1].y=1; //place penguin from team 1 on another tile
    }
    else
    {
        board[x][y].x=0; //removing penguin
        printf("This penguin can't move. It is automatically removed from the board. Program will choose another penguin to move");

        //remove penguin from the board and choose another penguin
        //we need to implement choosing another penguin
    }
}


int main()
{

    board_mov("Board.txt");

    print_array();

    struct smart penguin;
    penguin = find_penguin();
    printf("Coordinates of chosen penguin: %d %d\n", penguin.y, penguin.x);

    move(penguin.y, penguin.x);

}
*/

