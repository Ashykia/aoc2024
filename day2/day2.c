#include <string.h>
#include <stdio.h>
#include <math.h>
#include "../common/int_utils.h"

short check_values(IntArray* values, short (*compare)(int*, int*)) {
    if (values->length < 1) {
        printf("Array too small\n");
        return -1;
    }
    int safe_val = 0;
    int safe_counter = 0;
    int current = 0;
    int next = values->data[0];
    
    for (int position = 1; position < values->length; position++) {
        safe_val++;
        current = next;
        next = values->data[position];
        safe_counter += compare(&current, &next);
    }
    if (abs(safe_counter) < safe_val) {
        return 0;
    }
    return 1;
}

int num_safe(FILE* input_file, int allowed_problems, short (*compare)(int*, int*)) {
    char* line = NULL;
    char* token = NULL;
    size_t buffer_length = 0;
    size_t line_length = 0;
    int safe_lines = 0;
    short safe_val;
    short safe_counter;
    IntArray* numbers;
    IntArray* subset;
    const char* delim = " \n";
    while ((line_length = getline(&line, &buffer_length, input_file)) != -1) {
        int tmp = 0;
        numbers = construct_IntArray();
        safe_val = 0;
        safe_counter = 0;
        subset = NULL;
        if (token = strtok(line, delim)) {
            sscanf(token, "%d", &tmp);
            append_to_IntArray(numbers, tmp);
        }
        while (token = strtok(NULL, delim)) {
            sscanf(token, "%d", &tmp);
            append_to_IntArray(numbers, tmp);
        }
        if (check_values(numbers, compare)) {
            safe_lines++;
        } else if (allowed_problems) {
            for (int removed_value = 0; removed_value < numbers->length; removed_value++) {
                subset = construct_IntArray();
                for (int position = 0; position < numbers->length; position++) {
                    if (position != removed_value) {
                        append_to_IntArray(subset, numbers->data[position]);
                    }
                }
                if (check_values(subset, compare)) {
                    safe_lines++;
                    break;
                }
                destroy_IntArray(subset);
                subset = NULL;
            }
            if (subset) {
                destroy_IntArray(subset);
            }
        }
        destroy_IntArray(numbers);
        numbers = NULL;
    }
    free(line);
    return safe_lines;
}

short is_safe(int* num1, int* num2) {
    return compare_numbers(num1, num2) * (abs(*num1 - *num2) <= 3 && abs(*num1 - *num2) > 0);
}
