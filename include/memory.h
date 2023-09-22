# ifndef MEMORY_H
# define MEMORY_H
# endif
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <string.h>
# include <stddef.h>
# define META_SIZE sizeof(struct block_meta)

char memory[20000];

struct block_meta
{
    size_t size;
    struct block_meta *next;
    bool free;
};

struct block_meta *head = (void *)memory;

void init();
void split_memory(struct block_meta *block, size_t size);
void *malloc(size_t size);
void merge_memory(size_t noOfBytes);
void free(void *ptr);