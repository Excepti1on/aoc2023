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

typedef struct Card {
	uint64_t count;
	uint64_t winning_cards[WINNING_CARDS];
	uint64_t checking_cards[CHECK_CARDS];
} Card;

uint64_t Evaluate(Card **cards, size_t index) {
	uint64_t sum = 1;
	for (size_t i = 0; i < cards[index]->count; ++i) {
		sum += Evaluate(cards, index + i + 1);
	}
	return sum;
}

void Day4() {
	FILE *file = fopen("../day4/input.txt", "r");
	char buffer[128] = {};
	uint64_t global_sum = 0;
	Card **cards = malloc(CARD_COUNT * sizeof(Card *));
	size_t index = 0;
	while (fgets(buffer, sizeof buffer, file) != NULL) {
		strtok(buffer, ":");
		Card *card = malloc(sizeof(Card));
		char *p = strtok(NULL, " ");
		for (size_t i = 0; i < WINNING_CARDS; ++i, p = strtok(NULL, " | ")) {
			card->winning_cards[i] = strtoull(p, NULL, 10);
		}
		for (size_t i = 0; i < CHECK_CARDS; ++i, p = strtok(NULL, " | \n")) {
			card->checking_cards[i] = strtoull(p, NULL, 10);
		}
		card->count = 0;
		for (size_t i = 0; i < CHECK_CARDS; ++i) {
			for (size_t j = 0; j < WINNING_CARDS; ++j) {
				if (card->winning_cards[j] == card->checking_cards[i]) {
					card->count++;
				}
			}
		}
		cards[index] = card;
		index++;
	}
	fclose(file);
	for (size_t i = 0; i < CARD_COUNT; ++i) {
		global_sum += (cards[i]->count > 0) ? 1 << (cards[i]->count - 1) : 0;
	}
	printf("Points Part 1: %llu\n", global_sum);
	global_sum = 0;
	for (size_t i = 0; i < CARD_COUNT; ++i) {
		global_sum += Evaluate(cards, i);
		free(cards[i]);
	}
	free(cards);
	printf("Cards Part 2: %llu\n", global_sum);
}