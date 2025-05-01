# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pchung <pchung@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/29 20:00:57 by rhonda            #+#    #+#              #
#    Updated: 2025/05/01 17:41:04 by pchung           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cube3D

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = mlx_linux
MLX = $(MLX_DIR)/libmlx.a

SRCS = main.c
OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -Iincludes -I/usr/include -O3 -c $< -o $@

all: $(NAME)

$(NAME): init_mlx $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -L$(MLX_DIR) -lmlx -L/usr/lib -I$(MLX_DIR) -lXext -lX11 -lm -lz -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# MLXライブラリのビルドルール
$(MLX):
	cd $(MLX_DIR) && ./configure && make -f makefile.gen

# MLXのgitサブモジュールを初期化するルール
init_mlx:
	git submodule update --init --recursive

clean:
	$(RM) $(OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLX_DIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)

re: fclean all

.PHONY: all clean fclean re init_mlx