/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 02:44:56 by rhonda            #+#    #+#             */
/*   Updated: 2025/05/05 01:59:15 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_tab(void **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	if (tab)
	{
		free(tab);
		tab = NULL;
	}
}

static void	free_mlx(t_mlx *mlx)
{
	if (!mlx)
		return ;
	if (mlx->win_ptr && mlx->mlx_ptr)
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	if (mlx->mlx_ptr)
	{
		mlx_destroy_display(mlx->mlx_ptr);
		mlx_loop_end(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
	}
	// todo: img_ptr, img_data free
}

static void	free_map(t_map *map)
{
	if (!map)
		return ;
	if (map->grid)
		free_tab((void *)map->grid);
}

static void	free_player(t_player *player)
{
	if (!player)
		return ;
	if (player->pos)
		free(player->pos);
	if (player->dir)
		free(player->dir);
	if (player->plane)
		free(player->plane);
}

static void free_texinfo(t_texinfo *textures) // todo: あってる？
{
	int i;

	if (!textures)
		return ;
	i = 0;
	while (i < 4)
	{
		if (textures[i].path)
			free(textures[i].path);
		if (textures[i].img)
			free(textures[i].img);
		if (textures[i].data)
			free(textures[i].data);
		i++;
	}
}

int	free_game(t_game *game)
{
	if (!game)
		return (FAILURE);
	if (game->mlx)
		free_mlx(game->mlx);
	if (game->map)
		free_map(game->map);
	if (game->player)
		free_player(game->player);
	free_texinfo(game->textures);
	free_tab((void *)game->content);
	return (SUCCESS);
}
