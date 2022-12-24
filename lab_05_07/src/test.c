#include "../inc/test.h"

unsigned long long milliseconds_now(void)
{
    struct timeval val;

    if (gettimeofday(&val, NULL))
        return (unsigned long long) - 1;

    return val.tv_sec * 1000000ULL + val.tv_usec;
}

double rand_time(times_t *t)
{
    return (t->max - t->min) * (double)(rand()) / (double)RAND_MAX + t->min;
}

void test_time_memory(void)
{
    srand(time(NULL));

    long long unsigned list_time_beg, list_time_end, arr_time_beg, arr_time_end, t_1, t_2, sum = 0;
    int rc, i, num;
    size_t list_size, arr_size;

    node_t *tmp;
    arr_queue_t *arr_queue = NULL;
    list_queue_t *list_queue = NULL;

    rc = arr_queue_create(&arr_queue, stdin, MAX_ELEMS);
    
    arr_time_beg = milliseconds_now();
    for (i = 0; i < MAX_ELEMS; i++)
    {
        t_1 = milliseconds_now();
        num = rand() % 1000 - 500;
        t_2 = milliseconds_now();

        sum += t_2 - t_1;
        arr_push(arr_queue, &num);
    }
    arr_time_end = milliseconds_now();

    arr_time_end = arr_time_end - arr_time_beg - sum;
    sum = 0;

    rc = list_queue_create(&list_queue, stdin, MAX_ELEMS);
    
    list_time_beg = milliseconds_now();
    for (i = 0; i < MAX_ELEMS; i++)
    {
        t_1 = milliseconds_now();
        num = rand() % 1000 - 500;
        tmp = node_create(&num);
        t_2 = milliseconds_now();

        sum += t_2 - t_1;
        list_push(&list_queue, tmp);
    }
    list_time_end = milliseconds_now();

    list_time_end = list_time_end - list_time_beg - sum;
    sum = 0;

    printf("\n+--------------------+------------+------------+\n");
    printf("%s|  10 000 элементов  |   Массив   |   Список   |%s\n", MAGENTA, RESET);
    printf("+--------------------+------------+------------+\n");
    printf("| Добавление (мкс.)  |%12llu|%12llu|\n", arr_time_end, list_time_end);
    printf("+--------------------+------------+------------+\n");
    
    arr_time_beg = milliseconds_now();
    for (i = 0; i < MAX_ELEMS; i++)
        rc = arr_pop(arr_queue);
    arr_time_end = milliseconds_now();

    arr_time_end = arr_time_end - arr_time_beg;

    list_time_beg = milliseconds_now();
    for (i = 0; i < MAX_ELEMS; i++)
    {
        tmp = list_pop(list_queue);

        t_1 = milliseconds_now();
        free(tmp);
        t_2 = milliseconds_now();
        sum += t_2 - t_1;
    }
    list_time_end = milliseconds_now();

    list_time_end = list_time_end - list_time_beg;

    printf("|  Удаление (мкс.)   |%12llu|%12llu|\n", arr_time_end, list_time_end);
    printf("+--------------------+------------+------------+\n");

    list_size = MAX_ELEMS * sizeof(node_t);
    arr_size = MAX_ELEMS * sizeof(int);

    printf("|  Память (байтов)   |%12lu|%12lu|\n", arr_size, list_size);
    printf("+--------------------+------------+------------+\n");

    arr_clear(arr_queue);
    list_clear(list_queue);
    sum = 0;

    rc = arr_queue_create(&arr_queue, stdin, QUEUE);
    
    arr_time_beg = milliseconds_now();
    for (i = 0; i < QUEUE; i++)
    {
        t_1 = milliseconds_now();
        num = rand() % 1000 - 500;
        t_2 = milliseconds_now();

        sum += t_2 - t_1;
        arr_push(arr_queue, &num);
    }
    arr_time_end = milliseconds_now();

    arr_time_end = arr_time_end - arr_time_beg - sum;
    sum = 0;

    rc = list_queue_create(&list_queue, stdin, QUEUE);
    
    list_time_beg = milliseconds_now();
    for (i = 0; i < QUEUE; i++)
    {
        t_1 = milliseconds_now();
        num = rand() % 1000 - 500;
        tmp = node_create(&num);
        t_2 = milliseconds_now();

        sum += t_2 - t_1;
        list_push(&list_queue, tmp);
    }
    list_time_end = milliseconds_now();

    list_time_end = list_time_end - list_time_beg - sum;
    sum = 0;

    printf("\n+--------------------+------------+------------+\n");
    printf("|   1 000 элементов  |   Массив   |   Список   |\n");
    printf("+--------------------+------------+------------+\n");
    printf("| Добавление (мкс.)  |%12llu|%12llu|\n", arr_time_end, list_time_end);
    printf("+--------------------+------------+------------+\n");
    
    arr_time_beg = milliseconds_now();
    for (i = 0; i < QUEUE; i++)
        rc = arr_pop(arr_queue);
    arr_time_end = milliseconds_now();

    arr_time_end = arr_time_end - arr_time_beg;

    list_time_beg = milliseconds_now();
    for (i = 0; i < QUEUE; i++)
    {
        tmp = list_pop(list_queue);
        t_1 = milliseconds_now();
        free(tmp);
        t_2 = milliseconds_now();
        sum += t_2 - t_1;
    }
    list_time_end = milliseconds_now();

    list_time_end = list_time_end - list_time_beg - sum;

    printf("|  Удаление (мкс.)   |%12llu|%12llu|\n", arr_time_end, list_time_end);
    printf("+--------------------+------------+------------+\n");

    list_size = QUEUE * sizeof(node_t);
    arr_size = QUEUE * sizeof(int);

    printf("|  Память (байтов)   |%12lu|%12lu|\n", arr_size, list_size);
    printf("+--------------------+------------+------------+\n");

    arr_clear(arr_queue);
    list_clear(list_queue);

    rc += 10;
}

int change_time(times_t *t_1, times_t *t_2)
{
    int choice;
    double left, right, tmp; 

    printf("\n+-----------------------------+----------+----------+\n");
    printf("|          До                 |   Мин.   |   Макс.  |\n");
    printf("+-----------------------------+----------+----------+\n");
    printf("| 1. Время прихода (е. в.)    |%10.1lf|%10.1lf|\n", t_1->min, t_1->max);
    printf("+-----------------------------+----------+----------+\n");
    printf("| 2. Время обработки (е. в.)  |%10.1lf|%10.1lf|\n", t_2->min, t_2->max);
    printf("+-----------------------------+----------+----------+\n");

    printf("\nКакое время поменять: ");

    if (fscanf(stdin, "%d", &choice) != 1 || choice < 0 || choice > 2)
    {
        printf("Неверный пункт!\n");
        return ERR_WRONG_CHOICE;
    }

    printf("\nВведите граничные значения: ");

    if (fscanf(stdin, "%lf%lf", &left, &right) != 2 || left < 0 || right < 0 || fabs(left - right) < EPS)
    {
        printf("Неверное значение!\n");
        return ERR_WRONG_ELEM;
    }

    if (left > right)
    {
        tmp = left;
        left = right;
        right = tmp;
    }

    if (choice == 1)
    {
        t_1->min = left;
        t_1->max = right;
    }
    else
    {
        t_2->min = left;
        t_2->max = right;
    }

    printf("\n+-----------------------------+----------+----------+\n");
    printf("|          После              |   Мин.   |   Макс.  |\n");
    printf("+-----------------------------+----------+----------+\n");
    printf("%s| 1. Время прихода (е. в.)    |%10.1lf|%10.1lf|%s\n", MAGENTA, t_1->min, t_1->max, RESET);
    printf("+-----------------------------+----------+----------+\n");
    printf("%s| 2. Время обработки (е. в.)  |%10.1lf|%10.1lf|%s\n", MAGENTA, t_2->min, t_2->max, RESET);
    printf("+-----------------------------+----------+----------+\n\n");

    return SUCCESS;
}

void arr_modeling(times_t *t_1, times_t *t_2)
{
    int rc;

    arr_queue_t *arr_queue = NULL;

    rc = arr_queue_create(&arr_queue, stdin, MAX_ELEMS);
    rc += 10;

    double elapsed_time = 0;
    double waiting_time = 0;

    // время, оставшееся до выхода элемента очереди в ОА
    double time_to_out = 0; 
    // время, оставшееся до входа следуюшего элемента в очередь
    double time_to_in = rand_time(t_1); 

    // кол-во вышедших заявок
    int passed_tasks = 0;

    int avg_len = 0;
    int avg[10] = { 0 }, temp[10] = { 0 };

    int temp_task;
    int task_in_work = 0;

    // кол-во срабатываний аппарата
    int calls = 0;
    int tasks_in = 0;

    int work_mode = 0;

    int i = 0;

    while (passed_tasks < 1000)
    {
        if (work_mode == 0)
        {
            // если аппарат не работает
            // если в очереди есть элементы, то необходимо взять первый и запустить ОА
            if (!arr_is_empty(arr_queue))
            {
                task_in_work = arr_pop(arr_queue);
                time_to_out = rand_time(t_2);
                work_mode = 1;
                calls++;
            }
            else
            {
                // если в очереди нет эл-ов, нужно подождать, пока новый элемент войдет в очеред
                elapsed_time += time_to_in;
                waiting_time += time_to_in;

                time_to_in = 0;
                task_in_work = 0;
                
                if (arr_is_full(arr_queue))
                {
                    printf("Массив переполнен!\n");
                    break;
                }
                arr_push(arr_queue, &task_in_work);
                time_to_in = rand_time(t_1);
                tasks_in++;
            }
        }
        else
        {
            // если аппарат работает
            if (cmp_double(time_to_in, time_to_out) > 0)
            {
                // если заявка не успеет войти в очередь, как аппарат закончит работу
                // то заканчиваем работу аппарата
                time_to_in -= time_to_out;
                elapsed_time += time_to_out;

                time_to_out = 0;
                work_mode = 0;
                task_in_work++;

                // если из аппарата вышла заявка, которая проходила меньше 5 раз, то добавляем ее в очередь
                if (task_in_work < 5)
                {
                    if (arr_is_full(arr_queue))
                    {
                        printf("Массив переполнен!\n");
                        break;
                    }
                    arr_push(arr_queue, &task_in_work);
                }
                else
                {
                    passed_tasks++;
                    if (passed_tasks % 100 == 0 && passed_tasks)
                    {
                        avg_len += arr_queue->last;
                        temp[passed_tasks / 100 - 1] = arr_queue->last;
                        avg[passed_tasks / 100 - 1] = avg_len / (passed_tasks / 100);
                    }
                }
                // иначе она закончила свой цикл и вышла из системы
            }
            else
            {
                // если новая заявка успеет добавиться в очередь во время работы аппарата
                // вычитаем время захода из времени работы аппарата
                time_to_out -= time_to_in;
                elapsed_time += time_to_in;
                time_to_in = 0;
                // добавляем заявку в очередь
                temp_task = 0;

                if (arr_is_full(arr_queue))
                {
                    printf("Массив переполнен!\n");
                    break;
                }


                arr_push(arr_queue, &temp_task);

                tasks_in++;
                // генерируем новое время ожидания добавления
                time_to_in = rand_time(t_1);
            }
        }
    }
    printf("\n+--------------------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+\n");
    printf("%s| Кол-во вышедших заявок:  |   100   |   200   |   300   |   400   |   500   |   600   |   700   |   800   |   900   |   1000  |%s\n", MAGENTA, RESET);
    printf("+--------------------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+\n");
    printf("| Текущая длина (эл.)      |");
    for (int i = 0; i < 10; i++)
        printf("%9d|", temp[i]);
    printf("\n+--------------------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+\n");
    printf("| Средняя длина (эл.)      |");
    for (i = 0; i < 10; i++)
        printf("%9d|", avg[i]);
    printf("\n+--------------------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+\n\n");
   
    printf("\n+-----------------------------------+---------------+\n");
    printf("| Общее время моделирования (е. в)  |%15.1lf|\n", elapsed_time);
    printf("+-----------------------------------+---------------+\n");
    printf("| Кол-во вошедших в систему заявок  |%15d|\n", tasks_in);
    printf("+-----------------------------------+---------------+\n");
    printf("| Кол-во вышедших из системы заявок |%15d|\n", passed_tasks);
    printf("+-----------------------------------+---------------+\n");
    printf("| Кол-во обработок ОА               |%15d|\n", calls);
    printf("+-----------------------------------+---------------+\n");
    printf("| Время простоя аппарата            |%15.1lf|\n", waiting_time);
    printf("+-----------------------------------+---------------+\n");
    printf("| Длина очереди                     |%15d|\n", arr_queue->last);
    printf("+-----------------------------------+---------------+\n\n");

    double aver_time_in_one = (t_1->max + t_1->min) / 2; // среднее значение прихода 1 заявки
    double aver_time_out_one = (t_2->max + t_2->min) / 2; // среднее значение прихода 1 заявки
    
    double th_amount = aver_time_in_one * QUEUE;
    double pr_perc = fabs(elapsed_time - th_amount) / th_amount * 100;
    double zayv = elapsed_time / aver_time_in_one;

    printf("Расчет погрешности:\n\n");
    printf("Погрешность по входу:\n");
    printf("(Теор.) %.1lf е.в. / %.1lf е.в. = %.1lf заявок, (Практич.) = %d заявок, |(%d - %.1lf)| / %.1lf * 100%% = %.1lf%%\n", elapsed_time, aver_time_in_one, zayv, tasks_in, tasks_in, zayv, zayv, fabs(tasks_in - zayv) / (elapsed_time / aver_time_in_one) * 100);
    
    printf("\nПогрешность по выходу:\n");
    printf("(Теор.) t работы + t простоя = t моделир., (Практич.) %.1lf, |(%.1lf - %.1lf)| / %.1lf * 100%% = %.1lf%%\n", elapsed_time, calls * aver_time_out_one + waiting_time, elapsed_time, calls * aver_time_out_one + waiting_time, fabs(calls * aver_time_out_one + waiting_time - elapsed_time) / (calls * aver_time_out_one + waiting_time) * 100);
    
    printf("\nПогрешность по времени моделирования:\n");
    printf("(Теор.) %.1lf * 1000 = %.1lf, (Практич.) %lf, |(%.1lf - %.1lf)| / %.lf * 100%% = %.1lf%%\n\n", aver_time_in_one, th_amount, elapsed_time, elapsed_time, th_amount, th_amount, pr_perc);

    arr_clear(arr_queue);
}
    
void list_modeling(times_t *t_1, times_t *t_2)
{
    int rc;

    list_queue_t *list_queue = NULL;
    node_t *tmp = NULL;

    rc = list_queue_create(&list_queue, stdin, MAX_ELEMS);
    rc += 10;

    double elapsed_time = 0;
    double waiting_time = 0;

    // время, оставшееся до выхода элемента очереди в ОА
    double time_to_out = 0; 
    // время, оставшееся до входа следуюшего элемента в очередь
    double time_to_in = rand_time(t_1); 

    // кол-во вышедших заявок
    int passed_tasks = 0;

    int avg_len = 0;
    int avg[10] = { 0 }, temp[10] = { 0 };

    int temp_task;

    int task_in_work = 0;

    // кол-во срабатываний аппарата
    int calls = 0;
    int tasks_in = 0;

    int work_mode = 0;

    int i = 0;

    while (passed_tasks < 1000)
    {
        if (work_mode == 0)
        {
            // если аппарат не работает
            // если в очереди есть элементы, то необходимо взять первый и запустить ОА
            if (!list_is_empty(list_queue))
            {
                tmp = list_pop(list_queue);
                task_in_work = tmp->inf;

                free(tmp);

                time_to_out = rand_time(t_2);
                work_mode = 1;
                calls++;
            }
            else
            {
                // если в очереди нет эл-ов, нужно подождать, пока новый элемент войдет в очеред
                elapsed_time += time_to_in;
                waiting_time += time_to_in;

                time_to_in = 0;
                task_in_work = 0;

                tmp = node_create(&task_in_work);
                list_push(&list_queue, tmp);
                time_to_in = rand_time(t_1);
                tasks_in++;
            }
        }
        else
        {
            // если аппарат работает
            if (cmp_double(time_to_in, time_to_out) > 0)
            {
                // если заявка не успеет войти в очередь, как аппарат закончит работу
                // то заканчиваем работу аппарата
                time_to_in -= time_to_out;
                elapsed_time += time_to_out;

                time_to_out = 0;
                work_mode = 0;
                task_in_work++;

                // если из аппарата вышла заявка, которая проходила меньше 5 раз, то добавляем ее в очередь
                if (task_in_work < 5)
                {
                    tmp = node_create(&task_in_work);
                    list_push(&list_queue, tmp);
                }
                else
                {
                    passed_tasks++;
                    if (passed_tasks % 100 == 0 && passed_tasks)
                    {
                        avg_len += list_queue->cur_size;
                        temp[passed_tasks / 100 - 1] = list_queue->cur_size;
                        avg[passed_tasks / 100 - 1] = avg_len / (passed_tasks / 100);
                    }
                }
                // иначе она закончила свой цикл и вышла из системы
            }
            else
            {
                // если новая заявка успеет добавиться в очередь во время работы аппарата
                // вычитаем время захода из времени работы аппарата
                time_to_out -= time_to_in;
                elapsed_time += time_to_in;
                time_to_in = 0;
                // добавляем заявку в очередь
                temp_task = 0;

                tmp = node_create(&temp_task);
                list_push(&list_queue, tmp);

                tasks_in++;
                // генерируем новое время ожидания добавления
                time_to_in = rand_time(t_1);
            }
        }
    }

    printf("\n+--------------------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+\n");
    printf("%s| Кол-во вышедших заявок:  |   100   |   200   |   300   |   400   |   500   |   600   |   700   |   800   |   900   |   1000  |%s\n", MAGENTA, RESET);
    printf("+--------------------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+\n");
    printf("| Текущая длина (эл.)      |");
    for (int i = 0; i < 10; i++)
        printf("%9d|", temp[i]);
    printf("\n+--------------------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+\n");
    printf("| Средняя длина (эл.)      |");
    for (i = 0; i < 10; i++)
        printf("%9d|", avg[i]);
    printf("\n+--------------------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+\n\n");
   
    printf("\n+-----------------------------------+---------------+\n");
    printf("| Общее время моделирования (е. в)  |%15.1lf|\n", elapsed_time);
    printf("+-----------------------------------+---------------+\n");
    printf("| Кол-во вошедших в систему заявок  |%15d|\n", tasks_in);
    printf("+-----------------------------------+---------------+\n");
    printf("| Кол-во вышедших из системы заявок |%15d|\n", passed_tasks);
    printf("+-----------------------------------+---------------+\n");
    printf("| Кол-во обработок ОА               |%15d|\n", calls);
    printf("+-----------------------------------+---------------+\n");
    printf("| Время простоя аппарата            |%15.1lf|\n", waiting_time);
    printf("+-----------------------------------+---------------+\n");
    printf("| Длина очереди                     |%15d|\n", list_queue->cur_size);
    printf("+-----------------------------------+---------------+\n\n");

    double aver_time_in_one = (t_1->max + t_1->min) / 2; // среднее значение прихода 1 заявки
    double aver_time_out_one = (t_2->max + t_2->min) / 2; // среднее значение прихода 1 заявки
    
    double th_amount = aver_time_in_one * QUEUE;
    double pr_perc = fabs(elapsed_time - th_amount) / th_amount * 100;
    double zayv = elapsed_time / aver_time_in_one;

    printf("Расчет погрешности:\n\n");
    printf("Погрешность по входу:\n");
    printf("(Теор.) %.1lf е.в. / %.1lf е.в. = %.1lf заявок, (Практич.) = %d заявок, |(%d - %.1lf)| / %.1lf * 100%% = %.1lf%%\n", elapsed_time, aver_time_in_one, zayv, tasks_in, tasks_in, zayv, zayv, fabs(tasks_in - zayv) / (elapsed_time / aver_time_in_one) * 100);
    
    printf("\nПогрешность по выходу:\n");
    printf("(Теор.) t работы + t простоя = t моделир., (Практич.) %.1lf, |(%.1lf - %.1lf)| / %.1lf * 100%% = %.1lf%%\n", elapsed_time, calls * aver_time_out_one + waiting_time, elapsed_time, calls * aver_time_out_one + waiting_time, fabs(calls * aver_time_out_one + waiting_time - elapsed_time) / (calls * aver_time_out_one + waiting_time) * 100);
    
    printf("\nПогрешность по времени моделирования:\n");
    printf("(Теор.) %.1lf * 1000 = %.1lf, (Практич.) %lf, |(%.1lf - %.1lf)| / %.lf * 100%% = %.1lf%%\n\n", aver_time_in_one, th_amount, elapsed_time, elapsed_time, th_amount, th_amount, pr_perc);

    list_clear(list_queue);
}

