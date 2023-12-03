//
// Created by oliver on 03.12.2023.
//

#include "d3.h"
#include <stdint.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define GRID_SIZE 140
#define GRID 9

uint64_t D31() {
	FILE *file = fopen("../day3/input.txt", "r");
	char buffer[GRID_SIZE * GRID_SIZE];
	char digits[GRID_SIZE * GRID_SIZE] = {};
	char digits2[GRID_SIZE * GRID_SIZE] = {};
	uint64_t sum = 0;
	uint64_t sum2 = 0;
	for (size_t i = 0; i < GRID_SIZE; ++i) {
		fgets(buffer + i * GRID_SIZE, sizeof(buffer), file);
	}
	fclose(file);
	for (size_t i = 0; i < GRID_SIZE * GRID_SIZE; ++i) {
		if (buffer[i] != '.' && !isdigit(buffer[i])) {
			for (int j = 0; j < 3; ++j) {
				for (int k = 0; k < 3; ++k) {
					if (isdigit(buffer[i + j - 1 + (k - 1) * GRID_SIZE])) {
						int a = 0;
						while (isdigit(buffer[i + j - 1 + (k - 1) * GRID_SIZE - a])) {
							a++;
						}
						if (digits[i + j - 1 + (k - 1) * GRID_SIZE - a + 1] == 0) {
							digits[i + j - 1 + (k - 1) * GRID_SIZE - a + 1] = 1;
							sum += strtoull(buffer + i + j - 1 + (k - 1) * GRID_SIZE - a + 1, NULL, 10);
							printf("%llu\t",
								   strtoull(buffer + i + j - 1 + (k - 1) * GRID_SIZE - a + 1, NULL, 10));
							printf("%llu\n", i + j - 1 + (k - 1) * GRID_SIZE - a + 1);
						}
					}
				}
			}
		}
	}
	for (size_t i = 0; i < GRID_SIZE * GRID_SIZE; ++i) {
		if (buffer[i] == '*') {
			uint64_t ratio = 1;
			uint64_t found = 0;
			for (int j = 0; j < 3; ++j) {
				for (int k = 0; k < 3; ++k) {
					if (isdigit(buffer[i + j - 1 + (k - 1) * GRID_SIZE])) {
						int a = 0;
						while (isdigit(buffer[i + j - 1 + (k - 1) * GRID_SIZE - a])) {
							a++;
						}
						if (digits2[i + j - 1 + (k - 1) * GRID_SIZE - a + 1] == 0) {
							digits2[i + j - 1 + (k - 1) * GRID_SIZE - a + 1] = 1;
							ratio *= strtoull(buffer + i + j - 1 + (k - 1) * GRID_SIZE - a + 1, NULL, 10);
							found++;
							printf("%llu\t",
								   strtoull(buffer + i + j - 1 + (k - 1) * GRID_SIZE - a + 1, NULL, 10));
							printf("%llu\n", i + j - 1 + (k - 1) * GRID_SIZE - a + 1);
						}
					}
				}
			}
			if(found!=2){
				ratio = 0;
			}
			printf("Ratio: %llu\n", ratio);
			sum2 += ratio;
		}
	}
	return sum2;
}