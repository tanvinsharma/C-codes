#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define RED     "\x1b[31m"
#define GRN     "\x1b[32m"
#define YLL     "\x1b[33m"
#define BLU     "\x1b[34m"
#define MAG     "\x1b[35m"
#define CYN     "\x1b[36m"
#define RES     "\x1b[0m"

int *ptrtob = NULL;
int xsize, ysize;
int playanum = 6;
int score[15][2];

int game();
int makeboard();
int output();
int input();
int main(int argc, char *argv[])
{
    
    srand(time(NULL));
    xsize = atoi(argv[1]);
    ysize = atoi(argv[2]);
    int board[xsize][ysize][2];
    ptrtob = board;
    makeboard();
    game();

    return 0;
}

int makeboard(){
    int i, j;
    int tempran;
    for(i = 0; i < (xsize * ysize); i++){
        *(ptrtob + i) = rand() % 4;
        *(ptrtob + i + (xsize * ysize)) = 0;
    }
    for(i = 1; i <= playanum;){
        tempran = rand() % (xsize * ysize);
        if(*(ptrtob + tempran + (xsize * ysize)) == 0){
            *(ptrtob + tempran + (xsize * ysize)) = i;
            i++;
        }
    }
    for(i = 0; i < 15; i++){
        for(j = 0; j < 2; j++){
            score[i][j] = 0;
        }
    }
    for(i = 1; i <= playanum; i++){
        score[i][0] = i;
    }
    
}
int output(){
    int i, j;
    printf(YLL"skorbord\n");
    for(i = 0; i < 2; i++){
        for(j = 1; j < 15; j++){
            printf("%d ", score[j][i]);
        }
        printf("\n");
    }
    printf("\n");
    for(i = 0; i < (xsize * ysize); i++){
        if(*(ptrtob + i + (xsize * ysize)) != 0){
            printf(RED"%d", *(ptrtob + i + (xsize * ysize)));
        }
        else if(*(ptrtob + i) != 0){
            printf(RES"%d", *(ptrtob + i));
        }
        else
            printf(BLU" ");
        printf(BLU"-");
        if(((i + 1) % xsize) == 0){
            printf("\n");
        }
    }
}
int input(){
    int i, j, pos;
    int n, s, w, e;
    int ndis, sdis, wdis, edis;
    int scn, scs, scw, sce;
    scn  = scs  = scw  = sce  = 0;
    ndis = sdis = wdis = edis = 0;
    n    = s    = w    = e    = 0;
    char a;
    a = getchar();
   // for(i = 0; i < 2;){
        
        //FIND PLAYER
        
        for(j = 0; j < (xsize * ysize); j++){
            if(*(ptrtob + j + (xsize * ysize)) == 1){
                pos = j;
                break;
            }
        }
        
        //FIND PLAYER
        //SCAN PLAYERS SURROUNDINGS
        
        /*if(((pos + 1) % xsize != 0)&&(*(ptrtob + pos + 1) != 0)&&((*(ptrtob + pos + 1 + (xsize * ysize)) == 0)))
            e = 1;
        if((pos % xsize != 0)&&(*(ptrtob + pos - 1) != 0)&&((*(ptrtob + pos - 1 + (xsize * ysize)) == 0)))
            w = 1;
        if((pos >= xsize)&&(*(ptrtob + pos - xsize) != 0)&&(*(ptrtob + pos - xsize + (xsize * ysize)) == 0))
            n = 1;
        if((pos < (xsize * (ysize - 1)))&&(*(ptrtob + pos + xsize) != 0)&&(*(ptrtob + pos + xsize + (xsize * ysize)) == 0))
            s = 1;*/
            
        /*if((e == 0)&&(w == 0)&&(n == 0)&&(s == 0))   //kill nigga
            *(ptrtob + pos + (xsize * ysize)) = 0;*/
        
        //SCAN PLAYERS SURROUNDINGS
        //FIND PATH NORTH
        
        j = 0;
        for(;;){
            if((pos - j >= xsize)&&(*(ptrtob + pos - j - xsize) != 0)&&(*(ptrtob + pos - j - xsize + (xsize * ysize)) == 0)/*&&(*(ptrtob + pos + j) != 3)*/){
                j += xsize;
                ndis = (pos - j);
                scn += *(ptrtob + ndis);
                printf("tup ");
            }
            else{
                break;
            }
        }
        printf("\nNORTH: pos %d e %d w %d n %d s %d disp %d sc %d\n", pos, e, w, n, s, ndis, scn);
        
        //FIND PATH NORTH
        //FIND PATH SOUTH
        
        j = 0;
        for(;;){
            if((pos + j < (xsize * (ysize - 1)))&&(*(ptrtob + pos + xsize + j) != 0)&&(*(ptrtob + pos + j + xsize + (xsize * ysize)) == 0)){
                j += xsize;
                sdis = (pos + j);
                scs += *(ptrtob + sdis);
                printf("tup ");
            }
            else{
                break;
            }
        }
        printf("\nSOUTH: pos %d e %d w %d n %d s %d disp %d sc %d\n", pos, e, w, n, s, sdis, scs);
        
        //FIND PATH SOUTH
        //FIND PATH EAST
        
        j = 0;
        for(;;){
            if(((pos + 1 + j) % xsize != 0)&&(*(ptrtob + pos + 1 + j) != 0)&&((*(ptrtob + pos + j + 1 + (xsize * ysize)) == 0))){
                j++;
                edis = (pos + j);
                sce += *(ptrtob + edis);
                printf("tup ");
            }
            else{
                break;
            }
        }
        printf("\nEAST: pos %d e %d w %d n %d s %d disp %d sc %d\n", pos, e, w, n, s, edis, sce);
        
        //FIND PATH EAST
        //FIND PATH WEST
        
        j = 0;
        for(;;){
            if(((pos - j) % xsize != 0)&&(*(ptrtob + pos - 1 - j) != 0)&&((*(ptrtob + pos - j - 1 + (xsize * ysize)) == 0))){
                j++;
                wdis = (pos - j);
                scw += *(ptrtob + wdis);
                printf("tup ");
            }
            else{
                break;
            }
        }
        printf("\nWEST: pos %d e %d w %d n %d s %d disp %d sc %d\n", pos, e, w, n, s, wdis, scw);
        
        //FIND PATH WEST
        //EVALUATE BEST PATH
        
        printf("\nhere it will evaluate where to go based on potential score to get\n");
        
        //EVALUATE BEST PATH
    //}
    
    

    
}
int game(){
    for(;;){
        output();
        input();
        //input();
    }
}