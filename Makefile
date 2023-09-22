CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread #-fsanitize=thread
SRC = actions.c \
			check.c \
			fk.c \
			ft_atoi.c \
			ft_check_thread.c \
			ft_clean.c \
			ft_print.c \
			philosophers.c \
			thread_manager.c \
			time.c \
			utils.c
OBJ = $(SRC:.c=.o)
NAME= philo

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

all: server
	@echo "\\n\033[32;1mMAKE ALL OK \033[0m \\n"
	@echo "\033[32;1m      ___           ___           ___           ___                  \033[0m"
	@echo "\033[32;1m     /\__\         /\  \         /\  \         /\  \                 \033[0m"
	@echo "\033[32;1m    /:/ _/_       |::\  \       /::\  \       /::\  \         ___    \033[0m"
	@echo "\033[32;1m   /:/ /\  \      |:|:\  \     /:/\:\  \     /:/\:\__\       /|  |   \033[0m"
	@echo "\033[32;1m  /:/ /::\  \   __|:|\:\  \   /:/ /::\  \   /:/ /:/  /      |:|  |   \033[0m"
	@echo "\033[32;1m /:/__\/\:\__\ /::::|_\:\__\ /:/_/:/\:\__\ /:/_/:/__/___    |:|  |   \033[0m"
	@echo "\033[32;1m \:\  \ /:/  / \:\~~\  \/__/ \:\/:/  \/__/ \:\/:::::/  /  __|:|__|   \033[0m"
	@echo "\033[32;1m  \:\  /:/  /   \:\  \        \::/__/       \::/~~/~~~~  /::::\  \   \033[0m"
	@echo "\033[32;1m   \:\/:/  /     \:\  \        \:\  \        \:\~~\      ~~~~\:\  \  \033[0m"
	@echo "\033[32;1m    \::/  /       \:\__\        \:\__\        \:\__\          \:\__\ \033[0m"
	@echo "\033[32;1m     \/__/         \/__/         \/__/         \/__/           \/__/ \033[0m"
	@echo "\\n"

server: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) 
	@echo "\\n\033[32;1mCOMPILATION OK \033[0m \\n"

%.o: %.c
	$(CC) $(CFLAGS) -c $< 

clean:
	@echo "\\n\033[38;5;202;1mDeleting Objects... \033[0m \\n"
	rm -rf $(OBJ)
	@echo "\\n\033[32;1mDeleting OK \033[0m \\n"

fclean: clean
	@echo "\\n\033[38;5;202;1mCLEANING ALL... \033[0m \\n"
	rm -rf $(NAME)
	@echo "\\n\033[32;1mOK \033[0m \\n"

re: fclean all

.PHONY: all clean fclean re libft server client

.SILENT: