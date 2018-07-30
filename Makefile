NAME=libftprintf.a
DEPS=libft/libft.a
LIBFT_DIR=..
INCLUDES=$(LIBFT_DIR)/includes
REL_DEPS=$(DEPS:%=$(LIBFT_DIR)/%)
CC=gcc
CFLAGS=-c -Wall -Wextra -Werror -I $(INCLUDES) -Ofast
CFILES=ft_getstr.c ft_printf.c ft_putarg.c padding.c

OBJ=$(CFILES:%.c=build/%.o)

$(NAME): $(OBJ) $(REL_DEPS)
	@ar rcs $(NAME) $(OBJ) $(REL_DEPS)

$(REL_DEPS):
	@make -C $(dir $@)

build/%.o: %.c
	echo $(INCLUDES)
	@mkdir -p build
	@$(CC) $(CFLAGS) $< -o $@

all: $(NAME);

clean fclean re::
	@for file in $(dir $(REL_DEPS)) ; do $(MAKE) -C $$file $@ ; done

clean::
	@rm -rf build/

fclean::
	@rm -rf $(NAME)

re:: fclean all

.PHONY: clean fclean re all