#include "d13.h"

#include <stdio.h>
#include <string.h>

#define SIZE_X 9
#define SIZE_Y 7

void Day13()
{
    FILE *file = fopen("../day13/input.txt", "r");

    int x = 0;
    int y = 0;
    int x2 = 0;
    int y2 = 0;
    int arrayCount = 0;
    int xCount = 0;
    int yCount = 0;
    int sum;
    while (!feof(file))
    {
        arrayCount++;
        size_t sizeX;
        size_t sizeY;
        int index;
        char buffer[100][64];
        index = 0;
        while (!feof(file))
        {
            fgets(buffer[index], 64, file);
            if (buffer[index][0] == '\n')
            {
                break;
            }
            index++;
        }
        sizeY = index;
        sizeX = strlen(buffer[0]) - 1;
        bool validX;
        for (size_t i = 0; i < sizeY - 1; i++)
        {
            validX = true;
            for (int j = i, k = i + 1; j >= 0 && k < sizeY; k++, j--)
            {
                for (size_t l = 0; l < sizeX; l++)
                {
                    if (buffer[j][l] != buffer[k][l])
                    {
                        validX &= false;
                    }
                }
            }
            if (validX)
            {
                x += (i + 1) * 100;
                break;
            }
        }
        bool validY;
        for (size_t i = 0; i < sizeX - 1; i++)
        {
            validY = true;
            for (int j = i, k = i + 1; j >= 0 && k < sizeX; k++, j--)
            {
                for (size_t l = 0; l < sizeY; l++)
                {
                    if (buffer[l][j] != buffer[l][k])
                    {
                        validY &= false;
                    }
                }
            }
            if (validY)
            {
                y += i + 1;
                break;
            }
        }
        if (validY)
        {
            printf("Valid Y\n");
        }
        bool smudge = false;
        for (size_t a = 0; a < sizeY; a++)
        {
            for (size_t b = 0; b < sizeX; b++)
            {
                if (buffer[a][b] == '.')
                {
                    buffer[a][b] = '#';
                }
                else
                {
                    buffer[a][b] = '.';
                }
                bool validX;
                for (size_t i = 0; i < sizeY - 1; i++)
                {
                    validX = true;
                    for (int j = i, k = i + 1; j >= 0 && k < sizeY; k++, j--)
                    {
                        for (size_t l = 0; l < sizeX; l++)
                        {
                            if (buffer[j][l] != buffer[k][l])
                            {
                                validX &= false;
                            }
                        }
                    }
                    if (validX)
                    {
                        x = (i + 1) * 100;
                        break;
                    }
                }
                if (validX)
                {
                    if (buffer[a][b] == '.')
                    {
                        buffer[a][b] = '#';
                    }
                    else
                    {
                        buffer[a][b] = '.';
                    }
                    sum += x;
                    smudge = true;
                    break;
                }
                bool validY;
                for (size_t i = 0; i < sizeX - 1; i++)
                {
                    validY = true;
                    for (int j = i, k = i + 1; j >= 0 && k < sizeX; k++, j--)
                    {
                        for (size_t l = 0; l < sizeY; l++)
                        {
                            if (buffer[l][j] != buffer[l][k])
                            {
                                validY &= false;
                            }
                        }
                    }
                    if (validY)
                    {
                        y = i + 1;
                        break;
                    }
                }
                if (validX)
                {
                    if (buffer[a][b] == '.')
                    {
                        buffer[a][b] = '#';
                    }
                    else
                    {
                        buffer[a][b] = '.';
                    }
                    sum += y;
                    smudge = true;
                    break;
                }
            }
            if(smudge){
                break;
            }
        }
    }
    printf("x: %d, y: %d\n", x, y);
    printf("SUM: %d\n", y + x);
    printf("Fields: %d\n", arrayCount);
    printf("X hits: %d, Y hits: %d\n", xCount, yCount);
    printf("SUM2: %d\n", sum);
}