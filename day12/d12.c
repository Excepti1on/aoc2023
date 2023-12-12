//
// Created by oli on 12/12/23.
//

#include "d12.h"

#include <stdio.h>
#include <search.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

static uint64_t Solve(int str_len, char str[static str_len], int key_len, int keys[static key_len]);

static uint64_t FoundHash(int str_len, char str[static str_len], int key_len, int keys[static key_len]);

void Day12() {
	FILE *file = fopen("../day12/input.txt", "r");
	char buffer[256];
	uint64_t sum = 0;
	uint64_t sum2 = 0;
	while (fgets(buffer, sizeof buffer, file) != NULL) {
		char *input = strtok(buffer, " ");
		char *keys = strtok(NULL, "/n");
		int str_len = (int) strlen(input);
		char *temp = keys;
		int key_len;
		for (key_len = 0; temp[key_len]; temp[key_len] == ',' ? key_len++ : *temp++);
		int keys_i[key_len];
		keys_i[0] = (int) strtol(keys, &keys, 10);
		for (int i = 0; i < key_len; ++i) {
			keys_i[i + 1] = (int) strtol(keys + 1, &keys, 10);
		}
		key_len++;
		int keys2[key_len * 5] = {};
		for (int i = 0; i < key_len * 5; ++i) {
			keys2[i] = keys_i[i % key_len];
		}
		char input2[str_len * 5 + 5];
		sprintf(input2, "%s?%s?%s?%s?%s", input, input, input, input, input);
		hcreate(UINT_MAX>>11);
		uint64_t count = Solve(str_len, input, key_len, keys_i);
		sum += count;
		str_len = strlen(input2);
		count = Solve(str_len, input2, key_len * 5, keys2);
		hdestroy();
		sum2 += count;

	}
	printf("%lu\n", sum);
	printf("%lu\n", sum2);
}

uint64_t Solve(int str_len, char str[static str_len], int key_len, int keys[static key_len]) {
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
			ENTRY item;
//			char key[512] = {};
			char *key = malloc(sizeof(char)*(str_len+key_len*4 + 1));
			char *where = key;
			size_t printed = sprintf(where, "%s", str);
			where+=printed;
			for (int i = 0; i < key_len; ++i) {
				printed = sprintf(where, "%d,",keys[i]);
				where+=printed;
			}
			uint64_t data = FoundHash(str_len, str, key_len, keys);
			item.data = (void *) data;
			item.key = key;
			hsearch(item, ENTER);
			return Solve(str_len - 1, str + 1, key_len, keys) + data;
		}
	}
	return 0;
}
uint64_t FoundHash(int str_len, char str[static str_len], int key_len, int keys[static key_len]) {
	//no more keys left, no more options
	ENTRY *found;
	ENTRY item;
//	char *key = malloc(sizeof(char)*(str_len+key_len*4 + 1));
	char key[512] = {};
	char *where = key;
	size_t printed = sprintf(where, "%s", str);
	where+=printed;
	for (int i = 0; i < key_len; ++i) {
		printed = sprintf(where, "%d,",keys[i]);
		where += printed;
	}
	item.key = key;
	found = hsearch(item, FIND);
	if(found != NULL){
//		free(found->key);
		return (uint64_t)found->data;
	}
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
