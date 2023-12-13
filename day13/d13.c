#include "d13.h"

#include <stdio.h>
#include <string.h>

#define SIZE_X 9
#define SIZE_Y 7

void Day13() {
	FILE *file = fopen("../day13/input.txt", "r");

	int x = 0;
	int y = 0;
	int x2 = 0;
	int y2 = 0;
	int x_count = 0;
	int y_count = 0;
	int sum = 0;
	int sum2 = 0;
	while (!feof(file)) {
		size_t size_x;
		size_t size_y;
		int index;
		char buffer[100][64];
		index = 0;
		while (!feof(file)) {
			fgets(buffer[index], 64, file);
			if (buffer[index][0] == '\n') {
				break;
			}
			index++;
		}
		size_y = index;
		size_x = strlen(buffer[0]) - 1;
		bool valid_x;
		for (size_t i = 0; i < size_y - 1; i++) {
			valid_x = true;
			for (int j = i, k = i + 1; j >= 0 && k < size_y; k++, j--) {
				for (size_t l = 0; l < size_x; l++) {
					if (buffer[j][l] != buffer[k][l]) {
						valid_x &= false;
					}
				}
			}
			if (valid_x) {
				x = (i + 1);
				sum += x * 100;
				break;
			}
		}
		bool valid_y;
		for (size_t i = 0; i < size_x - 1; i++) {
			valid_y = true;
			for (int j = i, k = i + 1; j >= 0 && k < size_x; k++, j--) {
				for (size_t l = 0; l < size_y; l++) {
					if (buffer[l][j] != buffer[l][k]) {
						valid_y &= false;
					}
				}
			}
			if (valid_y) {
				y = i + 1;
				sum += y;
				break;
			}
		}
		for (size_t i = 0; i < size_y - 1; i++) {
			int diffs = 0;
			for (int j = i, k = i + 1; j >= 0 && k < size_y; k++, j--) {
				for (size_t l = 0; l < size_x; l++) {
					if (buffer[j][l] != buffer[k][l]) {
						diffs++;
					}
				}
			}
			if (diffs == 1) {
				x2 = (i + 1);
				sum2 += x2 * 100;
				break;
			}
		}
		for (size_t i = 0; i < size_x - 1; i++) {
			int diffs = 0;
			for (int j = i, k = i + 1; j >= 0 && k < size_x; k++, j--) {
				for (size_t l = 0; l < size_y; l++) {
					if (buffer[l][j] != buffer[l][k]) {
						diffs++;
					}
				}
			}
			if (diffs == 1) {
				y2 = i + 1;
				sum2 += y2;
				break;
			}
		}

	}
	printf("x: %d, y: %d\n", x, y);
	printf("SUM: %d\n", sum);
	printf("X hits: %d, Y hits: %d\n", x_count, y_count);
	printf("SUM2: %d\n", sum2);
	printf("x: %d, y: %d\n", x2, y2);
}