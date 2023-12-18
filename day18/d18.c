#include "d18.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1024
void Day18() {
    FILE *file = fopen("../day18/input.txt", "r");
    char ch;
    int lines = 1;
    while (!feof(file)) {
        ch = fgetc(file);
        if (ch == '\n') {
            lines++;
        }
    }
    rewind(file);
    char commands[SIZE][16];
    for (size_t i = 0; i < lines; i++) {
        fgets(commands[i], 16, file);
        commands[i][14] = '\0';
    }
    fclose(file);

    int pos[2] = {0, 0};
    int lastPos[2] = {0, 0};
    int pos2[2] = {0, 0};
    int lastPos2[2] = {0, 0};
    int maxX = 0, maxY = 0;
    int sum = 0;
    long long sum2 = 0;
    int cicumference = 0, circ2 = 0;
    for (size_t i = 0; i < lines; i++) {
        lastPos[0] = pos[0];
        lastPos[1] = pos[1];
        long num = strtol(commands[i] + 2, NULL, 10);
        strtok(commands[i], "#");
        char *pch = strtok(NULL, ")");
        long long num2 = strtoll(pch, NULL, 16);
        printf("%lld\n", num2);
        lastPos2[0] = pos2[0];
        lastPos2[1] = pos2[1];
        cicumference += num;
        circ2 += num2;
        switch (commands[i][0]) {
            case 'R': {
                pos[0] += num;
                pos2[0] += num2;
                break;
            }
            case 'D': {
                pos[1] += num;
                pos2[1] += num2;
                break;
            }
            case 'L': {
                pos[0] -= num;
                pos2[0] -= num2;
                break;
            }
            case 'U': {
                pos[1] -= num;
                pos2[1] -= num2;
                break;
            }
        }
        sum += lastPos[0] * pos[1] - lastPos[1] * pos[0];
        sum2 += lastPos2[0] * pos2[1] - lastPos2[1] * pos2[0];
    }
    int result = sum / 2 + cicumference / 2 + 1;
    long long result2 = sum2 / 2 + circ2 / 2 + 1;
    printf("%d\n", result);
    printf("%lld\n", result2);
}