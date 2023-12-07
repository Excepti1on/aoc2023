

#include "d7.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

typedef struct CardGame{
    char hand[6];
    uint64_t bid;
    uint64_t rank;
} CardGame;

typedef enum CardValues{
    HIGH_CARD,
    ONE_PAIR,
    TWO_PAIRS,
    THREE,
    FULL_HOUSE,
    FOUR,
    FIVE,
} CardValues;

void Day7(){
    FILE *file = fopen("../day7/input.txt", "r");
    char buffer[32];
    char ch;
    size_t lines = 1;
    while (!feof(file)){
        ch = fgetc(file);
        if(ch == '\n'){
            lines++;
        }
    }
    rewind(file);

    CardGame **game = malloc(sizeof(CardGame*));
    for (size_t i = 0; i < lines; i++)
    {
        fgets(buffer, sizeof buffer, file);
        char *pch = strtok(buffer, " ");
        game[i] = malloc(sizeof(CardGame));
        strcpy(game[i]->hand, pch);
        game[i]->bid = strtoull(strtok(NULL, "/n"), NULL, 10);
        game[i]->rank = 0;
    }
    
}