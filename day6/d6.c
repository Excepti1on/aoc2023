//
// Created by oliver on 06.12.2023.
//

#include "d6.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define NUM_RACES 4

void Day6() {
	FILE *file = fopen("../day6/input.txt", "r");
	char buffer[64];
	char buffer2[64];
	fgets(buffer, sizeof buffer, file);
	fgets(buffer2, sizeof buffer2, file);
	char *pch = buffer + 6;
	char *pch1 = buffer2 + 9;
	fclose(file);
	uint64_t races[NUM_RACES][2];
	for (size_t i = 0; i < NUM_RACES; ++i) {
		races[i][0] = strtoull(pch, &pch, 10);
		races[i][1] = strtoull(pch1, &pch1, 10);
	}
	uint64_t wins[NUM_RACES] = {};
	for (size_t i = 0; i < NUM_RACES; ++i) {
		for (int j = 1; j < races[i][0]; ++j) {
			uint64_t speed = j;
			uint64_t distance = (races[i][0] - j) * speed;
			if (distance > races[i][1]) {
				wins[i]++;
			}
		}
	}
	uint64_t all_wins = 1;
	for (size_t i = 0; i < NUM_RACES; ++i) {
		all_wins *= wins[i];
	}
	printf("Part 1, 4 Races: %lu\n", all_wins);


	char *number1 = calloc(20, sizeof(char));
	char *number2 = calloc(20, sizeof(char));
	pch = strtok(buffer, " ");
	for (int i = 0; i < NUM_RACES; ++i) {
		pch = strtok(NULL, " ");
		number1 = strcat(number1, pch);
	}
	pch1 = strtok(buffer2, " ");
	for (int i = 0; i < NUM_RACES; ++i) {
		pch1 = strtok(NULL, " ");
		number2 = strcat(number2, pch1);
	}
	uint64_t time = strtoull(number1, NULL, 10);
	uint64_t distance = strtoull(number2, NULL, 10);
	free(number1);
	free(number2);

	uint64_t begin = 0;
	uint64_t end = 0;
#define BLOCK_SIZE 0x10000
	for (size_t i = 1; i <= time; i += BLOCK_SIZE) {
		uint64_t travelled = (time - i) * i;
		if (travelled > distance) {
			begin = i;
			break;
		}
	}
	for (size_t i = begin - BLOCK_SIZE; i < begin; i++) {
		uint64_t travelled = (time - i) * i;
		if (travelled > distance) {
			begin = i;
			break;
		}
	}

	for (size_t i = time; i > 0; i -= BLOCK_SIZE) {
		uint64_t travelled = i * (time - i);
		if (travelled > distance) {
			end = i;
			break;
		}
	}
	for (size_t i = end + BLOCK_SIZE; i > end; i--) {
		uint64_t travelled = i * (time - i);
		if (travelled > distance) {
			end = i;
			break;
		}
	}
	printf("Part 2, 1 Race: %lu", end - begin);
}