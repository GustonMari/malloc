#include "../include/memory.h"

void    init()
{
    // Initialize the head of the linked list
    // head = sbrk(0);
    head->size = 20000 - META_SIZE;
    // head->size = 0;
    head->next = NULL;
    head->free = false;
}

// ? Making a way for a new block allocation by splitting a free block (assume first fit algorithm)
void    split_memory(struct block_meta *block, size_t size)
{
    // Split the memory into two blocks
    struct block_meta *new_block = (void *)((void *)block + META_SIZE + size);
    new_block->size = block->size - size - META_SIZE;
    new_block->next = block->next;
    new_block->free = true;
    block->size = size;
    block->next = new_block;
    block->free = false;
}

void    *malloc(size_t size)
{
    struct block_meta *prev, *current;
    void *result;
    if (head->size == 0)
        init();
        write(1,"Initialize Memory\n",strlen("Initialize Memory\n"));
    // ? First fit algorithm
    current = head;
    //check 
    while (((current->size < size) || (current->free == false)) && (current->next != NULL))
    {
        prev = current;
        current = current->next;
        write(1,"Check\n",strlen("Check\n"));
    }
	// ! case 3
    // if there is a memory chunk that fits perfectly the required size.
    if ((current->size) == size)
    {
        current->free = false;
        result = (void *)(current + 1);
        write(1, "Perfect size\n", strlen("Perfect size\n"));
        return result;
    }
	// ! case 2
    // if there is a memory chunk that fits the required size but it is bigger than the required size.
    else if ((current->size) > (size + META_SIZE))
    {
        split_memory(current, size);
        result = (void *)(current + 1);
        write(1, "Split\n", strlen("Split\n"));
        return result;
    }
    else
    {
		// TODO need to make case 1 and 4
        // There can be a situation where you have consecutive blocks that are set free by deallocating after they were previously allocated. 
        // This results in external fragmentation which will cause the MyMalloc() function to return a NULL pointer although we have enough memory to allocate.
        result = NULL;
		// TODO: we need to go to the furthermost to the right of the heap, then create a new block that is right after the last block.
        write(1, "No memory\n", strlen("No memory\n"));
        return result;
    }
}

//? we use a function called merge() to join the consecutive free blocks by removing the metadata blocks lying in between.
void    merge(struct block_meta *block)
{
    struct block_meta *current, *prev;
    current = head;
    while (current->next != NULL)
    {
        if ((current->free == true) && (current->next->free == true))
        {
            current->size += (current->next->size) + META_SIZE;
            current->next = current->next->next;
        }
        prev = current;
        current = current->next;
    }
}

void    free(void *ptr)
{
    struct block_meta *current = ptr;
    current--;
    current->free = true;
    merge(current);


    // struct block_meta *current;
    // if (((void *)head <= ptr) && (ptr <= (void *)(head + 1)))
    // {
    //     head->free = true;
    //     merge(head);
    //     return ;
    // }
    // current = head;
    // while (current->next != NULL)
    // {
    //     if (((void *)current->next <= ptr) && (ptr <= (void *)(current->next + 1)))
    //     {
    //         current->next->free = true;
    //         merge(current->next);
    //         return ;
    //     }
    //     current = current->next;
    // }
    // return ;
}