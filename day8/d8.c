#include "d8.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct direction
{
	u_int64_t leftN;
	u_int64_t rightN;
	u_int64_t nameN;
	char lastName
} direction;

u_int64_t gcd(u_int64_t a, u_int64_t b)
{
	if (b == 0)
	{
		return a;
	}
	return gcd(b, a % b);
}

u_int64_t lcm(u_int64_t a, u_int64_t b) { return (a / gcd(a, b)) * b; }

int cmp(const void *p1, const void *p2)
{
	direction *c1 = *(direction **)p1;
	direction *c2 = *(direction **)p2;
	return (c1->nameN - c2->nameN);
}

void Day8()
{
	FILE *file = fopen("../day8/input.txt", "r");
	char ch;
	size_t lines = 1;
	while (!feof(file))
	{
		ch = fgetc(file);
		if (ch == '\n')
		{
			lines++;
		}
	}
	direction **directions = malloc(sizeof(direction *) * (lines - 2));
	rewind(file);
	char instructions[512] = {};
	fgets(instructions, sizeof instructions, file);
	size_t instructionCount = strlen(instructions) - 1;
	char buffer[32];
	fgets(buffer, sizeof buffer, file);
	size_t index = 0;
	char temp[4] = {};
	while (fgets(buffer, sizeof buffer, file) != NULL)
	{
		directions[index] = malloc(sizeof(direction));
		strncpy(temp, buffer, 3);
		directions[index]->lastName = temp[2];
		directions[index]->nameN = strtoull(temp, NULL, 36);
		strncpy(temp, buffer + 7, 3);
		directions[index]->leftN = strtoull(temp, NULL, 36);
		strncpy(temp, buffer + 12, 3);
		directions[index]->rightN = strtoull(temp, NULL, 36);
		index++;
	}
	fclose(file);
	qsort(directions, lines - 2, sizeof(direction *), cmp);
	direction *current;
	u_int64_t aaa = strtoull("AAA", NULL, 36);
	for (size_t i = 0; i < index; i++)
	{
		if (directions[i]->nameN == aaa)
		{
			current = directions[i];
			break;
		}
	}
	size_t instructionIndex = 0;
	__uint64_t count = 0;
	u_int64_t zzz = strtoull("ZZZ", NULL, 36);
	while (current->nameN != zzz)
	{
		count++;
		size_t i = 0;
		switch (instructions[instructionIndex])
		{
		case 'L':
			while (current->leftN != directions[i]->nameN)
			{
				++i;
			}
			current = directions[i];
			instructionIndex = (instructionIndex + 1) % instructionCount;
			break;
		case 'R':

			while (current->rightN != directions[i]->nameN)
			{
				++i;
			}
			current = directions[i];
			instructionIndex = (instructionIndex + 1) % instructionCount;
			break;
		}
	}
	printf("%llu\n", count);

	size_t a_count = 0;
	for (size_t i = 0; i < index; i++)
	{
		if (directions[i]->lastName == 'A')
		{
			a_count++;
		}
	}
	direction **part_two = malloc(sizeof(direction *) * a_count);
	size_t a_index = 0;
	for (size_t i = 0; i < index; i++)
	{
		if (directions[i]->lastName == 'A')
		{
			part_two[a_index] = directions[i];
			a_index++;
		}
	}
	instructionIndex = 0;
	int is_z = 0;
	int check[a_count] = {};
	u_int64_t all_steps[a_count];
#pragma omp parallel for simd
	for (size_t j = 0; j < a_count; j++)
	{
		instructionIndex = 0;
		int steps = 0;
		while (part_two[j]->lastName != 'Z')
		{
			steps++;
			int found = 0;
			size_t i = 0;
			switch (instructions[instructionIndex])
			{
			case 'L':
			i = (part_two[j]->rightN - 13330) >> 13;
				while (part_two[j]->leftN != directions[i]->nameN)
				{
					++i;
				}
				part_two[j] = directions[i];
				instructionIndex = (instructionIndex + 1) % instructionCount;
				break;
			case 'R':
			i = (part_two[j]->rightN - 13330) >> 10;
				while (part_two[j]->rightN != directions[i]->nameN)
				{
					++i;
				}
				part_two[j] = directions[i];
				instructionIndex = (instructionIndex + 1) % instructionCount;
				break;
			}
		}
		all_steps[j] = steps;
	}
	for (size_t i = 0; i < index; i++)
	{
		free(directions[i]);
	}
	free(directions);
	free(part_two);
	u_int64_t result = 1;
	for (size_t i = 0; i < a_count; i++)
	{
		result = lcm(result, all_steps[i]);
	}
	printf("%llu\n", result);
}