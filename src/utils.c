# include "../include/memory.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s || !fd)
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	long	nbr;

	nbr = n;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		nbr *= -1;
	}
	if (nbr >= 10)
		ft_putnbr_fd((nbr / 10), fd);
	ft_putchar_fd(nbr % 10 + '0', fd);
}

void printAddress(void *addr)
{
    char hexChars[] = "0123456789abcdef";
    char addressBuffer[16]; // Assuming 64-bit address space

    long unsigned int i;
    for (i = 0; i < sizeof(void *) * 2; i++) {
        addressBuffer[i] = hexChars[((uintptr_t)addr >> ((sizeof(void *) * 2 - i - 1) * 4)) & 0xF];
    }
    addressBuffer[i] = '\0';

    write(STDOUT_FILENO, addressBuffer, sizeof(void *) * 2);
}