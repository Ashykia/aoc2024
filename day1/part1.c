#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    int length;
    char** data;
} FileContents;

void destroy_FileContents(FileContents* file_contents) {
    for (int position = 0; position < file_contents->length; position++) {
        free(file_contents->data[position]);
        file_contents->data[position] = NULL;
    }
    free(file_contents->data);
    file_contents->data = NULL;
}

char* get_path_from_args(int argc, char** argv) {
    if (argc < 2) {
        printf("Not enough arguments\n");
        return NULL;
    }

    char* file_path = argv[1];
    if (access(file_path, F_OK) != 0) {
        printf("Cannot read file: %s\n", file_path);
        return NULL;
    }
    return file_path;
}

FileContents read_lines(FILE* input_file) {
    char* line = NULL;
    size_t buffer_length = 0;
    FileContents input;
    input.length = 0;
    input.data = NULL;
    size_t input_size = 0;
    size_t line_length = 0;

    while ((line_length = getline(&line, &buffer_length, input_file)) != -1) {
        input.data = realloc(input.data, sizeof(char*) * (input.length + 1));
        input_size = input_size + line_length + 1;
        input.data[input.length] = malloc(line_length + 1);
        strcpy(input.data[input.length], line);
        input.length++;
    }
    free(line);
    return input;
}

int main(int argc, char** argv) {
    char* file_path = NULL;
    if (! (file_path = get_path_from_args(argc, argv))) {
        return 1;
    }
    FILE* input_file = fopen(file_path, "r");
    FileContents input = read_lines(input_file);
    fclose(input_file);

    int* first_numbers = NULL;
    int* second_numbers = NULL;
    int numbers_length = 0;

    for (int position = 0; position < input.length; position++) {
        char* line = input.data[position];
        first_numbers = realloc(first_numbers, sizeof(int) * (numbers_length + 1));
        second_numbers = realloc(second_numbers, sizeof(int) * (numbers_length + 1));
        sscanf(line, "%d   %d\n", &first_numbers[position], &second_numbers[position]);
        numbers_length++;
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

    qsort(first_numbers, numbers_length, sizeof(int), &compare_numbers);
    qsort(second_numbers, numbers_length, sizeof(int), &compare_numbers);
    int accumulator = 0;
    for (int position = 0; position < numbers_length; position++) {
        accumulator += abs(first_numbers[position] - second_numbers[position]);
    }
    printf("%d\n", accumulator);
    destroy_FileContents(&input);
    free(first_numbers);
    free(second_numbers);
    return 0;
}
