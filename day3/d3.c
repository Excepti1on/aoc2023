//
// Created by oliver on 03.12.2023.
//

#include "d3.h"
#include <stdint.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define GRID_SIZE 140

void Day3() {
	FILE *file = fopen("../Day3/input.txt", "r");
	char buffer[GRID_SIZE * GRID_SIZE] = {};
	for (size_t i = 0; i < GRID_SIZE; ++i) {
		fgets(buffer + i * GRID_SIZE, sizeof(buffer), file);
	}
	fclose(file);
	char digits[GRID_SIZE * GRID_SIZE] = {};
	uint64_t sum = 0;
	uint64_t sum2 = 0;
	for (size_t i = 0; i < GRID_SIZE * GRID_SIZE; ++i) {
		if (buffer[i] != '.' && !isdigit(buffer[i])) {
			uint64_t is_star = (buffer[i] == '*') ? UINT64_MAX : 0;
			uint64_t ratio = 1;
			uint64_t found = 0;
			for (size_t j = 0; j < 3; ++j) {
				for (size_t k = 0; k < 3; ++k) {
					if (isdigit(buffer[i + j - 1 + (k - 1) * GRID_SIZE])) {
						size_t a = 0;
						while (isdigit(buffer[i + j - 1 + (k - 1) * GRID_SIZE - a])) {
							a++;
						}
						if (digits[i + j - 1 + (k - 1) * GRID_SIZE - a + 1] == 0) {
							digits[i + j - 1 + (k - 1) * GRID_SIZE - a + 1] = 1;
							sum += strtoull(buffer + i + j - 1 + (k - 1) * GRID_SIZE - a + 1, NULL, 10);
							ratio *= strtoull(buffer + i + j - 1 + (k - 1) * GRID_SIZE - a + 1, NULL, 10) & is_star;
							found += is_star >> 63;
						}
					}
				}
			}
			if (found == 2) {
				sum2 += ratio;
			}
		}
	}
	printf("%llu\n", sum);
	printf("%llu\n", sum2);
}