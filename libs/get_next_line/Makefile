CC = cc
CFLAGS = -Wall -Wextra -Werror

LIB_SRCS = get_next_line_bonus.c get_next_line_utils_bonus.c

HEADERS_DIR = includes
PARENT_DIR = ..

LIB_HEADER = $(PARENT_DIR)/$(HEADERS_DIR)/get_next_line.h
LIB_HEADER_DIR = $(PARENT_DIR)/$(HEADERS_DIR)

LIB_OBJS = $(LIB_SRCS:.c=.o)

NAME = $(PARENT_DIR)/libgnl.a

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIB_OBJS)
	ar rc $@ $(LIB_OBJS)

%.o: %.c $(LIB_HEADER)
	$(CC) $(CFLAGS) -I $(LIB_HEADER_DIR) -c $< -o $@ 

clean:
	rm -f $(LIB_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
