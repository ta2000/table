#include "table.h"

#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

void table_init(
    struct table *table,
    size_t key_size,
    size_t value_size,
    unsigned int max_entry_count)
{
    table->keys = malloc(key_size * max_entry_count);
    table->key_size = key_size;
    table->values = malloc(value_size * max_entry_count);
    table->value_size = value_size;

    table->max_entry_count = max_entry_count;

    table->pack_func = NULL;

    table->value_counts =
        calloc(max_entry_count, sizeof(*table->value_counts));
}

/*
char *table_search(
    struct table *table,
    void *key)
{
    for (int i = 0; i < table->entry_count; i++) {
        if (
    }
}
*/

unsigned int JSHash(const char* str, unsigned int length)
{
   unsigned int hash = 1315423911;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash ^= ((hash << 5) + (*str) + (hash >> 2));
   }

   return hash;
}

void table_insert(
    struct table *table,
    void *key,
    void *value)
{
	int length = 0;
	char *data = calloc(1, 50);;
	table->pack_func(key, &length, &data);

    uint64_t bucket = JSHash(data, length) % table->max_entry_count;
    printf("%lu\n", bucket);

    free(data);

    table->value_counts[bucket]++;

    memcpy(&table->values[bucket], value, table->value_size);
}

/*
void table_delete(
    struct draw_table *draw_table,
    struct renderer_draw_command *draw_command
);
*/

void table_destroy(
    struct table *table)
{
    free(table->keys);
    free(table->values);
    free(table->value_counts);
}
