#include "../inc/stack.h"

node_stack_t *node_stack_create(char *data)
{
    node_stack_t *tmp = malloc(sizeof(node_stack_t));

    char *str = malloc(sizeof(data) + 1);
    strcpy(str, data);

    if (tmp)
    {
        tmp->data = str;
        tmp->next = NULL;
    }

    return tmp;
}

node_stack_t *stack_push(node_stack_t *head, node_stack_t *tmp)
{
    node_stack_t *cur = head;

    if (head)
    {
        for (; cur->next; cur = cur->next);

        cur->next = tmp;

        return head;
    }
    else
        return tmp;
}

int stack_is_empty(node_stack_t *head)
{
    return (head) ? SUCCESS : STACK_EMPTY;
}

char *stack_pop(node_stack_t **head)
{
    node_stack_t *cur = *head, *prev  = NULL;
    char *data;

    while (cur->next)
    {
        prev = cur;
        cur = cur->next;
    }
    
    data = cur->data;

    if (prev)
        prev->next = NULL;

    if ((void *)*head == (void *)cur)
    {
        free(*head);
        *head = NULL;
    }
    else
    {
        free(cur);
        cur = NULL;
    }

    return data;
}

void stack_free(node_stack_t *head)
{
    node_stack_t *cur = head;

    for (; head; head = cur)
    {
        cur = cur->next;
        
        free(head->data);
        free(head);
        head = NULL;
    }
}

// void stack_print(node_stack_t *head)
// {
//     for (; head; head = head->next)
//         printf("%s\n", head->data);
//     printf("\n");
// }

char *stack_top(node_stack_t *head)
{
    for (; head->next; head = head->next);

    return head->data;
}

// int len(node_stack_t *head)
// {
//     int i = 0;
//     while (head)
//     {
//         i += 1;
//         head = head->next;
//     }
//     return i;
// }

void conv_postfix(char *infix, char *postfix)
{
    node_stack_t *head = NULL, *tmp = NULL;

    char *delim = " ";
    char *infix_cur = strtok(infix, delim);
    char *ptr = NULL;

    while (infix_cur != NULL)
    {
        if (! strcmp(infix_cur, BRACE_OP))
        {
            tmp = node_stack_create(infix_cur);
            head = stack_push(head, tmp);
        }
        else if (! strcmp(infix_cur, BRACE_CL))
        {
            while (strcmp(stack_top(head), BRACE_OP) != 0)
            {
                ptr = stack_pop(&head);
                make_string(postfix, ptr);
                free(ptr);
            }
        
            ptr = stack_pop(&head);
            free(ptr);
        }
        else if (is_operand(infix_cur))
        {
            while (!stack_is_empty(head) && priority(infix_cur) >= priority(stack_top(head)))
            {
                ptr = stack_pop(&head);
                make_string(postfix, ptr);
                free(ptr);
            }

            tmp = node_stack_create(infix_cur);
            head = stack_push(head, tmp);
        }
        else
            make_string(postfix, infix_cur);
        
        infix_cur = strtok(NULL, delim);
    }
   
    while (!stack_is_empty(head))
    {
        ptr = stack_pop(&head);
        make_string(postfix, ptr);
        free(ptr);
    }
}

// int stack_calc(char *postfix)
// {
//     char copy_postfix[MAX_LEN];
    
//     size_t i = 0;
//     while (i < strlen(postfix))
//     {
//         copy_postfix[i] = postfix[i];
//         i++;
//     }

//     copy_postfix[i] = '\0';
    
//     char *delim = " ";
//     char *postfix_cur = strtok(copy_postfix, delim);

//     int left, right;
//     char *l_p = NULL, *r_p = NULL;
//     char res[20] = { '\0' };

//     node_stack_t *head = NULL, *tmp = NULL;

//     while (postfix_cur != NULL)
//     {
//         if (is_operand(postfix_cur))
//         {
//             r_p = stack_pop(&head);
//             l_p = stack_pop(&head);

//             left = atoi(l_p);
//             right = atoi(r_p);

//             free(l_p);
//             free(r_p);

//             sprintf(res, "%d", process(postfix_cur, left, right));

//             tmp = node_stack_create(res);
//         }
//         else
//             tmp = node_stack_create(postfix_cur);
    
//         head = stack_push(head, tmp);  
        
//         postfix_cur = strtok(NULL, delim);
//     }

//     l_p = stack_pop(&head);

//     left = atoi(l_p);

//     free(l_p); 

//     return left;
// }
