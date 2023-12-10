//
// Created by oli on 12/10/23.
//

#include "d10.h"
#include <stdio.h>

typedef enum Move {
	UP,
	RIGHT,
	DOWN,
	LEFT
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
	//Find Where to go from S
	int last_move;
	if (buffer[y - 1][x] == '|' || buffer[y - 1][x] == 'F' || buffer[y - 1][x] == '7') {
		x = x;
		y = y - 1;
		last_move = UP;
	} else if (buffer[y][x + 1] == '-' || buffer[y][x + 1] == '7' || buffer[y][x + 1] == 'J') {
		x = x + 1;
		y = y;
		last_move = RIGHT;
	} else if (buffer[y + 1][x] == '|' || buffer[y + 1][x] == 'F' || buffer[y + 1][x] == '7') {
		x = x;
		y = y + 1;
		last_move = DOWN;
	} else if (buffer[y][x - 1] == '-' || buffer[y][x - 1] == 'L' || buffer[y][x - 1] == 'F') {
		x = x - 1;
		y = y;
		last_move = LEFT;
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
			default:
				printf("error");
				break;
		}
		result++;
	}
	//result/2 because the loop is double the longest step Count
	printf("%d\n", result / 2);

	//don't ask me why it works
	int count = 0;
	for (int i = 0; i < SIZE_Y; ++i) {
		for (int j = 0; j < SIZE_X; ++j) {
			int below = -1;
			//if we are on a visited pipe we cant be inside
			if (visited[i][j] == 1) {
				continue;
			}
			//ray cast to the right
			int intersections = 0;
			for (int k = j; k < SIZE_X; ++k) {
				//the first column cant be inside, I don't know why it sometimes thinks it is
				if(k == 0){
					break;
				}
				//we have hit a possible intersection
				if (visited[i][k] == 1) {
					// track if we came from below, only if we exit up do we have an intersections
					if (buffer[i][k] == 'F') {
						below = 1;
					} else if (buffer[i][k] == 'L') {
						below = 0;
					} else if (buffer[i][k] == 'J' && below == 1) {
						intersections++;
					} else if (buffer[i][k] == '7' && below == 0) {
						intersections++;
					} else if (buffer[i][k] == '|') { // default case , it is always an intersection
						intersections++;
					} else if(buffer[i][k] == 'S'){ //honestly fuck this case,
													// may not work with a different input, but it works with mine
						intersections++;
					}
				}
			}
			if (intersections % 2 != 0 && intersections != 0) {
				count++;
				visited[i][j] = 2;
			}
		}
	}
	printf("Inside Tiles: %d\n", count);
}
