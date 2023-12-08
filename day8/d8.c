#include "d8.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct direction{
    char name[4];
    char left[4];
    char right[4];
}direction;

u_int64_t gcd(u_int64_t a, u_int64_t b){
    if(b == 0){
        return a;
    }
    return gcd(b, a%b);
}

u_int64_t lcm(u_int64_t a, u_int64_t b){
    return (a/gcd(a,b))*b;
}

void Day8(){
    FILE *file = fopen("../day8/input.txt", "r");
    char ch;
    size_t lines = 1;
    while (!feof(file))
    {
        ch = fgetc(file);
        if(ch == '\n'){
            lines++;
        }
    }
    direction **directions = malloc(sizeof(direction*)*(lines-2));
    rewind(file);
    char instructions[512] = {};
    fgets(instructions, sizeof instructions, file);
    size_t instructionCount = strlen(instructions)-1;
    char buffer[32];
    fgets(buffer, sizeof buffer, file);
    size_t index = 0;
    while (fgets(buffer, sizeof buffer, file)!=NULL)
    {
        directions[index] = malloc(sizeof(direction));
        strncpy(directions[index]->name, buffer, 3);
        strncpy(directions[index]->left, buffer+7,3);
        strncpy(directions[index]->right, buffer+12, 3);
        index++;
    }
    
    direction *current;
    for (size_t i = 0; i < index; i++)
    {
        if(strncmp(directions[i]->name, "AAA", 3)==0){
            current = directions[i];
            break;
        }
    }
    size_t instructionIndex = 0;
    __uint64_t count = 0;
    while (strncmp(current->name, "ZZZ", 3)!=0)
    {
        int found = 0;
        for (size_t i = 0; i < index; i++)
        {
            if(found == 1){
                break;
            }
            switch (instructions[instructionIndex])
            {
            case 'L':
                if(strncmp(current->left, directions[i]->name, 3)==0){
                    current = directions[i];
                    instructionIndex = (instructionIndex + 1)%instructionCount;
                    found = 1;
                    count++;
                }
                break;
            case 'R':
                if(strncmp(current->right, directions[i]->name, 3)==0){
                    current = directions[i];
                    instructionIndex = (instructionIndex + 1)%instructionCount;
                    found = 1;
                    count++;
                }
                break;
            default:
                break;
            }
        }
    }
    printf("%llu\n", count);
    

    size_t a_count = 0;
    for (size_t i = 0; i < index; i++)
    {
        if(directions[i]->name[2]=='A'){
            a_count++;
        }
    }
    direction **part_two = malloc(sizeof(direction*)*a_count);
    size_t a_index = 0;
    for (size_t i = 0; i < index; i++)
    {
        if(directions[i]->name[2]=='A'){
            part_two[a_index] = directions[i];
            a_index++;
        }
    }
    instructionIndex = 0;
    int is_z = 0;
    int check[a_count] = {};
    u_int64_t all_steps[a_count];
    #pragma omp parallel for
    for (size_t j = 0; j < a_count; j++)
    {
        instructionIndex = 0;
        int steps = 0;
        while (!(part_two[j]->name[2] == 'Z'))
        {
            steps++;
            int found = 0;
            for (size_t i = 0; i < index; i++)
            {
                if(found == 1){
                    break;
                }
                switch (instructions[instructionIndex])
                {
                case 'L':
                    if(strncmp(part_two[j]->left, directions[i]->name, 3)==0){
                        part_two[j] = directions[i];
                        instructionIndex = (instructionIndex + 1)%instructionCount;
                        found = 1;
                    }
                    break;
                case 'R':
                    if(strncmp(part_two[j]->right, directions[i]->name, 3)==0){
                        part_two[j] = directions[i];
                        instructionIndex = (instructionIndex + 1)%instructionCount;
                        found = 1;
                    }
                    break;
                default:
                    break;
                }
            }
        }
        all_steps[j] = steps;
    }
    u_int64_t result = 1;
    for (size_t i = 0; i < a_count; i++)
    {
        result = lcm(result, all_steps[i]);
    }
    printf("%llu\n", result);
}