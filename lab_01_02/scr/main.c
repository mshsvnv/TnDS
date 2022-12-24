#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "defs.h"
#include "typedefs.h"
#include "essential_funcs.h"
#include "optional_funcs.h"
#include "float_num_funcs.h"
#include "int_num_funcs.h"

int main(void)
{
    int_num first;
    int_num *p_first = &first;

    float_num second;
    float_num *p_second = &second;

    float_num res;
    float_num *p_res = &res;

    int rc;

    info();

    rc = check_num_int(p_first);

    if (rc == INT_VALUE_ERR)
        return INT_VALUE_ERR;
    else if (rc == INT_LEN_ERR)
        return INT_LEN_ERR;

    rc = check_num_float(p_second);
    if (rc == FL_LEN_ERR)
        return FL_LEN_ERR;
    else if (rc == FL_POW_ERR)
        return FL_POW_ERR;
    else if (rc == FL_VALUE_ERR)
        return FL_VALUE_ERR;

    rc = multiplication(p_first, p_second, p_res);

    if (rc == RES_POW_ERROR)
        return RES_POW_ERROR;

    output_res(p_res);

    return rc;
}
