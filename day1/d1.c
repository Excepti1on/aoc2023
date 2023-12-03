//
// Created by oliver on 01.12.2023.
//

#include "d1.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>

typedef enum Mode {
	FORWARD,
	BACKWARDS
} Mode;
/**
 * Return the Position of the first or last Digit in the Buffer.
 * @param mode check forwards or backwards
 * @param buffer_length buffer length
 * @param buffer the buffer to read from
 * @return the index of the digit.
 */
size_t CheckDigit(Mode mode, size_t buffer_length, const char buffer[static buffer_length]) {
	size_t index_digit;
	switch (mode) {
		case FORWARD:
			index_digit = 0;
			while (index_digit < buffer_length) {
				if (isdigit(buffer[index_digit])) {
					break;
				}
				index_digit++;
			}
			break;
		case BACKWARDS:
			index_digit = buffer_length;
			do {
				if (isdigit(buffer[index_digit])) {
					break;
				}
				index_digit--;
			} while (index_digit != 0);
			break;
	}
	return index_digit;
}

/**
 * Writes the first or last digit written as a word into number.
 * Requires
 * CheckDigit()
 * to be run first.
 * @param mode the mode of operation, can be FORWADS or BACKWARDS
 * @param index_digit the index returned by CheckDigit()
 * @param buffer_length the size of the buffer to read from
 * @param buffer the buffer to read from
 * @param number [out] the number to write to
 * @param alpha_numbers the digits 0-9 in alphabetical form.
 */
void CheckAlpha(Mode mode,
				size_t index_digit,
				size_t buffer_length,
				const char *buffer,
				char *number,
				const char alpha_numbers[10][6]) {
	size_t k;
	uint64_t index_alpha;
	switch (mode) {
		case FORWARD:
			index_alpha = ULLONG_MAX;
			for (k = 0; k < 10; ++k) {
				char *p = strstr(buffer, alpha_numbers[k]);
				if (!p) {
					continue;
				}
				if (p - buffer < index_digit) {
					if (p - buffer < index_alpha) {
						index_alpha = p - buffer;
						number[0] = (char) (k + 48);
					}
				}
			}
			return;
		case BACKWARDS:
			index_alpha = 0;
			k = buffer_length;
			bool set = false;
			do {
				for (size_t l = 0; l < 10; ++l) {
					char *p = strstr(buffer + k, alpha_numbers[l]);
					if (!p) {
						continue;
					}
					if (p - buffer > index_digit) {
						if (p - buffer > index_alpha) {
							index_alpha = p - buffer;
							number[1] = (char) (l + 48);
							set = true;
						}
					}
				}
				if (set) {
					break;
				}
				k--;
			} while (k != 0);
			return;
		default:
			return;
	}
}

uint64_t D11() {

	FILE *file = fopen("../day1/input.txt", "r");
	char buffer[64] = {};
	uint64_t result = 0;
	while (fgets(buffer, sizeof(buffer), file)) {
		char number[3] = {};
		size_t buffer_length = strlen(buffer);
		size_t index_digit = CheckDigit(FORWARD, buffer_length, buffer);
		number[0] = buffer[index_digit];
		index_digit = CheckDigit(BACKWARDS, buffer_length, buffer);
		number[1] = buffer[index_digit];
		result += strtoull(number, NULL, 10);
	}
	fclose(file);
	return result;
}

uint64_t D12() {
	FILE *file = fopen("../day1/input.txt", "r");
	uint64_t result = 0;
	char buffer[64] = {};
	char alpha_numbers[10][6] = {"zero", "one", "two", "three", "four", "five", "six",
								 "seven", "eight", "nine"};
	while (fgets(buffer, sizeof(buffer), file)) {
		char number[3] = {};
		size_t buffer_length = strlen(buffer);
		size_t index_digit = CheckDigit(FORWARD, buffer_length, buffer);
		number[0] = buffer[index_digit];
		CheckAlpha(FORWARD, index_digit, buffer_length, buffer, number, alpha_numbers);
		index_digit = CheckDigit(BACKWARDS, buffer_length, buffer);
		number[1] = buffer[index_digit];
		CheckAlpha(BACKWARDS, index_digit, buffer_length, buffer, number, alpha_numbers);
		result += strtoull(number, NULL, 10);
	}
	fclose(file);
	return result;
}

void Day1() {
	printf("%llu\n", D11());
	printf("%llu\n", D12());
}