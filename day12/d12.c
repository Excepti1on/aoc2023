//
// Created by oli on 12/12/23.
//

#include "d12.h"
#include "../hashmap/map.h"

#include <stdio.h>
#include <search.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

static hashmap *m;

static uint64_t Solve(int str_len, char str[static str_len], int key_len, char keys[static key_len]);

static uint64_t FoundHash(int str_len, char str[static str_len], int key_len, char keys[static key_len]);

static void FreeKeys(void *key, size_t ksize, uintptr_t value, void *usr) {
	free(key);
}

void Day12() {
	FILE *file = fopen("../day12/input.txt", "r");
	char buffer[256];
	uint64_t sum = 0;
	uint64_t sum2 = 0;
	m = hashmap_create();
	while (fgets(buffer, sizeof buffer, file) != NULL) {
		char *input = strtok(buffer, " ");
		char *keys = strtok(NULL, "/n");
		int str_len = (int) strlen(input);
		char *temp = keys;
		int key_len;
		for (key_len = 0; temp[key_len]; temp[key_len] == ',' ? key_len++ : *temp++);
		uint8_t keys_i[key_len] = {};
		keys_i[0] = (uint8_t) strtol(keys, &keys, 10);
		for (int i = 0; i < key_len; ++i) {
			keys_i[i + 1] = (char) strtol(keys + 1, &keys, 10);
		}
		key_len++;
		char keys2[key_len * 5];
		for (int i = 0; i < key_len * 5; ++i) {
			keys2[i] = keys_i[i % key_len];
		}
		char input2[str_len * 5 + 5];
		sprintf(input2, "%s?%s?%s?%s?%s", input, input, input, input, input);
		uint64_t count = Solve(str_len, input, key_len, keys_i);
		sum += count;
		str_len = strlen(input2);
		count = Solve(str_len, input2, key_len * 5, keys2);
		sum2 += count;

	}
	fclose(file);
	hashmap_iterate(m, FreeKeys, NULL);
	hashmap_free(m);
	printf("%lu\n", sum);
	printf("%lu\n", sum2);
}

uint64_t Solve(int str_len, char str[static str_len], int key_len, char keys[static key_len]) {
	// no more string left
	if (str_len == 0) {
		// no more keys so we are finished
		if (key_len == 0) {
			return 1;
			// we still have a key left, not a valid option
		} else {
			return 0;
		}
	}
	switch (str[0]) {
		//try the same keys at the next position
		case '.':
			return Solve(str_len - 1, str + 1, key_len, keys);
			// if we encounter a #, we check if we can fullfill the key
		case '#':
			return FoundHash(str_len, str, key_len, keys);
		case '?': {
			// try the number of options we get from assuming a . and a #
			char key[str_len+key_len+1];
			memcpy(key, str, str_len);
			memcpy(key + str_len, keys, key_len);
			uint64_t data;
			bool got = hashmap_get(m, key, str_len + key_len, &data);
			if (!got) {
				char *key2 = malloc(str_len + key_len+1);
				memcpy(key2, key, str_len+key_len+1);
				data = FoundHash(str_len, str, key_len, keys);
				hashmap_set(m, key2, str_len + key_len, data);
			}
			return Solve(str_len - 1, str + 1, key_len, keys) + data;
		}
	}
	return 0;
}
uint64_t FoundHash(int str_len, char str[static str_len], int key_len, char keys[static key_len]) {
	//no more keys left, no more options
	if (key_len == 0) {
		return 0;
	}
	//no more space left, no more options
	if (str_len < keys[0]) {
		return 0;
	}
	// no more space left, no more options
	for (int i = 0; i < keys[0]; ++i) {
		if (str[i] == '.') {
			return 0;
		}
	}
	// if there are n spaces left and we only have one key that has value n then we have one option, if we have
	// more then we have 0 options
	if (str_len == keys[0]) {
		if (key_len == 1) {
			return 1;
		}
		return 0;
	}
	//if the next character after n characters is a # we cant have options  for this character
	if (str[keys[0]] == '#') {
		return 0;
	}
	// Try the next key after keys[0] positions
	return Solve(str_len - keys[0] - 1, &str[keys[0] + 1], key_len - 1, &keys[1]);
}