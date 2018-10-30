#include "table.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct test_key_1
{
    unsigned int handle;
    float *reference;
};

struct test_value
{
    char *text;
    int number;
};

void pack_test_key_1(void *key_addr, int *length, char **data) {
    if (!*data)
        return;

    char *data_ptr = *data;

    struct test_key_1 *key = (struct test_key_1*)key_addr;

    memcpy(data_ptr, &key->handle, sizeof(key->handle));
    data_ptr += sizeof(key->handle);

    memcpy(data_ptr, &key->reference, sizeof(key->reference));
    data_ptr += sizeof(key->reference);

    *length = data_ptr - *data;
}

void test_table() {
    printf("Hash Table test.\n");

    struct table my_table;
    table_init(
        &my_table,
        sizeof(struct test_key_1),
        sizeof(struct test_value),
        19
    );
    my_table.pack_func = &pack_test_key_1;

    char *my_memory = malloc(500);
    printf("My memory block starts at %p\n", my_memory);

    struct test_key_1 keys[] = {
        {.handle = 200, .reference = (float*)(&my_memory[0])},
        {.handle = 201, .reference = (float*)(&my_memory[8])},
        {.handle = 202, .reference = (float*)(&my_memory[16])}
    };

    struct test_value values[] = {
        {.text = "Mercury", .number = 18},
        {.text = "Neptune", .number = 19},
        {.text = "Titan", .number = 20}
    };

    table_insert(&my_table, &keys[0], &values[0]);
    table_insert(&my_table, &keys[1], &values[1]);
    table_insert(&my_table, &keys[2], &values[2]);

    for (int i = 0; i < my_table.max_entry_count; i++) {
        if (my_table.value_counts[i])
            printf("Bucket [%d] has value\n", i);
    }

    free(my_memory);

    table_destroy(&my_table);
}

int main(int argc, char** argv)
{
    test_table();

    return 0;
}
