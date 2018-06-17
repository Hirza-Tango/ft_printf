NAME=libftprintf.a
CC=gcc
CFLAGS=-c -Wall -Wextra -Werror -I. -Ofast -g
CFILES=ft_getstr.c ft_helpers.c ft_printf.c ft_putarg.c

OBJ=$(CFILES:%.c=build/%.o)

$(NAME): $(OBJ) libft/libft.a
	@cp libft/libft.a $(NAME)
	@ar rcs $(NAME) $(OBJ) libft/libft.a

libft/libft.a:
	@make -C libft/

build/%.o: %.c ft_printf.h
	@mkdir -p build
	@$(CC) $(CFLAGS) $< -o $@

all: $(NAME);

clean:
	@rm -rf build/
	@make -C libft clean
 
fclean: clean
	@rm -rf $(NAME)
	@make -C libft fclean

re: fclean all

.PHONY: clean fclean re all