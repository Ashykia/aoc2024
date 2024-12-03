#include <stdio.h>
#include <stdlib.h>
#include "../common/file_utils.h"
#include "day1.h"

int main(int argc, char** argv) {
    char* file_path = NULL;
    if (! (file_path = get_path_from_args(argc, argv))) {
        return 1;
    }
    FILE* input_file = fopen(file_path, "r");
    FileContents* file_contents = read_lines(input_file);
    fclose(input_file);

    struct InputData input = get_input(file_contents);
    sort_input(&input);

    int accumulator = 0;
    for (int position = 0; position < input.left_hand_side->length; position++) {
        accumulator += abs(input.left_hand_side->data[position]
                         - input.right_hand_side->data[position]);
    }
    printf("%d\n", accumulator);
    wipe_pointer_array(file_contents->data, file_contents->length);
    destroy_FileContents(file_contents);
    free_input_data(&input);
    return 0;
}
