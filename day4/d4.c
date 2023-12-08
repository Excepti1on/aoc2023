//
// Created by oliver on 04.12.2023.
//

#include "d4.h"

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#define WINNING_CARDS 10
#define CHECK_CARDS 25
#define CARD_COUNT 198

void Day4() {
	FILE *file = fopen("../day4/input.txt", "r");

	char buffer[128] = {};
	uint32_t scores[CARD_COUNT] = {};
	uint32_t counts[CARD_COUNT] = {};
	size_t index = 0;
	uint32_t global_sum;

	while (fgets(buffer, sizeof buffer, file) != NULL) {
		uint32_t winning_cards[WINNING_CARDS] = {};
		uint32_t checking_cards[CHECK_CARDS] = {};

		strtok(buffer, ":");
		char *p = strtok(NULL, "|");
		size_t i;
		for (i = 0, winning_cards[0] = strtoull(p, &p, 10); i < WINNING_CARDS - 1;
			 i++, winning_cards[i] = strtoull(p, &p, 10));
		p = strtok(NULL, "\n");
		for (i = 0, checking_cards[0] = strtoull(p, &p, 10); i < CHECK_CARDS - 1;
			 i++, checking_cards[i] = strtoull(p, &p, 10));
		for (size_t i = 0; i < CHECK_CARDS; ++i) {
			for (size_t j = 0; j < WINNING_CARDS; ++j) {
				scores[index] += (checking_cards[i] == winning_cards[j]);
			}
		}

		counts[index] = 1;
		index++;
	}

	fclose(file);

	global_sum = 0;
	for (size_t i = 0; i < index; ++i) {
		if (scores[i] != 0) {
			global_sum += 1 << (scores[i] - 1);
		}

	}
	printf("Points Part 1: %u\n", global_sum);

	global_sum = 0;
	for (size_t i = 0; i < index; ++i) {
		for (int j = 0; j < scores[i]; ++j) {
			counts[i + j + 1] += counts[i];
		}
		global_sum += counts[i];
	}
	printf("Cards Part 2: %u\n", global_sum);
}