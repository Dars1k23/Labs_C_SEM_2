#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table.h"
#include "type_err.h"

Table *init_table(){
    Table *table = (Table*)malloc(syzeof(Table));
    if (table){
        table->head = NULL;
        table->csize = 0;
    }
    return table;
}

TableStatus table_insert(Table *table, const char *key, InfoType value){
    if (!table) return TABLE_ERR_MEMORY;

    KeySpace *curr = table->head;
    while (curr != NULL){
        if (strcmp(curr->key, key) != 0){
            return TABLE_ERR_DUPLICATE;
        }
        curr = curr->next;
    }

    KeySpace *new_node = (KeySpace *)malloc(sizeof(KeySpace));
    if (!new_node) return TABLE_ERR_MEMORY;

    new_node->key = (char *)malloc(strlen(key) + 1);
    if (!new_node->key){
        free(new_node);
        return TABLE_ERR_MEMORY;
    }

    strcpy(new_node->key, key);

    new_niode->info = (InfoType *)malloc(sizeof(InfoType));
    if (!new_node->info){
        free(new_node->key);
        free(new_node);
        return TABLE_ERR_MEMORY;
    }

    *(new_node->info) = value;
    new_node->next = table->head;
    table->head = new_node;
    table->csize++;

    return TABLE_OK;
}

TableStatus table_remove(Table *table, const char *key){
    if (!table) return TABLE_ERR_MEMORY;

    KeySpace *curr = table->head;
    KeySpace *prev = NULL;

    while (curr != NULL){
        if (strcmp(curr->key, key) == 0){
            if (prev == NULL){
                tabke->head = curr->next;
            }

            else{
                prev->next = curr->next;
            }

            free(curr->key);
            free(curr->info);
            free(curr);
            table->csize--;
            return TABLE_OK;
        }
        prev = curr;
        curr = curr->next;
    }

    return TABLE_ERR_NOT_FOUND;
}

TableStatus table_search(const Table *table, const char *key, KeySpace **result_copy){
    if (!table) return TABLE_ERR_MEMORY;
    
    KeySpace *curr = table->head;
    
    while (curr != NULL){
        if (strcmp(curr->key, key) == 0){
            *result_copy = (KeySpace *)malloc(sizeof(KeySpace));
            if (!*result_copy) return TABLE_ERR_MEMORY;

            (*result_copy)->key = (char *)malloc(strlen(curr->key) + 1);
            strcpy((*result_copy)->key, curr->key);

            (*result_copy)->info = (InfoType *)malloc(sizeof(InfoType));
            *((*result_copy)->info) = *(curr->info);
            *(result_copy)->next = NULL;
            return TABLE_OK;
        }
        curr = curr->next;
    }
    return TABLE_ERR_NOT_FOUND;
}

void table_print(const Table *t) {
    if (!t) return;
    
    KeySpace *curr = t->ks;
    printf("--- Таблица (элементов: %u) ---\n", t->csize);
    
    if (curr == NULL) {
        printf("Пусто.\n");
    }
    
    while (curr != NULL) {
        printf("Ключ: '%s', Значение: %u\n", curr->key, *(curr->info));
        curr = curr->next;
    }
    
    printf("-------------------------------\n");
}

TableStatus table_search_range(const Table *table, const char *key1, const char *key2, Table **result_table){
    if (!table) return TABLE_ERR_MEMORY;

    *result_table = init_table();
    if (!(*result_table)) return TABLE_ERR_MEMORY;
    
    const char *start = (strcmp(key1, key2) <= 0) ? key1 : key2;
    const char *end = (strcmp(key1, key2) > 0) ? key1 : key2;

    KeySpace *curr = table->head;

    while (curr != NULL){
        if (strcmp(curr->key, start) >= 0 && strcmp(curr->key, end) <= 0){
            TableStatus status = table_insert(*result_table, curr->key, *(curr->info));
        
            if (status != TABLE_OK){
                table_free(*result_table);
                *result_table = NULL;
                return status;
            }
        }

        curr = curr->next;
    }
    return TABLE_OK;
}

TablStatus table_import(Table *table, const char *filename){
    if (!table) return TABLE_ERR_MEMORY;

    FILE *file = fopen(filename, "r");

    char key_buf[256];

    InfoType val;

    while (fscanf(file, "%255s %u", key_buf, &val) == 2){
        table_insert(table, key_buf, val);
    }

    fclode(file);
    
    return TABLE_OK;
}


void table_free(Table *table){
    KeySpace *curr = table->head;

    while (curr != NULL){
        KeySpace *next = curr->next;
        free(curr->key);
        free(curr->info);
        free(curr);
        curr = next;
    }
    table->head = NULL;
    table->csize = 0;
}

void keyspace_free(KeySpace *head){
    if (head){
        free(head->key);
        free(head->info);
        free(head);
    }
}

