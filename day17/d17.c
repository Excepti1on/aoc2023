//
// Created by oli on 12/17/23.
//

#include "d17.h"

#include <stdio.h>

#define SIZE 13

enum Direction{
	UP,
	RIGHT,
	DOWN,
	LEFT
};

static int Dijkstra(char **buffer, int minsteps, int maxsteps);

void Day17(){
	FILE *file = fopen("../day17/input.txt", "r");
	char buffer[SIZE][SIZE+2];
	for (int i = 0; i < SIZE; ++i) {
		fgets(buffer[i], SIZE+2, file);
		buffer[i][SIZE] = '\0';
	}
	fclose(file);
}

