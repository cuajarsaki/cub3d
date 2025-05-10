/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 00:22:58 by rhonda            #+#    #+#             */
/*   Updated: 2025/05/10 19:42:58 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_mlx(t_game *game)
{
	game->mlx = malloc(sizeof(t_mlx));
	if (!game->mlx)
	{
		err_msg(NULL, ERR_MALLOC, 0);
		return ;
	}
    game->mlx->mlx_ptr = NULL;
    game->mlx->win_ptr = NULL;
    game->mlx->img_ptr = NULL; // todo: 何用の変数？
    game->mlx->img_data = NULL; // todo: 何用の変数？
    game->mlx->bpp = 32; // todo: 固定値で良い? 可変の場合どうやって取得する？
    game->mlx->size_line = 0; // todo: 何用の変数？
    game->mlx->endian = 0; // todo: 何用の変数？
}

void	init_map(t_game *game)
{
	game->map = malloc(sizeof(t_map));
	if (!game->map)
	{
		err_msg(NULL, ERR_MALLOC, 0);
		return ;
	}
    game->map->grid = NULL;
    game->map->width = 0;
    game->map->height = 0;
    game->map->floor_color = NULL;
    game->map->ceiling_color = NULL;
	game->map->floor_hex = 0xFFFFFFFF;
	game->map->ceiling_hex = 0xFFFFFFFF;
	game->map->start_dir = '0';
}

void	init_player(t_game *game)
{
	game->player = malloc(sizeof(t_player));
	if (!game->player)
	{
		err_msg(NULL, ERR_MALLOC, 0);
		return ;
	}
    game->player->pos = NULL; // todo: 固定値?可変値?
    game->player->dir = NULL; // todo: 固定値?可変値?
    game->player->plane = NULL; // todo: 固定値?可変値?
    game->player->move_speed = MOVE_SPEED;
    game->player->rot_speed = ROTATION_SPEED;
}

void	init_game(t_game *game, char *cubfile_name) //! todo: game構造体の中身はポインタにしない？ →一旦ポインタにした
{
    int i;

    init_mlx(game);
    init_map(game);
    init_player(game);
    ft_memset(game->textures, 0, sizeof(game->textures));
    i = 0;
    while (i < 256)
		game->keys[i++] = 0;
	game->content = NULL;
	game->cubfile_name = malloc(sizeof(char) * ft_strlen(cubfile_name));
	if (!game->cubfile_name)
	{
		err_msg(NULL, ERR_MALLOC, 0);
		return ;
	}
}
