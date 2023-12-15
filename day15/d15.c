#include "d15.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct ListNode
{
    int value;
    char* name;
    struct ListNode *next;
}ListNode;

static int hash_count = 0;

void Insert(ListNode **head, int value, char* name){
    printf("Insert: %d %s %d\n", value, name, strlen(name));
    ListNode *node = (ListNode*)malloc(sizeof(ListNode));
    node->next = NULL;
    node->value = value;
    node->name = calloc(strlen(name)+1, sizeof(char));
    strncpy(node->name, name, strlen(name));
    ListNode *temp = *head;
    if(temp == NULL){
        *head = node;
        hash_count++;
        return;
    }
    if(strcmp(temp->name, name)==0){
        temp->value = value;
        free(node->name);
        free(node);
        return;
    }
    while (temp->next != NULL)
    {
        temp = temp->next;
        if(strcmp(temp->name, name)==0){
            temp->value = value;
            free(node->name);
            free(node);
            return;
        }
    }
    node->next = temp->next;
    temp->next = node;
    hash_count++;
}

void Delete(ListNode **head, char *name){
    printf("Delete: %s %d\n", name, strlen(name));
    if(*head == NULL){
        return;
    }
    ListNode *temp = *head;
    if(strcmp((*head)->name, name)==0){
        if((*head)->next == NULL){
            *head = NULL;
        }else{
            *head = (*head)->next;
        }
        free(temp->name);
        free(temp);
        hash_count--;
        return;
    }
    while (temp->next != NULL &&  strcmp(temp->next->name, name)!=0)
    {
        temp = temp->next;
    }
    if(temp->next == NULL){
        return;
    }
    ListNode *delete = temp->next;
    temp->next = temp->next->next;
    free(delete->name);
    free(delete);
    hash_count--;
}

void PrintArray(ListNode *hashmap[256]){
    for (size_t i = 0; i < 256; i++)
    {
        printf("%d", i);
        ListNode *temp = hashmap[i];
        while (temp != NULL)
        {
            printf("%s %d\t", temp->name, temp->value);
            temp = temp->next;
        }
        printf("\n");
    }
    
}

int SumMap(ListNode *hashmap[256]){
    int sum = 0;
    for (size_t i = 0; i < 256; i++)
    {
        ListNode *temp = hashmap[i];
        int index = 1;
        while (temp != NULL)
        {
            sum += (i+1) * index * temp->value;
            temp = temp->next;
            index++;
        }   
    }
    return sum;
}

void DeleteMap(ListNode *hashmap[256]){
    for (size_t i = 0; i < 256; i++)
    {
        ListNode* temp = hashmap[i];
        ListNode* delete = temp;
        while (temp!=NULL){
            temp = temp->next;
            free(delete->name);
            free(delete);
            delete = temp;
        }
    }
    
}

void Day15(){
    FILE *file = fopen("../day15/input.txt", "r");
    char buffer[32768] = {};
    int sum = 0;
    ListNode *hashmap[256] = {NULL};
    while (fgets(buffer, sizeof buffer, file)!=NULL)
    {
        char *end;
        char *p = strtok_r(buffer, ",",&end);
        while (p)
        {
            int value = 0;
            int len = strlen(p);
            for (size_t i = 0; i < len; i++)
            {
                value += p[i];
                value *= 17;
                value %= 256;
            }
            sum += value;
            char *end_token;
            char *name = strtok_r(p, "=-", &end_token);
            char *val = strtok_r(NULL, ",", &end_token);
            value = 0;
            len = strlen(name);
            for (size_t i = 0; i < len; i++)
            {
                value += name[i];
                value *= 17;
                value %= 256;
            }
            if(val){
                int num = strtol(val, NULL, 10);
                Insert(&(hashmap[value]), num, name);
            }else{
                Delete(&(hashmap[value]), name);
            }
            p = strtok_r(NULL, "\n,", &end);
        }
    }
    printf("%d\n", sum);
    printf("%d\n", SumMap(hashmap));
    DeleteMap(hashmap);
    printf("%d\n", hash_count);
}