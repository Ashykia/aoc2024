#include <stdlib.h>

void wipe_pointer_array(void** array, int length) {
    for (int position = 0; position < length; position++) {
        free(array[position]);
    }
}
