#ifndef MTLIB_DSALGO_H
#define MTLIB_DSALGO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mtlib_common.h"

#ifndef MTLIB_DYNAMIC_ARRAY_IMPLEMENTATION

typedef struct {
    size_t length;
    size_t capacity;
    size_t padding;
    Allocator *a;
} Array_Header;

void *
array_alloc(size_t bytes, void *context) {
    (void)context;
    return malloc(bytes);
}

void *
array_free(size_t bytes, void *ptr, void *context) {
    (void)ptr; (void)context;
    free(ptr);
    ptr = NULL;
    return ptr;
}

Allocator allocator = { array_alloc, array_free, 0 };

#define ARRAY_INITIAL_CAPACITY 16

#define array(T, a) array_init(sizeof(T), ARRAY_INITIAL_CAPACITY, a)

#define array_header(a) ((Array_Header *)(a) - 1)
#define array_length(a) (array_header(a)->length)
#define array_capacity(a) (array_header(a)->capacity)

#define array_append(a, v) ( \
    (a) = array_ensure_capacity(a, 1, sizeof(v)), \
    (a)[array_header(a)->length] = (v), \
    &(a)[array_header(a)->length++])

void *
array_init(size_t item_size, size_t capacity, Allocator *a) {
    void *ptr = 0;
    size_t size = item_size * capacity + sizeof(Array_Header);
    Array_Header *h = a->alloc(size, 0);

    if (h) {
        h->capacity = capacity;
        h->length = 0;
        h->a = a;
        ptr = h + 1;
    }

    return ptr;
}

void *
array_ensure_capacity(void *a, size_t item_count, size_t item_size) {
    Array_Header *h = array_header(a);
    size_t desired_capacity = h->length + item_count;

    if (h->capacity < desired_capacity) {
        size_t new_capacity = h->capacity * 2;
        while (new_capacity < desired_capacity) {
            new_capacity *= 2;
        }

        size_t new_size = sizeof(Array_Header) + new_capacity * item_size;
        Array_Header *new_h = h->a->alloc(new_size, h->a->context);

        if (new_h) {
            size_t old_size = sizeof(*h) + h->length * item_size;
            memcpy(new_h, h, old_size);

            if (h->a->free) {
                h->a->free(old_size, h, h->a->context);
            }

            new_h->capacity = new_capacity;
            h = new_h + 1;
        } else {
            h = 0;
        }
    } else {
        h += 1;
    }

    return h;
}


#define array_remove(a, i) do { \
    Array_Header *h = array_header(a); \
    if (i == h->length - 1) { \
        h->length -= 1; \
    } else if (h->length > 1) { \
        void *ptr = &a[i]; \
        void *last = &a[h->length - 1]; \
        h->length -= 1; \
        memcpy(ptr, last, sizeof(*a)); \
    } \
} while (0)

#define array_pop_back(a) (array_header(a)->length -= 1)

#endif // MTLIB_DYNAMIC_ARRAY_IMPLEMENTATION
#endif // MTLIB_DSALGO_H