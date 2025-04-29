# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rhonda <rhonda@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/29 20:00:57 by rhonda            #+#    #+#              #
#    Updated: 2025/04/29 21:55:06 by rhonda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = ./mlx_linux/
MLX = ./mlx_linux/libmlx_Linux.a

SRCS = main.c \

OBJS = $(SRCS:.c=.o) $(LIBFT) $(MLX)

%.o: %.c
	$(CC) $(CFLAGS) -Iincludes -I/usr/include -O3 -c $< -o $@

all: $(NAME)

$(NAME): init_mlx $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

init_mlx:
	if [ ! -d $(MLX_DIR).git ]; then \
		git submodule update --init --recursive $(MLX_DIR); \
	fi

clean:
	$(RM) $(OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME) $(LIBFT)

re: fclean all

.PHONY: all clean fclean re init_mlx