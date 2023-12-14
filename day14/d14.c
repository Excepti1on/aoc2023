//
// Created by oli on 12/14/23.
//

#include "d14.h"
#include <stdio.h>
#include <stdlib.h>
#include "../hashmap/map.h"
#include <string.h>

#define SIZE 100
static int PartOne(char **buffer);
static int NorthLoad(char **buffer);
static void Cycle(char ***input) {
	char **buffer = *input;
	//NORTH
	for (int i = 0; i < SIZE; ++i) {
		int index = 0;
		int hash_index = 0;
		while (index < SIZE) {
			int stone_count = 0;
			int dot_count = 0;
			while (index < SIZE && buffer[index][i]!='#'){
				if(buffer[index][i] == 'O'){
					stone_count++;
				}if(buffer[index][i] == '.'){
					dot_count++;
				}
				index++;
			}
			for (int j = 0; j < stone_count; ++j) {
				buffer[j+hash_index][i] = 'O';
			}
			for (int j = 0; j < dot_count; ++j) {
				buffer[j+stone_count+hash_index][i] = '.';
			}
			index++;
			hash_index = index;
		}

	}
	//WEST
	for (int i = 0; i < SIZE; ++i) {
		int index = 0;
		int hash_index = 0;
		while (index < SIZE) {
			int stone_count = 0;
			int dot_count = 0;
			while (index < SIZE && buffer[i][index]!='#'){
				if(buffer[i][index] == 'O'){
					stone_count++;
				}if(buffer[i][index] == '.'){
					dot_count++;
				}
				index++;
			}
			for (int j = 0; j < stone_count; ++j) {
				buffer[i][j+hash_index] = 'O';
			}
			for (int j = 0; j < dot_count; ++j) {
				buffer[i][j+stone_count+hash_index] = '.';
			}
			index++;
			hash_index = index;
		}

	}
	//SOUTH
	for (int i = 0; i < SIZE; ++i) {
		int index = 0;
		int hash_index = 0;
		while (index < SIZE) {
			int stone_count = 0;
			int dot_count = 0;
			while (index < SIZE && buffer[SIZE-1-(index)][i]!='#'){
				if(buffer[SIZE-1-(index)][i] == 'O'){
					stone_count++;
				}if(buffer[SIZE-1-(index)][i] == '.'){
					dot_count++;
				}
				index++;
			}
			for (int j = 0; j < stone_count; ++j) {
				buffer[SIZE-1-(j+hash_index)][i] = 'O';
			}
			for (int j = 0; j < dot_count; ++j) {
				buffer[SIZE-1-(j+stone_count+hash_index)][i] = '.';
			}
			index++;
			hash_index = index;
		}

	}
	//EAST
	for (int i = 0; i < SIZE; ++i) {
		int index = 0;
		int hash_index = 0;
		while (index < SIZE) {
			int stone_count = 0;
			int dot_count = 0;
			while (index < SIZE && buffer[i][SIZE-1-(index)]!='#'){
				if(buffer[i][SIZE-1-(index)] == 'O'){
					stone_count++;
				}if(buffer[i][SIZE-1-(index)] == '.'){
					dot_count++;
				}
				index++;
			}
			for (int j = 0; j < stone_count; ++j) {
				buffer[i][SIZE-1-(j+hash_index)] = 'O';
			}
			for (int j = 0; j < dot_count; ++j) {
				buffer[i][SIZE-1-(j+stone_count+hash_index)] = '.';
			}
			index++;
			hash_index = index;
		}
	}
}

void Day14() {
	FILE *file = fopen("../day14/input.txt", "r");
	char **buffer = calloc(SIZE, sizeof(char *));
	for (int i = 0; i < SIZE; ++i) {
		buffer[i] = calloc(SIZE + 2, sizeof(char));
	}
	for (int i = 0; i < SIZE; ++i) {
		fgets(buffer[i], SIZE+2, file);
		buffer[i][SIZE] = '\0';
	}
	int sum = PartOne(buffer);
	printf("%d\n", sum);

	hashmap *map = hashmap_create();
	int cycle = 0;
	int point = 0;
	int first = 0;
	for (int i = 0; i < 1000000000; ++i) {
		Cycle(&buffer);
		printf("%d\n", i);
		char *key = calloc(SIZE*SIZE,sizeof(char));
		for (int j = 0; j < SIZE; ++j) {
			memcpy(key + (j*SIZE), buffer[j], SIZE);
		}
		uintptr_t value;
		bool got = hashmap_get(map, key, SIZE*SIZE, &value);
		if(got){
			cycle = i - value;
			point = i;
			first = value;
			break;
		}
		hashmap_set(map, key, SIZE*SIZE, i);
	}
	int cycles = (1000000000-first)%cycle;
	for (int i = 0; i < cycles-1; ++i) {
		Cycle(&buffer);
	}
	int sum2 = NorthLoad(buffer);
	printf("%d", sum2);
}
int PartOne(char **buffer) {
	int sum = 0;
	for (int i = 0; i < SIZE; ++i) {
		int top = 0;
		for (int j = 0; j < SIZE; ++j) {
			switch (buffer[j][i]) {
				case 'O':
					sum += SIZE - top;
					top++;
					break;
				case '#':
					top = j + 1;
					break;
				default:
					break;
			}
		}
	}
	return sum;
}
int NorthLoad(char **buffer) {
	int sum = 0;
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			sum += (buffer[j][i] == 'O')?SIZE-j:0;
		}
	}
	return sum;
}
