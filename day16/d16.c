//
// Created by oli on 12/17/23.
//

#include "d16.h"

#include <stdio.h>

#include <string.h>

#define SIZE 110

enum Direction {
	RIGHT,
	UP,
	DOWN,
	LEFT
};

struct Beam {
	int x;
	int y;
	enum Direction direction;
};

static void Path(struct Beam *beam, char buffer[SIZE][SIZE + 2], bool (*visited)[SIZE * SIZE * 4]);

void Day16() {
	FILE *file = fopen("../day16/input.txt", "r");
	char buffer[SIZE][SIZE + 2];
	for (int i = 0; i < SIZE; ++i) {
		fgets(buffer[i], SIZE + 2, file);
		buffer[i][SIZE] = '\0';
	}
	fclose(file);
	bool visited[SIZE * SIZE * 4] = {};
	Path(&(struct Beam) {0, 0, RIGHT}, buffer, &visited);
	int sum = 0;
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			sum += visited[i * SIZE + j + SIZE * SIZE * 0]
				| visited[i * SIZE + j + SIZE * SIZE * 1]
				| visited[i * SIZE + j + SIZE * SIZE * 2]
				| visited[i * SIZE + j + SIZE * SIZE * 3];
		}
	}
	printf("%d\n", sum);

	for (int j = 0; j < SIZE; ++j) {
		struct Beam *beams[4] =
			{&(struct Beam) {0, j, RIGHT},
			 &(struct Beam) {SIZE - 1, j, LEFT},
			 &(struct Beam) {j, 0, DOWN},
			 &(struct Beam) {j, SIZE - 1, UP}};
		for (int a = 0; a < 4; ++a) {
			memset(visited, false, SIZE * SIZE * 4);
			Path(beams[a], buffer, &visited);
			int temp = 0;
			for (int i = 0; i < SIZE; ++i) {
				for (int k = 0; k < SIZE; ++k) {
					temp += visited[i * SIZE + k + SIZE * SIZE * 0]
						| visited[i * SIZE + k + SIZE * SIZE * 1]
						| visited[i * SIZE + k + SIZE * SIZE * 2]
						| visited[i * SIZE + k + SIZE * SIZE * 3];
				}
			}
			sum = sum < temp ? temp : sum;
		}
	}
	printf("%d\n", sum);
}

void Path(struct Beam *beam, char buffer[SIZE][SIZE + 2], bool (*visited)[SIZE * SIZE * 4]) {
	while (true) {
		if ((*visited)[beam->y * SIZE + beam->x + beam->direction * SIZE * SIZE]
			|| beam->x >= SIZE || beam->y >= SIZE
			|| beam->x < 0 || beam->y < 0) {
			break;
		}
		(*visited)[beam->y * SIZE + beam->x + beam->direction * SIZE * SIZE] = true;
		switch (buffer[beam->y][beam->x]) {
			case '/':
				beam->direction += (beam->direction % 2) * -2 + 1;
				break;
			case '\\':
				beam->direction = (beam->direction + 2) % 4;
				break;
			case '|':
				switch (beam->direction) {
					case LEFT:
					case RIGHT:
						beam->direction = UP;
						Path(&(struct Beam) {beam->x, beam->y, DOWN}, buffer, visited);
						break;
					default:
						break;
				}
				break;
			case '-':
				switch (beam->direction) {
					case UP:
					case DOWN:
						beam->direction = RIGHT;
						Path(&(struct Beam) {beam->x, beam->y, LEFT}, buffer, visited);
						break;
					default:
						break;
				}
				break;
		}
		switch (beam->direction) {
			case RIGHT:
				beam->x++;
				break;
			case UP:
				beam->y--;
				break;
			case DOWN:
				beam->y++;
				break;
			case LEFT:
				beam->x--;
				break;
		}
	}
}