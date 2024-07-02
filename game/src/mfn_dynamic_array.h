#ifndef MFN_DYNAMIC_ARRAY_H
#define MFN_DYNAMIC_ARRAY_H

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define MFN_ARRAY_INIT(type, array_struct) \
do \
{ \
    type* items = malloc(sizeof(*items)); \
    assert(items != NULL); \
    memset(items, 0, sizeof(*items)); \
    (array_struct)->items = items; \
    (array_struct)->count = 0; \
    (array_struct)->capacity = 1; \
} while (0)

#define MFN_ARRAY_APPEND(type, array_struct, item) \
do \
{ \
    if ((array_struct)->count == (array_struct)->capacity) \
    { \
        size_t new_capacity = (array_struct)->capacity * 2; \
        type* ptr = realloc((array_struct)->items, sizeof(*ptr) * new_capacity); \
        assert(ptr != NULL); \
        memset(&ptr[(array_struct)->count], 0, sizeof(*ptr) * (array_struct)->capacity); \
        (array_struct)->items = ptr; \
        (array_struct)->capacity = new_capacity; \
    } \
    (array_struct)->items[(array_struct)->count++] = item; \
} while (0)

#define MFN_ARRAY_PREPEND(type, array_struct, item) \
do { \
    if ((array_struct)->count == (array_struct)->capacity) \
    { \
        size_t new_capacity = (array_struct)->capacity * 2; \
        type* ptr = realloc((array_struct)->items, sizeof(*ptr) * new_capacity); \
        assert(ptr != NULL); \
        memset(&ptr[(array_struct)->count], 0, sizeof(*ptr) * ((array_struct)->capacity)); \
        (array_struct)->items = ptr; \
        (array_struct)->capacity = new_capacity; \
    } \
    memmove(&(array_struct)->items[1], &(array_struct)->items[0], sizeof(*(array_struct)->items) * (array_struct)->count); \
    (array_struct)->items[0] = item; \
    ++(array_struct)->count; \
} while (0)

#define MFN_ARRAY_INSERT(type, array_struct, index, item) \
do { \
    if ((array_struct)->count == (array_struct)->capacity) \
    { \
        size_t new_capacity = (array_struct)->capacity * 2; \
        type* ptr = realloc((array_struct)->items, sizeof(*ptr) * new_capacity); \
        assert(ptr != NULL); \
        memset(&ptr[(array_struct)->count], 0, sizeof(*ptr) * ((array_struct)->capacity)); \
        (array_struct)->items = ptr; \
        (array_struct)->capacity = new_capacity; \
    } \
    memmove(&(array_struct)->items[index + 1], &(array_struct)->items[index], sizeof(*(array_struct)->items) * ((array_struct)->count - index)); \
    (array_struct)->items[index] = item; \
    ++(array_struct)->count; \
} while (0)

#define MFN_ARRAY_FREE(type, array_struct) \
do \
{ \
    if ((array_struct)->items != NULL) \
    { \
        free((array_struct)->items); \
        (array_struct)->items = NULL; \
    } \
    (array_struct)->count = 0; \
    (array_struct)->capacity = 0; \
} while (0)

#endif
