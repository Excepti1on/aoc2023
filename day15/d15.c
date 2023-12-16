#include "d15.h"

#include <ctype.h>
#include <search.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static constexpr size_t hashes = 256;
static constexpr size_t arr_size = 64;

typedef struct LLNode {
    uint32_t name;
    uint32_t value;
} LLNode;

typedef struct LLHead {
    size_t top;
    struct LLNode nodes[arr_size];
} LLHead;

static void InsertArray(LLHead head[static 1], const LLNode node[static 1]);

static void DeleteArray(LLHead head[static 1], const LLNode node[static 1]);

static uint32_t SumArray(const LLHead map[static hashes]);

void Day15() {
    FILE *file = fopen("../day15/input.txt", "r");
    char buffer[32768];
    fgets(buffer, sizeof buffer, file);
    fclose(file);

    LLHead map[hashes];
    uint32_t sum = 0;

    char *p = strtok(buffer, ",");
    while (p) {
        uint32_t value = 0;
        size_t i = 0;
        while (p[i] != '\0') {
            value += p[i];
            value *= 17;
            value %= hashes;
            i++;
        }
        sum += value;

        value = 0;
        i = 0;
        while (isalpha(p[i])) {
            value += p[i];
            value *= 17;
            value %= hashes;
            i++;
        }
        uint32_t name = strtol(p, &p, 36);
        uint32_t num = p[1] - '0';

        if (!(num < 1 || num > 9)) {
            InsertArray(&map[value], &(struct LLNode){name, num});
        } else {
            DeleteArray(&map[value], &(struct LLNode){name, num});
        }
        p = strtok(NULL, "\n,");
    }
    printf("%d\n", sum);
    printf("Sum: %d\n", SumArray(map));
}

int nodecmp(const void *a, const void *b) { return !(((const LLNode *)a)->name == ((const LLNode *)b)->name); }

void InsertArray(LLHead head[static 1], const LLNode node[static 1]) {
    LLNode *found = lsearch(node, head->nodes, &(head->top), sizeof(LLNode), nodecmp);
    found->value = node->value;
}

void DeleteArray(LLHead head[static 1], const LLNode node[static 1]) {
    LLNode *found = lfind(node, head->nodes, &head->top, sizeof(LLNode), nodecmp);
    if (found) {
        size_t index = (found - head->nodes);
        memmove(&head->nodes[index], &head->nodes[index + 1], arr_size - index - 1);
        head->top--;
    }
}

uint32_t SumArray(const LLHead map[static hashes]) {
    uint32_t sum = 0;
    for (size_t i = 0; i < hashes; i++) {
        for (size_t j = 0; j < map[i].top; j++) {
            sum += (i + 1) * (j + 1) * map[i].nodes[j].value;
        }
    }
    return sum;
}