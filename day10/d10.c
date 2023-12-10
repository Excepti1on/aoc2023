//
// Created by oli on 12/10/23.
//

#include "d10.h"
#include <stdio.h>

typedef enum Move {
	UP,
	RIGHT,
	DOWN = 2,
	LEFT = 4
} Move;

#define SIZE_X 140
#define SIZE_Y 140

void Day10() {
	//read input
	FILE *file = fopen("../day10/input.txt", "r");
	char buffer[SIZE_Y][SIZE_X + 2];
	int visited[SIZE_Y][SIZE_X] = {};
	int x = 0, y = 0;
	for (int i = 0; i < SIZE_Y; ++i) {
		fgets(buffer[i], SIZE_X + 2, file);
	}
	fclose(file);
	//find S
	for (int i = 0; i < SIZE_Y; ++i) {
		for (int j = 0; j < SIZE_X; ++j) {
			if (buffer[i][j] == 'S') {
				y = i;
				x = j;
				break;
			}
		}
	}
	visited[y][x] = 1;
	int start_x = x;
	int start_y = y;

	char s = 'S';
	//Find Where to go from S
	int last_move;
	int possibilities = 0;
	if (buffer[start_y - 1][start_x] == '|' || buffer[start_y - 1][start_x] == 'F'
		|| buffer[start_y - 1][start_x] == '7') {
		x = start_x;
		y = start_y - 1;
		last_move = UP;
		possibilities |= UP;
	}
	if (buffer[start_y][start_x + 1] == '-' || buffer[start_y][start_x + 1] == '7'
		|| buffer[start_y][start_x + 1] == 'J') {
		x = start_x + 1;
		y = start_y;
		last_move = RIGHT;
		possibilities |= RIGHT;
	}
	if (buffer[start_y + 1][start_x] == '|' || buffer[start_y + 1][start_x] == 'F'
		|| buffer[start_y + 1][start_x] == '7') {
		x = start_x;
		y = start_y + 1;
		last_move = DOWN;
		possibilities |= DOWN;
	}
	if (buffer[start_y][start_x - 1] == '-' || buffer[start_y][start_x - 1] == 'L'
		|| buffer[start_y][start_x - 1] == 'F') {
		x = start_x - 1;
		y = start_y;
		last_move = LEFT;
		possibilities |= LEFT;
	}
	switch (possibilities) {
		case 1:
			s = 'L';
			break;
		case 2:
			s = '|';
			break;
		case 3:
			s = 'F';
			break;
		case 4:
			s = 'J';
			break;
		case 5:
			s = '-';
			break;
		case 6:
			s = 'L';
			break;
	}

	//Walk the loop
	int result = 1;
	while (buffer[y][x] != 'S') {
		visited[y][x] = 1;
		switch (buffer[y][x]) {
			case '|':
				if (last_move == UP) {
					y--;
				} else if (last_move == DOWN) {
					y++;
				}
				break;
			case '-':
				if (last_move == RIGHT) {
					x++;
				} else if (last_move == LEFT) {
					x--;
				}
				break;
			case '7':
				if (last_move == RIGHT) {
					y++;
					last_move = DOWN;
				} else if (last_move == UP) {
					x--;
					last_move = LEFT;
				}
				break;
			case 'J':
				if (last_move == RIGHT) {
					y--;
					last_move = UP;
				} else if (last_move == DOWN) {
					x--;
					last_move = LEFT;
				}
				break;
			case 'L':
				if (last_move == DOWN) {
					x++;
					last_move = RIGHT;
				} else if (last_move == LEFT) {
					y--;
					last_move = UP;
				}
				break;
			case 'F':
				if (last_move == UP) {
					x++;
					last_move = RIGHT;
				} else if (last_move == LEFT) {
					y++;
					last_move = DOWN;
				}
				break;
		}
		result++;
	}
	//result/2 because the loop is double the longest step Count
	printf("%d\n", result / 2);
	buffer[start_y][start_x] = s;
	int count = 0;
	for (int i = 0; i < SIZE_Y; ++i) {
		for (int j = 1; j < SIZE_X; ++j) {
			int below;
			//if we are on a visited pipe we cant be inside
			if (visited[i][j] == 1) {
				continue;
			}
			//ray cast to the right
			int intersections = 0;
			for (int k = j; k < SIZE_X; ++k) {
				//we have hit a possible intersection
				if (visited[i][k] == 1) {
					// track if we came from below, only if we exit up do we have an intersections
					if (buffer[i][k] == 'J' && below == 1
						|| buffer[i][k] == '7' && below == 0
						|| buffer[i][k] == '|') {
						intersections++;
					} else if (buffer[i][k] == 'L') {
						below = 0;
					} else if (buffer[i][k] == 'F') {
						below = 1;
					}
				}
			}
			count += intersections % 2;
		}
	}
	printf("Inside Tiles: %d\n", count);
}