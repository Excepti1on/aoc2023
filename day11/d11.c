#include "d11.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <math.h>

#define SIZE 10

typedef struct Galaxy
{
    int x;
    int y;
} Galaxy;

static int dist = __INT_MAX__;

static void Permute(Galaxy *galaxies, int l, int r, int count);

static void swap(Galaxy *g1, Galaxy *g2);

static int distance(Galaxy g1, Galaxy g2);

void Day11(){
    FILE * file = fopen("../day11/input.txt", "r");
    char buffer[SIZE][SIZE+2];
    for (size_t i = 0; i < SIZE; i++)
    {
        fgets(buffer[i], SIZE+2, file);
    }
    fclose(file);
    int empty[2][SIZE] = {};
    int rowCount = 0;
    int colCount = 0;
    int galaxyCount = 0;
    for (size_t i = 0; i < SIZE; i++)
    {
        for (size_t j = 0; j < SIZE; j++)
        {
            if (buffer[i][j]=='#')
            {
                galaxyCount++;
            }
            
        }
        
        int isEmptyRow = 1;
        int isEmptyCol = 1;
        for (size_t j = 0; j < SIZE-1; j++)
        {
            if(buffer[i][j] != buffer[i][j+1]){
                isEmptyRow = 0;
            }
            if(buffer[j][i] != buffer[j+1][i]){
                isEmptyCol = 0;
            }
        }
        if(isEmptyRow){
            empty[0][i] = i;
            rowCount++;
        }
        if (isEmptyCol)
        {
            empty[1][i] = i;
            colCount++;
        }
    }
    printf("GalaxyCount: %d\nEmptyRows: %d\nEmptyCols: %d\n", galaxyCount, rowCount, colCount);

    Galaxy *galaxies = (Galaxy*)malloc(sizeof(Galaxy)*galaxyCount);
    int index = 0;
    for (size_t i = 0; i < SIZE; i++)
    {
        for (size_t j = 0; j < SIZE; j++)
        {
            if (buffer[i][j]=='#')
            {
                galaxies[index].x = j;
                galaxies[index].y = i;
                index++;    
            }
        }
    }
     for (size_t i = 0; i < galaxyCount; i++)
    {
        printf("(%d,%d)\n", galaxies[i].x, galaxies[i].y);
    }
    printf("\n");
    for (size_t i = 0; i < SIZE; i++)
    {
        if(empty[0][i]){
            for (ssize_t j = galaxyCount-1; j >= 0; j--)
            {
                if(galaxies[j].x > i){
                    galaxies[j].x++;
                }
            }
        }
        if(empty[1][i]){
            for (ssize_t j = galaxyCount-1; j >= 0; j--)
            {
                if(galaxies[j].y > i){
                    galaxies[j].y++;
                }
            }
        }
    }
    for (size_t i = 0; i < galaxyCount; i++)
    {
        printf("(%d,%d)\n", galaxies[i].x, galaxies[i].y);
    }
    Permute(galaxies, 0, 9, 10);
    printf("%d", dist);
}

void Permute(Galaxy *galaxies, int l, int r, int count){
    int i;
    if(l==r){
        int localDist = 0;
        for (size_t i = 0; i < count; i+=2)
        {
            localDist += distance(galaxies[i], galaxies[i+1]);
        }
        dist = (localDist<dist)?localDist:dist;
            
    }else{
        for (i = l; i <= r; i++)
        {
            swap(galaxies+l, galaxies+i);
            Permute(galaxies, l+1, r, count);
            swap(galaxies+l, galaxies+i);
        }
        
    }
}

void swap(Galaxy *g1, Galaxy *g2){
    Galaxy temp;
    temp = *g1;
    *g1 = *g2;
    *g2 = temp;
}

int distance(Galaxy g1, Galaxy g2){
    int distance = 0;
    distance += abs(g1.x - g2.x);
    distance += abs(g1.y - g1.y);
    return distance;
}