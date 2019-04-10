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
int playanum;
int score[15][2];
int k = 1;

int game();
int makeboard();
int output();
int input();
int main(int argc, char *argv[])
{
    
    srand(time(NULL));
    xsize = atoi(argv[1]);
    ysize = atoi(argv[2]);
    playanum = atoi(argv[3]);
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
    for(i = 0; i < 15; i++){
        for(j = 0; j < 2; j++){
            score[i][j] = 0;
        }
    }
    for(i = 1; i <= playanum; i++){
        score[i][0] = i;
    }
    for(i = 1; i <= playanum;){
        tempran = rand() % (xsize * ysize);
        if((*(ptrtob + tempran + (xsize * ysize)) == 0)&&(*(ptrtob + tempran) == 1)){
            *(ptrtob + tempran + (xsize * ysize)) = i;
            i++;
            *(ptrtob + tempran) = 0;
            score[(i - 1)][1] += 1;
        }
    }
    
}
int output(){
    int i, j;
    printf(YLL"scoreboard\n");
    for(i = 0; i < 2; i++){
        for(j = 1; j < 15; j++){
            if(score[j][i] >= 100)
            printf("%d ", score[j][i]);
            if(score[j][i] >= 10)
            printf("%d  ", score[j][i]);
            else
            printf("%d   ", score[j][i]);
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
    int i, j, pos, temp;
    int n, s, w, e;
    int ndis, sdis, wdis, edis;
    int scn, scs, scw, sce;
    scn  = scs  = scw  = sce  = 0;
    ndis = sdis = wdis = edis = 0;
    n    = s    = w    = e    = 0;
    int evtab[4];
    int dead = 0;
    //char a;
    //a = getchar();
    printf("\nPress enter to continue\n");
    char enter = 0;
    while (enter != '\r' && enter != '\n') { enter = getchar(); }
    //for(k = 1; k <= playanum; k++){
        
        //FIND PLAYER
        
        for(j = 0; j < (xsize * ysize); j++){
            if(*(ptrtob + j + (xsize * ysize)) == k){
                pos = j;
                break;
            }
        }
        if(pos == (xsize * ysize))
        dead = 1;
        
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
                //printf("tup ");
            }
            else{
                break;
            }
        }
        //printf("\nNORTH: pos %d e %d w %d n %d s %d disp %d sc %d\n", pos, e, w, n, s, ndis, scn);
        
        //FIND PATH NORTH
        //FIND PATH SOUTH
        
        j = 0;
        for(;;){
            if((pos + j < (xsize * (ysize - 1)))&&(*(ptrtob + pos + xsize + j) != 0)&&(*(ptrtob + pos + j + xsize + (xsize * ysize)) == 0)){
                j += xsize;
                sdis = (pos + j);
                scs += *(ptrtob + sdis);
                //printf("tup ");
            }
            else{
                break;
            }
        }
        //printf("\nSOUTH: pos %d e %d w %d n %d s %d disp %d sc %d\n", pos, e, w, n, s, sdis, scs);
        
        //FIND PATH SOUTH
        //FIND PATH EAST
        
        j = 0;
        for(;;){
            if(((pos + 1 + j) % xsize != 0)&&(*(ptrtob + pos + 1 + j) != 0)&&((*(ptrtob + pos + j + 1 + (xsize * ysize)) == 0))){
                j++;
                edis = (pos + j);
                sce += *(ptrtob + edis);
                //printf("tup ");
            }
            else{
                break;
            }
        }
        //printf("\nEAST: pos %d e %d w %d n %d s %d disp %d sc %d\n", pos, e, w, n, s, edis, sce);
        
        //FIND PATH EAST
        //FIND PATH WEST
        
        j = 0;
        for(;;){
            if(((pos - j) % xsize != 0)&&(*(ptrtob + pos - 1 - j) != 0)&&((*(ptrtob + pos - j - 1 + (xsize * ysize)) == 0))){
                j++;
                wdis = (pos - j);
                scw += *(ptrtob + wdis);
                //printf("tup ");
            }
            else{
                break;
            }
        }
        //printf("\nWEST: pos %d e %d w %d n %d s %d disp %d sc %d\n", pos, e, w, n, s, wdis, scw);
        
        //FIND PATH WEST
        //EVALUATE BEST PATH
        
        evtab[0] = scn;
        evtab[1] = scs;
        evtab[2] = sce;
        evtab[3] = scw;
        
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
        
        if(evtab[3] == scn)
        printf(RES"\nplayer %d goin north\n", k);
        else if(evtab[3] == scs)
        printf(RES"\nplayer %d goin south\n", k);
        else if(evtab[3] == sce)
        printf(RES"\nplayer %d goin east\n", k);
        else if(evtab[3] == scw)
        printf(RES"\nplayer %d goin west\n", k);
        else
        printf("\nTITBALLS! SHITASS! COKCNIPPLES! IT DOESN'T WORK! FUCK\n");
        
        //EVALUATE BEST PATH
        //KILL NIGGA
        
        if((scn == scs)&&(scs == sce)&&(sce == scw)&&(scw == 0)){
            *(ptrtob + pos + (xsize * ysize)) = 0;
            *(ptrtob + pos) = 0;                                    //DELET FISH. JUST IN CASE
            dead = 1;
        }
        if(dead == 1)
        printf(RED"\nplayer %d is DEAD\n", k);
        
        //KILL NIGGA
        //GO FOR IT!
        
        if(dead == 0){
            if(evtab[3] == scn){
                for(; pos > ndis;){
                    //printf("\nworking on it...\n");
                    pos -= xsize;
                    *(ptrtob + pos + xsize + (xsize * ysize)) = 0;
                    *(ptrtob + pos + (xsize * ysize)) = k;              //PLAYER NUMBER!!!!
                    //score[0][1] += 5; /**(ptrtob + pos);*/            //PLAYA NUMBER!!!!
                    *(ptrtob + pos) = 0;
                }
                score[k][1] += scn;
            }
            else if(evtab[3] == scs){
                for(; pos < sdis;){
                    //printf("\nworking on it...\n");
                    pos += xsize;
                    *(ptrtob + pos - xsize + (xsize * ysize)) = 0;
                    *(ptrtob + pos + (xsize * ysize)) = k;              //PLAYER NUMBER!!!!
                    //score[0][1] += 5; /**(ptrtob + pos);*/            //PLAYA NUMBER!!!!
                    *(ptrtob + pos) = 0;
                }
                score[k][1] += scs;
            }
            else if(evtab[3] == sce){
                for(; pos < edis;){
                    //printf("\nworking on it...\n");
                    pos++;
                    *(ptrtob + pos - 1 + (xsize * ysize)) = 0;
                    *(ptrtob + pos + (xsize * ysize)) = k;              //PLAYER NUMBER!!!!
                    //score[0][1] += 5; /**(ptrtob + pos);*/            //PLAYA NUMBER!!!!
                    *(ptrtob + pos) = 0;
                }
                score[k][1] += sce;
            }
            else if(evtab[3] == scw){
                for(; pos > wdis;){
                    //printf("\nworking on it...\n");
                    pos--;
                    *(ptrtob + pos + 1 + (xsize * ysize)) = 0;
                    *(ptrtob + pos + (xsize * ysize)) = k;              //PLAYER NUMBER!!!!
                    //score[0][1] += 5; /**(ptrtob + pos);*/            //PLAYA NUMBER!!!!
                    *(ptrtob + pos) = 0;
                }
                score[k][1] += scw;
            }
        }
        
        //GO FOR IT!
    //}
    

    
}
int game(){
    for(;;){
        output();
        input();
        k++;
        if(k == (playanum + 1))
        k = 1;
        //input();
    }
}
