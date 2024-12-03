#include <stdio.h>
#include <stdlib.h>
#include "../common/dynamic_array.h"
#include "../common/file_utils.h"

DYNAMIC_ARRAY(int, IntArray)

int main(int argc, char** argv) {
    char* file_path = NULL;
    if (! (file_path = get_path_from_args(argc, argv))) {
        return 1;
    }
    FILE* input_file = fopen(file_path, "r");
    FileContents* input = read_lines(input_file);
    fclose(input_file);

    IntArray* first_numbers = construct_IntArray();
    IntArray* second_numbers = construct_IntArray();
    int first_number;
    int second_number;

    for (int position = 0; position < input->length; position++) {
        char* line = input->data[position];
        first_number = 0;
        second_number = 0;
        sscanf(line, "%d   %d\n", &first_number, &second_number);
        append_to_IntArray(first_numbers, first_number);
        append_to_IntArray(second_numbers, second_number);
    }

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

    qsort(first_numbers->data, first_numbers->length, sizeof(int), &compare_numbers);
    qsort(second_numbers->data, second_numbers->length, sizeof(int), &compare_numbers);
    int accumulator = 0;
    for (int position = 0; position < first_numbers->length; position++) {
        accumulator += abs(first_numbers->data[position] - second_numbers->data[position]);
    }
    printf("%d\n", accumulator);
    wipe_pointer_array(input->data, input->length);
    destroy_FileContents(input);
    destroy_IntArray(first_numbers);
    destroy_IntArray(second_numbers);
    return 0;
}
