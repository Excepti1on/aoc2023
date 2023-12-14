#include "d13.h"

#include <stdio.h>
#include <string.h>
#include <stdint.h>

static uint64_t Mirror(size_t size_1, size_t size_2, const char buffer[100][64], int differences, bool horizontal);

void Day13() {
	FILE *file = fopen("../day13/input.txt", "r");
	uint64_t sum = 0;
	uint64_t sum2 = 0;
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
		sum += Mirror(size_x, size_y, buffer, 0, true);
		sum += Mirror(size_y, size_x, buffer, 0, false);
		sum2 += Mirror(size_x, size_y, buffer, 1, true);
		sum2 += Mirror(size_y, size_x, buffer, 1, false);
	}
	printf("SUM: %lu\n", sum);
	printf("SUM2: %lu\n", sum2);
}

uint64_t Mirror(size_t size_1, size_t size_2, const char buffer[100][64], int differences, bool horizontal) {
	for (ssize_t i = 0; i < size_2 - 1; i++) {
		int diffs = 0;
		for (ssize_t j = i, k = i + 1; j >= 0 && k < size_2; k++, j--) {
			for (ssize_t l = 0; l < size_1; l++) {
				if (horizontal ? buffer[j][l] != buffer[k][l] : buffer[l][j] != buffer[l][k])
					diffs++;
			}
		}
		if (differences == diffs) {
			return horizontal ? (i + 1) * 100 : i + 1;
		}
	}
	return 0;
}
