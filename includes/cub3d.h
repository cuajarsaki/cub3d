
#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line.h"
# include "../mlx_linux/mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include <sys/time.h>
# include <stdbool.h>
# include <errno.h>
// # include <X11/keysym.h>

/* 定数定義 */
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
# define MOVE_SPEED 0.05
# define ROTATION_SPEED 0.3
# define FOV 0.9

/* キー定義 */
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

/* Event */
# define ON_DESTROY 17
# define ON_KEYDOWN 2

/* Event Mast */
# define BUTTON_PRESS_MASK (1L << 2)
# define KEY_PRESS_MASK (1L << 0)

/* Error Message */
# define ERR_USAGE "usage: ./cub3D <path_to_map.cub>"
# define ERR_FILE_IS_DIR "Is a directory"
# define ERR_FILE_NOT_CUB "Not a .cub file"
# define ERR_FILE_NOT_XPM "Not a .xpm file"
# define ERR_MALLOC "Could not allocate memory"
# define ERR_TEX_INVAILD "Invalid texture"
# define ERR_FLOOR_CEILING "Invalid RGB color"
# define ERR_INVALID_MAP "Wrong or incomplete map"
# define ERR_TEX_MISSING "Missing texture"
# define ERR_COLOR_MISSING "Missing color"
# define ERR_TEX_RGB_VAL "Invalid RGB value (0-255)"
# define ERR_MAP_MISSING "Missing map"
# define ERR_MAP_NO_CLOSED "Map is not closed by walls"
# define ERR_MAP_TOO_SMALL "Map is too small"
# define ERR_INV_CHAR "Invalid character in map"
# define ERR_NUM_PLAYER "Invalid num of player"
# define ERR_PLAYER_DIR "Map has no player position (N, S, E, W)"
# define ERR_PLAYER_POS "Invalid player position"
# define ERR_MAP_END "Map is not at the end of the file"
# define ERR_MLX_START "Could not start mlx"
# define ERR_MLX_WIN "Could not create mlx window"

/* return code */
# define SUCCESS 0
# define FAILURE 1
# define ERR 2
# define BREAK 3
# define CONTINUE 4

/* file type */
# define CUB 0
# define XPM 1

/* direction code */
# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

/* side in DDA */
# define X 0
# define Y 1

/* 構造体定義 */
typedef struct s_vector {
    double x;
    double y;
} t_vector;

typedef struct s_texinfo {
    char *path;
    void *img;
    char *data;
    int width;
    int height;
    int bpp;
    int size_line;
    int endian;
} t_texinfo;

typedef struct s_player {
    t_vector *pos;
    t_vector *dir;
    t_vector *plane;
    double move_speed;
    double rot_speed;
} t_player;

typedef struct s_ray {
    t_vector dir;
    t_vector side_dist;
    t_vector delta_dist;
    double perp_wall_dist;
    int map_x;
    int map_y;
    int step_x;
    int step_y;
    int hit;
    int side;
    int line_height;
    int draw_start;
    int draw_end;
    int tex_x;
} t_ray;

typedef struct s_map {
    char 			**grid;
    int 			width;
    int 			height;
    int 			*floor_color;
    int 			*ceiling_color;
	unsigned int	floor_hex;
	unsigned int	ceiling_hex;
	char			start_dir;
} t_map;

typedef struct s_mlx {
    void *mlx_ptr;
    void *win_ptr;
    void *img_ptr;
    char *img_data;
    int bpp;
    int size_line;
    int endian;
} t_mlx;

typedef struct s_game {
    t_mlx *mlx;
    t_map *map;
    t_player *player;
    t_texinfo textures[4];
    int keys[256];
	char **content;
	char *cubfile_name;
} t_game;

/* プロトタイプ宣言 */
// init
void	init_game(t_game *game, char *cubfile_name);
void	init_mlx_window(t_game *game);

// parse
int 	parse_args(t_game *game, char **argv);
int		check_file_type(char *file, int file_type);
void	parse_game(t_game *game, char *file);
int		get_file_data(t_game *game, char **content);
int		get_color_texture(t_game *game, t_map *map, char *line, int j);
int		get_map(t_game *game, char **content, int i);
int		check_textures_validity(t_game *game, t_texinfo *textures, t_map *map);
int		check_map_validity(t_game *game, t_map *map);
int		check_map_borders(t_map *map, char **grid);
int		check_player_surround(t_game *game, char **grid);

// render
int	render(t_game *game);
int	init_player_direction(t_game *game);

// input
void	register_hook(t_game *game);

// cleanup
int		free_game(t_game *game);
void	free_tab(void **tab);

// utils
int 	err_msg(char *detail, char *msg, int code);
int		err_msg_int(int detail, char *msg, int code);
void	clean_exit(t_game *game, int code);

// debug
void	print_tab(char **content);

#endif