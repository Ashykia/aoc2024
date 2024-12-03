#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../common/file_utils.h"
#include "day1.h"

struct IntHashEntryStruct {
    int key;
    int value;
    struct IntHashEntryStruct* next;
};

typedef struct IntHashEntryStruct IntHashEntry;

typedef struct {
    size_t width;
    IntHashEntry** buckets;
} IntHashTable;

IntHashEntry* construct_IntHashEntry(int key, int value) {
    IntHashEntry* entry = malloc(sizeof(IntHashEntry));
    entry->key = key;
    entry->value = value;
    entry->next = NULL;
    return entry;
}

void destroy_IntHashEntry(IntHashEntry* entry) {
    IntHashEntry* next_entry = NULL;
    if (next_entry = entry->next) {
        destroy_IntHashEntry(next_entry);
    }
    free(entry);
}

IntHashTable* construct_IntHashTable(size_t width) {
    IntHashTable* hash_table = malloc(sizeof(IntHashTable));
    hash_table->buckets = malloc(sizeof(IntHashEntry*) * width);
    for (int bucket = 0; bucket < width; bucket++) {
        hash_table->buckets[bucket] = NULL;
    }
    hash_table->width = width;
    return hash_table;
}

void destroy_IntHashTable(IntHashTable* hash_table) {
    for (int bucket = 0; bucket < hash_table->width; bucket++) {
        IntHashEntry* entry = hash_table->buckets[bucket];
        if (entry) {
            destroy_IntHashEntry(entry);
        }
    }
    free(hash_table->buckets);
    free(hash_table);
}

int modulo_hash(int key, int width) {
    return key % width;
}

IntHashEntry** get_entry_IntHashTable(IntHashTable* hash_table, int key) {
    IntHashEntry** entry = &hash_table->buckets[modulo_hash(key, hash_table->width)];
    if (*entry) {
        do {
            if ((*entry)->key == key) {
                return entry;
            }
            entry = &(*entry)->next;
        } while (*entry);
    }
    return entry;
}

void put_IntHashTable(IntHashTable* hash_table, int key, int value) {
    IntHashEntry** entry = get_entry_IntHashTable(hash_table, key);
    if (*entry) {
        (*entry)->value = value;
        return;
    }
    *entry = construct_IntHashEntry(key, value);
}

int get_number_count(IntHashTable* hash_table, int key) {
    IntHashEntry* entry = *get_entry_IntHashTable(hash_table, key);
    if (entry) {
        return entry->value;
    }
    return 0;
}

int main(int argc, char** argv) {
    char* file_path = NULL;
    if (! (file_path = get_path_from_args(argc, argv))) {
        return 1;
    }
    FILE* input_file = fopen(file_path, "r");
    FileContents* file_contents = read_lines(input_file);
    fclose(input_file);
    struct InputData input = get_input(file_contents);
    wipe_pointer_array(file_contents->data, file_contents->length);
    destroy_FileContents(file_contents);

    IntHashTable* right_hand_number_count = construct_IntHashTable(256);
    int number = 0;

    for (int position = 0; position < input.right_hand_side->length; position++) {
        number = input.right_hand_side->data[position];
        IntHashEntry* entry = *get_entry_IntHashTable(right_hand_number_count, number);
        if (entry) {
            put_IntHashTable(right_hand_number_count, number, entry->value + 1);
            continue;
        }
        put_IntHashTable(right_hand_number_count, number, 1);
    }

    int accumulator = 0;
    for (int position = 0; position < input.left_hand_side->length; position++) {
        int number = input.left_hand_side->data[position];
        int count = get_number_count(
                right_hand_number_count,
                input.left_hand_side->data[position]);
        accumulator += number * count;
    }
    printf("%d\n", accumulator);
    destroy_IntHashTable(right_hand_number_count);
    free_input_data(&input);
}
