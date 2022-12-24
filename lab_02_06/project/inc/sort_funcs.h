#ifndef __SORT_FUNCS_H__
#define __SORT_FUNCS_H__

int compare_flats(const void *l, const void *r);  
int compare_keys(const void *l, const void *r); 
int sort_keys_quicksort(keys_t *keys, int *count); 
int sort_table_quicksort(flat_t *flats, int *count); 
int sort_keys_slowsort(keys_t *keys, int *count); 
int sort_table_slowsort(flat_t *flats, int *count); 
void mysort(void *base, size_t num, size_t size, int (*compare)(const void *, const void *)); 
void swap(char *a, char *b, size_t size); 

#endif //__SORT_FUNCS_H__