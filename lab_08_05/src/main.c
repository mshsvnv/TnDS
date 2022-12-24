#include "../inc/graph.h"
#include "../inc/options.h"

int main(int argc, char **argv)
{
    int rc, choice = 1;
    graph_t *cur_graph = NULL;
    char *name = "initial_graph", buf[20];

    FILE *f_in = NULL;
    FILE *f_out = NULL;

    while (choice != 0)
    {
        print_menu();

        if (fscanf(stdin, "%d", &choice) != 1 || choice < 0 || choice > 3)
        {
            fgets(buf, 20, stdin);
            printf("\nНеверно выбранный пункт меню!\n");
            rc = ERR_WRONG_CHOICE;
        }
        else
        {
            switch (choice)
            {
            case 1:
                {
                    if (cur_graph)
                        graph_free(cur_graph);
                        
                    if (argc != 0)
                        f_in = fopen(argv[1], "r");

                    if (!f_in)
                    {
                        printf("\nНет доступного файла!\n");
                        rc = ERR_NO_FIlE;
                        break;
                    }

                    if (file_size(f_in) == 0)
                    {
                        printf("\nВходной файл пуст!\n");
                        rc = ERR_EMPTY_FIlE;
                        break;
                    }

                    cur_graph = graph_fill(cur_graph, f_in, &rc);

                    if (cur_graph)
                        printf("\nГраф проинициализирован!\n");

                    fclose(f_in);
                    break;
                }
            case 2:
                {
                    if (cur_graph)
                    {
                        rc = graph_check_tree(cur_graph);

                        break;
                    }
                    else
                    {
                        printf("\nНет доступного графа!\n");
                        rc = ERR_NO_GRAPH;   
                    }
                    break;
                }
            case 3:
                {
                    if (cur_graph)
                    {
                        f_out = fopen("initial_graph.gv", "wb");

                        export_to_dot(cur_graph, f_out, name, -1);

                        fclose(f_out);

                        rc = SUCCESS;
                    }
                    else
                    {
                        printf("\nНет доступного графа!\n");
                        rc = ERR_NO_GRAPH;
                    }
                    break;
                }
            case 0:
                {
                    printf("\nЗаверешение программы!\n");
                    break;
                }
            }
        }

    }

    graph_free(cur_graph);

    return rc;
}
