CC = cc
CFLAGS = -Wall -Wextra -Werror

LIB_SRCS = ft_printf.c
UTILS_SRCS = _c_char.c _d_dec.c _i_int.c _other.c _p_pt.c _s_str.c _u_u_dec.c _x_hex.c switch.c

UTILS_DIR = utils

HEADERS_DIR = includes
PARENT_DIR = ..

LIB_HEADER = $(PARENT_DIR)/$(HEADERS_DIR)/ft_printf.h
LIB_HEADER_DIR = $(PARENT_DIR)/$(HEADERS_DIR)

LIB_OBJS = $(LIB_SRCS:.c=.o)
UTILS_OBJS = $(addprefix $(UTILS_DIR)/,$(UTILS_SRCS:.c=.o))
TARGET_OBJS = $(LIB_OBJS) $(UTILS_OBJS)

NAME = $(PARENT_DIR)/libftprintf.a

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(TARGET_OBJS)
	ar rc $@ $(TARGET_OBJS)

%.o: %.c $(LIB_HEADER)
	$(CC) $(CFLAGS) -I $(LIB_HEADER_DIR) -c $< -o $@ 

clean:
	rm -f $(LIB_OBJS) $(UTILS_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
