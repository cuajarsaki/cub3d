/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 01:24:01 by rhonda            #+#    #+#             */
/*   Updated: 2025/06/01 17:25:48 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	destroy_handler(t_game *game)
{
	clean_exit(game, SUCCESS);
	return (0);
}

int	key_handler(int key, t_game *game)
{
	int	x;
	int	y;

	if (!game->player || !game->player->pos)
		return (0);
	printf("key pressed: %d\n", key);
	x = (int)game->player->pos->x;
	y = (int)game->player->pos->y;
	if (key == KEY_ESC)
		destroy_handler(game);
	if (key == KEY_W && y > 0 && game->map->grid[y - 1][x] != '1')
		game->player->pos->y -= 1;
	if (key == KEY_A && x > 0 && game->map->grid[y][x - 1] != '1')
		game->player->pos->x -= 1;
	if (key == KEY_S && y + 1 < game->map->height && game->map->grid[y + 1][x] != '1')
		game->player->pos->y += 1;
	if (key == KEY_D && x + 1 < game->map->width && game->map->grid[y][x + 1] != '1')
		game->player->pos->x += 1;
	if (key == KEY_LEFT)
	{
		// 回転行列の公式
		double	oldDirX = game->player->dir->x;
		game->player->dir->x = oldDirX * cos(ROTATION_SPEED) - game->player->dir->y * sin(ROTATION_SPEED);
		game->player->dir->y = oldDirX * sin(ROTATION_SPEED) + game->player->dir->y * cos(ROTATION_SPEED);
		double	oldPlaneX = game->player->plane->x;
		game->player->plane->x = oldPlaneX * cos(ROTATION_SPEED) - game->player->dir->y * sin(ROTATION_SPEED);
		game->player->plane->y = oldPlaneX * sin(ROTATION_SPEED) + game->player->dir->x * cos(ROTATION_SPEED);
	}
	if (key == KEY_RIGHT)
	{
		// 回転行列の公式
		double	oldDirX = game->player->dir->x;
		game->player->dir->x = oldDirX * cos(-ROTATION_SPEED) - game->player->dir->y * sin(-ROTATION_SPEED);
		game->player->dir->y = oldDirX * sin(-ROTATION_SPEED) + game->player->dir->y * cos(-ROTATION_SPEED);
		double	oldPlaneX = game->player->plane->x;
		game->player->plane->x = oldPlaneX * cos(-ROTATION_SPEED) - game->player->dir->y * sin(-ROTATION_SPEED);
		game->player->plane->y = oldPlaneX * sin(-ROTATION_SPEED) + game->player->dir->x * cos(-ROTATION_SPEED);
	}
	return (0);
}

void	register_hook(t_game *game)
{
	mlx_hook(game->mlx->win_ptr, ON_DESTROY, BUTTON_PRESS_MASK, destroy_handler, game);
	mlx_hook(game->mlx->win_ptr, ON_KEYDOWN, KEY_PRESS_MASK, key_handler, game);
	mlx_loop_hook(game->mlx->mlx_ptr, render, game);
}

/** （参考）　回転行列
 * 
 *  ベクトル dir(x, y) を左方向（反時計回り）に θ度 回転させるとき、回転後のベクトル dir(newX, newY) は、
 * 
 * 　　newX = x * cosθ - y * sinθ
 * 　　newY = x * sinθ + y * cosθ
 * 
 *  で表される
 * */
