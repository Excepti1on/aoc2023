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

static void Path(struct Beam *beam,
				 char buffer[SIZE][SIZE + 2],
				 bool (*lights)[SIZE][SIZE],
				 bool (*visited)[SIZE * SIZE * 4]);

void Day16() {
	FILE *file = fopen("../day16/input.txt", "r");
	char buffer[SIZE][SIZE + 2];
	for (int i = 0; i < SIZE; ++i) {
		fgets(buffer[i], SIZE + 2, file);
		buffer[i][SIZE] = '\0';
	}
	bool lights[SIZE][SIZE] = {false};
	bool visited[SIZE * SIZE * 4] = {};
	struct Beam *beam = &(struct Beam) {0, 0, RIGHT};
	Path(beam, buffer, &lights, &visited);
	int sum = 0;
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			sum += lights[i][j];
		}
	}
	printf("%d\n", sum);
	int sum2 = 0;
	for (int j = 0; j < SIZE; ++j) {
		memset(lights, false, SIZE * SIZE);
		memset(visited, false, SIZE * SIZE * 4);
		struct Beam *beam1 = &(struct Beam) {0, j, RIGHT};
		Path(beam1, buffer, &lights, &visited);
		int temp = 0;
		for (int i = 0; i < SIZE; ++i) {
			for (int k = 0; k < SIZE; ++k) {
				temp += lights[i][k];
			}
		}
		sum2 = (sum2 < temp) ? temp : sum2;

		memset(lights, false, SIZE * SIZE);
		memset(visited, false, SIZE * SIZE * 4);
		struct Beam *beam2 = &(struct Beam) {SIZE - 1, j, LEFT};
		Path(beam2, buffer, &lights, &visited);
		temp = 0;
		for (int i = 0; i < SIZE; ++i) {
			for (int k = 0; k < SIZE; ++k) {
				temp += lights[i][k];
			}
		}
		sum2 = (sum2 < temp) ? temp : sum2;

		memset(lights, false, SIZE * SIZE);
		memset(visited, false, SIZE * SIZE * 4);
		struct Beam *beam3 = &(struct Beam) {j, 0, DOWN};
		Path(beam3, buffer, &lights, &visited);
		temp = 0;
		for (int i = 0; i < SIZE; ++i) {
			for (int k = 0; k < SIZE; ++k) {
				temp += lights[i][k];
			}
		}
		sum2 = (sum2 < temp) ? temp : sum2;

		memset(lights, false, SIZE * SIZE);
		memset(visited, false, SIZE * SIZE * 4);
		struct Beam *beam4 = &(struct Beam) {j, SIZE - 1, UP};
		Path(beam4, buffer, &lights, &visited);
		temp = 0;
		for (int i = 0; i < SIZE; ++i) {
			for (int k = 0; k < SIZE; ++k) {
				temp += lights[i][k];
			}
		}
		sum2 = (sum2 < temp) ? temp : sum2;
	}
	printf("%d\n", sum2);
}

void Path(struct Beam *beam,
		  char buffer[SIZE][SIZE + 2],
		  bool (*lights)[SIZE][SIZE],
		  bool (*visited)[SIZE * SIZE * 4]) {
	while (true) {
		if ((*visited)[beam->y * SIZE + beam->x + beam->direction * SIZE * SIZE]) {
			break;
		}
		(*lights)[beam->y][beam->x] = true;
		(*visited)[beam->y * SIZE + beam->x + beam->direction * SIZE * SIZE] = true;
		switch (buffer[beam->y][beam->x]) {
			case '/':
				switch (beam->direction) {
					case RIGHT:
						beam->direction = UP;
						break;
					case UP:
						beam->direction = RIGHT;
						break;
					case DOWN:
						beam->direction = LEFT;
						break;
					case LEFT:
						beam->direction = DOWN;
						break;
				}
				break;
			case '\\':
				switch (beam->direction) {
					case RIGHT:
						beam->direction = DOWN;
						break;
					case UP:
						beam->direction = LEFT;
						break;
					case DOWN:
						beam->direction = RIGHT;
						break;
					case LEFT:
						beam->direction = UP;
						break;
				}
				break;
			case '|':
				if (beam->direction == RIGHT || beam->direction == LEFT) {
					beam->direction = UP;
					struct Beam *new_beam = &(struct Beam) {beam->x, beam->y, DOWN};
					Path(new_beam, buffer, lights, visited);
				}
				break;
			case '-':
				if (beam->direction == UP || beam->direction == DOWN) {
					beam->direction = RIGHT;
					struct Beam *new_beam = &(struct Beam) {beam->x, beam->y, LEFT};
					Path(new_beam, buffer, lights, visited);
				}
				break;
			default:
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
		if (beam->x >= SIZE || beam->y >= SIZE || beam->x < 0 || beam->y < 0) {
			break;
		}
	}
}