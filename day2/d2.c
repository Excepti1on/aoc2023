//
// Created by oliver on 02.12.2023.
//

#include "d2.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define RED_CUBES 12
#define GREEN_CUBES 13
#define BLUE_CUBES 14

#define MAX(a, b) ((a) < (b) ? (b) : (a))

size_t GetLineCount(FILE *file) {
	char ch;
	size_t lines = 1;
	while (!feof(file)) {
		ch = (char)fgetc(file);
		if (ch == '\n') {
			lines++;
		}
	}
	rewind(file);
	return lines;
}

uint64_t D21() {
	FILE *file = fopen("../day2/input.txt", "r");
	size_t lines = GetLineCount(file);
	uint64_t count = 0;
	char buffer[256] = {};
	for (size_t i = 0; i < lines; ++i) {
		fgets(buffer, sizeof(buffer), file);
		char *p;
		char **draws = malloc(sizeof(char *) * 50);
		strtok(buffer, ":");
		bool failure = false;
		size_t j = 0;
		draws[j] = strtok(NULL, ";");
		while (draws[j] != NULL) {
			j++;
			draws[j] = strtok(NULL, ";");
		}
		for (size_t k = 0; k < j; ++k) {
			uint64_t blue = 0;
			uint64_t red = 0;
			uint64_t green = 0;
			p = strtok(draws[k], ",");
			while (p != NULL) {
				if (strstr(p, "blue")) {
					blue += strtoull(p, NULL, 10);
				} else if (strstr(p, "green")) {
					green += strtoull(p, NULL, 10);
				} else if (strstr(p, "red")) {
					red += strtoull(p, NULL, 10);
				}
				p = strtok(NULL, ",");
			}
			if (blue > BLUE_CUBES || red > RED_CUBES || green > GREEN_CUBES) {
				failure = true;
				break;
			}
		}
		free(draws);
		if (!failure) {
			count += i + 1;
		}
	}
	fclose(file);
	return count;
}

uint64_t D22() {
	FILE *file = fopen("../day2/input.txt", "r");
	size_t lines = GetLineCount(file);
	uint64_t count = 0;
	char buffer[256] = {};
	for (size_t i = 0; i < lines; ++i) {
		fgets(buffer, sizeof(buffer), file);
		char *p;
		char **draws = malloc(sizeof(char *) * 50);
		strtok(buffer, ":");
		size_t j = 0;
		draws[j] = strtok(nullptr, ";");
		while (draws[j] != NULL) {
			j++;
			draws[j] = strtok(NULL, ";");
		}
		uint64_t blue = 0;
		uint64_t red = 0;
		uint64_t green = 0;
		for (size_t k = 0; k < j; ++k) {
			p = strtok(draws[k], ",");
			while (p != NULL) {
				if (strstr(p, "blue")) {
					blue = MAX(blue, strtoull(p, NULL, 10));
				} else if (strstr(p, "green")) {
					green = MAX(green, strtoull(p, NULL, 10));
				} else if (strstr(p, "red")) {
					red = MAX(red, strtoull(p, NULL, 10));
				}
				p = strtok(NULL, ",");
			}
		}
		free(draws);
		count += blue * red * green;
	}
	fclose(file);
	return count;
}