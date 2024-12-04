#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../common/file_utils.h"
#include "../common/int_utils.h"

int main(int argc, char** argv) {
    char* file_path = NULL;
    if (! (file_path = get_path_from_args(argc, argv))) {
        return 1;
    }
    FILE* input_file = fopen(file_path, "r");
    char* line = NULL;
    char* token = NULL;
    size_t buffer_length = 0;
    size_t line_length = 0;
    int num_safe = 0;
    int tmp1 = 0;
    int tmp2 = 0;
    short safe_val;
    short difference;
    short safe_counter;
    const char* delim = " \n";
    while ((line_length = getline(&line, &buffer_length, input_file)) != -1) {
        safe_val = 0;
        safe_counter = 0;
        if (token = strtok(line, delim)) {
            sscanf(token, "%d", &tmp1);
        }
        while (token = strtok(NULL, delim)) {
            safe_val++;
            tmp2 = tmp1;
            sscanf(token, "%d", &tmp1);
            if ((difference = abs(tmp1 - tmp2)) > 3) {
                goto unsafe;
            }
            safe_counter += compare_numbers(&tmp1, &tmp2);
        }
        if (abs(safe_counter) == safe_val) {
            num_safe++;
        }
        unsafe:;
    }
    free(line);
    fclose(input_file);
    printf("%d\n", num_safe);
    return 0;
}
