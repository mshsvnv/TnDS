#ifndef __MULTIPLICATION_FUNCS_H__
#define __MULTIPLICATION_FUNCS_H__

int multiplication_matrix(ordinary_mtr_t *matrix_p_1, ordinary_mtr_t *matrix_p_2,  ordinary_mtr_t *res_p);
int multiplication_sparse_matrix(sparse_mtr_t *matrix_p_1, sparse_mtr_t *matrix_p_2,  sparse_mtr_t *res_p);

#endif // __MULTIPLICATION_FUNCS_H__