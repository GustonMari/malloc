# include "../include/memory.h"

void print_info_string(char *str)
{
	ft_putstr_fd("str string = ", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd("\nstr *p = ", 1);
	printAddress(str);
	ft_putstr_fd("\n", 1);

}

int main(void)
{
    char *str = malloc(50);
    char *str2 = malloc(50);
    // char *str3 = malloc(50);
    str = "Hello World";
    str2 = "no mais allo quoi";
	print_info_string(str);
	// print_info_string(str2);
	// print_info_string(str3);

    // print_memory(0);
    // print_memory(1);
    // print_memory(2);
    // print_memory(3);

    return 0;
}

