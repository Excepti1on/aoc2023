//
// Created by oliver on 05.12.2023.
//

#include "d5.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define SEED_COUNT 20
#define MIN(a, b) (((a)<(b))?(a):(b))

#define BLOCK_SIZE 1024
void Day5() {
	FILE *file = fopen("../day5/input.txt", "r");
	char buffer[256];
	fgets(buffer, sizeof buffer, file);
	int64_t numbers[SEED_COUNT] = {};
	char *pch = buffer + 6;
	for (size_t i = 0; i < SEED_COUNT; ++i) {
		numbers[i] = strtoll(pch, &pch, 10);
	}
	uint64_t seedCount = 0;
	for (size_t i = 1; i < SEED_COUNT; i += 2) {
		seedCount += numbers[i];
	}
	uint32_t category = 0;
	int64_t almanac[SEED_COUNT][8] = {{}};
	for (int i = 0; i < SEED_COUNT; ++i) {
		almanac[i][0] = numbers[i];
	}

	while (fgets(buffer, sizeof buffer, file) != NULL) {
		int64_t map[3] = {};
		if (buffer[0] == '\n') {
			continue;
		}
		if (isalpha(buffer[0])) {
			category++;
			for (int i = 0; i < SEED_COUNT; ++i) {
				almanac[i][category] = almanac[i][category - 1];
			}
			continue;
		}
		pch = buffer;
		for (size_t i = 0; i < 3; ++i) {
			map[i] = strtoll(pch, &pch, 10);
		}
		int64_t diff = map[0] - map[1];
		for (size_t i = 0; i < SEED_COUNT; ++i) {
			if (almanac[i][category - 1] >= map[1] && almanac[i][category - 1] < map[1] + map[2]) {
				almanac[i][category] += diff;
			}
		}
	}
	rewind(file);
	int64_t min = INT64_MAX;
	for (int i = 0; i < SEED_COUNT; ++i) {
		min = MIN(min, almanac[i][7]);
	}
	printf("%lld\n", min);

	size_t insanity = 0;
	int64_t min2 = INT64_MAX;
	for (int x = 0; x < SEED_COUNT; x += 2) {
		printf("%lld \t%lld \t %d\t", numbers[x], numbers[x + 1], x);
		int64_t nums = numbers[x + 1];
		uint32_t *check = calloc(nums * 2, sizeof(uint32_t));
		for (int j = 0; j < nums; ++j) {
			check[j+nums] = numbers[x] + j;
		}
		category = 0;
		fgets(buffer, sizeof buffer, file);
		uint64_t block_count = numbers[x+1]/BLOCK_SIZE;
		uint64_t last_block = numbers[x+1]%BLOCK_SIZE;
		while (fgets(buffer, sizeof buffer, file) != NULL) {
			int64_t map[3] = {};
			if (buffer[0] == '\n') {
				continue;
			}
			if (isalpha(buffer[0])) {
				category++;
				for (int i = 0; i < nums; ++i) {
					check[i] = check[i + nums];
				}
				continue;
			}
			pch = buffer;
			for (size_t i = 0; i < 3; ++i) {
				map[i] = strtoll(pch, &pch, 10);
			}
			int64_t diff = map[0] - map[1];

			#pragma omp parallel for simd collapse(2)
			for (size_t i = 0; i < block_count-1; i++)
			{
				for (size_t j = 0; j < BLOCK_SIZE; j++)
				{
					insanity++;
					if (check[i*BLOCK_SIZE + j] >= map[1]
					&& check[i*BLOCK_SIZE + j] < map[1] + map[2]) {
					check[i*BLOCK_SIZE + j + nums] += diff;
					}
				}
				
			}
			#pragma omp for simd
			for (size_t i = 0; i < last_block; i++)
			{
				if (check[i] >= map[1]
					&& check[i] < map[1] + map[2]) {
					check[i + nums] += diff;
				}
			}
			
		}
		rewind(file);
		min = INT64_MAX;
		for (int i = 0; i < nums; ++i) {
			min = MIN(min, check[i + nums]);
		}
		min2 = MIN(min, min2);
		printf("%lld\n", min2);
		free(check);
	}
	printf("Insanity: %zu/n", insanity);
}