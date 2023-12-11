#include "d11.h"
#include <stdio.h>
#include <stdlib.h>

#define SIZE 140

#define EXPANSION 999999 // THIS SHOULD BE 1000000 WHY DOES IT ONLY WORK WITH 999999

typedef struct Galaxy {
	int64_t x;
	int64_t y;
} Galaxy;

void Day11() {
	FILE *file = fopen("../day11/input.txt", "r");
	char buffer[SIZE][SIZE + 2];
	for (size_t i = 0; i < SIZE; i++) {
		fgets(buffer[i], SIZE + 2, file);
	}
	fclose(file);
	bool empty[2][SIZE] = {};
	size_t row_count = 0;
	size_t col_count = 0;
	size_t galaxy_count = 0;
	for (size_t i = 0; i < SIZE; i++) {
		for (size_t j = 0; j < SIZE; j++) {
			if (buffer[i][j] == '#') {
				galaxy_count++;
			}
		}
		int is_empty_row = 1;
		int is_empty_col = 1;
		for (size_t j = 0; j < SIZE - 1; j++) {
			if (buffer[i][j] != buffer[i][j + 1]) {
				is_empty_row = 0;
			}
			if (buffer[j][i] != buffer[j + 1][i]) {
				is_empty_col = 0;
			}
		}
		if (is_empty_row) {
			empty[0][i] = 1;
			row_count++;
		}
		if (is_empty_col) {
			empty[1][i] = 1;
			col_count++;
		}
	}
	printf("GalaxyCount: %zu\nEmptyRows: %zu\nEmptyCols: %zu\n", galaxy_count, row_count, col_count);

	Galaxy *galaxies = (Galaxy *) malloc(sizeof(Galaxy) * galaxy_count);
	Galaxy *far_galaxies = (Galaxy *) malloc(sizeof(Galaxy) * galaxy_count);
	size_t index = 0;
	for (size_t i = 0; i < SIZE; i++) {
		for (size_t j = 0; j < SIZE; j++) {
			if (buffer[i][j] == '#') {
				galaxies[index].x = (int64_t) j;
				galaxies[index].y = (int64_t) i;
				far_galaxies[index].x = (int64_t) j;
				far_galaxies[index].y = (int64_t) i;
				index++;
			}
		}
	}
	size_t count_x = 0;
	size_t count_y = 0;
	for (size_t i = 0; i < SIZE; i++) {
		if (empty[1][i]) {
			for (size_t j = 0; j < galaxy_count; j++) {
				if (galaxies[j].x > i + count_x) {
					galaxies[j].x++;
					far_galaxies[j].x += EXPANSION;
				}
			}
			count_x++;
		}
		if (empty[0][i]) {
			for (size_t j = 0; j < galaxy_count; j++) {
				if (galaxies[j].y > i + count_y) {
					galaxies[j].y++;
					far_galaxies[j].y += EXPANSION;
				}
			}
			count_y++;
		}
	}
	int64_t sum = 0;
	int64_t sum_far = 0;
	for (size_t i = 0; i < galaxy_count - 1; ++i) {
		for (size_t j = i + 1; j < galaxy_count; ++j) {
			sum += labs(galaxies[i].x - galaxies[j].x) + labs(galaxies[i].y - galaxies[j].y);
			sum_far += labs(far_galaxies[i].x - far_galaxies[j].x) + labs(far_galaxies[i].y - far_galaxies[j].y);
		}
	}
	free(galaxies);
	free(far_galaxies);
	printf("%ld\n", sum);
	printf("%ld\n", sum_far);
}