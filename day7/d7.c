

#include "d7.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX(a,b) (((a)>(b))?(a):(b))

typedef struct CardGame{
    char hand[6];
    uint64_t bid;
    uint64_t rank;
    uint64_t highest_card;
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

int CardValue(CardGame *card, size_t n){
    if(isdigit(card->hand[n])){
        return card->hand[n]-'0'-2;
    }else {
        switch (card->hand[n])
            {
            case 'T':
                return 8;
                break;
            case 'J':
                return 9;
                break;
            case 'Q':
                return 10;
                break;
            case 'K':
                return 11;
                break;
            case 'A':
                return 12;
                break;
            default:
                break;
            }
    }
}

int CardValue2(CardGame *card, size_t n){
    if(isdigit(card->hand[n])){
        return card->hand[n]-'0'-2;
    }else {
        switch (card->hand[n])
            {
            case 'T':
                return 8;
                break;
            case 'J':
                return -1;
                break;
            case 'Q':
                return 9;
                break;
            case 'K':
                return 10;
                break;
            case 'A':
                return 11;
                break;
            default:
                break;
            }
    }
}

int comparefun(const void *p1, const void *p2){
    CardGame* c1 = *(CardGame**)p1;
    CardGame* c2 = *(CardGame**)p2;
    if(c1->rank > c2->rank){
        return 1;
    }else if(c1->rank < c2->rank){
        return -1;
    }else if(c1->rank == c2->rank){
        for (size_t i = 0; i < 5; i++)
        {
            if(CardValue(c1, i) == CardValue(c2, i)){
                continue;
            }else if(CardValue(c1, i) < CardValue(c2, i)){
                return -1;
            }else if(CardValue(c1, i) > CardValue(c2, i)){
                return 1;
            }
        }
    }
    return 0;
}

int comparefun2(const void *p1, const void *p2){
    CardGame* c1 = *(CardGame**)p1;
    CardGame* c2 = *(CardGame**)p2;
    if(c1->rank > c2->rank){
        return 1;
    }else if(c1->rank < c2->rank){
        return -1;
    }else if(c1->rank == c2->rank){
        for (size_t i = 0; i < 5; i++)
        {
            if(CardValue2(c1, i) == CardValue2(c2, i)){
                continue;
            }else if(CardValue2(c1, i) < CardValue2(c2, i)){
                return -1;
            }else if(CardValue2(c1, i) > CardValue2(c2, i)){
                return 1;
            }
        }
    }
    return 0;
}

void CheckValue2(CardGame * card){
    uint_fast8_t cards[12] = {};
    uint64_t value = 0;
    uint64_t jokers = 0;
    for (size_t i = 0; i < 5; i++)
    {
        if(isdigit(card->hand[i])){
            cards[(card->hand[i]-'0'-2)]++;
        }else if(isalpha(card->hand[i])){
            switch (card->hand[i])
            {
            case 'T':
                cards[8]++;
                break;
            case 'J':
                jokers++;
                break;
            case 'Q':
                cards[9]++;
                break;
            case 'K':
                cards[10]++;
                break;
            case 'A':
                cards[11]++;
                break;
            default:
                break;
            }
        }
    }        
    for (size_t i = 0; i < 12; i++)
    {
        if(cards[i]==5-jokers){
            value = MAX(value, FIVE);
        } else if(cards[i]==4-jokers){
            value = MAX(value,FOUR);
        } else if(cards[i]==3-jokers){
            for (size_t j = 0; j < 12; j++)
            {
                if(cards[j] == 2 && i != j){
                    value = MAX(value,FULL_HOUSE);
                }
            }
            value = MAX(value,THREE);
        } else if(cards[i]==2-jokers){
            for (size_t j = 0; j < 12; j++)
            {
                if(cards[j] == 3-jokers && cards[i]==2 && i != j){
                    value = MAX(value,FULL_HOUSE);
                }
                if(cards[j] == 2 && i != j){
                    value = MAX(value,TWO_PAIRS);
                }
            }
            value = MAX(value,ONE_PAIR);
        }else {
            value = MAX(value,HIGH_CARD);
        }
    }
    card->rank = value;
}
void CheckValue(CardGame *card){
    
    uint_fast8_t cards[13] = {};
    uint64_t value = 0;
    for (size_t i = 0; i < strlen(card->hand); i++)
    {
        if(isdigit(card->hand[i])){
            cards[(card->hand[i]-'0'-2)]++;
        }else if(isalpha(card->hand[i])){
            switch (card->hand[i])
            {
            case 'T':
                cards[8]++;
                break;
            case 'J':
                cards[9]++;
                break;
            case 'Q':
                cards[10]++;
                break;
            case 'K':
                cards[11]++;
                break;
            case 'A':
                cards[12]++;
                break;
            default:
                break;
            }
        }
    }    
    for (size_t i = 0; i < 13; i++)
    {
        if(cards[i]==5){
            value = MAX(value, FIVE);
        } else if(cards[i]==4){
            value = MAX(value,FOUR);
        } else if(cards[i]==3){
            for (size_t j = 0; j < 13; j++)
            {
                if(cards[j] == 2 && i != j){
                    value = MAX(value,FULL_HOUSE);
                }
            }
            value = MAX(value,THREE);
        } else if(cards[i]==2){
            for (size_t j = 0; j < 13; j++)
            {
                if(cards[j] == 3 && i != j){
                    value = MAX(value,FULL_HOUSE);
                }
                if(cards[j] == 2 && i != j){
                    value = MAX(value,TWO_PAIRS);
                }
            }
            value = MAX(value,ONE_PAIR);
        }else {
            value = MAX(value,HIGH_CARD);
        }
    }
    card->rank = value;
}

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
    CardGame **game = malloc(sizeof(CardGame*)*lines);
    for (size_t i = 0; i < lines; i++)
    {
        if(fgets(buffer, sizeof buffer, file)==NULL){
            break;
        }
        char *pch = strtok(buffer, " ");
        game[i] = malloc(sizeof(CardGame));
        strcpy(game[i]->hand, pch);
        pch = strtok(NULL, " \n");
        game[i]->bid = strtoull(pch, NULL, 10);
        CheckValue(game[i]);
    }
    qsort(game, lines, sizeof(game[0]), comparefun);
    uint64_t result = 0;
    for (size_t i = 0; i < lines; i++)
    {
        result += game[i]->bid * (i+1);
    }
    printf("Result Part one: %llu\n", result);

    for (size_t i = 0; i < lines; i++)
    {
        CheckValue2(game[i]);
    }
    qsort(game, lines, sizeof(game[0]), comparefun2);
    result = 0;
    for (size_t i = 0; i < lines; i++)
    {
        result += game[i]->bid * (i+1);
    }
    printf("Result Part two: %llu\n", result);
}