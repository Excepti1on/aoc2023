#include "d7.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX(a, b) (((a)>(b))?(a):(b))

typedef struct CardGame {
	char hand[6];
	uint64_t bid;
	uint64_t rank;
} CardGame;

typedef enum HandValues {
	HIGH_CARD,
	ONE_PAIR,
	TWO_PAIRS,
	THREE,
	FULL_HOUSE,
	FOUR,
	FIVE,
} HandValues;

static bool part2 = false;

static int64_t CardValue(CardGame *card, size_t n);
static int32_t CompareFunction(const void *p1, const void *p2);
static void HandValue(CardGame *card);

void Day7() {
	//Input parsing
	FILE *file = fopen("../day7/input.txt", "r");
	char buffer[32];
	char ch;
	size_t lines = 1;
	while (!feof(file)) {
		ch = (char) fgetc(file);
		if (ch == '\n') {
			lines++;
		}
	}
	rewind(file);
	CardGame **game = malloc(sizeof(CardGame *) * lines);
	for (size_t i = 0; i < lines; i++) {
		if (fgets(buffer, sizeof buffer, file) == NULL) {
			break;
		}
		char *pch = strtok(buffer, " ");
		game[i] = malloc(sizeof(CardGame));
		strcpy(game[i]->hand, pch);
		pch = strtok(NULL, " \n");
		game[i]->bid = strtoull(pch, NULL, 10);
		//belongs to part 1
		HandValue(game[i]);
	}
	fclose(file);
	//part 1:
	qsort(game, lines, sizeof(CardGame *), CompareFunction);

	uint64_t result = 0;
	for (size_t i = 0; i < lines; i++) {
		result += game[i]->bid * (i + 1);
	}
	printf("Result Part one: %lu\n", result);

	//part 2:
	part2 = true;
	for (size_t i = 0; i < lines; i++) {
		HandValue(game[i]);
	}
	qsort(game, lines, sizeof(CardGame *), CompareFunction);
	result = 0;
	for (size_t i = 0; i < lines; i++) {
		result += game[i]->bid * (i + 1);
		free(game[i]);
	}
	free(game);
	printf("Result Part two: %lu\n", result);
}

void HandValue(CardGame *card) {
	char cards[13] = {};
	uint64_t value = 0;
	uint64_t jokers = 0;
	size_t len = strlen(card->hand);
	for (size_t i = 0; i < len; i++) {
		if (isdigit(card->hand[i])) {
			cards[(card->hand[i] - '0' - 2)]++;
		} else if (isalpha(card->hand[i])) {
			switch (card->hand[i]) {
				case 'T':
					cards[8]++;
					break;
				case 'J':
					if (part2) {
						jokers++;
						break;
					}
					cards[9]++;
					break;
				case 'Q':
					if (part2) {
						cards[9]++;
						break;
					}
					cards[10]++;
					break;
				case 'K':
					if (part2) {
						cards[10]++;
						break;
					}
					cards[11]++;
					break;
				case 'A':
					if (part2) {
						cards[11]++;
						break;
					}
					cards[12]++;
					break;
				default:
					break;
			}
		}
	}
	if (!part2) {
		for (size_t i = 0; i < 13; i++) {
			if (cards[i] == 5) {
				value = MAX(value, FIVE);
			} else if (cards[i] == 4) {
				value = MAX(value, FOUR);
			} else if (cards[i] == 3) {
				for (size_t j = 0; j < 13; j++) {
					if (cards[j] == 2 && i != j) {
						value = MAX(value, FULL_HOUSE);
					}
				}
				value = MAX(value, THREE);
			} else if (cards[i] == 2) {
				for (size_t j = 0; j < 13; j++) {
					if (cards[j] == 3 && i != j) {
						value = MAX(value, FULL_HOUSE);
					}
					if (cards[j] == 2 && i != j) {
						value = MAX(value, TWO_PAIRS);
					}
				}
				value = MAX(value, ONE_PAIR);
			} else {
				value = MAX(value, HIGH_CARD);
			}
		}
	} else {
		for (size_t i = 0; i < 12; i++) {
			if (cards[i] == 5 - jokers) {
				value = MAX(value, FIVE);
			} else if (cards[i] == 4 - jokers) {
				value = MAX(value, FOUR);
			} else if (cards[i] == 3 - jokers) {
				for (size_t j = 0; j < 12; j++) {
					if (cards[j] == 2 && i != j) {
						value = MAX(value, FULL_HOUSE);
					}
				}
				value = MAX(value, THREE);
			} else if (cards[i] == 2 - jokers) {
				for (size_t j = 0; j < 12; j++) {
					if (cards[j] == 3 - jokers && cards[i] == 2 && i != j) {
						value = MAX(value, FULL_HOUSE);
					}
					if (cards[j] == 2 && i != j) {
						value = MAX(value, TWO_PAIRS);
					}
				}
				value = MAX(value, ONE_PAIR);
			} else {
				value = MAX(value, HIGH_CARD);
			}
		}
	}
	card->rank = value;
}

int32_t CompareFunction(const void *p1, const void *p2) {
	CardGame *c1 = *(CardGame **) p1;
	CardGame *c2 = *(CardGame **) p2;
	if (c1->rank > c2->rank) {
		return 1;
	} else if (c1->rank < c2->rank) {
		return -1;
	} else if (c1->rank == c2->rank) {
		for (size_t i = 0; i < 5; i++) {
			if (CardValue(c1, i) == CardValue(c2, i)) {
				continue;
			} else if (CardValue(c1, i) < CardValue(c2, i)) {
				return -1;
			} else if (CardValue(c1, i) > CardValue(c2, i)) {
				return 1;
			}
		}
	}
	return 0;
}

int64_t CardValue(CardGame *card, size_t n) {
	if (isdigit(card->hand[n])) {
		if (part2) {
			return card->hand[n] - '0' - 1;
		}
		return card->hand[n] - '0' - 2;
	} else {
		switch (card->hand[n]) {
			case 'T':
				if (part2) {
					return 9;
				}
				return 8;
			case 'J':
				if (part2) {
					return 0;
				}
				return 9;
			case 'Q':
				return 10;
			case 'K':
				return 11;
			case 'A':
				return 12;
			default:
				break;
		}
	}
	return -1;
}