#include "int_utils.h"
#include "dynamic_array.h"

DYNAMIC_ARRAY_IMPL(int, IntArray)

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
