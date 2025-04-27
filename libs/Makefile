COMMON_DIR_NAME = common
PRINTF_DIR_NAME = ft_printf
GNL_DIR_NAME = get_next_line

ARCHIVE_LIBFT =libft.a 
ARCHIVE_PRINTF = libftprintf.a
ARCHIVE_GNL = libgnl.a

NAME = $(ARCHIVE_LIBFT) $(ARCHIVE_PRINTF) $(ARCHIVE_GNL)

.PHONY: all clean fclean re

all: 
	make -C $(COMMON_DIR_NAME) bonus
	make -C $(PRINTF_DIR_NAME)
	make -C $(GNL_DIR_NAME)

clean:
	make -C $(COMMON_DIR_NAME) clean
	make -C $(PRINTF_DIR_NAME) clean
	make -C $(GNL_DIR_NAME) clean

fclean: clean
	rm -f $(NAME)

re: fclean all
