# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rhonda <rhonda@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/29 20:00:57 by rhonda            #+#    #+#              #
#    Updated: 2025/05/02 01:10:41 by rhonda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = ./mlx_linux
MLX = $(MLX_DIR)/libmlx.a

SRCS = main.c
OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -Iincludes -I/usr/include -O3 -c $< -o $@

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -L$(MLX_DIR) -lmlx -L/usr/lib -I$(MLX_DIR) -lXext -lX11 -lm -lz -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@echo "==> Ensuring submodule '$(MLX_DIR)' is fully initialized..."
	@if [ ! -f "$(MLX_DIR)/Makefile.gen" ]; then \
		if [ -d ".git/modules/$(MLX_DIR)" ]; then \
			echo "==> Cleaning stale Git module directory..."; \
			rm -rf .git/modules/$(MLX_DIR); \
		fi; \
		if ! git config -f .gitmodules --get submodule.$(MLX_DIR).url > /dev/null; then \
			echo "==> Registering submodule for $(MLX_DIR)"; \
			git submodule add https://github.com/42paris/minilibx-linux.git $(MLX_DIR); \
		fi; \
		git submodule init; \
		git submodule update --recursive; \
	fi && \
	cd $(MLX_DIR) && ./configure && make -f makefile.gen

clean:
	$(RM) $(OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLX_DIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)  
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re init_mlx