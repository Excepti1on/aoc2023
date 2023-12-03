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

void Day2() {
	FILE *file = fopen("../day2/input.txt", "r");
	uint64_t count = 0;
	uint64_t sum = 0;
	uint64_t i = 1;
	char buffer[256] = {};
	while (fgets(buffer, sizeof buffer, file) != NULL) {
		char *p;
		uint64_t digit = 0;
		uint64_t red = 0;
		uint64_t blue = 0;
		uint64_t green = 0;
		bool possible = true;
		for (p = strtok(buffer, " :,;\n"); p != NULL; p = strtok(NULL, " :,;\n")) {
			if (isdigit(*p)) {
				digit = strtoull(p, NULL, 10);
			} else {
				switch (*p) {
					case 'r':
						possible &= digit <= RED_CUBES;
						red = (digit > red) ? digit : red;
						break;
					case 'g':
						possible &= digit <= GREEN_CUBES;
						green = (digit > green) ? digit : green;
						break;
					case 'b':
						possible &= digit <= BLUE_CUBES;
						blue = (digit > blue) ? digit : blue;
						break;
				}
			}
		}
		count += i * possible;
		sum += red * green * blue;
		i++;
	}
	fclose(file);
	printf("%llu\n", count);
	printf("%llu\n", sum);
}