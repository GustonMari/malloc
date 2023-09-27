#include "../include/memory.h"

// Divided in 3 types of chuncks aka TINY, SMALL, LARGE
chunck_memory *head[3] = {NULL, NULL, NULL};

int     define_index(size_t size)
{
    if (size <= TINY)
        return 0;
    else if (size > TINY && size <= SMALL)
        return 1;
    else if (size > SMALL)
        return 2;
    return -1;
}

void    *push_back(size_t size, int index)
{
    chunck_memory *tmp = head[index];
    chunck_memory *new = NULL;

    if (tmp == NULL)
    {
        printf("1");
        head[index] = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        head[index]->size = 0;
        head[index]->head = NULL;
        head[index]->next = NULL;
        head[index]->free = true;
        return head[index];
    }
    while (tmp->next != NULL)
    {

        printf("2");
        tmp = tmp->next;
    }
    new = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    new->size = 0;
    new->head = NULL;
    new->next = NULL;
    new->free = true;
    tmp->next = new;
    return new;
}

// @return -1 if the head is not empty or return the good category of chunk size
int     head_is_empty(size)
{
    if (size <= TINY && head[0] == NULL)
        return (TINY);
    else if (size > TINY && size <= SMALL && head[1] == NULL)
        return (SMALL);
    else if (size > SMALL && head[2] == NULL)
        return (LARGE);
    return -1;
}

void    *search_memory(size_t size)
{
    int ret = -1;
    void *result = NULL;

    if ((ret = head_is_empty(size)) != -1)
        if (ret <= SMALL)
            //! TODO: really need to uncomment the * 100
            result = push_back(ret/*  * 100 */, define_index(ret));
        else
            result = push_back(size, define_index(ret));
    else
    {

        printf("Chunck of the size %d is not empty\n", ret);
        // if (ret <= SMALL)
        //     //! TODO: really need to uncomment the * 100
        //     result = push_back(ret/*  * 100 */, define_index(ret));
        // else
        //     result = push_back(size, define_index(ret));
        //! search for a free block
    }
    return result;
}

void    *malloc(size_t size)
{
    void *result = NULL;

    if (size <= 0)
        return result;

    if (size <= SMALL)
    {
        result = search_memory(size);
        if (result == NULL)
        {
            printf("Need to push back into the actual chunck\n");
            return result;
        }
    }
    else
    {
        write(1, "LARGE\n", 6);
        //! allocate directly memory for the good size
    }
    return result;
}

void    print_memory(int index)
{
    if (index < 0 || index > 3)
    {
        printf("Wrong index to print\n");
    }
    else
    {
        printf("PRINT MEMORY");
        while (head[index] != NULL)
        {
            printf("\n-----------------\nIndex = %d\n\n", index);
            printf("size = %zu\n", head[index]->size);
            // printf(head[index]->head);
            // printf(head[index]->next);
            printf("free = %d\n", head[index]->free);
            printf("addr = %p\n", head[index]);
            head[index] = head[index]->next;
        }
    }
}
