# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rhonda <rhonda@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/29 20:00:57 by rhonda            #+#    #+#              #
#    Updated: 2025/05/31 16:42:08 by rhonda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a \
	$(LIBFT_DIR)/libgnl.a		## todo: lobprintf.a入れる

MLX_DIR = ./mlx_linux
MLX = $(MLX_DIR)/libmlx.a

SRCS = main.c \
	srcs/cleanup/free.c \
	srcs/init/init_game.c \
	srcs/init/init_mlx_info.c \
	srcs/input/hook.c \
	srcs/parse/check_file_type.c \
	srcs/parse/parse_args.c \
	srcs/parse/parse_game.c \
	srcs/parse/get_file_data.c \
	srcs/parse/get_color_texture.c \
	srcs/parse/get_map.c \
	srcs/parse/check_textures_validity.c \
	srcs/parse/check_map_validity.c \
	srcs/parse/check_map_borders.c \
	srcs/parse/check_player_surround.c \
	srcs/render/render.c \
	srcs/utils/error.c \
	srcs/utils/exit.c 
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
			echo "==> Cleaning stale Git module dir .git/modules/$(MLX_DIR)"; \
			rm -rf .git/modules/$(MLX_DIR); \
		fi; \
		if git ls-files --error-unmatch $(MLX_DIR) > /dev/null 2>&1; then \
			echo "==> Cleaning submodule entry from Git index"; \
			git rm --cached -f $(MLX_DIR); \
		fi; \
		if ! git config -f .gitmodules --get submodule.$(MLX_DIR).url > /dev/null 2>&1; then \
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