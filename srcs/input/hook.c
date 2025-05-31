/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 01:24:01 by rhonda            #+#    #+#             */
/*   Updated: 2025/05/31 23:20:12 by rhonda           ###   ########.fr       */
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
	// if (key == KEY_LEFT)
	// 	// todo
	// if (key == KEY_RIGHT)
	// 	// todo
	return (0);
}

void	register_hook(t_game *game)
{
	mlx_hook(game->mlx->win_ptr, ON_DESTROY, BUTTON_PRESS_MASK, destroy_handler, game);
	mlx_hook(game->mlx->win_ptr, ON_KEYDOWN, KEY_PRESS_MASK, key_handler, game);
	mlx_loop_hook(game->mlx->mlx_ptr, render, game);
}
