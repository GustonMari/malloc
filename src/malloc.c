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

void split_memory(struct block_meta *block, size_t size)
{
    struct block_meta *new = NULL;

    //! take the current addr of the block and add the size of the block_meta
    new = (void *)((char *)block + META_SIZE + size);
    COLOR(BHGRN, "SPLIT MEMORY\n");
    new->size = block->size - size - META_SIZE;
    new->next = block->next;
    new->free = true;
    block->size = size;
    block->next = new;
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
    size_t round_size = define_size(size);
    head[index] = mmap(NULL, round_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    head[index]->size = round_size;
    head[index]->meta = NULL;
    head[index]->next = NULL;
    head[index]->free = true;
    init_meta(head[index], size);
    return head[index];
}

void    *add_chunk(size_t index, size_t size)
{
    chunck_memory *tmp = head[index];
    chunck_memory *new = NULL;
    size_t new_size = 1;
    size_t round_size = define_size(size);

    while (tmp->next != NULL)
    {
        tmp = tmp->next;
        //! scan if there is space available
        new_size += 1;
    }
    new = mmap(NULL, round_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    new->size = round_size;
    new->meta = (struct block_meta *)((char *)head[index] + sizeof(struct chunck_memory));
    new->meta->size = size;
    new->meta->next = NULL;
    new->meta->free = true;
    new->next = NULL;
    new->free = true;
    tmp->next = new;
    return new;
}

void    *search_free_space(size_t index, size_t size)
{
    chunck_memory *tmp = head[index];
    void *result = NULL;
    size_t occuped_size = 0;

    while (tmp != NULL)
    {
        //! if chunk is free and size is enough
        if (tmp->free == true && tmp->size >= size)
        {
            //! check if meta is free and size is enough
            if (tmp->meta->free == true && tmp->meta->size >= size)
            {
                while (tmp->meta->next != NULL)
                {
                    if (tmp->meta->free == true)
                    {
                        occuped_size += tmp->meta->size;
                        // result = tmp->meta;
                        // break ;
                    }
                    tmp->meta = tmp->meta->next;
                }
                if (occuped_size + sizeof(struct block_meta) + size <= tmp->size)
                    COLOR(BHGRN, "THERE IS SPACE\n");
                else
                    COLOR(BHRED, "THERE IS NO SPACE\n");
                ft_putnbr_fd(occuped_size, 1);
                ft_putstr_fd("\nstruct", 1);
                ft_putnbr_fd(sizeof(struct block_meta), 1);
                ft_putstr_fd("\nsize =", 1);
                ft_putnbr_fd(size, 1);
                ft_putstr_fd("\ntmp-.size =", 1);
                ft_putnbr_fd(tmp->size, 1);
                ft_putstr_fd("\n", 1);
       
            }
            result = tmp;
            break ;
        }
        tmp = tmp->next;
    }
    return result;
}

void    *add(size_t index, size_t size)
{
    void *result = NULL;
    
    search_free_space(index, size);
    result = add_chunk(index, size);
    return result;
    // ADD new chunck (add_chunk) or search for space in a chunck that have already space in it
}

void    *push_back(size_t size)
{
    size_t index = define_index(size);

    if (head[index] == NULL)
    {
		COLOR(BYEL, "Head is empty");
        return init_chunk(index, size);
    }
    return add(index, size);
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



void    *malloc(size_t size)
{
    void *result = NULL;

    if (size <= 0)
        return result;

    if (size <= SMALL)
        result = push_back(size);
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
