//
// Created by oliver on 01.12.2023.
//

#include "d1.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>

enum Mode{
    FORWARD,
    BACKWARDS
};

size_t CheckDigit(enum Mode mode, const char *buffer, size_t buffer_length) {
    size_t index_digit;
    switch (mode) {
        case FORWARD:
		  index_digit = 0;
            do{
                if(isdigit(buffer[index_digit])){
                    break;
                }
                index_digit++;
            } while (index_digit < buffer_length - 1);
            break;
        case BACKWARDS:
		  index_digit = buffer_length;
            do {
                if(isdigit(buffer[index_digit])){
                    break;
                }
                index_digit--;
            } while (index_digit != 0);
            break;
    }
    return index_digit;
}

void CheckAlpha(enum Mode mode, size_t index_digit, const char *buffer, char *number, const char alpha_numbers[10][6]) {
    size_t k;
    uint64_t index_alpha;
    switch (mode) {
        case FORWARD:
		  index_alpha = ULLONG_MAX;
            for (k = 0; k < 10; ++k) {
                char *p = strstr(buffer, alpha_numbers[k]);
                if (!p) { continue; }
                if(p-buffer < index_digit) {
                    if(p-buffer < index_alpha){
					  index_alpha = p - buffer;
                        number[0] = (char)(k+48);
                    }
                }
            }
            break;
        case BACKWARDS:
		  index_alpha = 0;
            k = strlen(buffer);
            while (k != ULLONG_MAX){
                for (size_t l = 0; l < 10; ++l) {
                    char *p = strstr(buffer+k, alpha_numbers[l]);
                    if(!p) continue;
                    if(p-buffer > index_digit){
                        if(p - buffer > index_alpha){
						  index_alpha = p - buffer;
                            number[1] = (char)(l+48);
                        }
                    }
                }
                k--;
            }
            break;
    }
}

uint64_t D11(){
    FILE *file = fopen("../day1/input.txt", "r");
    char buffer[64] = {};
    uint64_t result = 0;
    while (fgets(buffer, sizeof(buffer), file)) {
        char number[3] = {};
        size_t buffer_length = strlen(buffer);
        size_t index_digit = CheckDigit(FORWARD, buffer, buffer_length);
        number[0] = buffer[index_digit];
	  index_digit = CheckDigit(BACKWARDS, buffer, buffer_length);
        number[1] = buffer[index_digit];
        result += strtoull(number, NULL, 10);
    }
    fclose(file);
    return result;
}

uint64_t D12(){
    FILE *file = fopen("../day1/input.txt", "r");
    uint64_t result = 0;
    char buffer[64] = { };
    char alpha_numbers[10][6] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    while (fgets(buffer, sizeof(buffer), file)) {
        char number[3] = {};
        size_t buffer_length = strlen(buffer);
        size_t index_digit = CheckDigit(FORWARD, buffer, buffer_length);
        number[0] = buffer[index_digit];
	  CheckAlpha(FORWARD, index_digit, buffer, number, alpha_numbers);
	  index_digit = CheckDigit(BACKWARDS, buffer, buffer_length);
        number[1] = buffer[index_digit];
	  CheckAlpha(BACKWARDS, index_digit, buffer, number, alpha_numbers);
        result+= strtoull(number, NULL, 10);
    }
    fclose(file);
    return result;
}