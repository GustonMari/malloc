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
	COLOR(BRED, "Something is wrong in define_index()");
    return -1;
}

size_t	define_size(size_t size)
{
	if (size <= TINY)
		return TINY;
	else if (size > TINY && size <= SMALL)
		return SMALL;
	else if (size > SMALL)
		return size;
	COLOR(BRED, "Something is wrong in define_size()");
	return -1;
}

void    *init_chunk(size_t index, size_t size)
{
    head[index] = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    head[index]->size = 1;
    head[index]->head = NULL;
    head[index]->next = NULL;
    head[index]->free = true;
    return head[index];
}

void    *add_chunk(size_t index, size_t size)
{
    chunck_memory *tmp = head[index];
    chunck_memory *new = NULL;
    size_t new_size = 1;

    while (tmp->next != NULL)
    {
        tmp = tmp->next;
        //! scan if there is space available
        new_size += 1;
    }
    new = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    new->size = new_size + 1;
    new->head = NULL;
    new->next = NULL;
    new->free = true;
    tmp->next = new;
    return new;
}

void    *push_back(size_t size)
{
    size_t ret = -1;
    size_t index = define_index(size);
    ret = define_size(size);

    if (size <= SMALL)
        size = ret /* * 100 */;

    if (head[index] == NULL)
    {
		COLOR(BYEL, "Head is empty");
        return init_chunk(index, size);
    }
    return add_chunk(index, size);
}

// @return -1 if the head is not empty or return the good category of chunk size
int     head_is_empty(size_t size)
{
    if (size <= TINY && head[0] == NULL)
        return (TINY);
    else if (size > TINY && size <= SMALL && head[1] == NULL)
        return (SMALL);
    else if (size > SMALL && head[2] == NULL)
        return (LARGE);
	// COLOR(BRED, "Something is wrong in head_is_empty()");
    return -1;
}

void    *search_memory(size_t size)
{
    void *result = NULL;

    result = push_back(size);
    return result;
}

void    *malloc(size_t size)
{
    void *result = NULL;

    if (size <= 0)
        return result;

    if (size <= SMALL)
        result = search_memory(size);
    else
    {
		ft_putstr_fd("LARGE\n", 1);
        //! allocate directly memory for the good size
    }
    return result;
}

void    print_memory(int index)
{
    if (index < 0 || index > 3)
    {
        ft_putstr_fd("Wrong index to print\n", 1);
    }
    else
    {
        COLOR(BHGRN, "PRINT MEMORY\n");

        while (head[index] != NULL)
        {
			ft_putstr_fd("\n-----------------\nIndex = ", 1);
            if (index == 0)
                ft_putstr_fd("TINY", 1);
            else if (index == 1)
                ft_putstr_fd("SMALL", 1);
            else if (index == 2)
                ft_putstr_fd("LARGE", 1);
			ft_putnbr_fd(index, 1);
			ft_putstr_fd("\n\nsize = ", 1);
			ft_putnbr_fd(head[index]->size, 1);
			ft_putstr_fd("\nfree = ", 1);
			ft_putnbr_fd((int)(head[index]->free), 1);
			ft_putstr_fd("\naddr = ", 1);
			printAddress(head[index]);
			ft_putstr_fd("\n", 1);
			ft_putstr_fd((char *)head[index], 1);
            head[index] = head[index]->next;
        }
    }
}
