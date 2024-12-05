#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../common/file_utils.h"

int main(int argc, char** argv) {
    char* file_path = NULL;
    if (! (file_path = get_path_from_args(argc, argv))) {
        return 1;
    }
    FILE* input_file = fopen(file_path, "r");
    long long result = 0;
    char* current = NULL;
    char* last = NULL;
    const char* delim = "()";
    size_t buffer_length = 0;
    size_t line_length = 0;
    char* line = NULL;

    while ((line_length = getline(&line, &buffer_length, input_file)) != -1) {
        if (! (last = strtok(line, delim))) {
            continue;
        }
        while (current = strtok(NULL, delim)) {
            int tmp[2] = {0};
            int last_len = strlen(last);
            char* tmp_str = malloc(8);
            int num_good_values = sscanf(current, "%d,%d", &tmp[0], &tmp[1]);
            snprintf(tmp_str, 8, "%d,%d", tmp[0], tmp[1]);
            
            if (last_len >= 3 && strcmp((last + last_len - 3), "mul") == 0 && num_good_values == 2 && strcmp(current, tmp_str) == 0) {
                result += tmp[0] * tmp[1];
            }
            last = current;
            free(tmp_str);
        }
    }
    fclose(input_file);
    free(line);
    printf("%d\n", result);
    return 0;
}
