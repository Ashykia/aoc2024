#ifndef FILE_UTILS_H
#define FILE_UTILS_H
#include "dynamic_array.h"

DYNAMIC_ARRAY_DECLARES(char*, FileContents)

FileContents* read_lines(FILE* input_file);
char* get_path_from_args(int argc, char** argv);
#endif
