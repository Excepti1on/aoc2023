#include "d8.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct direction {
	uint64_t left_n;
	uint64_t right_n;
	uint64_t name_n;
	char last_name;
} Direction;

uint64_t Gcd(uint64_t a, uint64_t b) {
	if (b == 0) {
		return a;
	}
	return Gcd(b, a % b);
}

uint64_t Lcm(uint64_t a, uint64_t b) {
	return (a / Gcd(a, b)) * b;
}

void Day8() {
	FILE *file = fopen("../day8/input.txt", "r");
	const size_t kLines = 716;
	Direction **directions = malloc(sizeof(Direction *) * (kLines - 2));
	rewind(file);
	char instructions[512] = {};
	fgets(instructions, sizeof instructions, file);
	size_t instruction_count = strlen(instructions) - 1;
	char buffer[32];
	fgets(buffer, sizeof buffer, file);
	size_t index = 0;
	char temp[4] = {};
	while (fgets(buffer, sizeof buffer, file) != NULL) {
		directions[index] = malloc(sizeof(Direction));
		strncpy(temp, buffer, 3);
		directions[index]->last_name = temp[2];
		directions[index]->name_n = strtoull(temp, NULL, 36);
		strncpy(temp, buffer + 7, 3);
		directions[index]->left_n = strtoull(temp, NULL, 36);
		strncpy(temp, buffer + 12, 3);
		directions[index]->right_n = strtoull(temp, NULL, 36);
		index++;
	}
	fclose(file);

	uint64_t *lookup = calloc(46655, sizeof(uint64_t));
	for (size_t i = 0; i < index; i++) {
		lookup[directions[i]->name_n] = i;
	}

	Direction *current = directions[0];
	uint64_t aaa = strtoull("AAA", NULL, 36);
	for (size_t i = 0; i < index; i++) {
		if (directions[i]->name_n == aaa) {
			current = directions[i];
			break;
		}
	}
	size_t instruction_index = 0;
	uint64_t count = 0;
	uint64_t zzz = strtoull("ZZZ", NULL, 36);
	while (current->name_n != zzz) {
		count++;
		switch (instructions[instruction_index]) {
			case 'L':
				current = directions[lookup[current->left_n]];
				instruction_index = (instruction_index + 1) % instruction_count;
				break;
			case 'R':
				current = directions[lookup[current->right_n]];
				instruction_index = (instruction_index + 1) % instruction_count;
				break;
		}
	}
	printf("%lu\n", count);

	size_t a_count = 0;
	for (size_t i = 0; i < index; i++) {
		if (directions[i]->last_name == 'A') {
			a_count++;
		}
	}
	Direction **part_two = malloc(sizeof(Direction *) * a_count);
	size_t a_index = 0;
	for (size_t i = 0; i < index; i++) {
		if (directions[i]->last_name == 'A') {
			part_two[a_index] = directions[i];
			a_index++;
		}
	}
	uint64_t all_steps[a_count];
	for (size_t j = 0; j < a_count; j++) {
		instruction_index = 0;
		int steps = 0;
		while (part_two[j]->last_name != 'Z') {
			steps++;
			switch (instructions[instruction_index]) {
				case 'L':
					part_two[j] = directions[lookup[part_two[j]->left_n]];
					instruction_index = (instruction_index + 1) % instruction_count;
					break;
				case 'R':
					part_two[j] = directions[lookup[part_two[j]->right_n]];
					instruction_index = (instruction_index + 1) % instruction_count;
					break;
			}
		}
		all_steps[j] = steps;
	}
	for (size_t i = 0; i < index; i++) {
		free(directions[i]);
	}
	free(lookup);
	free(directions);
	free(part_two);
	uint64_t result = 1;
	for (size_t i = 0; i < a_count; i++) {
		result = Lcm(result, all_steps[i]);
	}
	printf("%lu\n", result);
}