#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../common/file_utils.h"

typedef struct {
    int x;
    int y;
} Point;

const char* XMAS = "XMAS";
const char* MAS = "MAS";


bool check_upper_bound(const FileContents* search_grid, const Point* point) {
    Point upper_bound;
    upper_bound.y = search_grid->length;
    upper_bound.x = strlen(search_grid->data[0]);
    if (point->y >= upper_bound.y) {
        return false;
    }
    if (point->x >= upper_bound.x) {
        return false;
    }
    return true;
}

static inline bool check_lower_bound(const Point* point) {
    return (! (point->x < 0 || point->y < 0));
}

bool check_next_char(
        const FileContents* search_grid,
        const Point* point,
        const Point* direction,
        const char* string) {
    if (! check_lower_bound(point)) {
        return false;
    }
    if (! check_upper_bound(search_grid, point)) {
        return false;
    }
    char char_at_point = search_grid->data[point->y][point->x];
    if (! (char_at_point == string[0])) {
        return false;
    }
    if (strlen(string) < 2) {
        //printf("%c", char_at_point);
        return true;
    }
    Point next_point;
    next_point.x = point->x + direction->x;
    next_point.y = point->y + direction->y;
    if (next_point.x < 0 || next_point.y < 0) {
        return false;
    }
    //printf("%c", char_at_point);
    int x = check_next_char(search_grid, &next_point, direction, string + 1);
    //printf("\n");
    return x;
}

int match_string(
        const FileContents* search_grid,
        const Point* start_point,
        const char* string) {
    if (! check_upper_bound(search_grid, start_point)){
        return 0;
    }
    char char_at_point = search_grid->data[start_point->y][start_point->x];
    if (! (char_at_point == string[0])) {
        return 0;
    }
    if (strlen(string) < 2) {
        return 1;
    }
    int result = 0;
    Point next_point;
    Point direction;
    for (direction.x = -1; direction.x <= 1; direction.x++) {
        for (direction.y = -1; direction.y <= 1; direction.y++) {
            //printf("\n");
            //printf("%c", char_at_point);
            if (direction.x == 0 && direction.y == 0) {
                continue;
            }
            next_point.x = start_point->x + direction.x;
            next_point.y = start_point->y + direction.y;
            if (next_point.x < 0 || next_point.y < 0) {
                continue;
            }
            bool x = check_next_char(search_grid, &next_point, &direction, string + 1);
            if (x) {
                //printf("Good!\n");
            }
            result+=x;
        }
    }
    //printf("\n");
    return result;
}

bool match_x_string(
        const FileContents* search_grid,
        const Point* start_point,
        const char* string) {
    int string_length = strlen(string);
    char* reversed_string = malloc(string_length + 1);
    for (int char_position = 1; char_position <= string_length; char_position++) {
        reversed_string[char_position-1] = string[string_length - char_position];
    }
    reversed_string[string_length] = '\0';
    const char** strings = malloc(sizeof(char*) * 2);
    strings[0] = string;
    strings[1] = reversed_string;
    Point forward_direction;
    forward_direction.x = 1;
    forward_direction.y = -1;
    Point backward_direction;
    backward_direction.x = -1;
    backward_direction.y = -1;
    Point backward_point;
    backward_point.x = start_point->x + string_length - 1;
    backward_point.y = start_point->y;
    for (int position1 = 0; position1 <= 1; position1++) {
        for (int position2 = 0; position2 <= 1; position2++) {
            if (check_next_char(search_grid, start_point, &forward_direction, strings[position1])
                    && check_next_char(search_grid, &backward_point, &backward_direction, strings[position2])) {
                return true;
            }
        }
    }
    free(strings);
    free(reversed_string);
    return false;
}


int main(int argc, char** argv) {
    char* file_path = NULL;
    if (! (file_path = get_path_from_args(argc, argv))) {
        return 1;
    }
    int result = 0;
    FILE* input_file = fopen(file_path, "r");
    FileContents* search_grid = read_lines(input_file);
    fclose(input_file);
    Point point;
    for (point.x = 0; point.x < search_grid->length; point.x++) {
        for (point.y = 0; point.y <= strlen(search_grid->data[point.x]) - 1; point.y++) {
            result += match_x_string(search_grid, &point, MAS);
        }
    }
    printf("%d\n", result);
    return 0;
}