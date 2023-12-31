# ifndef MEMORY_H
# 	define MEMORY_H
//! malloc is in stdlib.h
// # include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <string.h>
# include <stddef.h>
# include <sys/mman.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <errno.h>
# include <stdint.h>
# include "color.h"
# define META_SIZE sizeof(block_meta)
# define CHUNK_SIZE sizeof(chunck_memory)
# define TINY 256
# define SMALL 4096
# define LARGE 20000
// char memory[20000];

typedef struct block_meta
{
    size_t size;
    struct block_meta *next;
    bool free;
} block_meta;

// block_meta *head = (void *)memory;
typedef struct chunck_memory
{
    size_t size;
    block_meta *meta;
    struct chunck_memory *next;
    bool free;
} chunck_memory;

// chunck_memory *head[3] = {NULL, NULL, NULL};

// void init();
// void split_memory(struct block_meta *block, size_t size);
void *malloc(size_t size);
void    print_memory(int index);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void printAddress(void *addr);

//? =================== META ===================

void    init_meta(chunck_memory *memory, size_t size);

// void merge_memory(size_t noOfBytes);
// void free(void *ptr);

# endif