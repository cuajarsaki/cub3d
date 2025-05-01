
#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <string.h>
# include <sys/time.h>

/* 定数定義 */
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
# define MOVE_SPEED 0.05
# define ROTATION_SPEED 0.03
# define FOV 60

/* キー定義 */
# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124

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
    t_vector pos;
    t_vector dir;
    t_vector plane;
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
    char **grid;
    int width;
    int height;
    int floor_color;
    int ceiling_color;
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
    t_mlx mlx;
    t_map map;
    t_player player;
    t_texinfo textures[4];
    int keys[256];
} t_game;

#endif