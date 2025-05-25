/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 13:04:39 by rhonda            #+#    #+#             */
/*   Updated: 2025/05/25 13:13:12 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_mlx_window(t_game *game)
{
	game->mlx->mlx_ptr = mlx_init();
	if (!game->mlx->mlx_ptr)
		clean_exit(game, err_msg("mlx", ERR_MLX_START, 1));
	game->mlx->win_ptr = mlx_new_window(game->mlx->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (!game->mlx->win_ptr)
		clean_exit(game, err_msg("mlx", ERR_MLX_WIN, 1));
}
