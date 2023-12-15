#include "d15.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct ListNode {
    int value;
    int name;
    struct ListNode *next;
} ListNode;

static void Insert(ListNode **head, int value, int name);

static void Delete(ListNode **head, int name);

static int SumMap(ListNode *hashmap[static 256]);

static void DeleteMap(ListNode *hashmap[static 256]);

void Day15() {
    FILE *file = fopen("../day15/input.txt", "r");
    char buffer[32768] = {};
    int sum = 0;
    ListNode *hashmap[256] = {NULL};
    fgets(buffer, sizeof buffer, file);
    fclose(file);
    char *end;
    char *p = strtok(buffer, ",");
    while (p) {
        int value = 0;
        size_t i = 0;
        while (p[i] != '\0') {
            value += p[i];
            value *= 17;
            value %= 256;
            i++;
        }
        sum += value;

        char *val;
        int name = strtol(p, &val, 36);
        int num = val[1] - '0';
        value = 0;
        i = 0;
        while (isalpha(p[i])) {
            value += p[i];
            value *= 17;
            value %= 256;
            i++;
        }
        if (!(num < 1 || num > 9)) {
            Insert(&hashmap[value], num, name);
        } else {
            Delete(&hashmap[value], name);
        }
        p = strtok(NULL, "\n,");
    }
    printf("%d\n", sum);
    printf("%d\n", SumMap(hashmap));
    DeleteMap(hashmap);
}

void Insert(ListNode **head, int value, int name) {
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    node->next = NULL;
    node->value = value;
    node->name = name;
    register ListNode *temp = *head;
    if (temp == NULL) {
        *head = node;
        return;
    }
    if (temp->name == name) {
        temp->value = value;
        free(node);
        return;
    }
    while (temp->next != NULL) {
        temp = temp->next;
        if (temp->name == name) {
            temp->value = value;
            free(node);
            return;
        }
    }
    node->next = temp->next;
    temp->next = node;
}

void Delete(ListNode **head, int name) {
    if (*head == NULL) {
        return;
    }
    register ListNode *temp = *head;
    if ((*head)->name == name) {
        *head = (*head)->next;
        free(temp);
        return;
    }
    while (temp->next != NULL && temp->next->name != name) {
        temp = temp->next;
    }
    if (temp->next == NULL) {
        return;
    }
    ListNode *delete = temp->next;
    temp->next = temp->next->next;
    free(delete);
}

int SumMap(ListNode *hashmap[static 256]) {
    int sum = 0;
    for (size_t i = 0; i < 256; i++) {
        ListNode *temp = hashmap[i];
        int index = 1;
        while (temp != NULL) {
            sum += (i + 1) * index * temp->value;
            temp = temp->next;
            index++;
        }
    }
    return sum;
}

void DeleteMap(ListNode *hashmap[static 256]) {
    for (size_t i = 0; i < 256; i++) {
        ListNode *temp = hashmap[i];
        ListNode *delete = temp;
        while (temp != NULL) {
            temp = temp->next;
            free(delete);
            delete = temp;
        }
    }
}