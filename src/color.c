#include "../include/memory.h"

void __print_color(char * color, char *str)
{
	write(1, color, strlen(color));
	write(1, str, strlen(str));
	write(1, CRESET, strlen(CRESET));
	write(1, "\n", 1);
}