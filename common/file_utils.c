#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "file_utils.h"
#include "dynamic_array.h"

DYNAMIC_ARRAY_IMPL(char*, FileContents)

FileContents* read_lines(FILE* input_file) {
    char* line = NULL;
    size_t buffer_length = 0;
    FileContents* input = construct_FileContents();
    size_t input_size = 0;
    size_t line_length = 0;
    char* tmp;

    while ((line_length = getline(&line, &buffer_length, input_file)) != -1) {
        tmp = malloc(line_length + 1);
        strcpy(tmp, line);
        append_to_FileContents(input, tmp);
    }
    free(line);
    return input;
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

