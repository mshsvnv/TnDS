#ifndef __OTHER_FUNCS_H__
#define __OTHER_FUNCS_H__

void print(ordinary_mtr_t *matrix_p, sparse_mtr_t *sparse_matrix);
void generate_matrix(ordinary_mtr_t *matrix_p, size_t fill);
int init_res_matrix(ordinary_mtr_t *matrix_p_1, ordinary_mtr_t *matrix_p_2,  ordinary_mtr_t *res_p);
int init_res_sparse_matrix(sparse_mtr_t *matrix_p_1, sparse_mtr_t *matrix_p_2,  sparse_mtr_t *res_p);
int transpose(ordinary_mtr_t *matrix);

#endif // __OTHER_FUNCS_H__