#ifndef __FILE_FUNCS_H__
#define __FILE_FUNCS_H__

int fill_matrix(FILE *f, ordinary_mtr_t *matrix_p, size_t row, int (*func_ptr)(FILE *, ordinary_mtr_t *));
int fill_sparse_matrix(ordinary_mtr_t *matrix_p, sparse_mtr_t *sparse_p);
long check_file_size(FILE *f);
int read_rows_columns(FILE *f, ordinary_mtr_t *matrix, size_t row);
int read_matrix_file(FILE *f, ordinary_mtr_t *matrix);
int read_matrix_random(FILE *f, ordinary_mtr_t *matrix_p);
int read_matrix_manual(FILE *f, ordinary_mtr_t *matrix_p);
void write_file(FILE *f, ordinary_mtr_t *matrix);

#endif // __FILE_FUNCS_H__