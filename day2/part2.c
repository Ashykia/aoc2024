
#include <stdio.h>
#include "../common/file_utils.h"
#include "day2.h"

int main(int argc, char** argv) {
    char* file_path = NULL;
    if (! (file_path = get_path_from_args(argc, argv))) {
        return 1;
    }
    FILE* input_file = fopen(file_path, "r");
    int safe_lines = num_safe(input_file, 1, &is_safe);
    fclose(input_file);
    printf("%d\n", safe_lines);
    return 0;
}
