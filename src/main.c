# include "../include/memory.h"

int main(void)
{
    char *str = malloc(50);
    char *str2 = malloc(50);
    str = "Hello World";
    // printf("str string = %s\n", str);
    // printf("str *p = %p\n", str);
    str2 = "no mais allo quoi";
    // printf("str2 string = %s\n", str2);
    // printf("str2 *p = %p\n", str2);
    print_memory(0);
    print_memory(1);
    print_memory(2);
    print_memory(3);

    return 0;
}