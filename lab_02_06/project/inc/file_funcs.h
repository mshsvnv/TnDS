#ifndef __FILE_FUNCS_H__
#define __FILE_FUNCS_H__

long file_size(FILE *f); 
int read_file(flat_t *flats, int *count, FILE *f); 
int read_struct(flat_t *tmp, FILE *f, int type); 
int write_file(flat_t *flats, int *count, FILE *f);

#endif //__FILE_FUNCS_H__