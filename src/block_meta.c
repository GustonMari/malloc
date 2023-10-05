#include "../include/memory.h"

void    init_meta(chunck_memory *memory, size_t size)
{
    memory->meta = (struct block_meta *)((char *)memory + sizeof(struct chunck_memory));
    memory->meta->size = size;
    memory->meta->next = NULL;
    memory->meta->free = true;
}

// void    *init_meta(void *)
// {
//     memory->meta = (struct Node *)((char *)memory + sizeof(struct Memory));
//     memory->meta->size = newSize;
//     memory->meta->next = NULL;
//     memory->meta->free = true;
// }

// block_meta  *add_meta(size_t size)
// {
//     block_meta *meta;


//     return meta;
// }