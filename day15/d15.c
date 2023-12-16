#include "d15.h"

#include <ctype.h>
#include <search.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static constexpr size_t hashes = 256;
static constexpr size_t arr_size = 64;

struct LLNode {
    uint32_t name;
    uint32_t value;
};

struct LLHead {
    size_t top;
    struct LLNode nodes[arr_size];
};

int NodeCmp(const void *a, const void *b);

static void Insert(struct LLHead head[static 1], const struct LLNode node[static 1]);

static void Delete(struct LLHead head[static 1], const struct LLNode node[static 1]);

static uint32_t Sum(const struct LLHead map[static hashes]);

void Day15() {
    FILE *file = fopen("../day15/input.txt", "r");
    char buffer[32768];
    fgets(buffer, sizeof buffer, file);
    fclose(file);

    struct LLHead map[hashes];
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
            Insert(&map[value], &(struct LLNode){name, num});
        } else {
            Delete(&map[value], &(struct LLNode){name, num});
        }
        p = strtok(NULL, "\n,");
    }
    printf("%d\n", sum);
    printf("Sum: %d\n", Sum(map));
}

int NodeCmp(const void *a, const void *b) {
    return !(((const struct LLNode *)a)->name == ((const struct LLNode *)b)->name);
}

void Insert(struct LLHead head[static 1], const struct LLNode node[static 1]) {
    ((struct LLNode *)lsearch(node, head->nodes, &(head->top), sizeof(struct LLNode), NodeCmp))
        ->value = node->value;
}

void Delete(struct LLHead head[static 1], const struct LLNode node[static 1]) {
    struct LLNode *found = lfind(node, head->nodes, &head->top, sizeof(struct LLNode), NodeCmp);
    if (found) {
        size_t index = found - head->nodes;
        memmove(&head->nodes[index], &head->nodes[index + 1], arr_size - index - 1);
        head->top--;
    }
}

uint32_t Sum(const struct LLHead map[static hashes]) {
    uint32_t sum = 0;
    for (size_t i = 0; i < hashes; i++) {
        for (size_t j = 0; j < map[i].top; j++) {
            sum += (i + 1) * (j + 1) * map[i].nodes[j].value;
        }
    }
    return sum;
}