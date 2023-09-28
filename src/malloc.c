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

void    *push_back(size_t size, int index)
{
    chunck_memory *tmp = head[index];
    chunck_memory *new = NULL;
	size_t new_size = 1;
    if (tmp == NULL)
    {
		COLOR(BYEL, "Head is empty");
        head[index] = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        head[index]->size = 1;
        head[index]->head = NULL;
        head[index]->next = NULL;
        head[index]->free = true;
        return head[index];
    }
    while (tmp->next != NULL)
    {
		ft_putstr_fd("iterator\n", 1);
        tmp = tmp->next;
		new_size += 1;
    }
	ft_putstr_fd("push_back\n", 1);
    new = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    new->size = new_size + 1;
    new->head = NULL;
    new->next = NULL;
    new->free = true;
    tmp->next = new;
    return new;
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
    int ret = -1;
    void *result = NULL;

	ret = define_size(size);
	if (size <= SMALL)
	{
		//! TODO: really need to uncomment the * 100
		result = push_back(ret/*  * 100 */, define_index(ret));
	}
	else
		result = push_back(size, define_index(ret));
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
            ft_putstr_fd("Need to push back into the actual chunck\n", 1);
			result = push_back(size, define_index(size));
            return result;
        }
    }
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
