#include "d18.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define SIZE 1024
void Day18() {
	FILE *file = fopen("../day18/input.txt", "r");
	char ch;
	size_t lines = 638;
	rewind(file);
	char commands[SIZE][16];
	for (size_t i = 0; i < lines; i++) {
		fgets(commands[i], 16, file);
		commands[i][14] = '\0';
	}
	fclose(file);

	int64_t pos[2] = {0, 0};
	int64_t last_pos[2] = {0, 0};
	int64_t pos2[2] = {0, 0};
	int64_t last_pos_2[2] = {0, 0};
	int64_t sum = 0;
	int64_t sum2 = 0;
	int64_t circ = 0;
	int64_t circ2 = 0;
	for (size_t i = 0; i < lines; i++) {
		last_pos[0] = pos[0];
		last_pos[1] = pos[1];
		int64_t num = strtol(commands[i] + 2, NULL, 10);
		strtok(commands[i], "#");
		char *pch = strtok(NULL, ")");
		char number[5];
		memcpy(number, pch, 5);
		int64_t num2 = strtoll(number, NULL, 16);
		last_pos_2[0] = pos2[0];
		last_pos_2[1] = pos2[1];
		circ += num;
		circ2 += num2;
		switch (commands[i][0]) {
			case 'R':
				pos[0] += num;
				break;
			case 'D':
				pos[1] += num;
				break;
			case 'L':
				pos[0] -= num;
				break;
			case 'U':
				pos[1] -= num;
				break;
		}
		switch (pch[5]) {
			case '0':
				pos2[0] += num2;
				break;
			case '1':
				pos2[1] += num2;
				break;
			case '2':
				pos2[0] -= num2;
				break;
			case '3':
				pos2[1] -= num2;
				break;
		}
		sum += last_pos[0] * pos[1] - last_pos[1] * pos[0];
		sum2 += last_pos_2[0] * pos2[1] - last_pos_2[1] * pos2[0];
	}
	int64_t result = sum / 2 + circ / 2 + 1;
	int64_t result2 = sum2 / 2 + circ2 / 2 + 1;
	printf("%ld\n", result);
	printf("%ld\n", result2);
}