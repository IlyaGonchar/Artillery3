#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>   //Для sin, sinf, sinl

const double PI = 3.141592653589793238463;    //value of pi
const double G = 9.80665;   //value acceleration of free fall

int numPlayers = 0;
int nowPlayer = 0;
int nowTarget = 0;
int iter = 0;
float angle = 0;
float dist, erate, edist, etdist;
int temp;
char tempStr[3];

float field[3][3] = {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
};
int speed[3] = {0, 0, 0};

int midle_game(){
    temp = numPlayers;
    while (temp >= 2) {
        iter += 1;
        printf("\n\nROUND %d", iter);
        for (int i = 0; i < numPlayers; i++) {
            if (speed[i] == 0) continue;
            nowPlayer = i;
            if (numPlayers == 3) {
                printf("\n\nPLAYER %d SHOOTING TO = ", nowPlayer);
                scanf("%d", &nowTarget);
                while (nowTarget > 2 || nowTarget < 0 || nowPlayer == nowTarget)
                {
                    printf("ERROR--PLAYERS DESIGNATED 1,2,3 AND NOT YOU AND NOT LOSERS.");
                    printf("\n\nPLAYER %d SHOOTING TO = ", nowPlayer);
                    scanf("%d", &nowTarget);
                    if (speed[nowTarget] == 0) nowTarget = -1;
                }
            }
            else {
                nowTarget = numPlayers - 1 - i;
                printf("\n\nPLAYER %d SHOOTING TO = %d", nowPlayer, nowTarget);
            }

            printf("\nFIRING ANGLE = ");
            scanf("%f", &angle);
            while (angle > 180 && angle < 0)
            {
                printf("\nERROR--FIRED! 0 < ANGLE <= 180");
                printf("\nPLAYER %d SHOOTING TO = ", nowPlayer);
                scanf("%f", &angle);
            }
            if (angle >= 90) {
                printf("\nERROR--FIRED WRONG WAY, LOSE SHOT.");
            }
            else {
                srand(time(NULL)); // Новое время для случайного числа
                float rand1 = ((float)rand() / (float)(RAND_MAX) * 1.0);
                dist = sinf(2 * angle / 180 * PI) * speed[nowPlayer] * speed[nowPlayer] / G;
                erate = field[nowPlayer][nowTarget] / 1000 * rand1;
                edist = dist * erate + dist;
                etdist = field[nowPlayer][nowTarget] * 0.05;
                printf("\ndist = %f", dist);
                if (edist < etdist) {
                    printf("\nTOO CLOSE TO - %d IS DEFUNCT.", nowTarget);
                }
                else if (abs(edist - field[nowPlayer][nowTarget]) < etdist) {
                    printf("\nA HIT - %d IS DEFUNCT.", nowTarget);
                    speed[nowTarget] = 0;
                }
                else if (edist < field[nowPlayer][nowTarget]) {
                    dist = abs(edist - field[nowPlayer][nowTarget]);
                    printf("\nYOU UNDERSHOT BY %f FEET.", dist);
                }
                else if (edist > field[nowPlayer][nowTarget]) {
                    dist = abs(edist - field[nowPlayer][nowTarget]);
                    printf("\nYOU OVERSHOT BY %f FEET.", dist);
                }
            }
            temp = 0;
            for (int i = 0; i < numPlayers; i++) {
                if (speed[i] == 0) temp--;
            }
            if (temp < 2) break;
        }
    }
    return 0;  
}

int start_game(){
    printf("\nARTILLERY 3");
    printf("\nMORRISTOWN, NEW JERSEY");

    printf("\nWELCOME TO 'WAR3'. TWO OR THREE HUMANS MAY PLAY!");
    /*printf("\nDO YOU WISH SOME ASSISTANCE: ");

    scanf("%s", &tempStr);
    if (tempStr == "YES" || tempStr == "yes" || tempStr == "Yes") {
        printf("\n\nTHIS IS A WAR GAME. TWO OR THREE PLAYERS ARE GIVEN");
        printf("\n(THEORETICAL) CANNONS WITH WHICH THEY ATTEMPT TO SHOOT EACH");
        printf("\nOTHER. THE PARAMETERS FOR DISTANCES AND MUZZLE VELOCITIES ARE");
        printf("\nSET AT THE BEGINNING OF THE GAME. THE SHOTS ARE FIRED BY");
        printf("\nGIVING A FIRING ANGLE, EXPRESSED IN DEGREES FROM HORIZONTAL");
        printf("\n\nTHE COMPUTER WILL KEEP TRACK OF THE GAME AND REPORT ALL");
        printf("\nMOVES. A 'HIT' IS SCORED BY FIRING A SHOT WITHIN 5% OF THE");
        printf("\nTOTAL DISTANCE FIRED OVER. GOOD LUCK\n\n");
    }*/

    printf("\nNUM OF PLAYERS = ");
    scanf("%d", &numPlayers);
    if (numPlayers != 2 && numPlayers != 3){
        printf("ERROR--TWO OR THREE PLAYERS!");
        return -1;
    }


    // 290-440
    // Set distance from player to player
    for (int i = 0; i < numPlayers; i++){
        for (int j = 0; j < numPlayers; j++) {
            if (j != i && field[i][j] == 0) {
                printf("\nDISTANCE (FT.) %d TO Player%d = ", i, j);
                int d = 0;
                scanf("%d", &d);
                field[i][j] = d;
                field[j][i] = d;
            }
        }
    }
    // 380-440
    // Set shooting speed player
    for (int i = 0; i < numPlayers; i++){
        printf("\nMUZZLE VELOCITY (FT./SEC.) OF Player %d = ", i);
        scanf("%d", &speed[i]);
    }
    return 0;
}
int main() { // (10 - 20) 
    printf("                    BINARY");
    printf("\n  CREATIVE COMPUTING  MORRISTOWN NEW JERSEY\n");

    start_game();
    midle_game();
    printf("\nGAME OVER. PLAYER#%d WINS.", nowPlayer);
}
