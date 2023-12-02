//
// Created by oliver on 02.12.2023.
//

#include "d2.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define RED_CUBES 12
#define GREEN_CUBES 13
#define BLUE_CUBES 14

uint64_t D21() {
	FILE *file = fopen("../day2/input.txt", "r");
	uint64_t count = 0;
	uint64_t i = 1;
	char buffer[256] = {};
	while (fgets(buffer, sizeof buffer, file) != NULL) {
		char *p;
		uint64_t digit = 0;
		bool possible = true;
		for (p = strtok(buffer, " :,;\n"); p != NULL; p = strtok(NULL, " :,;\n")) {
			if (isdigit(p[0])) {
				digit = strtoull(p, NULL, 10);
			} else {
				switch (p[0]) {
					case 'r':
						if (digit > RED_CUBES) {
							possible = false;
						}
						break;
					case 'g':
						if (digit > GREEN_CUBES) {
							possible = false;
						}
						break;
					case 'b':
						if (digit > BLUE_CUBES) {
							possible = false;
						}
						break;
				}
			}
			if (!possible) {
				break;
			}
		}
		if (possible) {
			count += i + 1;
		}
		i++;
	}
	fclose(file);
	return count;
}

uint64_t D22() {
	FILE *file = fopen("../day2/input.txt", "r");
	uint64_t count = 0;
	char buffer[256] = {};
	while (fgets(buffer, sizeof buffer, file) != NULL) {
		char *p;
		uint64_t digit = 0;
		uint64_t red = 0;
		uint64_t blue = 0;
		uint64_t green = 0;
		for (p = strtok(buffer, " :,;\n"); p != NULL; p = strtok(NULL, " :,;\n")) {
			if (isdigit(p[0])) {
				digit = strtoull(p, NULL, 10);
			} else {
				switch (p[0]) {
					case 'r':
						if (digit > red) {
							red = digit;
						}
						break;
					case 'g':
						if (digit > green) {
							green = digit;
						}
						break;
					case 'b':
						if (digit > blue) {
							blue = digit;
						}
						break;
				}
			}
		}
		count += red * green * blue;
	}
	fclose(file);
	return count;
}