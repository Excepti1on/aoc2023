#include "d11.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define SIZE 140

#define EXPANSION 1
#define EXPANSION2 999998 // THIS SHOULD BE 1000000 WHY DOES IT ONLY WORK WITH 999999

typedef struct Galaxy {
	int64_t x;
	int64_t y;
} Galaxy;

static int64_t Distance(Galaxy *g1, Galaxy *g2);

void Day11() {
	FILE *file = fopen("../day11/input.txt", "r");
	char buffer[SIZE][SIZE + 2];
	for (size_t i = 0; i < SIZE; i++) {
		fgets(buffer[i], SIZE + 2, file);
	}
	fclose(file);
	bool empty[2][SIZE] = {};
	int row_count = 0;
	int col_count = 0;
	int galaxy_count = 0;
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
	printf("GalaxyCount: %d\nEmptyRows: %d\nEmptyCols: %d\n", galaxy_count, row_count, col_count);

	Galaxy **galaxies = (Galaxy **) malloc(sizeof(Galaxy *) * galaxy_count);
	int index = 0;
	for (size_t i = 0; i < SIZE; i++) {
		for (size_t j = 0; j < SIZE; j++) {
			if (buffer[i][j] == '#') {
				galaxies[index] = (Galaxy *) malloc(sizeof(Galaxy));
				galaxies[index]->x = (int) j;
				galaxies[index]->y = (int) i;
				index++;
			}
		}
	}
	size_t count_x = 0;
	size_t count_y = 0;
	for (size_t i = 0; i < SIZE; i++) {
		if (empty[1][i]) {
			for (ssize_t j = 0; j < galaxy_count; j++) {
				if (galaxies[j]->x >  i + count_x) {
					galaxies[j]->x += EXPANSION;
				}
			}
			count_x += EXPANSION;
		}
		if (empty[0][i]) {
			for (ssize_t j = 0; j < galaxy_count; j++) {
				if (galaxies[j]->y > i + count_y) {
					galaxies[j]->y += EXPANSION;
				}
			}
			count_y += EXPANSION;
		}
	}
	int64_t sum = 0;
	for (int i = 0; i < galaxy_count - 1; ++i) {
		for (int j = i + 1; j < galaxy_count; ++j) {
			sum += Distance(galaxies[i], galaxies[j]);
		}
	}
	printf("%lld\n", sum);
	count_x = 1;
	count_y = 1;
	for (size_t i = 0; i < SIZE; i++) {
		if (empty[1][i]) {
			for (ssize_t j = 0; j < galaxy_count; j++) {
				if (galaxies[j]->x >  i + count_x) {
					galaxies[j]->x += EXPANSION2;
				}
			}
			count_x += EXPANSION2;
		}
		if (empty[0][i]) {
			for (ssize_t j = 0; j < galaxy_count; j++) {
				if (galaxies[j]->y > i + count_y) {
					galaxies[j]->y += EXPANSION2;
				}
			}
			count_y += EXPANSION2;
		}
	}
	sum = 0;
	for (int i = 0; i < galaxy_count - 1; ++i) {
		for (int j = i + 1; j < galaxy_count; ++j) {
			sum += Distance(galaxies[i], galaxies[j]);
		}
	}
	printf("%lld\n", sum);

}
int64_t Distance(Galaxy *g1, Galaxy *g2) {
	return llabs(g1->x - g2->x) + llabs(g1->y - g2->y);
}