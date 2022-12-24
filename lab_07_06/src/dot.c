#include "../inc/dot.h"

void tree_export_to_dot(node_tree_t *tree, FILE *f, char *name)
{
    fprintf(f, "digraph \"%s\" {\ngraph [ordering=\"out\"];\n", name);

    post_order(tree, node_to_dot, f, NULL);

    fprintf(f, "}\n");
}

void chained_table_export_to_dot(hash_table_t *table, FILE *f, char *name)
{
    int i, j;
    list_cell_t **list = table->cells, *cur = NULL;

    fprintf(f, "digraph \"%s\" {\nrankdir=LR;\nnode [shape=record,width=.1,height=.1];\n\n", name);

    for (i = 0; i <= table->max_size; i++)
    {
        
        if (i == 0)
        {
            fprintf(f, "node%d [label = \"", i);
            fprintf(f, "<f0> Хеш");

            for (j = 1; j <= table->max_size; j++)
                fprintf(f, "| <f%d> %d", j, j - 1);
            
            fprintf(f, "\"];\n");
        }
        else
        {
            if (list[i - 1])
            {
                cur = list[i - 1];
                j = (i + 1) * 10;
                fprintf(f, "node0:f%d -> node%d [arrowtail=dot, dir=both, tailclip=false];\n", i, j);

                while (cur->next)
                {
                    fprintf(f, "node%d [label = \"", j);
                    fprintf(f, "{<data> %d | <ref>}\"];\n", cur->key);

                    fprintf(f, "node%d:ref:node%d -> node%d:data [arrowtail=dot, dir=both, tailclip=false];\n", j, j + 1, j + 1);
                    cur = cur->next;
                    j++;
                }

                fprintf(f, "node%d [label = \"", j);
                fprintf(f, "{ %d }\"];\n", cur->key);
            }
        }
    }
   
    fprintf(f, "}\n");
}

void open_adr_table_export_to_dot(hash_table_t *table, FILE *f, char *name)
{
    int i, j;
    cell_t *cells = table->cells;

    fprintf(f, "digraph \"%s\" {\nrankdir=LR;\nnode [shape=record,width=.1,height=.1];\n\n", name);

    for (i = 0; i <= table->max_size; i++)
    {
        
        if (i == 0)
        {
            fprintf(f, "node%d [label = \"", i);
            fprintf(f, "<f0> Хеш");

            for (j = 1; j <= table->max_size; j++)
                fprintf(f, "| <f%d> %d", j, j - 1);
            
            fprintf(f, "\"];\n");
        }
        else
        {
            if (cells[i - 1].empty)
            {
                fprintf(f, "node%d [label = \"", i);
                fprintf(f, "{ %d }\"];\n", cells[i - 1].key);
                fprintf(f, "node0:f%d -> node%d [arrowtail=dot, dir=both, tailclip=false];\n", i, i);
            }
        }
    }
   
    fprintf(f, "}\n");
}

void node_to_dot(node_tree_t *tree, void *arg_1, void *arg_2)
{
    FILE *f = arg_1;

    if (tree->left && ! arg_2)
    {
        if (tree->operand == -1)
        {
            if (tree->left->operand == -1)
                fprintf(f, "\"%d\" -> \"%d\";\n", tree->value, tree->left->value);
            else  
                fprintf(f, "\"%d\" -> \"%c | %d\";\n", tree->value, tree->left->operand, tree->left->value); 
        }
        else
        {
            if (tree->left->operand == -1)
                fprintf(f, "\"%c | %d\"-> \"%d\";\n", tree->operand, tree->value, tree->left->value);
            else  
                fprintf(f, "\"%c | %d\" -> \"%c | %d\";\n", tree->operand, tree->value, tree->left->operand, tree->left->value); 
        }    
    } 

    if (tree->right)
    {
        if (tree->operand == -1)
        {
            if (tree->right->operand == -1)
                fprintf(f, "\"%d\" -> \"%d\";\n", tree->value, tree->right->value);
            else  
                fprintf(f, "\"%d\" -> \"%c | %d\";\n", tree->value, tree->right->operand, tree->right->value); 
        }
        else
        {
            if (tree->right->operand == -1)
                fprintf(f, "\"%c | %d\"-> \"%d\";\n", tree->operand, tree->value, tree->right->value);
            else  
                fprintf(f, "\"%c | %d\" -> \"%c | %d\";\n", tree->operand, tree->value, tree->right->operand, tree->right->value); 
        }    
    }
}