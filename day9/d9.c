#include "d9.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define NUM_COUNT 21

void Day9(){
    FILE *file = fopen("../day9/input.txt", "r");
    char buffer[128];
    int64_t numbers[NUM_COUNT];
    int64_t numbers_part_two[NUM_COUNT];
    int64_t sum = 0;
    int64_t sum_2 = 0;
    char *pEnd;
    while (fgets(buffer, sizeof buffer, file)!= NULL)   
    {
        numbers[0] = strtoll(buffer, &pEnd, 10);
        numbers_part_two[0] = numbers[0];
        for (size_t i = 0; i < NUM_COUNT-1; i++)
        {
            numbers[i+1] = strtoll(pEnd, &pEnd, 10);
            numbers_part_two[i+1] = numbers[i+1];
        }
        for (size_t n = NUM_COUNT-1; n > 0; n--)
        {
            if(numbers[n]==0){
                break;
            }
            for (size_t i = 0; i < n; i++)
            {
                numbers[i] = numbers[i+1]-numbers[i];
            }
            
        }
        for (size_t i = 0; i < NUM_COUNT; i++)
        {
            sum += numbers[i];
        }
        for (size_t n = 0; n < NUM_COUNT-1; n++)
        {
            if(numbers[NUM_COUNT-n]==0){
                break;
            }
            for (size_t i = NUM_COUNT-1; i > n; i--)
            {
                numbers_part_two[i] = numbers_part_two[i]-numbers_part_two[i-1];
            }
        }
        for (ssize_t i = NUM_COUNT-1; i > 0; i--)
        {
            numbers_part_two[i-1] = numbers_part_two[i-1]-numbers_part_two[i];
        }
        sum_2 += numbers_part_two[0];
    }
    fclose(file);
    printf("Sum: %llu\n", sum);
    printf("Sum Part 2: %lld\n", sum_2);
}