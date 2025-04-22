
CC = gcc
CFLAGS = -Wall -Wextra -Werror
MLXFLAGS = -lmlx -lXext -lX11 -lm

SRC_DIR = srcs
INC_DIR = includes
OBJ_DIR = objs
LIBFT_DIR = libft

SRC_FILES = $(wildcard $(SRC_DIR)/**/*.c) $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
MAIN_SRC = main.c
MAIN_OBJ = $(OBJ_DIR)/main.o

NAME = cub3D

LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -I$(INC_DIR) -I$(LIBFT_DIR)

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/Canvas
	mkdir -p $(OBJ_DIR)/Casting
	mkdir -p $(OBJ_DIR)/Checker
	mkdir -p $(OBJ_DIR)/Keys
	mkdir -p $(OBJ_DIR)/Map
	mkdir -p $(OBJ_DIR)/Player
	mkdir -p $(OBJ_DIR)/Sprites
	mkdir -p $(OBJ_DIR)/Utils

$(MAIN_OBJ): $(MAIN_SRC) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJ_DIR) $(MAIN_OBJ) $(OBJ_FILES)
	$(CC) $(CFLAGS) $(MAIN_OBJ) $(OBJ_FILES) $(LIBFT) $(MLXFLAGS) -o $(NAME)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus