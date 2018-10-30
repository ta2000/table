#ifndef TABLE_H_
#define TABLE_H_

#include <stdbool.h>
#include <stddef.h>

/*
struct value
{
    char *value;
    struct value *next;
};
*/

struct table
{
    char *keys;
    size_t key_size;
    char *values;
    size_t value_size;
    int *value_counts; // Num values in bucket for each bucket
    int max_entry_count;
    void (*pack_func)(void *, int *, char **);
};

void table_init(
    struct table *table,
    size_t key_size,
    size_t value_size,
    unsigned int max_entry_count
);

void table_insert(
    struct table *table,
    void *key,
    void *value
);

/*
void table_delete(
    struct table *table,
    struct renderer_draw_command *draw_command
);*/

void table_destroy(
    struct table *table
);

#endif
