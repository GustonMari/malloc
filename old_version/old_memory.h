# ifndef MEMORY_H
# 	define MEMORY_H
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <string.h>
# include <stddef.h>
# include <sys/mman.h>
# include <sys/time.h>
# include <sys/resource.h>
# define META_SIZE sizeof(block_meta)
# define CHUNK_SIZE sizeof(chunck_memory)

char memory[20000];

typedef struct block_meta
{
    size_t size;
    struct block_meta *next;
    bool free;
} block_meta;


block_meta *head = (void *)memory;


void init();
void split_memory(struct block_meta *block, size_t size);
void *malloc(size_t size);
void merge_memory(size_t noOfBytes);
void free(void *ptr);

# endif