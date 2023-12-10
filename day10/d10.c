//
// Created by oli on 12/10/23.
//

#include "d10.h"
#include <stdio.h>
#include <stdint.h>

typedef enum Move {
	UP = 1,
	RIGHT = 2,
	DOWN = 4,
	LEFT = 8
} Move;

#define SIZE_X 140
#define SIZE_Y 140

void Day10() {
	//read input
	FILE *file = fopen("../day10/input.txt", "r");
	char buffer[SIZE_Y][SIZE_X + 2];
	bool visited[SIZE_Y][SIZE_X] = {};
	int x = 0, y = 0;
	for (size_t i = 0; i < SIZE_Y; ++i) {
		fgets(buffer[i], SIZE_X + 2, file);
	}
	fclose(file);
	//find S
	for (size_t i = 0; i < SIZE_Y; ++i) {
		for (size_t j = 0; j < SIZE_X; ++j) {
			if (buffer[i][j] == 'S') {
				y = (int)i;
				x = (int)j;
				break;
			}
		}
	}
	visited[y][x] = true;
	int start_x = x;
	int start_y = y;
	//Find Where to go from S
	uint_fast8_t last_move;
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
	char s;
	switch (possibilities) {
		case 0b0011:
			s = 'L';
			break;
		case 0b0101:
			s = '|';
			break;
		case 0b0110:
			s = 'F';
			break;
		case 0b1001:
			s = 'J';
			break;
		case 0b1010:
			s = '-';
			break;
		case 0b1100:
			s = '7';
			break;
		default:
			s = 'S';
			break;
	}
	//Walk the loop
	int result = 1;
	while (buffer[y][x] != 'S') {
		visited[y][x] = true;
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
	auto count = 0;
	//kind of ray casting to find if a point is inside the shape drawn into visited
	for (size_t i = 0; i < SIZE_Y; ++i) {
		for (size_t j = 1; j < SIZE_X; ++j) {
			int last_direction = RIGHT;
			//if we are on a visited pipe we cant be inside
			if (visited[i][j]) {
				continue;
			}
			//ray cast to the right
			int intersections = 0;
			for (size_t k = j; k < SIZE_X; ++k) {
				//we have hit a possible intersection
				if (!visited[i][k]) {
					continue;
				}
				// track if we came from last_direction, only if we exit up do we have an intersections
				if (buffer[i][k] == '|'
					|| buffer[i][k] == 'J' && last_direction == UP
					|| buffer[i][k] == '7' && last_direction == DOWN) {
					intersections++;
				} else if (buffer[i][k] == 'F') {
					last_direction = UP;
				} else if (buffer[i][k] == 'L') {
					last_direction = DOWN;
				}
			}
			count += intersections % 2;
		}
	}
	printf("Inside Tiles: %d\n", count);
}