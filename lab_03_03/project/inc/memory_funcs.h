#ifndef __MEMORY_FUNCS_H__
#define __MEMORY_FUNCS_H__

int allocation_matrix(ordinary_mtr_t *matrix_p);
int allocation_sparse_matrix(sparse_mtr_t *sparse_p, size_t *non_zero, size_t rows);
void free_matrix(ordinary_mtr_t *matrix_p);
void free_sparse_matrix(sparse_mtr_t *sparse_p);

#endif // __MEMORY_FUNCS_H__