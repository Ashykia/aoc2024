#include <stdio.h>
#include <stdlib.h>
#include "day1.h"
#include "../common/dynamic_array.h"
#include "../common/file_utils.h"

DYNAMIC_ARRAY_IMPL(int, IntArray)

int compare_numbers(const void* pointer1, const void* pointer2) {
    int* number1 = (int*) pointer1;
    int* number2 = (int*) pointer2;
    if (*number1 < *number2) {
        return -1;
    }
    if (*number1 == *number2) {
        return 0;
    }
    return 1;
}

struct InputData get_input(FileContents* file_contents) {
    struct InputData input;
    input.left_hand_side = construct_IntArray();
    input.right_hand_side = construct_IntArray();
    int first_number = 0;
    int second_number = 0;
    char* line = NULL;

    for (int position = 0; position < file_contents->length; position++) {
        line = file_contents->data[position];
        sscanf(line, "%d   %d\n", &first_number, &second_number);
        append_to_IntArray(input.left_hand_side, first_number);
        append_to_IntArray(input.right_hand_side, second_number);
    }
    return input;
}

void sort_input(struct InputData* input) {
    qsort(
        input->left_hand_side->data,
        input->left_hand_side->length,
        sizeof(int),
        &compare_numbers);
    qsort(
        input->right_hand_side->data,
        input->right_hand_side->length,
        sizeof(int),
        &compare_numbers);
}

void free_input_data(struct InputData* input) {
    destroy_IntArray(input->left_hand_side);
    destroy_IntArray(input->right_hand_side);
}
