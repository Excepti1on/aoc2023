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
	int64_t min2 = INT64_MAX;
	for (int x = 0; x < SEED_COUNT; x += 2) {
		printf("%lld\t%lld\t%d\t", numbers[x], numbers[x + 1],x);
		int64_t nums = numbers[x + 1];
		int64_t *check = calloc(numbers[x + 1] * 8, sizeof(int64_t));
		for (int j = 0; j < numbers[x + 1]; ++j) {
			check[j] = numbers[x] + j;
		}
		category = 0;
		fgets(buffer, sizeof buffer, file);
		uint64_t it = 0;
		while (fgets(buffer, sizeof buffer, file) != NULL) {
			int64_t map[3] = {};
			if (buffer[0] == '\n') {
				continue;
			}
			if (isalpha(buffer[0])) {
				category++;
				for (int i = 0; i < numbers[x + 1]; ++i) {
					check[i + nums*category] = check[i+ nums*(category-1)];
				}
				continue;
			}
			pch = buffer;
			for (size_t i = 0; i < 3; ++i) {
				map[i] = strtoll(pch, &pch, 10);
			}
			int64_t diff = map[0] - map[1];
			it++;
			for (size_t i = 0; i < numbers[x + 1]; ++i) {
				if (check[i+ nums*(category-1)] >= map[1]
					&& check[i+ nums*(category-1)] < map[1] + map[2]) {
					check[i+ nums*(category)] += diff;
				}
			}
		}
		rewind(file);
		min = INT64_MAX;
		for (int i = 0; i < numbers[x + 1]; ++i) {
			min = MIN(min, check[i + 7*nums]);
		}
		min2 = MIN(min, min2);
		printf("%lld\n", min2);
		free(check);
	}
}