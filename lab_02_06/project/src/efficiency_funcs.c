#include "../inc/defs.h"
#include "../inc/sort_funcs.h"
#include "../inc/keys_funcs.h"
#include "../inc/file_funcs.h"


unsigned long long milliseconds_now(void)
{
    struct timeval val;

    if (gettimeofday(&val, NULL))
        return (unsigned long long) - 1;

    return val.tv_sec * 1000000 + val.tv_usec;
}

void efficiency_table(void)
{
    int num = 0, rc = 0;
    long long unsigned time_tb[5] = {0}, time_k[5] = {0}, aver_tb = 0, aver_k = 0;
    size_t tb_1, tb_2, tb_3, tb_4, tb_5;
    
    long long unsigned beg, end;
    flat_t flats_test[MAX_STRUCTS];
    keys_t keys_test[MAX_STRUCTS];
    FILE *f;

    char files[][MAX_STREET] = {"test_10.txt", "test_100.txt", "test_500.txt", "test_1000.txt", "test_1500.txt"};

    printf("\n*Measurements of time in microseconds\nMeasurements of memory in bytes\n\n");
    printf("//-----------------------/---------/---------/---------/---------/---------/---------//\n");
    printf("//          Size         / %7d / %7d / %7d / %7d / %7d / Average //\n", TEST_10, TEST_100, TEST_500, TEST_1000, TEST_1500);
    printf("//-----------------------/---------/---------/---------/---------/---------/---------//\n");

    for (int i = 0; i < 5; i++)
    {
        f = fopen(files[i], "r");

        rc = read_file(flats_test, &num, f);
        if (rc == SUCCESS)
            make_keys(keys_test, flats_test, &num);

        beg = milliseconds_now();
        mysort(flats_test, num, sizeof(flat_t), compare_flats);
        end = milliseconds_now();
        time_tb[i] = end - beg;
        aver_tb += time_tb[i];

        beg = milliseconds_now();
        mysort(keys_test, num, sizeof(keys_t), compare_keys);
        end = milliseconds_now();
        time_k[i] = end - beg;
        aver_k += time_k[i];
 
        fclose(f);
    }
 
    printf("//Bubble sort: data_table/ %7llu / %7llu / %7llu / %7llu / %7llu / %7d //\n", time_tb[0], time_tb[1], time_tb[2], time_tb[3], time_tb[4], (int)(aver_tb / 5));
    printf("//-----------------------/---------/---------/---------/---------/---------/---------//\n");
    printf("//Bubble sort: key_table / %7llu / %7llu / %7llu / %7llu / %7llu / %7d //\n", time_k[0], time_k[1], time_k[2], time_k[3], time_k[4], (int)(aver_k / 5));
    printf("//-----------------------/---------/---------/---------/---------/---------/---------//\n");

    aver_k = 0;
    aver_tb = 0;

    for (int i = 0; i < 5; i++)
    {
        f = fopen(files[i], "r");

        rc = read_file(flats_test, &num, f);
        if (rc == SUCCESS)
            make_keys(keys_test, flats_test, &num);

        beg = milliseconds_now();
        qsort(flats_test, num, sizeof(flat_t), compare_flats);
        end = milliseconds_now();
        time_tb[i] = end - beg;
        aver_tb += time_tb[i];

        beg = milliseconds_now();
        qsort(keys_test, num, sizeof(keys_t), compare_keys);
        end = milliseconds_now();
        time_k[i] = end - beg;
        aver_k += time_k[i];

        fclose(f);
    }
    
    printf("//Quick sort: data_table / %7llu / %7llu / %7llu / %7llu / %7llu / %7d //\n", time_tb[0], time_tb[1], time_tb[2], time_tb[3], time_tb[4], (int)(aver_tb / 5));
    printf("//-----------------------/---------/---------/---------/---------/---------/---------//\n");
    printf("//Quick sort: key_table  / %7llu / %7llu / %7llu / %7llu / %7llu / %7d //\n", time_k[0], time_k[1], time_k[2], time_k[3], time_k[4], (int)(aver_k / 5));
    printf("//-----------------------/---------/---------/---------/---------/---------/---------//\n");

    tb_1 = sizeof(flat_t)*TEST_10;
    tb_2 = sizeof(flat_t)*TEST_100;
    tb_3 = sizeof(flat_t)*TEST_500;
    tb_4 = sizeof(flat_t)*TEST_1000;
    tb_5 = sizeof(flat_t)*TEST_1500;
    printf("//Memory of data_table   / %7ld / %7ld / %7ld / %7ld / %7ld /---------//\n", tb_1, tb_2, tb_3, tb_4, tb_5);
    printf("//-----------------------/---------/---------/---------/---------/---------/---------//\n");

    tb_1 += sizeof(keys_t)*TEST_10;
    tb_2 += sizeof(keys_t)*TEST_100;
    tb_3 += sizeof(keys_t)*TEST_500;
    tb_4 += sizeof(keys_t)*TEST_1000;
    tb_5 += sizeof(keys_t)*TEST_1500;
    printf("//Memory of key_table    / %7ld / %7ld / %7ld / %7ld / %7ld /---------//\n", tb_1, tb_2, tb_3, tb_4, tb_5);
    printf("//-----------------------/---------/---------/---------/---------/---------/---------//\n");
}