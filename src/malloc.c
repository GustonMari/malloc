#include "../include/memory.h"

// @return -1 if the head is not empty or return the good category of chunk size
int   head_is_empty(size)
{
    if (head == NULL)
    {
        if (size <= TINY && head[0]->size != 0)
            return (TINY);
        else if (size > TINY && size <= SMALL && head[1]->size != 0)
            return (SMALL);
        else if (size > SMALL && head[2]->size != 0)
            return (LARGE);
    }
    return -1;
}

void    *search_memory(size_t size)
{
    int ret = -1;

    if ((ret = head_is_empty(size)) != -1)
        if (ret <= SMALL)
            mmap(NULL, ret * 100, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        else
            mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
}

void    *malloc(size_t size)
{
    void *result;
    if (size <= 0)
        return NULL;
    
    if (size <= TINY)
    {
        search_memory(size);
    }
    else if (size > TINY && size <= SMALL)
    {
        // search_memory(size);
        //! search for memory but chunk will be different size (4096) ??
    }
    else
    {
        write(1, "LARGE\n", 6);
        //! allocate directly memory for the good size
    }


}
