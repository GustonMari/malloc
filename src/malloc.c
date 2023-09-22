#include "../include/memory.h"

void init()
{
    // Initialize the head of the linked list
    // head = sbrk(0);
    head->size = 20000 - META_SIZE;
    // head->size = 0;
    head->next = NULL;
    head->free = false;
}

// ? Making a way for a new block allocation by splitting a free block (assume first fit algorithm)
void split_memory(struct block_meta *block, size_t size)
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

void *malloc(size_t size)
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

    // if there is a memory chunk that fits perfectly the required size.
    if ((current->size) == size)
    {
        current->free = false;
        result = (void *)(current + 1);
        write(1, "Perfect size\n", strlen("Perfect size\n"));
        return result;
    }
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
    }



    // // Initialize the head of the linked list
    // if (head->size == 0)
    //     init();
    // // ? First fit algorithm
    // struct block_meta *current = head;
    // while (current)
    // {
    //     if (current->free && current->size >= size)
    //     {
    //         // ? Split the memory into two blocks
    //         if (current->size > size + META_SIZE)
    //             split_memory(current, size);
    //         current->free = false;
    //         return (void *)(current + 1);
    //     }
    //     current = current->next;
    // }
    // return NULL;
}



