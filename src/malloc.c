#include "../include/memory.h"

chunck_memory *head[3] = {NULL, NULL, NULL};
// bool start = true;

// void init_chunk_memory()
// {
//     for (int i = 0; i < 3; i++)
//     {
//         // head[i] = mmap(NULL, CHUNK_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
//         head[i]->size = 0;
//         head[i]->head = NULL;
//         head[i]->next = NULL;
//         head[i]->free = true;
//     }
// }

// @return -1 if the head is not empty or return the good category of chunk size
int   head_is_empty(size)
{
    // if (head == NULL)
    // {
        if (size <= TINY && head[0] == NULL)
            return (TINY);
        else if (size > TINY && size <= SMALL && head[1] == NULL)
            return (SMALL);
        else if (size > SMALL && head[2] == NULL)
            return (LARGE);
    // }
    return -1;
}

void    *search_memory(size_t size)
{
    int ret = -1;
    void *result = NULL;

    if ((ret = head_is_empty(size)) != -1)
        if (ret <= SMALL)
            result = mmap(NULL, ret * 100, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        else
            result = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    else
    {
        printf("Chunck of the size %d is not empty\n", ret);
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
        write(1, "TINY or SMALL\n", strlen("TINY or SMALL\n"));
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
