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

uint32_t Evaluate(size_t n, uint32_t counts[static n], size_t index) {
	uint32_t sum = 1;
	for (size_t i = 0; i < counts[index]; ++i) {
		sum += Evaluate(n, counts, index + i + 1);
	}
	return sum;
}

void Day4() {
	FILE *file = fopen("../day4/input.txt", "r");

	char buffer[128] = {};
	uint32_t counts[CARD_COUNT] = {};
	uint32_t winning_cards[WINNING_CARDS] = {};
	uint32_t checking_cards[CHECK_CARDS] = {};
	size_t index = 0;
	while (fgets(buffer, sizeof buffer, file) != NULL) {
		strtok(buffer, ":");
		char *p = strtok(NULL, " ");
		for (size_t i = 0; i < WINNING_CARDS; ++i, p = strtok(NULL, " | ")) {
			winning_cards[i] = strtoul(p, NULL, 10);
		}
		for (size_t i = 0; i < CHECK_CARDS; ++i, p = strtok(NULL, " \n")) {
			checking_cards[i] = strtoul(p, NULL, 10);
		}
		counts[index] = 0;
		for (size_t i = 0; i < CHECK_CARDS; ++i) {
			for (size_t j = 0; j < WINNING_CARDS; ++j) {
				if (winning_cards[j] == checking_cards[i]) {
					counts[index]++;
				}
			}
		}
		index++;
	}
	fclose(file);
	uint32_t global_sum = 0;
	for (size_t i = 0; i < index; ++i) {
		global_sum += (counts[i] > 0) ? 1 << (counts[i] - 1) : 0;
	}
	printf("Points Part 1: %u\n", global_sum);

	global_sum = 0;
	for (size_t i = 0; i < index; ++i) {
		global_sum += Evaluate(index, counts, i);
	}
	printf("Cards Part 2: %u\n", global_sum);
}