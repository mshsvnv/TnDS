#include "../inc/defs.h"

void make_keys(keys_t *keys, flat_t *flats, int *count)
{
    int i = 0;
    for (; i < *count; i++)
    {
        keys[i].index = i;
        keys[i].count_rooms = flats[i].count_rooms;
    }
}

void add_keys(keys_t *keys, int *count_rooms, int *count)
{
    keys[*count - 1].index = *count - 1;
    keys[*count - 1].count_rooms = *count_rooms;
}