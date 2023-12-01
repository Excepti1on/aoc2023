//
// Created by oliver on 01.12.2023.
//

#include "d1.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int d1_1(){
    FILE *file = fopen("../day1/input.txt", "r");
    char ch;
    int lines = 1;
    while (!feof(file)){
        ch = fgetc(file);
        if(ch == '\n'){
            lines++;
        }
    }
    rewind(file);
    char buffer[128] = {};
    int result = 0;
    for (int i = 0; i < lines; ++i) {
        fgets(buffer, sizeof(buffer), file);
        int j = 0;
        char number[3] = {};
        while (buffer[j]!='\0'){
            if(isdigit(buffer[j])){
                number[0] = buffer[j];
                break;
            }
            j++;
        }
        j = strlen(buffer);
        while (j >= 0){
            if(isdigit(buffer[j])){
                number[1] = buffer[j];
                break;
            }
            --j;
        }
        result += atoi(number);
    }
    fclose(file);
    return result;
}
int d1_2(){
    FILE *file = fopen("../day1/input.txt", "r");
    char ch;
    int lines = 1;
    while (!feof(file)){
        ch = fgetc(file);
        if(ch == '\n'){
            lines++;
        }
    }
    rewind(file);
    int result = 0;
    char alphaNumbers[10][6] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    for (int i = 0; i < lines; ++i) {
        char number[3] = {};
        char buffer[128] = { };
        fgets(buffer, sizeof(buffer), file);
        int len = strlen(buffer);
        int j = 0;
        int index1 = INT_MAX;
        while (j < len){
            if(isdigit(buffer[j])){
                break;
            }
            j++;
        }
        number[0] = buffer[j];
        for (int k = 0; k < 10; ++k) {
            char *p = strstr(buffer, alphaNumbers[k]);
            if(!p)continue;
            if(p-buffer < j) {
                if(p-buffer < index1){
                    index1 = p - buffer;
                    number[0] = k+48;
                }
            }
        }
        j = len;
        while (j >= 0){
            if(isdigit(buffer[j])){
                break;
            }
            j--;
        }
        number[1] = buffer[j];
        int k = len;
        index1 = INT_MIN;
        while (k >= 0){
            for (int l = 0; l < 10; ++l) {
                char *p = strstr(buffer+k, alphaNumbers[l]);
                if(!p) continue;
                if(p-buffer > j){
                    if(p - buffer > index1){
                        index1 = p - buffer;
                        number[1] = l+48;
                    }
                }
            }
            k--;
        }
        result+= atoi(number);
    }
    fclose(file);
    return result;
}