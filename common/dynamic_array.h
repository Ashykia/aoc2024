#include <stdlib.h>
#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

void wipe_pointer_array(void* array_start, int length);

#define DYNAMIC_ARRAY_DECLARES(type, typename) \
    typedef struct { \
        size_t length; \
        size_t allocated_spaces; \
        type* data; \
    } typename; \
\
    typename* construct_ ## typename(); \
    int append_to_ ## typename(typename* array_ptr, type item); \
    void destroy_ ## typename(typename* array_ptr);

#define DYNAMIC_ARRAY_IMPL(type, typename) \
    typename* construct_ ## typename() { \
        typename* array_ptr = malloc(sizeof(typename)); \
        array_ptr->data = NULL; \
        array_ptr->length = 0; \
        array_ptr->allocated_spaces = 0; \
        return array_ptr; \
    } \
\
    int append_to_ ## typename(typename* array_ptr, type item) { \
        if (array_ptr->length >= array_ptr->allocated_spaces) { \
            type* tmp = \
                realloc(array_ptr->data, sizeof(type) * (array_ptr->allocated_spaces + 256)); \
            if (!tmp) { \
                return 1; \
            } \
            array_ptr->data = tmp; \
            array_ptr->allocated_spaces += 256; \
        } \
        array_ptr->data[array_ptr->length] = item; \
        array_ptr->length++; \
        return 0; \
    } \
\
    void destroy_ ## typename(typename* array_ptr) { \
        free(array_ptr->data); \
        free(array_ptr); \
    }

#define DYNAMIC_ARRAY(type, typename) \
    DYNAMIC_ARRAY_DECLARES(type, typename) \
    DYNAMIC_ARRAY_IMPL(type, typename)

#endif
