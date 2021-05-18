#include <stdio.h>
#include <stdlib.h>
#include "requests.h"

Request *newRequest(int initial_block, int blocks_qtd, char mode)
{
    Request *temp = (Request *)malloc(sizeof(Request));
    if (temp == NULL)
        return NULL;

    temp->initial_block = initial_block;
    temp->blocks_qtd = blocks_qtd;
    temp->mode = mode;
    temp->next = NULL;

    return temp;
}

void show(Request **head)
{
    Request *tmp = (*head);
    while (tmp->next != NULL)
    {
        printf("%d %d %c\n", tmp->initial_block, tmp->blocks_qtd, tmp->mode);
        tmp = tmp->next;
    }
    printf("%d %d %c\n", tmp->initial_block, tmp->blocks_qtd, tmp->mode);
}

void pop(Request **head)
{
    Request *temp = *head;
    (*head) = (*head)->next;
    free(temp);
}

Request *push(Request **head, int initial_block, int blocks_qtd, char mode)
{
    Request *new_element = newRequest(initial_block, blocks_qtd, mode);

    if (isEmpty(head))
    {
        build(head, &new_element);
        return *head;
    }
    while (merge(head))
        ;

    Request *atual_element = (*head);

    if ((*head)->initial_block > initial_block)
    {
        new_element->next = atual_element;
        (*head) = new_element;
    }
    else
    {
        while (atual_element->next != NULL && atual_element->next->initial_block < initial_block)
            atual_element = atual_element->next;

        Request *tmp = atual_element->next;
        atual_element->next = new_element;
        new_element->next = tmp;
    }

    return (*head);
}

int merge(Request **head)
{
    Request *atual_element = (*head);
    int flag = 0;
    while (atual_element->next != NULL)
    {
        if (atual_element->initial_block + atual_element->blocks_qtd >= atual_element->next->initial_block &&
            atual_element->mode == atual_element->next->mode)
        {
            Request *tmp = atual_element->next;
            int inital_block_distance = tmp->initial_block - atual_element->initial_block;
            int max_atual_range = atual_element->initial_block + (atual_element->blocks_qtd - inital_block_distance);
            int new_blocks_qtd = tmp->initial_block + tmp->blocks_qtd - atual_element->initial_block;
            if (new_blocks_qtd <= 64)
            {
                atual_element->next = tmp->next;
                atual_element->blocks_qtd = new_blocks_qtd;
                free(tmp);
                flag = 1;
            }
            else
            {
                atual_element = atual_element->next;
            }
        }
        else
        {
            atual_element = atual_element->next;
        }
    }
    return flag;
}

int isEmpty(Request **head)
{
    return (*head) == NULL;
}

int build(Request **head, Request **element)
{
    (*head) = (*element);
    return (element != NULL) ? 1 : 0;
}