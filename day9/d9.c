#include "d9.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define NUM_COUNT 21

void Day9() {
	FILE *file = fopen("../day9/input.txt", "r");
	char buffer[128], *p_end;
	int64_t numbers[NUM_COUNT], numbers_part_two[NUM_COUNT];
	int64_t sum = 0, sum_2 = 0;
	while (fgets(buffer, sizeof buffer, file) != NULL) {
		numbers[0] = strtoll(buffer, &p_end, 10);
		for (size_t i = 0; i < NUM_COUNT - 1; i++) {
			numbers[i + 1] = strtoll(p_end, &p_end, 10);
		}
		memcpy(numbers_part_two, numbers, NUM_COUNT * sizeof(int64_t));
		for (size_t n = NUM_COUNT - 1; numbers[n] != 0; n--) {
			for (size_t i = 0; i < n; i++) {
				numbers[i] = numbers[i + 1] - numbers[i];
			}
			sum += numbers[n];
		}
		for (size_t n = 0; numbers[NUM_COUNT - n] != 0; n++) {
			for (size_t i = NUM_COUNT - 1; i > n; i--) {
				numbers_part_two[i] = numbers_part_two[i] - numbers_part_two[i - 1];
			}
		}
		for (size_t i = NUM_COUNT - 1; i > 0; i--) {
			numbers_part_two[i - 1] = numbers_part_two[i - 1] - numbers_part_two[i];
		}
		sum_2 += numbers_part_two[0];
	}
	fclose(file);
	printf("Sum: %ld\n", sum);
	printf("Sum Part 2: %ld\n", sum_2);
}