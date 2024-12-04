#ifndef DAY1_H
#define DAY1_H
#include "../common/dynamic_array.h"
#include "../common/file_utils.h"
#include "../common/int_utils.h"

struct InputData {
    IntArray* left_hand_side;
    IntArray* right_hand_side;
};

struct InputData get_input(FileContents* file_contents);
void sort_input(struct InputData* input);
void free_input_data(struct InputData* input);

#endif
