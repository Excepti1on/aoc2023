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
	char input[GRID_SIZE * GRID_SIZE] = {};
	for (size_t i = 0; i < GRID_SIZE; ++i) {
		fgets(input + i * GRID_SIZE, sizeof(input), file);
	}
	fclose(file);

	char digits[GRID_SIZE * GRID_SIZE] = {};
	uint64_t part_one = 0;
	uint64_t part_two = 0;

	for (size_t position = 0; position < GRID_SIZE * GRID_SIZE; ++position) {
		if (input[position] != '.' && !isdigit(input[position])) {
			uint64_t is_star = (input[position] == '*') ? UINT64_MAX : 0;
			uint64_t gear_ratio = 1;
			uint64_t gear_count = 0;

			for (size_t x = 0; x < 3; ++x) {
				for (size_t y = 0; y < 3; ++y) {
					if (isdigit(input[position + x - 1 + (y - 1) * GRID_SIZE])) {
						size_t offset = 0;
						while (isdigit(input[position + x - 1 + (y - 1) * GRID_SIZE - offset])) {
							offset++;
						}

						if (digits[position + x - 1 + (y - 1) * GRID_SIZE - offset + 1] == 0) {
							digits[position + x - 1 + (y - 1) * GRID_SIZE - offset + 1] = 1;
							part_one += strtoull(input + position + x - 1 + (y - 1) * GRID_SIZE - offset + 1, NULL, 10);
							gear_ratio *=
								strtoull(input + position + x - 1 + (y - 1) * GRID_SIZE - offset + 1, NULL, 10)
									& is_star;
							gear_count += is_star >> 63;
						}
					}
				}
			}

			part_two += (gear_count == 2) * gear_ratio;
		}
	}
	printf("%llu\n", part_one);
	printf("%llu\n", part_two);
}