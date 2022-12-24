#include "../inc/defs.h"

int compare_keys(const void *l, const void *r)
{
    const keys_t *l_t = l;
    const keys_t *r_t = r;

    if (l_t->count_rooms > r_t->count_rooms)
        return 1;
    else if (l_t->count_rooms > r_t->count_rooms)
        return -1;
    else
        return 0;
}

int sort_keys_quicksort(keys_t *keys, int *count)
{
    if (*count == 0)
    {
        printf("Not avaliable data!\n");
        return EMPTY_TABLE_ERR;
    }
    else 
        qsort(keys, *count, sizeof(keys_t), compare_keys);

    return SUCCESS;
}

int compare_flats(const void *l, const void *r)
{
    const flat_t *l_t = l;
    const flat_t *r_t = r;

    if (l_t->count_rooms > r_t->count_rooms)
        return 1;
    else if (l_t->count_rooms > r_t->count_rooms)
        return -1;
    else
        return 0;
}

int sort_table_quicksort(flat_t *flats, int *count)
{
    if (*count == 0)
    {
        printf("Not avaliable data!\n");
        return EMPTY_TABLE_ERR;
    }
    else 
        qsort(flats, *count, sizeof(flat_t), compare_flats);

    return SUCCESS;
}

void swap(char *a, char *b, size_t size)
{
    size_t size_cur = size;		
    char *new_a = a, *new_b = b;

    do								      
    {								      
        char tmp = *new_a;						      
        *new_a++ = *new_b;	  
        *new_b++ = tmp;						      
    } while (--size_cur > 0);
}

void mysort(void *base, size_t num, size_t size, int (*compare)(const void *, const void *))
{
    char *pb = (char *)base;
    char *pe = pb + (num - 1) * size;
    char *last = pb, *end = pe;

    for (char *pi = pb; pi < pe; pi += size)
    {
        for (char *pj = pb; pj < end; pj += size)
        { 
            if (compare(pj, pj + size) > 0)
            {
                last = pj;
                swap(pj, pj + size, size);
            }
        }
        end = last;
    }
}

int sort_keys_slowsort(keys_t *keys, int *count)
{
    if (*count == 0)
    {
        printf("Not avaliable data!\n");
        return EMPTY_TABLE_ERR;
    }
    else 
        mysort(keys, *count, sizeof(keys_t), compare_keys);

    return SUCCESS;
}

int sort_table_slowsort(flat_t *flats, int *count)
{
    if (*count == 0)
    {
        printf("Not avaliable data!\n");
        return EMPTY_TABLE_ERR;
    }
    else 
        mysort(flats, *count, sizeof(flat_t), compare_flats);

    return SUCCESS;
}


